/* START OF "dsmap.hpp" FILE */

#pragma once
#ifndef _DSMAP_HPP
#define _DSMAP_HPP

#include <stack>


template <typename KEY_TYPE, typename VALUE_TYPE>
dsMAP<KEY_TYPE, VALUE_TYPE>::dsMAP (const dsMAP<KEY_TYPE, VALUE_TYPE> & map)
{
   NODE<ELEM_TYPE> * node;
   NODE<ELEM_TYPE> * mapNode = map.root;
   std::stack<NODE<ELEM_TYPE> *> mapBuff;
   std::stack<NODE<ELEM_TYPE> *> buff;

   node = new NODE<ELEM_TYPE>;
   node->parent = nil;
   node->data = mapNode->data;
   node->color = mapNode->color;
   root = node;

   while ((mapBuff.size() != 0) || mapNode != nil) {
      if (mapNode != nil) {
         if (mapNode->left == nil) {
            node->left = nil;
         } else {
            node->left = new NODE<ELEM_TYPE>;
            node->left->data = mapNode->left->data;
            node->left->color = mapNode->left->color;
            node->left->parent = node;
         }

         if (mapNode->right == nil) {
            node->right = nil;
         } else {
            node->right = new NODE<ELEM_TYPE>;
            node->right->data = mapNode->right->data;
            node->right->color = mapNode->right->color;
            node->right->parent = node;
         }

         if (mapNode->right != nil) {
            mapBuff.push(mapNode->right);
            buff.push(node->right);
         }

         mapNode = mapNode->left;
         node = node->left;
      } else {
         mapNode = mapBuff.top();
         mapBuff.pop();

         node = buff.top();
         buff.pop();
      }
   }
}

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
   NODE<ELEM_TYPE> * node;
   
   if (it == End()) {
      ELEM_TYPE insertPair;
      insertPair.first = key;
      node = InsertElem(insertPair);
   } else {
      return it->second;
   }
   
   return node->data.second;
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
      DeleteElem((*it).data);
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
