/*
 * LibSylph Class Library
 * Copyright (C) 2009 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LibSylph Pulbic License as published
 * by the LibSylph Developers; either version 1.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LibSylph
 * Public License for more details.
 *
 * You should have received a copy of the LibSylph Public License
 * along with this Library, if not, contact the LibSylph Developers.
 *
 * Created on: 26 november 2008
 */

#ifndef STRING_H_
#define STRING_H_

#include "Object.h"
#include "Comparable.h"
#include "Primitives.h"
#include "Hashable.h"
#include "BoolConvertible.h"
#include "Array.h"

// for convenience
#include "I18N.h"

#include <cstdint>
#include <string>

class QString;

SYLPH_BEGIN_NAMESPACE

//#ifndef SYLPH_DOXYGEN
//#define SYLPH_STRING_CLASS MutableString
//class MutableString;
//typedef const MutableString String;
//#else
#define SYLPH_STRING_CLASS String
//#endif

SYLPH_PUBLIC

typedef std::uint16_t uchar;

static Array<uchar> spacechars = {' ','\n','\r','\f','\t','\013'};

class SYLPH_STRING_CLASS : public Hashable, 
        public BoolConvertible<SYLPH_STRING_CLASS> {
    friend bool operator==(const String lhs, const String rhs);
    friend bool operator<(const String lhs, const String rhs);
    friend String operator+(const String lhs, const String rhs);
    //friend String operator%(const String lhs, const String rhs);
    friend String operator&(const String lhs, const String(*rhs)(const String));
    friend String operator&(const String(*lhs)(String), const String rhs);
    friend String operator*(const String lhs, const std::size_t len);
    friend std::ostream& operator<<(std::ostream& lhs, const String rhs);

public:
    SYLPH_STRING_CLASS();
    SYLPH_STRING_CLASS(const char * orig);
    SYLPH_STRING_CLASS(const Array<char> orig);
    SYLPH_STRING_CLASS(const Array<uchar> orig);
    SYLPH_STRING_CLASS(const std::string & orig);
    SYLPH_STRING_CLASS(const QString & orig);
    SYLPH_STRING_CLASS(const String & orig);
    SYLPH_STRING_CLASS(const char c);
    SYLPH_STRING_CLASS(const bool b);
    SYLPH_STRING_CLASS(const sint i);
    SYLPH_STRING_CLASS(const suint i);
    SYLPH_STRING_CLASS(const slong l);
    SYLPH_STRING_CLASS(const sulong l);
    SYLPH_STRING_CLASS(const float f);
    SYLPH_STRING_CLASS(const double d);
    virtual ~SYLPH_STRING_CLASS();

    std::size_t length() const;
    const uchar at(std::size_t idx) const;
    const char * ascii() const;
    const char * utf8() const;
    const Array<uchar> utf16() const;

    String toLowerCase() const;
    String toUpperCase() const;
    bool equalsIgnoreCase(const String other) const;

    bool endsWith(const String other) const;
    bool startsWith(const String other) const;
    bool contains(const String other) const;

    String trim() const;
    String substring(std::idx_t begin) const;
    String substring(std::idx_t begin, std::idx_t end) const;

    sidx_t indexOf(const String substr, idx_t start = 0) const;
    sidx_t lastIndexOf(const String substr) const;
    sidx_t lastIndexOf(const String substr, idx_t start) const;

    String copy() const;
    bool merge(String other) const;
    int hashCode() const;

    static String fromHex(int,bool up);
    static String fromOct(int, bool up);
    static String fromSci(float, bool up);
    static String fromSci(double, bool up);

    bool boolValue() const;
    sint intValue() const;
    suint uintValue() const;
    slong longValue() const;
    sulong ulongValue() const;
    float floatValue() const;
    double doubleValue() const;

    inline bool toBool() const {
        return *this != "";
    }
    
    const String& operator=(const char * orig) const;
    const String& operator=(const std::string & orig) const;
    const String& operator=(const String orig) const;

    const String& operator+=(const String rhs) const;

    operator const char *() const;
    operator std::string() const;

//private:
    void fromAscii(const char* ascii) const;
    void fromUtf8(const char* unicode) const;
    struct Data {
        Data(size_t len) : data(len),refcount(1) {}
        virtual ~Data() {}
        Array<uchar> data;
        mutable std::size_t refcount;
    };
    mutable Data * strdata;

};

bool operator==(const String lhs, const String rhs);
inline bool operator==(const String lhs, const char* rhs) {
    return operator==(lhs,String(rhs));
}
inline bool operator==(const char* rhs, const String lhs) {
    return operator==(String(rhs),lhs);
}
bool operator<(const String lhs, const String rhs);
String operator+(const String lhs, const String rhs);
//String operator%(const String lhs, const String rhs);
String operator&(const String lhs, String(*rhs)(const String));
String operator&(String(*lhs)(const String), const String rhs);
String operator*(const String lhs, const std::size_t len);
std::ostream& operator<<(std::ostream& lhs, const String rhs);

String lc(const String rhs);
String uc(const String rhs);
String t(const String rhs);

SYLPH_END_NAMESPACE

#endif /* STRING_H_ */
