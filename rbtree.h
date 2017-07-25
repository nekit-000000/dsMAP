/* START OF "rbtree.h" FILE */

#ifndef _RBTREE_H_INCLUDED
#define _RBTREE_H_INCLUDED
#pragma once

template <typename ValueType>
struct NODE
{ // element of a red-black tree
  typedef enum
  {
    BLACK,
    RED
  } nodeColor;

	nodeColor color;
	ValueType data;
	NODE * parent;
	NODE * left;
	NODE * right;

  NODE (void);
  NODE (const NODE & n);
  NODE (nodeColor color, NODE * parent, NODE * left, NODE * right);
  NODE (nodeColor color, ValueType data, NODE * parent, NODE * left, NODE * right);

  ~NODE() {}
};

template <typename ValueType>
class RBTREE
{
public:
  typedef NODE<ValueType> vertex;
  typedef typename NODE<ValueType>::nodeColor color;

  RBTREE (void);
  RBTREE (const ValueType & data);

  virtual ~RBTREE (void);

  vertex * insertElem (const ValueType & data);
  void deleteElem     (const ValueType & data);
  vertex * findNode   (const ValueType & data);
  vertex * findMin    (vertex * x);
  color elemColor     (const ValueType & data);
  ValueType rootData  (void) { return root->data; }

protected:
  static color black;
  static color red;

  vertex * root;
  static vertex * nil;

  void rotateLeft  (vertex * x);
  void rotateRight (vertex * y);
  void insertFixup (vertex * z);
  void deleteFixup (vertex * x);
  void transplant  (vertex * u, vertex * v);
};

template <typename ValueType>
typename NODE<ValueType>::nodeColor RBTREE<ValueType>::black = NODE<ValueType>::BLACK;

template <typename ValueType>
typename NODE<ValueType>::nodeColor RBTREE<ValueType>::red = NODE<ValueType>::RED;

template <typename ValueType>
NODE<ValueType> * RBTREE<ValueType>::nil = new vertex(black, NULL, nil, nil);

#include "rbtree.hpp"

#endif // _RBTREE_H_INCLUDED

/* END OF "rbtree.h" FILE */
