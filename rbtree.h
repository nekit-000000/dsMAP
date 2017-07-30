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
   NODE (void);
   NODE (const NODE & n);
   NODE (NODE_COLOR color, NODE * parent, NODE * left, NODE * right);
   NODE (NODE_COLOR color, VALUE_TYPE data, NODE * parent, NODE * left, NODE * right);
   
   ~NODE (void) {}
   
   NODE_COLOR color;
   VALUE_TYPE data;
   NODE * parent;
   NODE * left;
   NODE * right;
};


template <typename VALUE_TYPE>
class RBTREE {
public:
   typedef NODE<VALUE_TYPE> VERTEX;
   typedef NODE_COLOR COLOR;

   RBTREE (void);
   RBTREE (const VALUE_TYPE & data);

   ~RBTREE (void);

   VERTEX * InsertElem (const VALUE_TYPE & data);
   void DeleteElem     (const VALUE_TYPE & data);
   COLOR ElemColor     (const VALUE_TYPE & data);
   VALUE_TYPE RootData (void) { return root->data; }

protected:
   void RotateLeft   (VERTEX * x);
   void RotateRight  (VERTEX * y);
   void InsertFixup  (VERTEX * z);
   void DeleteFixup  (VERTEX * x);
   void Transplant   (VERTEX * u, VERTEX * v);
   VERTEX * FindNode (const VALUE_TYPE & data);
   VERTEX * FindMin  (VERTEX * x);

   VERTEX * root;
   static VERTEX leaf;
   static VERTEX * nil;
};


template <typename VALUE_TYPE>
NODE<VALUE_TYPE> RBTREE<VALUE_TYPE>::leaf = VERTEX(NODE_COLOR::BLACK, NULL, &leaf, &leaf);

template <typename VALUE_TYPE>
NODE<VALUE_TYPE> * RBTREE<VALUE_TYPE>::nil = &RBTREE<VALUE_TYPE>::leaf;


#include "rbtree.hpp"

#endif // _RBTREE_H

/* END OF "rbtree.h" FILE */
