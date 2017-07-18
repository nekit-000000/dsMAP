/* START OF "dsmap.h" FILE */

#ifndef _DSMAP_H_INCLUDED
#define _DSMAP_H_INCLUDED
#pragma once

#include "mapiterator.h"
#include "pair.h"

template <typename KeyType, typename ValueType>
class dsMAP : private RBTREE<PAIR<KeyType, ValueType>>
{ // map is an ordered red-black tree of {key, value} values, unique keys
public:
  typedef PAIR<KeyType, ValueType> elemType;
  typedef MAPITERATOR<elemType> iterator;

  dsMAP (void) {}
  dsMAP (const dsMAP & map) = default;
  ~dsMAP(void) {}

  iterator begin (void);
  iterator end (void);

  ValueType & operator[] (const KeyType &key);

  int size (void);
  bool empty (void);
  void clear (void);
  void erase (const KeyType & key);
  bool count (const KeyType & key);
  iterator find (const KeyType & key);
  PAIR<iterator, bool> insert(const elemType & val);
};

template <typename KeyType, typename ValueType>
typename dsMAP<KeyType, ValueType>::iterator dsMAP<KeyType, ValueType>::end(void)
{
  return iterator(NULL);
}

template <typename KeyType, typename ValueType>
typename dsMAP<KeyType, ValueType>::iterator dsMAP<KeyType, ValueType>::begin (void)
{
  if (root == nil)
    return end();
  return iterator(root);
}

template <typename KeyType, typename ValueType>
ValueType & dsMAP<KeyType, ValueType>::operator[] (const KeyType & key)
{
  iterator it = find(key);
  NODE<elemType> *NODE;

  if (it == end())
  {
    elemType insertPair;
    insertPair.first = key;
    NODE = insertElem(insertPair);
  }
  else
    return it->second;

  return NODE->data.second;
}

template <typename KeyType, typename ValueType>
int dsMAP<KeyType, ValueType>::size (void)
{
  int cnt = 0;
  for (iterator it = begin(); it != end(); ++it)
    cnt++;

  return cnt;
}

template <typename KeyType, typename ValueType>
bool dsMAP<KeyType, ValueType>::empty (void)
{
  return root == nil;
}

template <typename KeyType, typename ValueType>
void dsMAP<KeyType, ValueType>::clear (void)
{
  NODE<elemType> * x = root;
  NODE<elemType> * y = root;

  while (y != nil)
  {
    while (x->left != nil || x->right != nil)
    {
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

  root = nil;
}

template <typename KeyType, typename ValueType>
void dsMAP<KeyType, ValueType>::erase (const KeyType & key)
{
  iterator it = find(key);

  if (it != end())
    deleteElem(*it);
}

template <typename KeyType, typename ValueType>
typename dsMAP<KeyType, ValueType>::iterator dsMAP<KeyType, ValueType>::find (const KeyType & key)
{
  NODE<elemType> * x = root;

  while (x->parent != NULL && x->data.first != key) {
    if (key < x->data.first)
      x = x->left;
    else
      x = x->right;
  }

  if (x->parent == NULL)
    return end();
  return iterator(x);
}

template <typename KeyType, typename ValueType>
PAIR<typename dsMAP<KeyType, ValueType>::iterator, bool> dsMAP<KeyType, ValueType>::insert(const elemType & val)
{
  iterator it = find(val.first);

  if (it == end())
  {
    elemType insertPair;
    insertPair = val;
    insertElem(insertPair);
    return PAIR<iterator, bool>(end(), true);
  }

  return PAIR<iterator, bool>(it, false);
}


template <typename KeyType, typename ValueType>
bool dsMAP<KeyType, ValueType>::count(const KeyType &key)
{
  return find(key) == end() ? false : true;
}

#endif // _DSMAP_H_INCLUDED

/* END OF "dsmap.h" FILE */
