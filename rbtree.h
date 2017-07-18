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

  RBTREE (void);
  RBTREE (const ValueType & data);

  ~RBTREE (void);

  vertex * insertElem (const ValueType & data);
  void deleteElem     (const ValueType & data);
  vertex * findNode   (const ValueType & data);
  vertex * findMin    (vertex * x);

protected:
  static typename NODE<ValueType>::nodeColor black;
  static typename NODE<ValueType>::nodeColor red;

  vertex * root;
  static vertex * nil;

  void rotateLeft  (vertex * x);
  void rotateRight (vertex * y);
  void insertFixup (vertex * z);
  void deleteFixup (vertex * x);
  void transplant  (vertex * u, vertex * v);
};

template <typename ValueType>
NODE<ValueType> * RBTREE<ValueType>::nil = new vertex(black, NULL, nil, nil);

template <typename ValueType>
typename NODE<ValueType>::nodeColor RBTREE<ValueType>::black = NODE<ValueType>::BLACK;

template <typename ValueType>
typename NODE<ValueType>::nodeColor RBTREE<ValueType>::red = NODE<ValueType>::RED;

template <typename ValueType>
NODE<ValueType>::NODE (void) : data()
{
}

template <typename ValueType>
NODE<ValueType>::NODE (const NODE & n) : NODE(n)
{
}

template <typename ValueType>
NODE<ValueType>::NODE (nodeColor color, NODE * parent, NODE * left, NODE * right) :
  color(color), parent(parent), left(left), right(right)
{
}

template <typename ValueType>
NODE<ValueType>::NODE (nodeColor color, ValueType data, NODE * parent, NODE * left, NODE * right) :
  color(color), parent(parent), left(left), right(right), data(data)
{
}

template <typename ValueType>
RBTREE<ValueType>::RBTREE (void)
{
  root = nil;
}

template <typename ValueType>
RBTREE<ValueType>::RBTREE (const ValueType & data)
{
  root = new vertex;
  root->parent = nil;
  root->right = nil;
  root->left = nil;
  root->color = black;
  root->data = data;
}

template <typename ValueType>
RBTREE<ValueType>::~RBTREE (void)
{
  vertex * x = root;
  vertex * y = root;

  while (y != nil) {
    while (x->left != nil || x->right != nil) {
      if (x->left == nil)
        x = x->right;
      else
        x = x->left;
    }
    y = x->parent;

    if (x == x->parent->right)
      x->parent->right = nil;
    else
      x->parent->left = nil;

    delete x;
    x = y;
  }

  delete nil;
}

template <typename ValueType>
void RBTREE<ValueType>::rotateLeft (vertex * x)
{
  if (x->right == nil)
    return;

  vertex * y = x->right;

  x->right = y->left;

  if (y->left != nil)
    y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == nil)
    root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;

  y->left = x;
  x->parent = y;
}

template <typename ValueType>
void RBTREE<ValueType>::rotateRight (vertex * y)
{
  if (y->left == nil)
    return;

  vertex * x = y->left;

  y->left = x->right;

  if (x->right != nil)
    x->right->parent = y;
  x->parent = y->parent;
  if (y->parent == nil)
    root = x;
  else if (y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;

  x->right = y;
  y->parent = x;
}

template <typename ValueType>
void RBTREE<ValueType>::insertFixup (vertex * z)
{
  vertex * y;

  while (z->parent->color == red && z->parent->parent != nil)
    if (z->parent == z->parent->parent->left) {
      y = z->parent->parent->right;

      if (y->color == red) {
        z->parent->color = black;
        y->color = black;
        z->parent->parent->color = red;
        z = z->parent->parent;
      } else if (z == z->parent->right) {
          z = z->parent;
          rotateLeft(z);
      } else {
          z->parent->color = black;
          z->parent->parent->color = red;
          rotateRight(z->parent->parent);
      }
    } else {
        y = z->parent->parent->left;

        if (y->color == red) {
          z->parent->color = black;
          y->color = black;
          z->parent->parent->color = red;
          z = z->parent->parent;
        } else if (z == z->parent->left) {
            z = z->parent;
            rotateRight(z);
        } else {
            z->parent->color = black;
            z->parent->parent->color = red;
            rotateLeft(z->parent->parent);
        }
    }

  root->color = black;
}

template <typename ValueType>
NODE<ValueType> * RBTREE<ValueType>::insertElem (const ValueType & data)
{
  vertex * z = new vertex(red, data, NULL, nil, nil);
  vertex * y = nil;
  vertex * x = root;

  while (x != nil) {
    y = x;
    if (z->data < x->data)
      x = x->left;
    else
      x = x->right;
  }

  z->parent = y;
  if (y == nil)
    root = z;
  else if (z->data < y->data)
    y->left = z;
  else
    y->right = z;

  insertFixup(z);
  return z;
}

template <typename ValueType>
void RBTREE<ValueType>::transplant (vertex * u, vertex * v)
{
  if (u->parent == nil)
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;

  v->parent = u->parent;
}

template <typename ValueType>
NODE<ValueType> *RBTREE<ValueType>::findNode (const ValueType & data)
{
  vertex *x = root;

  while (x != nil && x->data != data) {
    if (data > x->data)
      x = x->right;
    else
      x = x->left;
  }

  return x;
}

template <typename ValueType>
NODE<ValueType> *RBTREE<ValueType>::findMin (vertex * x)
{
  vertex * y = x;

  while (y->left != nil)
    y = y->left;

  return y;
}


template <typename ValueType>
void RBTREE<ValueType>::deleteFixup (vertex * x)
{
  vertex * w;

  while (x != root && x->color == black) {
    if (x == x->parent->left) {
      w = x->parent->right;

      if (w->color == red) {
        w->color = black;
        x->parent->color = red;
        rotateLeft(x->parent);
        w = x->parent->right;
      }
      if (w->left->color == black && w->right->color == black) {
        w->color = red;
        x = x->parent;
      } else if (w->right->color = black) {
          w->left->color = black;
          w->color = red;
          rotateRight(w);
          w = x->parent->right;
      } else {
          w->color = x->parent->color;
          x->parent->color = black;
          w->right->color = black;
          rotateLeft(x->parent);
          x = root;
      }
    } else {
        w = x->parent->left;

        if (w->color == red) {
          w->color = black;
          x->parent->color = red;
          rotateRight(x->parent);
          w = x->parent->left;
        }
        if (w->left->color == black && w->right->color == black) {
          w->color = red;
          x = x->parent;
        } else if (w->left->color = black) {
            w->right->color = black;
            w->color = red;
            rotateLeft(w);
            w = x->parent->left;
        } else {
            w->color = x->parent->color;
            x->parent->color = black;
            w->left->color = black;
            rotateRight(x->parent);
            x = root;
        }
    }
  }

  x->color = black;
}

template <typename ValueType>
void RBTREE<ValueType>::deleteElem (const ValueType & data)
{
  vertex * z;
  vertex * y;
  vertex * x;

  if ((z = findNode(data)) == nil)
    return;

  y = z;
  typename vertex::nodeColor yOrigColor = y->color;

  if (z->left == nil) {
    x = z->right;
    transplant(z, z->right);
  } else if (z->right == nil) {
      x = z->left;
      transplant(z, z->left);
  } else {
      y = findMin(z->right);
      yOrigColor = y->color;
      x = y->right;

      if (y->parent == z)
        x->parent = y;
      else {
        transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
  }

  delete z;

  if (yOrigColor == black)
    deleteFixup(x);
  nil->parent = NULL;
}

#endif // _RBTREE_H_INCLUDED

/* END OF "rbtree.h" FILE */
