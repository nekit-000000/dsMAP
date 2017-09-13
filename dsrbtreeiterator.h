/* START OF "dsrbtreeiterator.h" FILE */

#pragma once
#ifndef _DSRBTREEITERATOR_H
#define _DSRBTREEITERATOR_H


// forward declaration
template <typename VALUE_TYPE>
class dsRB_TREE;

// forward declaration
template <typename VALUE_TYPE>
class dsRB_TREE_ITERATOR;


template <typename VALUE_TYPE>
class dsRB_TREE_CONST_ITERATOR {
   friend class dsRB_TREE<VALUE_TYPE>;
   friend class dsRB_TREE_ITERATOR<VALUE_TYPE>;

public:
   typedef typename dsRB_TREE<VALUE_TYPE>::NODE NODE;

   dsRB_TREE_CONST_ITERATOR (void);
   dsRB_TREE_CONST_ITERATOR (const NODE * p);
   dsRB_TREE_CONST_ITERATOR (const dsRB_TREE_CONST_ITERATOR & it);

   ~dsRB_TREE_CONST_ITERATOR (void) {}

   const VALUE_TYPE & operator*          (void) const;
   const VALUE_TYPE * operator->         (void) const;
   bool operator!=                       (const dsRB_TREE_CONST_ITERATOR & it) const;
   bool operator==                       (const dsRB_TREE_CONST_ITERATOR & it) const;
   bool operator!=                       (const dsRB_TREE_ITERATOR<VALUE_TYPE> & it) const;
   bool operator==                       (const dsRB_TREE_ITERATOR<VALUE_TYPE> & it) const;
   dsRB_TREE_CONST_ITERATOR & operator=  (const dsRB_TREE_CONST_ITERATOR & it);
   dsRB_TREE_CONST_ITERATOR & operator++ (void);
   dsRB_TREE_CONST_ITERATOR & operator++ (int i);

private:
   const NODE * p;
};


template <typename VALUE_TYPE>
class dsRB_TREE_ITERATOR {
   friend class dsRB_TREE<VALUE_TYPE>;
   friend class dsRB_TREE_CONST_ITERATOR<VALUE_TYPE>;

public:
   typedef typename dsRB_TREE<VALUE_TYPE>::NODE NODE;

   dsRB_TREE_ITERATOR (void);
   dsRB_TREE_ITERATOR (NODE * p);
   dsRB_TREE_ITERATOR (const NODE * p);
   dsRB_TREE_ITERATOR (const dsRB_TREE_CONST_ITERATOR<VALUE_TYPE> & it);
   dsRB_TREE_ITERATOR (const dsRB_TREE_ITERATOR & it);

   ~dsRB_TREE_ITERATOR (void) {}

   VALUE_TYPE & operator*          (void) const;
   VALUE_TYPE * operator->         (void) const;
   bool operator!=                 (const dsRB_TREE_ITERATOR & it) const;
   bool operator==                 (const dsRB_TREE_ITERATOR & it) const;
   dsRB_TREE_ITERATOR & operator=  (const dsRB_TREE_ITERATOR & it);
   dsRB_TREE_ITERATOR & operator++ (void);
   dsRB_TREE_ITERATOR & operator++ (int i);

private:
   NODE * p;
};


#include "dsrbtreeiterator.hpp"

#endif // _DSRBTREEITERATOR_H

/* END OF "dsrbtreeiterator.h" FILE */
