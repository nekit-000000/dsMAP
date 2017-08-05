/* START OF "rbtree.h" FILE */

#pragma once
#ifndef _RBTREE_H
#define _RBTREE_H

enum class NODE_COLOR {
   BLACK,
   RED
};

template <typename VALUE_TYPE>
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


template <typename VALUE_TYPE>
class dsRB_TREE {
public:
   typedef NODE<VALUE_TYPE> VERTEX;
   typedef NODE_COLOR COLOR;

   dsRB_TREE (void);
   dsRB_TREE (const VALUE_TYPE & data);

   ~dsRB_TREE (void);

   VERTEX * InsertElem (const VALUE_TYPE & data);
   void DeleteElem     (const VALUE_TYPE & data);
   VERTEX * FindNode   (const VALUE_TYPE & data) const;
   VERTEX * FindMin    (VERTEX * x) const;

private:
   void RotateLeft   (VERTEX * x);
   void RotateRight  (VERTEX * y);
   void InsertFixup  (VERTEX * z);
   void DeleteFixup  (VERTEX * x);
   void Transplant   (VERTEX * u, VERTEX * v);

protected:
   VERTEX * root;
   static VERTEX leaf;
   static VERTEX * nil;
};


template <typename VALUE_TYPE>
NODE<VALUE_TYPE> dsRB_TREE<VALUE_TYPE>::leaf = VERTEX(NODE_COLOR::BLACK, NULL, &leaf, &leaf);

template <typename VALUE_TYPE>
NODE<VALUE_TYPE> * dsRB_TREE<VALUE_TYPE>::nil = &dsRB_TREE<VALUE_TYPE>::leaf;


#include "rbtree.hpp"

#endif // _RBTREE_H

/* END OF "rbtree.h" FILE */
