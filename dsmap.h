/* START OF "dsmap.h" FILE */

#pragma once
#ifndef _DSMAP_H
#define _DSMAP_H

#include <iostream>

#include "mapiterator.h"


template <typename KEY_TYPE, typename VALUE_TYPE>
class dsMAP : private RBTREE<std::pair<KEY_TYPE, VALUE_TYPE>> {
   // map is an ordered red-black tree of {key, value} values, unique keys
public:
   typedef std::pair<KEY_TYPE, VALUE_TYPE> ELEM_TYPE;
   typedef MAPITERATOR<ELEM_TYPE> ITERATOR;
   
   dsMAP (void) {}
   dsMAP (const dsMAP & map) = default;

   ~dsMAP (void) {}
   
   ITERATOR Begin (void);
   ITERATOR End   (void);
   
   VALUE_TYPE & operator[] (const KEY_TYPE &key);
   
   int Size                         (void);
   bool Empty                       (void);
   void Clear                       (void);
   void Erase                       (const KEY_TYPE & key);
   bool Count                       (const KEY_TYPE & key);
   ITERATOR Find                    (const KEY_TYPE & key);
   std::pair<ITERATOR, bool> Insert (const ELEM_TYPE & val);
};


#include "dsmap.hpp"

#endif // _DSMAP_H

/* END OF "dsmap.h" FILE */
