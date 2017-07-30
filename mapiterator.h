/* START OF "mapiterator.h" FILE */

#pragma once
#ifndef _MAPITERATOR_H
#define _MAPITERATOR_H

#include <stack>
 
#include "rbtree.h"


template <typename VALUE_TYPE>
class MAPITERATOR {
public:
   MAPITERATOR (void);
   MAPITERATOR (const MAPITERATOR & it);
   MAPITERATOR (NODE<VALUE_TYPE> * p);

   ~MAPITERATOR() {}

   VALUE_TYPE operator*     (void) const;
   VALUE_TYPE * operator->  (void) const;
   bool operator!=          (MAPITERATOR const & it) const;
   bool operator==          (MAPITERATOR const & it) const;
   MAPITERATOR & operator++ (void);
   MAPITERATOR & operator++ (int i);

private:
   NODE<VALUE_TYPE> * p;
   std::stack<NODE<VALUE_TYPE> *> buff;
};


template <typename VALUE_TYPE>
MAPITERATOR<VALUE_TYPE>::MAPITERATOR (NODE<VALUE_TYPE> * p) : p(p)
{
}

template <typename VALUE_TYPE>
MAPITERATOR<VALUE_TYPE>::MAPITERATOR (void) :
   p(NULL)
{
}

template <typename VALUE_TYPE>
MAPITERATOR<VALUE_TYPE>::MAPITERATOR (const MAPITERATOR & it) :
   p(it.p)
{
}

template <typename VALUE_TYPE>
VALUE_TYPE MAPITERATOR<VALUE_TYPE>::operator* (void) const
{
   return p->data;
}

template <typename VALUE_TYPE>
VALUE_TYPE * MAPITERATOR<VALUE_TYPE>::operator-> (void) const
{
   return &p->data;
}

template <typename VALUE_TYPE>
bool MAPITERATOR<VALUE_TYPE>::operator!= (MAPITERATOR const & it) const
{
   return p != it.p;
}

template <typename VALUE_TYPE>
bool MAPITERATOR<VALUE_TYPE>::operator== (MAPITERATOR const & it) const
{
   return p == it.p;
}

template <typename VALUE_TYPE>
MAPITERATOR<VALUE_TYPE> & MAPITERATOR<VALUE_TYPE>::operator++ (void)
{
   if (p->parent != NULL || (buff.size() != 0)) {
      if (p->parent != NULL) {
         if (p->right->parent != NULL)
            buff.push(p->right);

         p = p->left;
      } else {
         p = buff.top();
         buff.pop();
      }
   } else
      p = NULL;
   
   // skipping leaves
   if (p != NULL && p->parent == NULL && buff.size() != 0) {
      p = buff.top();
      buff.pop();
   } else if (p != NULL && buff.size() == 0 && p->parent == NULL)
      p = NULL;

   return *this;
}

template <typename VALUE_TYPE>
MAPITERATOR<VALUE_TYPE> & MAPITERATOR<VALUE_TYPE>::operator++ (int i)
{
   MAPITERATOR<VALUE_TYPE> * it = this;
   ++(*this);

   return *it;
}

#endif // _MAPITERATOR_H

/* END OF "mapiterator.h" FILE */
