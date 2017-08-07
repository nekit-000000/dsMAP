/* START OF "rbtree.hpp" FILE */

#pragma once
#ifndef _RBTREE_HPP
#define _RBTREE_HPP

template <typename VALUE_TYPE>
NODE<VALUE_TYPE>::NODE (void) : data()
{
}

template <typename VALUE_TYPE>
NODE<VALUE_TYPE>::NODE (const NODE & n)
{
   color = n.color;
   left = n.left;
   right = n.right;
   parent = n.parent;
   data = n.data;
}

template <typename VALUE_TYPE>
NODE<VALUE_TYPE>::NODE (NODE_COLOR color, NODE * parent, NODE * left, NODE * right) :
   color(color), parent(parent), left(left), right(right)
{
}

template <typename VALUE_TYPE>
NODE<VALUE_TYPE>::NODE (NODE_COLOR color, VALUE_TYPE data, NODE * parent, 
   NODE * left, NODE * right) :
   color(color), parent(parent), left(left), right(right), data(data)
{
}

template <typename VALUE_TYPE>
dsRB_TREE<VALUE_TYPE>::dsRB_TREE (void)
{
   root = nil;
}

template <typename VALUE_TYPE>
dsRB_TREE<VALUE_TYPE>::dsRB_TREE (const VALUE_TYPE & data)
{
   root = new VERTEX;
   root->parent = nil;
   root->right = nil;
   root->left = nil;
   root->color = COLOR::BLACK;
   root->data = data;
}

template <typename VALUE_TYPE>
dsRB_TREE<VALUE_TYPE>::~dsRB_TREE (void)
{
   VERTEX * x = root;
   VERTEX * y = root;

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
}

template <typename VALUE_TYPE>
void dsRB_TREE<VALUE_TYPE>::RotateLeft (VERTEX * x)
{
   if (x->right == nil) {
      return;
   }

   VERTEX * y = x->right;

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
void dsRB_TREE<VALUE_TYPE>::RotateRight (VERTEX * y)
{
   if (y->left == nil) {
      return;
   }
   
   VERTEX * x = y->left;
   
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
void dsRB_TREE<VALUE_TYPE>::InsertFixup (VERTEX * z)
{
   VERTEX * y;
   
   while (z->parent->color == COLOR::RED && z->parent->parent != nil) {
      if (z->parent == z->parent->parent->left) {
         y = z->parent->parent->right;

         if (y->color == COLOR::RED) {
            z->parent->color = COLOR::BLACK;
            y->color = COLOR::BLACK;
            z->parent->parent->color = COLOR::RED;
            z = z->parent->parent;
         }
         else if (z == z->parent->right) {
            z = z->parent;
            RotateLeft(z);
         }
         else {
            z->parent->color = COLOR::BLACK;
            z->parent->parent->color = COLOR::RED;
            RotateRight(z->parent->parent);
         }
      }
      else {
         y = z->parent->parent->left;

         if (y->color == COLOR::RED) {
            z->parent->color = COLOR::BLACK;
            y->color = COLOR::BLACK;
            z->parent->parent->color = COLOR::RED;
            z = z->parent->parent;
         }
         else if (z == z->parent->left) {
            z = z->parent;
            RotateRight(z);
         }
         else {
            z->parent->color = COLOR::BLACK;
            z->parent->parent->color = COLOR::RED;
            RotateLeft(z->parent->parent);
         }
      }
   }
   
   root->color = COLOR::BLACK;
}

template <typename VALUE_TYPE>
NODE<VALUE_TYPE> * dsRB_TREE<VALUE_TYPE>::InsertElem (const VALUE_TYPE & data)
{
   VERTEX * z = new VERTEX(COLOR::RED, data, NULL, nil, nil);
   VERTEX * y = nil;
   VERTEX * x = root;
   
   while (x != nil) {
      y = x;
      if (z->data < x->data)
         x = x->left;
      else
         x = x->right;
   }
   
   z->parent = y;
   if (y == nil)
      root = z;
   else if (z->data < y->data)
      y->left = z;
   else
      y->right = z;
   
   InsertFixup(z);
   return z;
}

template <typename VALUE_TYPE>
void dsRB_TREE<VALUE_TYPE>::Transplant (VERTEX * u, VERTEX * v)
{
   if (u->parent == nil)
      root = v;
   else if (u == u->parent->left)
      u->parent->left = v;
   else
      u->parent->right = v;
   
   v->parent = u->parent;
}

template <typename VALUE_TYPE>
NODE<VALUE_TYPE> *dsRB_TREE<VALUE_TYPE>::FindNode (const VALUE_TYPE & data) const
{
   VERTEX * x = root;
   
   while (x != nil && x->data != data) {
      if (data > x->data)
         x = x->right;
      else
         x = x->left;
   }
   
   return x;
}

template <typename VALUE_TYPE>
NODE<VALUE_TYPE> *dsRB_TREE<VALUE_TYPE>::FindMin (VERTEX * x) const
{
   VERTEX * y = x;
   
   while (y->left != nil)
      y = y->left;
   
   return y;
}


template <typename VALUE_TYPE>
void dsRB_TREE<VALUE_TYPE>::DeleteFixup (VERTEX * x)
{
   VERTEX * w;
   
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
void dsRB_TREE<VALUE_TYPE>::DeleteElem (const VALUE_TYPE & data)
{
   VERTEX * z;
   VERTEX * y;
   VERTEX * x;
   
   if ((z = FindNode(data)) == nil) {
      return;
   }
   
   y = z;
   NODE_COLOR yOrigColor = y->color;
   
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
}

#endif // _RBTREE_HPP

/* END OF "rbtree.hpp" FILE */
