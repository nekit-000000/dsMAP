/* START OF "mapiterator.h" FILE */

#ifndef _MAPITERATOR_H_INCLUDED
#define _MAPITERATOR_H_INCLUDED
#pragma once

#include <stack>
#include "rbtree.h"

template <typename ValueType>
class MAPITERATOR
{
public:
  MAPITERATOR (void);
  MAPITERATOR (const MAPITERATOR & it);
  MAPITERATOR (NODE<ValueType> * p);

  ~MAPITERATOR() {}

  ValueType operator* (void) const;
  ValueType * operator-> (void) const;
  bool operator!= (MAPITERATOR const & it) const;
  bool operator== (MAPITERATOR const & it) const;
  MAPITERATOR & operator++ (void);
  MAPITERATOR & operator++ (int i);

private:
  NODE<ValueType> * p;
  std::stack<NODE<ValueType> *> buff;
};

template <typename ValueType>
MAPITERATOR<ValueType>::MAPITERATOR (NODE<ValueType> * p) : p(p)
{
}

template <typename ValueType>
MAPITERATOR<ValueType>::MAPITERATOR (void) :
  p(NULL)
{
}

template <typename ValueType>
MAPITERATOR<ValueType>::MAPITERATOR (const MAPITERATOR & it) :
  p(it.p)
{
}

template <typename ValueType>
ValueType MAPITERATOR<ValueType>::operator* (void) const
{
  return p->data;
}

template <typename ValueType>
ValueType * MAPITERATOR<ValueType>::operator-> (void) const
{
  return &p->data;
}

template <typename ValueType>
bool MAPITERATOR<ValueType>::operator!= (MAPITERATOR const & it) const
{
  return p != it.p;
}

template <typename ValueType>
bool MAPITERATOR<ValueType>::operator== (MAPITERATOR const & it) const
{
  return p == it.p;
}

template <typename ValueType>
MAPITERATOR<ValueType> & MAPITERATOR<ValueType>::operator++ (void)
{
  if (p->parent != NULL || (buff.size() != 0)) {
    if (p->parent != NULL) {
      if (p->right->parent != NULL)
        buff.push(p->right);

        p = p->left;
    }
    else {
      p = buff.top();
      buff.pop();
    }
  }
  else
    p = NULL;

  // skipping leaves
  if (p != NULL && p->parent == NULL && buff.size() != 0) {
    p = buff.top();
    buff.pop();
  }
  else if (p != NULL && buff.size() == 0 && p->parent == NULL)
    p = NULL;

  return *this;
}

template <typename ValueType>
MAPITERATOR<ValueType> & MAPITERATOR<ValueType>::operator++ (int i)
{
  MAPITERATOR<ValueType> *it = this;
  ++(*this);
  return *it;
}

#endif // _MAPITERATOR_H_INCLUDED

/* END OF "mapiterator.h" FILE */
