/* START OF "dsrbtree.h" FILE */

#pragma once
#ifndef _DSRBTREE_H
#define _DSRBTREE_H

template <typename VALUE_TYPE>
class MAP_ITERATOR;

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

   dsRB_TREE (void);
   dsRB_TREE (const VALUE_TYPE & data);

   ~dsRB_TREE (void);

   NODE * InsertElem (const VALUE_TYPE & data);
   void DeleteElem   (const VALUE_TYPE & data);
   NODE * FindNode   (const VALUE_TYPE & data) const;
   NODE * FindMin    (NODE * x) const;

private:
   void RotateLeft  (NODE * x);
   void RotateRight (NODE * y);
   void InsertFixup (NODE * z);
   void DeleteFixup (NODE * x);
   void Transplant  (NODE * u, NODE * v);

protected:
   NODE * root;
   static NODE leaf;
   static NODE * nil;
};


template <typename VALUE_TYPE>
typename dsRB_TREE<VALUE_TYPE>::NODE dsRB_TREE<VALUE_TYPE>::leaf = NODE(NODE_COLOR::BLACK, NULL, &leaf, &leaf);

template <typename VALUE_TYPE>
typename dsRB_TREE<VALUE_TYPE>::NODE * dsRB_TREE<VALUE_TYPE>::nil = &dsRB_TREE<VALUE_TYPE>::leaf;


#include "dsrbtree.hpp"

#endif // _DSRBTREE_H

/* END OF "dsrbtree.h" FILE */
