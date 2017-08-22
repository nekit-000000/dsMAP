/* START OF "mapiterator.h" FILE */

#pragma once
#ifndef _MAPITERATOR_H
#define _MAPITERATOR_H

// forward declaration
template <typename VALUE_TYPE>
class dsRB_TREE;


enum class NODE_COLOR {
   BLACK,
   RED
};


template <typename VALUE_TYPE>
class MAP_ITERATOR {
   friend class dsRB_TREE<VALUE_TYPE>;

public:
   struct NODE { // element of a red-black tree
   public:
      NODE (void);
      NODE (const NODE & n);
      NODE (NODE_COLOR color, NODE * parent, NODE * left, NODE * right);
      NODE (NODE_COLOR color, VALUE_TYPE data, NODE * parent, NODE * left, NODE * right);

      ~NODE (void) {}

   public:
      NODE_COLOR color;
      VALUE_TYPE data;
      NODE * parent;
      NODE * left;
      NODE * right;
   };

public:
   MAP_ITERATOR (void);
   MAP_ITERATOR (const MAP_ITERATOR & it);
   MAP_ITERATOR (NODE * p);
   MAP_ITERATOR (const NODE * p);

   ~MAP_ITERATOR (void) {}

   VALUE_TYPE & operator*    (void) const;
   VALUE_TYPE * operator->   (void) const;
   bool operator!=           (MAP_ITERATOR const & it) const;
   bool operator==           (MAP_ITERATOR const & it) const;
   MAP_ITERATOR & operator++ (void);
   MAP_ITERATOR & operator++ (int i);

private:
   long long path;
   long long offset;
   NODE * p;
};

template <typename VALUE_TYPE>
MAP_ITERATOR<VALUE_TYPE>::NODE::NODE (void) : data()
{
}

template <typename VALUE_TYPE>
MAP_ITERATOR<VALUE_TYPE>::NODE::NODE (const NODE & n)
{
   color = n.color;
   left = n.left;
   right = n.right;
   parent = n.parent;
   data = n.data;
}

template <typename VALUE_TYPE>
MAP_ITERATOR<VALUE_TYPE>::NODE::NODE (NODE_COLOR color, NODE * parent, NODE * left, NODE * right) :
   color(color), parent(parent), left(left), right(right)
{
}

template <typename VALUE_TYPE>
MAP_ITERATOR<VALUE_TYPE>::NODE::NODE (NODE_COLOR color, VALUE_TYPE data, NODE * parent,
   NODE * left, NODE * right) :
   color(color), parent(parent), left(left), right(right), data(data)
{
}

template <typename VALUE_TYPE>
MAP_ITERATOR<VALUE_TYPE>::MAP_ITERATOR (NODE * p) : p(p), path(0), offset(0)
{
}

template <typename VALUE_TYPE>
MAP_ITERATOR<VALUE_TYPE>::MAP_ITERATOR (const NODE * p) : p(p), path(0), offset(0)
{
}

template <typename VALUE_TYPE>
MAP_ITERATOR<VALUE_TYPE>::MAP_ITERATOR (void) :
   p(NULL), path(0), offset(0)
{
}

template <typename VALUE_TYPE>
MAP_ITERATOR<VALUE_TYPE>::MAP_ITERATOR (const MAP_ITERATOR & it) :
   p(it.p), path(0), offset(0)
{
}

template <typename VALUE_TYPE>
VALUE_TYPE & MAP_ITERATOR<VALUE_TYPE>::operator* (void) const
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
   if (p->left->parent != NULL) {
      p = p->left;
      path += ((long long)1 << offset);
   } else {
      long long maxOffset = ((long long)1 << (offset - 1));
      while (p->right->parent == NULL && offset >= 0) {
         if (path > maxOffset) {
            path -= maxOffset;
            offset--;
            p = p->parent;
         } else {
            while (path < maxOffset) {
               p = p->parent;
               offset--;
               maxOffset = ((long long)1 << (offset - 1));
            }

            path -= maxOffset;
            offset--;
            p = p->parent;
         }
      }

      if (offset < 0) {
         p = NULL;
         return *this;
      }

      p = p->right;
   }

   offset++;
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
