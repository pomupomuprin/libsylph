/* 
 * File:   Array.h
 * Author: frank
 *
 * Created on 8 februari 2009, 14:18
 */

#ifndef ARRAY_H_
#define	ARRAY_H_

#include "Iterable.h"
#include "Iterator.h"
#include "Comparable.h"
#include "Exception.h"
#include "Range.h"
#include "Util.h"
#include "Primitives.h"

#include <algorithm>
#include <initializer_list>

SYLPH_BEGIN_NAMESPACE
class Any;

SYLPH_PUBLIC

template<class T>
class Array_base {
    friend class Array<T>;
public:
    class iterator : public RandomAccessIterator<T, Array<T> > {
    public:
        S_RANDOM_ACCESS_ITERATOR(iterator,T, Array<T>)
        void construct(bool begin, Array<T>* obj) {
            _obj = obj;
            _currentIndex = begin ? 0 : _obj->length;
        }
        bool equals(iterator& other) {
            return _currentIndex == other._currentIndex &&
                    _obj == other._obj;
        }
        void copyFrom(iterator& other) {
            _currentIndex = other._currentIndex;
            _obj = other._obj;
        }
        pointer current() {
            return *_obj[_currentIndex];
        }
        bool hasNext() {
            return _obj->length < _currentIndex;
        }
        void next() {
            _currentIndex++;
        }
        bool hasPrevious() {
            return _currentIndex >= 0;
        }
        void previous() {
            currentIndex--;
        }
        idx_t currentIndex() {
            return _currentIndex;
        }
        size_t length() {
            return _obj->length;
        }
    private:
        mutable idx_t _currentIndex;
        Array<T>* _obj;
    };
    S_ITERABLE(T)
public:
    /**
     * A function that is used for filtering by the filter() method. This
     * function takes both an instance of the class this Array contains, and
     * a reference to a reference to any kind of other data that may need to
     * be passed to the FilterFunction.
     */
    typedef bool(*FilterFunction)(const T&, Any&);
    /**
     * The length of the array. This variable is 1-based, while the array itself
     * is 0-based, i.e. if length == N the highest entry in this array is N-1.
     * E.g if array.length == 5, then the higest entry is array[4]
     */
    const int & length;
    /**
     * Creates an Array<T> from a pointer to T and a length. The new array will
     * have the length specified in <code>length</code>. The original array will
     * not be modified, the contents are copied. No bounds-checking
     * is done, therefore, use this function at your own responsability!
     * @param length The length of the original C array
     * @param orig The original C array, supplied as a pointer.
     */
    inline static Array<T> fromPointer(std::size_t length, T * orig) {
        Array<T> ar(length);
        for (int x = 0; x < length; x++)ar[x] = orig[x];
        return ar;
    }
public:

    /**
     * Creates a new array with the given length. A new instance of the
     * reference counted data is created, its refcount set to 1. The memory
     * gets zeroed, so it is perfectly safe to compare with 0 to see
     * if a particular entry in the array has been initialized.
     * @param len the length of the new Array.
     */
    explicit Array_base(std::size_t len) : _length(len), length(_length) {
        data = new Data(len);
        data->_carray = new T[length];
    }

    /**
     * Creates an array from an initializer list. The length is the same as the
     * length of the initializer list. A new instance of the reference counted
     * data is created, its refcount set to 1.
     * @param il the initializer list
     */
    Array_base(const std::initializer_list<T> & il) : _length(il.size()), length(_length) {
        data = new Data(_length);
        data->_carray = (T*) calloc(il.size(), sizeof (T));
        carraycopy(il.begin(), 0, data->_carray, 0, il.size());
    }

    /**
     * Creates an array from a C-style array. The contents of the array are
     * copied into this array. The original array will not be modified. The
     * length is the same as the length of the C array. A new instance of the
     * reference counted data is created, its refcount set to 1.
     * @param array the c-style array
     */
    Array_base(const T array[]) : _length(carraysize(array)), length(_length) {
        data = new Data(_length);
        data->_carray = (T*) calloc(_length, sizeof (T));
        carraycopy(array, 0, data->_carray, 0, _length);
    }

    /**
     * Copy constructor. As Array is reference-counted, it will just copy the
     * pointer to the internal reference and increase the counter by 1.
     * @param other A reference to the other Array.
     */
    Array_base(const Array_base<T> & other) : _length(other._length) {
        if (this == &other) return;
        this->data = other.data;
        this->_length = other.data->_length;
        data->refcount++;
    }
   /**
     * Creates an array from a range. The following syntax
     * <pre> Array<int>(range(X, Y)); </pre>
     * is just shorthand for
     * <pre>Array<int>(Y-X) arr;
     * for(int i = X; i < Y; i++) arr[i]=X+i;</pre>
     * A new shared data pointer gets created. Length is equal to ran.last() -
     * ran.first() . In order for this constructor to be useful, operator< and
     * operator++ need to have meaningful implementations.
     * @param ran The range describing the contents of the array.
     */
    Array_base(const basic_range<T> & ran) : _length(ran.last() - ran.first()),
            length(_length) {
        data = new Data(_length);
        data->_carray = (T*) calloc(_length, sizeof (T));
        idx_t idx = 0;
        for (T x = ran.first(); x < ran.last(); x++) {
            *this[idx] = x; idx++;
        }
    }

    /**
     * Destructor. This will decrease the reference counter by one. If the
     * counter reaches zero, the backing data will be deleted.
     */
    virtual ~Array_base() {
        data->refcount--;
        if (!data->refcount) delete data;
    }

    /**
     * Returns a c-style array representing the contents of this Array. The
     * array returned is not a copy of this array, in fact, changes to the
     * returned array are reflected in this Array.
     */
    T * carray() {
        return data->_carray;
    }

    /**
     * Returns a c-style array representing the contents of this Array. The
     * array returned is not a copy of this array, in fact, changes to the
     * returned array are reflected in this Array. This version returns a const
     * c-style array and is used when this Array is const.
     */
    const T *carray() const {
        return data->_carray;
    }

    /**
     * Creates a copy of this array. The Array returned from this method is
     * an exact copy of this Array, such that ar == ar.copy() . The returned
     * Array is different from the one returned by operator=, as the reference
     * counted data gets copied as well, in other words, both Arrays will
     * track their own reference count from now.
     * @return A new Array containing the same data as this Array.
     */
    Array_base<T> copy() {
        Array_base<T> toReturn(length);
        arraycopy(*this,0,toReturn,0,length);
        return toReturn;
    }

    /**
     * This will filter the Array according to a FilterFunction. This function
     * returns a new, 'filtered' Array, which only contains the entries for
     * which the FilterFunction returns true.
     * @param func A pointer to the function which is used for filtering
     * @param clientData %Any data to be passed to the FilterFunction
     * @return A new array containing only the filtered data
     */
    Array_base<T> filter(FilterFunction func, Any& clientData) {
        // I'm terribly sorry but we'll need to iterate twice over the Array...
        size_t newlength;
        for(idx_t i = 0; i < length; i++) {
            if(func(*this[i],clientData)) newlength++;
        }
        Array<T> toReturn(newlength);
        idx_t curpos = 0;
        for(idx_t i = 0; i < length; i++) {
            if(func(*this[i],clientData)) {
                toReturn[curpos] = *this[i];
                curpos++;
            }
        }
        return toReturn;
    }

    /**
     * Swaps the data pointer of this Array with the other Array. The refcount
     * for the current data pointer gets decreased, the refcount for the data
     * pointer of the other array gets increased. In case the this Array's
     * original data pointer's refcount reaches zero, the original data is
     * deleted.
     * @param other The other array from which to use the data pointer
     */
    Array_base<T> & operator=(const Array_base<T> & other) {
        if (this->data == other.data) return;
        this->data->refcount--;
        if (!this->data->refcount) delete this->data;
        this->data = other.data;
        this->_length = other.data->_length;
        data->refcount++;
        return *this;
    }

    /**
     * Used for accessing the Array's contents. Its behaviour is identical to
     * that of c-style arrays, but throws an exception instead of overflowing
     * or causing segfaults.
     * @param idx the index in the array from which to return an element
     * @throw ArrayException if <code>idx > length</code>
     */
    T & operator[](std::sidx_t idx) throw (Exception) {
        if (abs(idx) < length) {
            return idx > 0 ? data->_carray[idx] : data->_carray(length + idx);
        } else {
            sthrow(ArrayException, "Array overflow");
        }
    }

    /**
     * This is the <code>const</code> version of T& operator[] . Its behaviour
     * is identical to that of c-style const arrays, but throws an exception
     * instead of overflowing or causing segfaults.
     * @param idx the index in the array from which to return an element
     * @throw ArrayException if <code>idx > length</code>
     */
    const T & operator[](std::sidx_t idx) const throw (Exception) {
        if (abs(idx) < length) {
            return idx > 0 ? data->_carray[idx] : data->_carray(length + idx);
        } else {
            sthrow(ArrayException, "Array overflow");
        }
    }

    /**
     * Slices the array and returns the subarray. E.g. :
     * <pre>Array<String> subarr = myarr[range(5,8)]</pre>
     * <code>subarr</code> now contains the values of @c myarr[5] to @c myarr[8]
     * . Please note that the subarray contains a copy of the original.
     * @param ran The range describing the slice.
     * @throw ArrayException if ran.last() > length
     */
    Array_base<T> operator[](const range & ran) throw (Exception) {
        if (ran.first() < 0 || ran.last() > length)
            sthrow(ArrayException, "Array overflow");

        Array_base<T> toReturn = Array_base<T>::fromPointer(ran.last() - ran.first(),
                data->_carray + ran.first());
        return toReturn;
    }

    /**
     * Const-version of operator[](const range &) .
     * @param ran The range describing the slice
     * @throw ArrayException if ran.last() > length
     */
    const Array_base<T> operator[](const range & ran) const throw (Exception) {
        if (ran.first() < 0 || ran.last() > length)
            sthrow(ArrayException, "Array overflow");

        Array_base<T> toReturn = Array_base<T>::fromPointer(ran.last() - ran.first(),
                data->_carray + ran.first());
        return toReturn;
    }

#ifndef SYLPH_DOXYGEN
protected:

    struct Data {
        explicit Data(size_t length) : Data::_length(length), refcount(1) {

        }

        virtual ~Data() {
            delete _carray;
        }
        const int _length;
        T * _carray;
        suint refcount;
    } * data;
    int _length;
#endif
};

/**
 * Array provides a safe array. It works the same like a c-style array (not like
 * std::vector which can expand), but instead of overflowing, it throws an
 * @c Exception whenever you try to access data outside its bounds. Therefore it
 * also keeps track of its own length.
 */
template <class T>
class Array : public Array_base<T> {

    explicit Array(std::size_t len) : Array_base<T>(len) {}
    Array(const std::initializer_list<T> & il) : Array_base<T>(il) {}

    Array(const T array[]) : Array_base<T>(array){
    }
    Array(const Array<T> & other) : Array_base<T>(other) {
    }
    Array(const basic_range<T> & ran) : Array_base<T>(ran) {
    }
    virtual ~Array() {}
};

template <class T>
class Array<T*> : public Array_base<T> {
    explicit Array<T*>(std::size_t len) : Array_base<T>(len) {}
    Array<T*>(const std::initializer_list<T> & il) : Array_base<T*>(il) {}

    Array<T*>(const T array[]) : Array_base<T*>(array){
    }
    Array<T*>(const Array<T> & other) : Array_base<T*>(other) {
    }
    Array<T*>(const basic_range<T> & ran) : Array_base<T*>(ran) {
    }
    virtual ~Array<T*>() {
        for(idx_t i = 0; i < length; i++) {
            delete *this[i];
        }
    }
};

S_CREATE_SYLPH_ITERATOR(Array)

/**
 * Compares the two Arrays on equality. To Arrays compare equal when their
 * lengths are identical and each of the items compare equal to the item on the
 * same position in the other array.
 * @return <i>true</i> when the two arrays compare equal, <i>false</i>
 * otherwise.
 */
template<class T>
inline bool operator==(const Array<T>& lhs, const Array<T>& rhs) {
    return lhs.length == rhs.length ?
            std::equal(lhs.carray[0], lhs.carray[lhs.length - 1], rhs[0]) : false;
}

/**
 * Compares the two Arrays. To Arrays compare less than when their lengths are
 * identical and each of the items compare less than to the item on the same
 * position in the other array.
 * @return <i>true</i> when the first array compares less than the first,
 * <i>false</i> otherwise.
 */
template<class T>
inline bool operator<(const Array<T>& lhs, const Array<T>& rhs) {
    return lhs.length == rhs.length ?
            std::lexicographical_compare(lhs.carray[0], lhs.carray[lhs.length - 1],
            rhs[0], rhs[rhs.length - 1]) : false;
}

SYLPH_END_NAMESPACE

#endif	/* ARRAY_H_ */

