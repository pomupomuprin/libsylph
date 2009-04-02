/*
 * File:   Object.h
 * Author: SeySayux <seysayux@gmail.com>
 *
 * Created on 4 november 2008, 18:48
 */

#ifndef OBJECT_H_
#define	OBJECT_H_

#ifdef SYLPH_PUBLIC
#undef SYLPH_PUBLIC
#endif /* SYLPH_PUBLIC */
#define SYLPH_PUBLIC

#define SYLPH_BEGIN_NAMESPACE namespace Sylph {
#define SYLPH_END_NAMESPACE }

#include <cstddef>

/**
 * \namespace Sylph
 * The Sylph namespace contains everything in LibSylph.
 */


SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

/**
 * Used for LibSylph's garbage collection. It is passed as a parameter to new,
 * e.g.
 * <pre>
 * Array<int>; = new (NoGC) Array<int>(5); // create a length-5 array without GC
 * </pre>
 * This is most often used for creating LibSylph-objects not managed by the
 * garbage collector.
 */
enum GCPlacement {
    UseGC, /**< Use the garbage collector; this is the default */
    NoGC, /**< Do not use the garbage collector for this specific object */
    PointerFreeGC /**< When the object you create does not contain pointers,
                   * use this to speed up GC -- however, this is usually not
                   * useful, as most LibSylph containers contain pointers. */
};

/**
 * The root of all classes. This class contains the overloaded new and delete
 * operators. All classes in LibSylph extend from this class. If you want your
 * class to communicate with LibSylph, or just if you want to let LibSylph's
 * garbage collector manage dynamic allocation of your class, you should derive
 * from Object.
 */
class Object {
#ifndef SYLPH_DOXYGEN
public:
    inline Object();
    inline virtual ~Object();
    inline void* operator new( size_t size);
    inline void* operator new( size_t size, GCPlacement gcp);
    inline void* operator new( size_t size, void *p);
    inline void operator delete( void* obj);
    inline void operator delete( void*, GCPlacement);
    inline void operator delete( void*, void*);

    // Arrays from Object are *never* gc'ed, and I recommend using Sylph::Array
    // instead. Maybe we should document this somewhere?
    inline void* operator new[](size_t size);
    inline void* operator new[](size_t size, void *p);
    inline void operator delete[](void* obj);
    inline void operator delete[](void*, void*);

private:
    inline static void cleanup(void* obj, void* clientData);
#endif
};

SYLPH_END_NAMESPACE

#endif	/* OBJECT_H_ */

