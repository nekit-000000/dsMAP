/* START OF "dsrbtree.h" FILE */

#pragma once
#ifndef _DSRBTREE_H
#define _DSRBTREE_H

#include "mapiterator.h"


template <typename VALUE_TYPE>
class dsRB_TREE {
public:
   typedef NODE_COLOR COLOR;
   typedef typename MAP_ITERATOR<VALUE_TYPE>::NODE NODE;
   typedef typename MAP_ITERATOR<const VALUE_TYPE>::NODE CONST_NODE;
   typedef MAP_ITERATOR<VALUE_TYPE> ITERATOR;
   typedef MAP_ITERATOR<const VALUE_TYPE> CONST_ITERATOR;

   dsRB_TREE (void);
   dsRB_TREE (const VALUE_TYPE & data);

   ~dsRB_TREE (void);

   ITERATOR Begin (void);
   ITERATOR End   (void);

   CONST_ITERATOR Begin (void) const;
   CONST_ITERATOR End   (void) const;

   std::pair<ITERATOR, bool> Insert (const VALUE_TYPE & val);
   void Delete                      (ITERATOR & it);
   void Delete                      (const VALUE_TYPE & data);
   ITERATOR Find                    (const VALUE_TYPE & data);

private:
   void RotateLeft     (NODE * x);
   void RotateRight    (NODE * y);
   void InsertFixup    (NODE * z);
   void DeleteFixup    (NODE * x);
   void Transplant     (NODE * u, NODE * v);
   NODE * FindMin      (NODE * x);
   ITERATOR InsertElem (const VALUE_TYPE & data);

protected:
   NODE * root;
   static NODE leaf;
   static NODE * nil;
};

template <typename VALUE_TYPE>
typename MAP_ITERATOR<VALUE_TYPE>::NODE dsRB_TREE<VALUE_TYPE>::leaf = NODE(NODE_COLOR::BLACK, NULL, &leaf, &leaf);

template <typename VALUE_TYPE>
typename MAP_ITERATOR<VALUE_TYPE>::NODE * dsRB_TREE<VALUE_TYPE>::nil = &dsRB_TREE<VALUE_TYPE>::leaf;


#include "dsrbtree.hpp"

#endif // _DSRBTREE_H

/* END OF "dsrbtree.h" FILE */
