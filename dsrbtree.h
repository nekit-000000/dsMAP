/* START OF "dsrbtree.h" FILE */

#pragma once
#ifndef _DSRBTREE_H
#define _DSRBTREE_H

#include "rbtreeiterator.h"


enum class NODE_COLOR {
   BLACK,
   RED
};


template <typename VALUE_TYPE>
class dsRB_TREE {
public:
   struct NODE { // element of a red-black tree
   public:
      NODE (void);
      NODE (const NODE & n);
      NODE (NODE_COLOR color, NODE * parent, NODE * left, NODE * right);
      NODE (NODE_COLOR color, VALUE_TYPE data, NODE * parent, NODE * left, NODE * right);

      ~NODE (void) {}

   public:
      NODE_COLOR color;
      VALUE_TYPE data;
      NODE * parent;
      NODE * left;
      NODE * right;
   };

public:
   typedef NODE_COLOR COLOR;
   typedef RB_TREE_ITERATOR<VALUE_TYPE> ITERATOR;
   typedef RB_TREE_ITERATOR<const VALUE_TYPE> CONST_ITERATOR;

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
   int size;
};


template <typename VALUE_TYPE>
typename dsRB_TREE<VALUE_TYPE>::NODE dsRB_TREE<VALUE_TYPE>::leaf = NODE(NODE_COLOR::BLACK, NULL, &leaf, &leaf);

template <typename VALUE_TYPE>
typename dsRB_TREE<VALUE_TYPE>::NODE * dsRB_TREE<VALUE_TYPE>::nil = &dsRB_TREE<VALUE_TYPE>::leaf;


#include "dsrbtree.hpp"

#endif // _DSRBTREE_H

/* END OF "dsrbtree.h" FILE */
