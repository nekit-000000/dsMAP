/* START OF "rbtreeiterator.h" FILE */

#pragma once
#ifndef _RBTREEITERATOR_H
#define _RBTREEITERATOR_H


// forward declaration
template <typename VALUE_TYPE>
class dsRB_TREE;

// forward declaration
template <typename VALUE_TYPE>
struct NODE;


template <typename VALUE_TYPE>
class RB_TREE_ITERATOR {
   friend class dsRB_TREE<VALUE_TYPE>;

public:
   typedef typename dsRB_TREE<VALUE_TYPE>::NODE NODE;

   RB_TREE_ITERATOR (void);
   RB_TREE_ITERATOR (const RB_TREE_ITERATOR & it);
   RB_TREE_ITERATOR (NODE * p);
   RB_TREE_ITERATOR (const NODE * p);

   ~RB_TREE_ITERATOR (void) {}

   VALUE_TYPE & operator*        (void) const;
   VALUE_TYPE * operator->       (void) const;
   bool operator!=               (RB_TREE_ITERATOR const & it) const;
   bool operator==               (RB_TREE_ITERATOR const & it) const;
   RB_TREE_ITERATOR & operator++ (void);
   RB_TREE_ITERATOR & operator++ (int i);

private:
   NODE * p;
};


template <typename VALUE_TYPE>
RB_TREE_ITERATOR<VALUE_TYPE>::RB_TREE_ITERATOR (NODE * p) : p(p)
{
}


template <typename VALUE_TYPE>
RB_TREE_ITERATOR<VALUE_TYPE>::RB_TREE_ITERATOR (const NODE * p) : p(p)
{
}


template <typename VALUE_TYPE>
RB_TREE_ITERATOR<VALUE_TYPE>::RB_TREE_ITERATOR (void) : p(NULL)
{
}


template <typename VALUE_TYPE>
RB_TREE_ITERATOR<VALUE_TYPE>::RB_TREE_ITERATOR (const RB_TREE_ITERATOR & it) : p(it.p)
{
}


template <typename VALUE_TYPE>
VALUE_TYPE & RB_TREE_ITERATOR<VALUE_TYPE>::operator* (void) const
{
   return p->data;
}


template <typename VALUE_TYPE>
VALUE_TYPE * RB_TREE_ITERATOR<VALUE_TYPE>::operator-> (void) const
{
   return &p->data;
}


template <typename VALUE_TYPE>
bool RB_TREE_ITERATOR<VALUE_TYPE>::operator!= (RB_TREE_ITERATOR const & it) const
{
   return p != it.p;
}


template <typename VALUE_TYPE>
bool RB_TREE_ITERATOR<VALUE_TYPE>::operator== (RB_TREE_ITERATOR const & it) const
{
   return p == it.p;
}


template <typename VALUE_TYPE>
RB_TREE_ITERATOR<VALUE_TYPE> & RB_TREE_ITERATOR<VALUE_TYPE>::operator++ (void)
{
   if (p->right->parent != NULL) {
      p = p->right;

      while (p->left->parent != NULL) {
         p = p->left;
      }
   } else {
      NODE * pnode;
      while (!((pnode = p->parent)->parent == NULL)
         && p == pnode->right) {
         p = pnode;
      }
      p = pnode;
   }

   if (p->parent == NULL) {
      p = NULL;
      return *this;
   }

   return *this;
}


template <typename VALUE_TYPE>
RB_TREE_ITERATOR<VALUE_TYPE> & RB_TREE_ITERATOR<VALUE_TYPE>::operator++ (int i)
{
   MAP_ITERATOR<VALUE_TYPE> * it = this;
   ++(*this);

   return *it;
}


#endif // _RBTREEITERATOR_H

/* END OF "rbtreeiterator.h" FILE */
