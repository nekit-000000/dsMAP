/* START OF "dsmap.hpp" FILE */

#pragma once
#ifndef _DSMAP_HPP
#define _DSMAP_HPP

#include <stack>


template <typename KEY_TYPE, typename VALUE_TYPE>
dsMAP<KEY_TYPE, VALUE_TYPE>::dsMAP(dsMAP && map) : dsRB_TREE<ELEM_TYPE>(std::move(map))
{
}


template <typename KEY_TYPE, typename VALUE_TYPE>
dsMAP<KEY_TYPE, VALUE_TYPE>::dsMAP(const dsMAP & map) : dsRB_TREE<ELEM_TYPE>(map)
{
}


template <typename KEY_TYPE, typename VALUE_TYPE>
dsMAP<KEY_TYPE, VALUE_TYPE> & dsMAP<KEY_TYPE, VALUE_TYPE>::operator= (const dsMAP & map)
{
   dsRB_TREE<ELEM_TYPE>::operator= (map);
   return *this;
}


template <typename KEY_TYPE, typename VALUE_TYPE>
dsMAP<KEY_TYPE, VALUE_TYPE> & dsMAP<KEY_TYPE, VALUE_TYPE>::operator= (dsMAP && map)
{
   dsRB_TREE<ELEM_TYPE>::operator= (std::move(map));
   return *this;
}


template <typename KEY_TYPE, typename VALUE_TYPE>
VALUE_TYPE & dsMAP<KEY_TYPE, VALUE_TYPE>::operator[] (const KEY_TYPE & key)
{
   ITERATOR it = Find(key);
   
   if (it == End()) {
      ELEM_TYPE insertPair;
      insertPair.first = key;
      it = Insert(insertPair).first;
   }

   return it->second;
}


template <typename KEY_TYPE, typename VALUE_TYPE>
int dsMAP<KEY_TYPE, VALUE_TYPE>::Size (void) const
{
   return size;
}


template <typename KEY_TYPE, typename VALUE_TYPE>
bool dsMAP<KEY_TYPE, VALUE_TYPE>::Empty (void) const
{
   return root == nil;
}


template <typename KEY_TYPE, typename VALUE_TYPE>
void dsMAP<KEY_TYPE, VALUE_TYPE>::Clear (void)
{
   NODE * x = root;
   NODE * y = root;
   
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
   size = 0;
}


template <typename KEY_TYPE, typename VALUE_TYPE>
void dsMAP<KEY_TYPE, VALUE_TYPE>::Erase (const KEY_TYPE & key)
{
   ITERATOR it = Find(key);
   
   if (it != End()) {
      Delete(it);
   }
}


template <typename KEY_TYPE, typename VALUE_TYPE>
typename dsMAP<KEY_TYPE, VALUE_TYPE>::ITERATOR dsMAP<KEY_TYPE, VALUE_TYPE>::Find (const KEY_TYPE & key)
{
   NODE * x = root;
   ITERATOR it;

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
typename dsMAP<KEY_TYPE, VALUE_TYPE>::CONST_ITERATOR dsMAP<KEY_TYPE, VALUE_TYPE>::Find (const KEY_TYPE & key) const
{
   const NODE * x = root;
   CONST_ITERATOR it;

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
   return CONST_ITERATOR(x);
}


template <typename KEY_TYPE, typename VALUE_TYPE>
int dsMAP<KEY_TYPE, VALUE_TYPE>::Count (const KEY_TYPE & key)
{
   return Find(key) == End() ? 0 : 1;
}


#endif // _DSMAP_HPP

/* END OF "dsmap.hpp" FILE */
