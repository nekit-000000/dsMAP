/* START OF "dsrbtreeiterator.hpp" FILE */

#pragma once
#ifndef _DSRBTREEITERATOR_HPP
#define _DSRBTREEITERATOR_HPP


template <typename VALUE_TYPE>
dsRB_TREE_ITERATOR<VALUE_TYPE>::dsRB_TREE_ITERATOR (NODE * p) : p(p)
{
}


template <typename VALUE_TYPE>
dsRB_TREE_ITERATOR<VALUE_TYPE>::dsRB_TREE_ITERATOR (const dsRB_TREE_ITERATOR & it) : p(it.p)
{
}


template <typename VALUE_TYPE>
dsRB_TREE_ITERATOR<VALUE_TYPE>::dsRB_TREE_ITERATOR (const NODE * p) : p(p)
{
}


template <typename VALUE_TYPE>
dsRB_TREE_ITERATOR<VALUE_TYPE>::dsRB_TREE_ITERATOR (void) : p(NULL)
{
}


template <typename VALUE_TYPE>
dsRB_TREE_ITERATOR<VALUE_TYPE>::dsRB_TREE_ITERATOR (const dsRB_TREE_CONST_ITERATOR<VALUE_TYPE> & it) : p((NODE *)it.p)
{
}


template <typename VALUE_TYPE>
VALUE_TYPE & dsRB_TREE_ITERATOR<VALUE_TYPE>::operator* (void) const
{
   return p->data;
}


template <typename VALUE_TYPE>
VALUE_TYPE * dsRB_TREE_ITERATOR<VALUE_TYPE>::operator-> (void) const
{
   return &p->data;
}


template <typename VALUE_TYPE>
dsRB_TREE_ITERATOR<VALUE_TYPE> & dsRB_TREE_ITERATOR<VALUE_TYPE>::operator= (const dsRB_TREE_ITERATOR & it)
{
   p = it.p;
   return *this;
}


template <typename VALUE_TYPE>
bool dsRB_TREE_ITERATOR<VALUE_TYPE>::operator!= (dsRB_TREE_ITERATOR const & it) const
{
   return p != it.p;
}


template <typename VALUE_TYPE>
bool dsRB_TREE_ITERATOR<VALUE_TYPE>::operator== (dsRB_TREE_ITERATOR const & it) const
{
   return p == it.p;
}


template <typename VALUE_TYPE>
dsRB_TREE_ITERATOR<VALUE_TYPE> & dsRB_TREE_ITERATOR<VALUE_TYPE>::operator++ (void)
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
dsRB_TREE_ITERATOR<VALUE_TYPE> & dsRB_TREE_ITERATOR<VALUE_TYPE>::operator++ (int i)
{
   dsRB_TREE_ITERATOR<VALUE_TYPE> * it = this;
   ++(*this);

   return *it;
}

template <typename VALUE_TYPE>
dsRB_TREE_CONST_ITERATOR<VALUE_TYPE>::dsRB_TREE_CONST_ITERATOR (const NODE * p) : p(p)
{
}


template <typename VALUE_TYPE>
dsRB_TREE_CONST_ITERATOR<VALUE_TYPE>::dsRB_TREE_CONST_ITERATOR (const dsRB_TREE_CONST_ITERATOR & it) : p(it.p)
{
}


template <typename VALUE_TYPE>
dsRB_TREE_CONST_ITERATOR<VALUE_TYPE>::dsRB_TREE_CONST_ITERATOR (void) : p(NULL)
{
}


template <typename VALUE_TYPE>
const VALUE_TYPE & dsRB_TREE_CONST_ITERATOR<VALUE_TYPE>::operator* (void) const
{
   return p->data;
}


template <typename VALUE_TYPE>
const VALUE_TYPE * dsRB_TREE_CONST_ITERATOR<VALUE_TYPE>::operator-> (void) const
{
   return &p->data;
}


template <typename VALUE_TYPE>
dsRB_TREE_CONST_ITERATOR<VALUE_TYPE> & dsRB_TREE_CONST_ITERATOR<VALUE_TYPE>::operator= (const dsRB_TREE_CONST_ITERATOR & it)
{
   p = it.p;
   return *this;
}


template <typename VALUE_TYPE>
bool dsRB_TREE_CONST_ITERATOR<VALUE_TYPE>::operator!= (dsRB_TREE_CONST_ITERATOR const & it) const
{
   return p != it.p;
}


template <typename VALUE_TYPE>
bool dsRB_TREE_CONST_ITERATOR<VALUE_TYPE>::operator== (dsRB_TREE_CONST_ITERATOR const & it) const
{
   return p == it.p;
}



template <typename VALUE_TYPE>
bool dsRB_TREE_CONST_ITERATOR<VALUE_TYPE>::operator!= (const dsRB_TREE_ITERATOR<VALUE_TYPE> & it) const
{
   return p != it.p;
}


template <typename VALUE_TYPE>
bool dsRB_TREE_CONST_ITERATOR<VALUE_TYPE>::operator== (const dsRB_TREE_ITERATOR<VALUE_TYPE> & it) const
{
   return p == it.p;
}


template <typename VALUE_TYPE>
dsRB_TREE_CONST_ITERATOR<VALUE_TYPE> & dsRB_TREE_CONST_ITERATOR<VALUE_TYPE>::operator++ (void)
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
dsRB_TREE_CONST_ITERATOR<VALUE_TYPE> & dsRB_TREE_CONST_ITERATOR<VALUE_TYPE>::operator++ (int i)
{
   dsRB_TREE_CONST_ITERATOR<VALUE_TYPE> * it = this;
   ++(*this);

   return *it;
}


#endif // _DSRBTREEITERATOR_H

/* END OF "dsrbtreeiterator.hpp" FILE */
