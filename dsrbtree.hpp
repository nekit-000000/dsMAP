/* START OF "dsrbtree.hpp" FILE */

#pragma once
#ifndef _DSRBTREE_HPP
#define _DSRBTREE_HPP

#include <stack>


template <typename VALUE_TYPE>
dsRB_TREE<VALUE_TYPE>::NODE::NODE (void) : data()
{
}


template <typename VALUE_TYPE>
dsRB_TREE<VALUE_TYPE>::NODE::NODE (const NODE & n)
{
   color = n.color;
   left = n.left;
   right = n.right;
   parent = n.parent;
   data = n.data;
}


template <typename VALUE_TYPE>
dsRB_TREE<VALUE_TYPE>::NODE::NODE (NODE_COLOR color, NODE * parent, NODE * left, NODE * right) :
   color(color), parent(parent), left(left), right(right)
{
}


template <typename VALUE_TYPE>
dsRB_TREE<VALUE_TYPE>::NODE::NODE (NODE_COLOR color, VALUE_TYPE data, NODE * parent,
   NODE * left, NODE * right) :
   color(color), parent(parent), left(left), right(right), data(data)
{
}


template <typename VALUE_TYPE>
typename dsRB_TREE<VALUE_TYPE>::ITERATOR dsRB_TREE<VALUE_TYPE>::End (void)
{
   return ITERATOR((NODE *)NULL);
}


template <typename VALUE_TYPE>
typename dsRB_TREE<VALUE_TYPE>::ITERATOR dsRB_TREE<VALUE_TYPE>::Begin (void)
{
   if (root == nil) {
      return End();
   }
   return ITERATOR(FindMin(root));
}


template <typename VALUE_TYPE>
typename dsRB_TREE<VALUE_TYPE>::CONST_ITERATOR dsRB_TREE<VALUE_TYPE>::End (void) const
{
   return CONST_ITERATOR((const NODE *)NULL);
}


template <typename VALUE_TYPE>
typename dsRB_TREE<VALUE_TYPE>::CONST_ITERATOR dsRB_TREE<VALUE_TYPE>::Begin (void) const
{
   if (root == nil) {
      return End();
   }

   const NODE * pnode = root;
   while (pnode->left != nil) {
      pnode = pnode->left;
   }
   
   return CONST_ITERATOR(pnode);
}


template <typename VALUE_TYPE>
void dsRB_TREE<VALUE_TYPE>::CopySubTree (NODE * dest, NODE * parent, const NODE * src)
{
   dest->parent = parent;
   dest->data = src->data;
   dest->color = src->color;

   if (src->left != nil) {
      dest->left = new NODE;
      CopySubTree(dest->left, dest, src->left);
   }
   else {
      dest->left = nil;
   }

   if (src->right != nil) {
      dest->right = new NODE;
      CopySubTree(dest->right, dest, src->right);
   }
   else {
      dest->right = nil;
   }
}


template <typename VALUE_TYPE>
dsRB_TREE<VALUE_TYPE>::dsRB_TREE (const dsRB_TREE & tree)
{
   root = new NODE;
   CopySubTree(root, nil, tree.root);
   size = tree.size;
}


template <typename VALUE_TYPE>
dsRB_TREE<VALUE_TYPE>::dsRB_TREE (dsRB_TREE && tree)
{
   root = tree.root;
   size = tree.size;
   tree.size = 0;
   tree.root = nil;
}


template <typename VALUE_TYPE>
dsRB_TREE<VALUE_TYPE>::dsRB_TREE (void) : size(0), root(nil)
{
}


template <typename VALUE_TYPE>
dsRB_TREE<VALUE_TYPE>::dsRB_TREE (const VALUE_TYPE & data) : size(1)
{
   root = new NODE;
   root->parent = nil;
   root->right = nil;
   root->left = nil;
   root->color = COLOR::BLACK;
   root->data = data;
}

template <typename VALUE_TYPE>
void dsRB_TREE<VALUE_TYPE>::DeleteSubTree (NODE * subTree)
{
   if (subTree == nil) {
      return;
   }

   NODE * x = subTree;
   NODE * y = subTree;
   NODE * parent = subTree->parent;

   while (y != parent) {
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
}


template <typename VALUE_TYPE>
dsRB_TREE<VALUE_TYPE>::~dsRB_TREE (void)
{
   DeleteSubTree(root);
}


template <typename VALUE_TYPE>
void dsRB_TREE<VALUE_TYPE>::CopyWithoutAlloc (NODE * dest, NODE * parent, const NODE * src)
{
   dest->color = src->color;
   dest->data = src->data;
   dest->parent = parent;

   if (dest->left == nil && src->left != nil) {
      dest->left = new NODE;
      CopySubTree(dest->left, dest, src->left);
   } else if (src->left == nil) {
      if (dest->left != nil) {
         DeleteSubTree(dest->left);
      }

      dest->left = nil;
   } else {
      CopyWithoutAlloc(dest->left, dest, src->left);
   }

   if (dest->right == nil && src->right != nil) {
      dest->right = new NODE;
      CopySubTree(dest->right, dest, src->right);
   } else if (src->right == nil) {
      if (dest->right != nil) {
         DeleteSubTree(dest->right);
      }

      dest->right = nil;
   } else {
      CopyWithoutAlloc(dest->right, dest, src->right);
   }
}


template <typename VALUE_TYPE>
dsRB_TREE<VALUE_TYPE> & dsRB_TREE<VALUE_TYPE>::operator= (dsRB_TREE && tree)
{
   DeleteSubTree(root);

   root = tree.root;
   size = tree.size;
   tree.size = 0;
   tree.root = nil;
   return *this;
}


template <typename VALUE_TYPE>
dsRB_TREE<VALUE_TYPE> & dsRB_TREE<VALUE_TYPE>::operator= (const dsRB_TREE & tree)
{
   if (root == tree.root) {
      return *this;
   }

   if (root == nil) {
      root = new NODE;
      root->left = nil;
      root->right = nil;
   }

   CopyWithoutAlloc(root, nil, tree.root);
   size = tree.size;
   return *this;
}

template <typename VALUE_TYPE>
void dsRB_TREE<VALUE_TYPE>::RotateLeft (NODE * x)
{
   if (x->right == nil) {
      return;
   }

   NODE * y = x->right;

   x->right = y->left;

   if (y->left != nil) {
      y->left->parent = x;
   }
   y->parent = x->parent;

   if (x->parent == nil) {
      root = y;
   } else if (x == x->parent->left) {
      x->parent->left = y;
   } else {
      x->parent->right = y;
   }
   
   y->left = x;
   x->parent = y;
}


template <typename VALUE_TYPE>
void dsRB_TREE<VALUE_TYPE>::RotateRight (NODE * y)
{
   if (y->left == nil) {
      return;
   }
   
   NODE * x = y->left;
   
   y->left = x->right;
   
   if (x->right != nil) {
      x->right->parent = y;
   }
   x->parent = y->parent;

   if (y->parent == nil) {
      root = x;
   } else if (y == y->parent->left) {
      y->parent->left = x;
   } else {
      y->parent->right = x;
   }
   
   x->right = y;
   y->parent = x;
}


template <typename VALUE_TYPE>
void dsRB_TREE<VALUE_TYPE>::InsertFixup (NODE * z)
{
   NODE * y;
   
   while (z->parent->color == COLOR::RED && z->parent->parent != nil) {
      if (z->parent == z->parent->parent->left) {
         y = z->parent->parent->right;

         if (y->color == COLOR::RED) {
            z->parent->color = COLOR::BLACK;
            y->color = COLOR::BLACK;
            z->parent->parent->color = COLOR::RED;
            z = z->parent->parent;
         } else if (z == z->parent->right) {
            z = z->parent;
            RotateLeft(z);
         } else {
            z->parent->color = COLOR::BLACK;
            z->parent->parent->color = COLOR::RED;
            RotateRight(z->parent->parent);
         }
      } else {
         y = z->parent->parent->left;

         if (y->color == COLOR::RED) {
            z->parent->color = COLOR::BLACK;
            y->color = COLOR::BLACK;
            z->parent->parent->color = COLOR::RED;
            z = z->parent->parent;
         } else if (z == z->parent->left) {
            z = z->parent;
            RotateRight(z);
         } else {
            z->parent->color = COLOR::BLACK;
            z->parent->parent->color = COLOR::RED;
            RotateLeft(z->parent->parent);
         }
      }
   }
   
   root->color = COLOR::BLACK;
}


template <typename VALUE_TYPE>
void dsRB_TREE<VALUE_TYPE>::Transplant (NODE * u, NODE * v)
{
   if (u->parent == nil) {
      root = v;
   } else if (u == u->parent->left) {
      u->parent->left = v;
   } else {
      u->parent->right = v;
   }
   
   v->parent = u->parent;
}


template <typename VALUE_TYPE>
typename dsRB_TREE<VALUE_TYPE>::NODE * dsRB_TREE<VALUE_TYPE>::FindMin (NODE * x)
{
   NODE * y = x;

   while (y->left != nil) {
      y = y->left;
   }

   return y;
}


template <typename VALUE_TYPE>
void dsRB_TREE<VALUE_TYPE>::DeleteFixup (NODE * x)
{
   NODE * w;
   
   while (x != root && x->color == COLOR::BLACK) {
      if (x == x->parent->left) {
         w = x->parent->right;
         
         if (w->color == COLOR::RED) {
            w->color = COLOR::BLACK;
            x->parent->color = COLOR::RED;
            RotateLeft(x->parent);
            w = x->parent->right;
         }

         if (w->left->color == COLOR::BLACK && w->right->color == COLOR::BLACK) {
            w->color = COLOR::RED;
            x = x->parent;
         } else if (w->right->color == COLOR::BLACK) {
            w->left->color = COLOR::BLACK;
            w->color = COLOR::RED;
            RotateRight(w);
            w = x->parent->right;
         } else {
            w->color = x->parent->color;
            x->parent->color = COLOR::BLACK;
            w->right->color = COLOR::BLACK;
            RotateLeft(x->parent);
            x = root;
         }
      } else {
         w = x->parent->left;
      
         if (w->color == COLOR::RED) {
            w->color = COLOR::BLACK;
            x->parent->color = COLOR::RED;
            RotateRight(x->parent);
            w = x->parent->left;
         }

         if (w->left->color == COLOR::BLACK && w->right->color == COLOR::BLACK) {
            w->color = COLOR::RED;
            x = x->parent;
         } else if (w->left->color == COLOR::BLACK) {
            w->right->color = COLOR::BLACK;
            w->color = COLOR::RED;
            RotateLeft(w);
            w = x->parent->left;
         } else {
            w->color = x->parent->color;
            x->parent->color = COLOR::BLACK;
            w->left->color = COLOR::BLACK;
            RotateRight(x->parent);
            x = root;
         }
      }
   }
   
   x->color = COLOR::BLACK;
}


template <typename VALUE_TYPE>
dsRB_TREE_ITERATOR<VALUE_TYPE> dsRB_TREE<VALUE_TYPE>::InsertElem (const VALUE_TYPE & data)
{
   NODE * z = new NODE(COLOR::RED, data, NULL, nil, nil);
   NODE * y = nil;
   NODE * x = root;

   while (x != nil) {
      y = x;
      if (z->data < x->data) {
         x = x->left;
      } else {
         x = x->right;
      }
   }

   z->parent = y;
   if (y == nil) {
      root = z;
   } else if (z->data < y->data) {
      y->left = z;
   } else {
      y->right = z;
   }

   InsertFixup(z);
   return ITERATOR(z);
}


template <typename VALUE_TYPE>
dsRB_TREE_CONST_ITERATOR<VALUE_TYPE> dsRB_TREE<VALUE_TYPE>::Find (const VALUE_TYPE & data) const
{
   NODE * x = root;

   while (x != nil && x->data != data) {
      if (data > x->data) {
         x = x->right;
      }
      else {
         x = x->left;
      }
   }

   if (x == nil) {
      return End();
   }
   return CONST_ITERATOR(x);
}


template <typename VALUE_TYPE>
void dsRB_TREE<VALUE_TYPE>::Delete (ITERATOR & it)
{
   if (it == End())
      return;

   NODE * z = it.p;
   NODE * y;
   NODE * x;

   y = z;
   COLOR yOrigColor = y->color;

   if (z->left == nil) {
      x = z->right;
      Transplant(z, z->right);
   } else if (z->right == nil) {
      x = z->left;
      Transplant(z, z->left);
   } else {
      y = FindMin(z->right);
      yOrigColor = y->color;
      x = y->right;

      if (y->parent == z) {
         x->parent = y;
      } else {
         Transplant(y, y->right);
         y->right = z->right;
         y->right->parent = y;
      }

      Transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
   }

   delete z;

   if (yOrigColor == COLOR::BLACK) {
      DeleteFixup(x);
   }
   nil->parent = NULL;
   size--;
}


template <typename VALUE_TYPE>
void dsRB_TREE<VALUE_TYPE>::Delete (const VALUE_TYPE & data)
{
   DeleteElem(FindNode(data));
}


template <typename VALUE_TYPE>
std::pair<typename dsRB_TREE<VALUE_TYPE>::ITERATOR, bool> dsRB_TREE<VALUE_TYPE>::Insert (const VALUE_TYPE & val)
{
   ITERATOR it = Find(val);

   if (it == End()) {
      VALUE_TYPE insertPair;
      insertPair = val;
      it = InsertElem(insertPair);
      size++;
      return std::make_pair(it, true);
   }

   return std::make_pair(it, false);
}


#endif // _DSRBTREE_HPP

/* END OF "dsrbtree.hpp" FILE */
