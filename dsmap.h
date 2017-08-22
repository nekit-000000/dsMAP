/* START OF "dsmap.h" FILE */

#pragma once
#ifndef _DSMAP_H
#define _DSMAP_H

#include "dsrbtree.h"


template <typename KEY_TYPE, typename VALUE_TYPE>
class dsMAP : public dsRB_TREE<std::pair<KEY_TYPE, VALUE_TYPE>> {
   // map is an ordered red-black tree of {key, value} values, unique keys
public:
   typedef std::pair<KEY_TYPE, VALUE_TYPE> ELEM_TYPE;
   typedef typename MAP_ITERATOR<ELEM_TYPE>::NODE NODE;
   typedef MAP_ITERATOR<ELEM_TYPE> ITERATOR;
   typedef MAP_ITERATOR<const ELEM_TYPE> CONST_ITERATOR;
   
   dsMAP (void) {}
   dsMAP (const dsMAP & map);

   ~dsMAP (void) {}

   VALUE_TYPE & operator[] (const KEY_TYPE &key);
   
   int Size      (void) const;
   bool Empty    (void) const;
   void Clear    (void);
   void Erase    (const KEY_TYPE & key);
   int Count     (const KEY_TYPE & key);
   ITERATOR Find (const KEY_TYPE & key);
};


#include "dsmap.hpp"

#endif // _DSMAP_H

/* END OF "dsmap.h" FILE */
