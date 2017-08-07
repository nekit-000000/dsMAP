/* START OF "dsmap.h" FILE */

#pragma once
#ifndef _DSMAP_H
#define _DSMAP_H

#include <iostream>

#include "mapiterator.h"


template <typename KEY_TYPE, typename VALUE_TYPE>
class dsMAP : private dsRB_TREE<std::pair<KEY_TYPE, VALUE_TYPE>> {
   // map is an ordered red-black tree of {key, value} values, unique keys
public:
   typedef std::pair<KEY_TYPE, VALUE_TYPE> ELEM_TYPE;
   typedef typename dsRB_TREE<ELEM_TYPE>::NODE NODE;
   typedef MAP_ITERATOR<ELEM_TYPE> ITERATOR;
   
   dsMAP (void) {}
   dsMAP (const dsMAP & map);

   ~dsMAP (void) {}
   
   ITERATOR Begin (void) const;
   ITERATOR End   (void) const;
   
   VALUE_TYPE & operator[] (const KEY_TYPE &key);
   
   int Size                         (void) const;
   bool Empty                       (void) const;
   void Clear                       (void);
   void Erase                       (const KEY_TYPE & key);
   bool Count                       (const KEY_TYPE & key) const;
   ITERATOR Find                    (const KEY_TYPE & key) const;
   std::pair<ITERATOR, bool> Insert (const ELEM_TYPE & val);
};


#include "dsmap.hpp"

#endif // _DSMAP_H

/* END OF "dsmap.h" FILE */
