/* START OF "dsmap.hpp" FILE */

#pragma once
#ifndef _DSMAP_HPP
#define _DSMAP_HPP

template <typename KEY_TYPE, typename VALUE_TYPE>
typename dsMAP<KEY_TYPE, VALUE_TYPE>::ITERATOR dsMAP<KEY_TYPE, VALUE_TYPE>::End (void) const
{
   return ITERATOR(NULL);
}

template <typename KEY_TYPE, typename VALUE_TYPE>
typename dsMAP<KEY_TYPE, VALUE_TYPE>::ITERATOR dsMAP<KEY_TYPE, VALUE_TYPE>::Begin (void) const
{
   if (root == nil) {
      return End();
   }
   return ITERATOR(root);
}

template <typename KEY_TYPE, typename VALUE_TYPE>
VALUE_TYPE & dsMAP<KEY_TYPE, VALUE_TYPE>::operator[] (const KEY_TYPE & key)
{
   ITERATOR it = Find(key);
   NODE<ELEM_TYPE> *NODE;
   
   if (it == End()) {
      ELEM_TYPE insertPair;
      insertPair.first = key;
      NODE = InsertElem(insertPair);
   } else {
      return it->second;
   }
   
   return NODE->data.second;
}

template <typename KEY_TYPE, typename VALUE_TYPE>
int dsMAP<KEY_TYPE, VALUE_TYPE>::Size (void) const
{
   int cnt = 0;
   for (ITERATOR it = Begin(); it != End(); ++it) {
      cnt++;
   }
   
   return cnt;
}

template <typename KEY_TYPE, typename VALUE_TYPE>
bool dsMAP<KEY_TYPE, VALUE_TYPE>::Empty (void) const
{
   return root == nil;
}

template <typename KEY_TYPE, typename VALUE_TYPE>
void dsMAP<KEY_TYPE, VALUE_TYPE>::Clear (void)
{
   NODE<ELEM_TYPE> * x = root;
   NODE<ELEM_TYPE> * y = root;
   
   while (y != nil) {
      while (x->left != nil || x->right != nil) {
         if (x->left == nil) {
            x = x->right;
         } else {
            x = x->left;
         }
      }
      y = x->parent;
      
      if (x == x->parent->right) {
         x->parent->right = nil;
      } else {
         x->parent->left = nil;
      }
      
      delete x;
      x = y;
   }
   
   root = nil;
}

template <typename KEY_TYPE, typename VALUE_TYPE>
void dsMAP<KEY_TYPE, VALUE_TYPE>::Erase (const KEY_TYPE & key)
{
   ITERATOR it = Find(key);
   
   if (it != End()) {
      DeleteElem(*it);
   }
}

template <typename KEY_TYPE, typename VALUE_TYPE>
typename dsMAP<KEY_TYPE, VALUE_TYPE>::ITERATOR dsMAP<KEY_TYPE, VALUE_TYPE>::Find (const KEY_TYPE & key) const
{
   NODE<ELEM_TYPE> * x = root;
   
   while (x->parent != NULL && x->data.first != key) {
      if (key < x->data.first) {
         x = x->left;
      } else {
         x = x->right;
      }
   }
   
   if (x->parent == NULL) {
      return End();
   }
   return ITERATOR(x);
}

template <typename KEY_TYPE, typename VALUE_TYPE>
std::pair<typename dsMAP<KEY_TYPE, VALUE_TYPE>::ITERATOR, bool> dsMAP<KEY_TYPE, VALUE_TYPE>::Insert (const ELEM_TYPE & val)
{
   ITERATOR it = Find(val.first);
   
   if (it == End()) {
      ELEM_TYPE insertPair;
      insertPair = val;
      InsertElem(insertPair);
      return std::pair<ITERATOR, bool>(End(), true);
   }
   
   return std::pair<ITERATOR, bool>(it, false);
}

template <typename KEY_TYPE, typename VALUE_TYPE>
bool dsMAP<KEY_TYPE, VALUE_TYPE>::Count (const KEY_TYPE & key) const
{
   return Find(key) == End() ? false : true;
}

#endif // _DSMAP_HPP

/* END OF "dsmap.hpp" FILE */
