/* START OF "dsmap.h" FILE */

#ifndef _DSMAP_H_INCLUDED
#define _DSMAP_H_INCLUDED
#pragma once

#include "mapiterator.h"
#include "pair.h"

template <typename KeyType, typename ValueType>
class dsMAP : private RBTREE<PAIR<KeyType, ValueType>>
{ // map is an ordered red-black tree of {key, value} values, unique keys
  friend class testing::Test;
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

#include "dsmap.hpp"

#endif // _DSMAP_H_INCLUDED

/* END OF "dsmap.h" FILE */
