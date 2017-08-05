/* START OF "mapiterator.h" FILE */

#pragma once
#ifndef _MAPITERATOR_H
#define _MAPITERATOR_H

#include <stack>
 
#include "rbtree.h"


template <typename VALUE_TYPE>
class MAP_ITERATOR {
public:
   MAP_ITERATOR (void);
   MAP_ITERATOR (const MAP_ITERATOR & it);
   MAP_ITERATOR (NODE<VALUE_TYPE> * p);

   ~MAP_ITERATOR (void) {}

   VALUE_TYPE operator*     (void) const;
   VALUE_TYPE * operator->  (void) const;
   bool operator!=          (MAP_ITERATOR const & it) const;
   bool operator==          (MAP_ITERATOR const & it) const;
   MAP_ITERATOR & operator++ (void);
   MAP_ITERATOR & operator++ (int i);

private:
   NODE<VALUE_TYPE> * p;
   std::stack<NODE<VALUE_TYPE> *> buff;
};


template <typename VALUE_TYPE>
MAP_ITERATOR<VALUE_TYPE>::MAP_ITERATOR (NODE<VALUE_TYPE> * p) : p(p)
{
}

template <typename VALUE_TYPE>
MAP_ITERATOR<VALUE_TYPE>::MAP_ITERATOR (void) :
   p(NULL)
{
}

template <typename VALUE_TYPE>
MAP_ITERATOR<VALUE_TYPE>::MAP_ITERATOR (const MAP_ITERATOR & it) :
   p(it.p)
{
}

template <typename VALUE_TYPE>
VALUE_TYPE MAP_ITERATOR<VALUE_TYPE>::operator* (void) const
{
   return p->data;
}

template <typename VALUE_TYPE>
VALUE_TYPE * MAP_ITERATOR<VALUE_TYPE>::operator-> (void) const
{
   return &p->data;
}

template <typename VALUE_TYPE>
bool MAP_ITERATOR<VALUE_TYPE>::operator!= (MAP_ITERATOR const & it) const
{
   return p != it.p;
}

template <typename VALUE_TYPE>
bool MAP_ITERATOR<VALUE_TYPE>::operator== (MAP_ITERATOR const & it) const
{
   return p == it.p;
}

template <typename VALUE_TYPE>
MAP_ITERATOR<VALUE_TYPE> & MAP_ITERATOR<VALUE_TYPE>::operator++ (void)
{
   if (p->parent != NULL || (buff.size() != 0)) {
      if (p->parent != NULL) {
         if (p->right->parent != NULL) {
            buff.push(p->right);
         }

         p = p->left;
      } else {
         p = buff.top();
         buff.pop();
      }
   } else {
      p = NULL;
   }
   
   // skipping leaves
   if (p != NULL && p->parent == NULL && buff.size() != 0) {
      p = buff.top();
      buff.pop();
   } else if (p != NULL && buff.size() == 0 && p->parent == NULL) {
      p = NULL;
   }

   return *this;
}

template <typename VALUE_TYPE>
MAP_ITERATOR<VALUE_TYPE> & MAP_ITERATOR<VALUE_TYPE>::operator++ (int i)
{
   MAP_ITERATOR<VALUE_TYPE> * it = this;
   ++(*this);

   return *it;
}

#endif // _MAPITERATOR_H

/* END OF "mapiterator.h" FILE */
