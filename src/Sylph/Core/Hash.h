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
 * Created on 4 maart 2009, 12:45
 */

#ifndef HASH_H_
#define	HASH_H_

#include "Object.h"
#include "Exception.h"
#include "Primitives.h"
#include "Hashable.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
inline sint hash_internal(const byte * b, std::size_t len) {
   suint hash = 0;
   suint x    = 0;
   suint i    = 0;

   for(i = 0; i < len; b++, i++)
   {
      hash = (hash << 4) + (*b);
      if((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }
      hash &= ~x;
   }

   return hash;
}

template<class T>
inline sint Hash(const T & t) {
    return hash_internal(reinterpret_cast<const byte*>(&t), sizeof(T));
}

template<class T>
inline sint Hash<T*>(const T*& t) {
    return t == NULL ? 0 : Hash(*t);
}

template<>
inline sint Hash<int>(int & i) {
    return i;
}

// 'Hashables' provide their own hasing method, usually it's based on this one
template<>
inline sint Hash<Hashable>(Hashable & h) {
    return h.hashCode();
}

SYLPH_END_NAMESPACE

#endif	/* HASH_H_ */

