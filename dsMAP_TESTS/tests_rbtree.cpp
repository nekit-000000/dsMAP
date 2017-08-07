/* START OF "tests_rbtree.cpp" FILE */

#include <map>
#include <stack>
#include <vector>
#include <gtest/gtest.h>

#include "dsmap.h"

#define RBTREESIZE 100000


struct RBTREETEST : public testing::Test, public dsRB_TREE<int> {
   RBTREETEST(void)
   {
     for (int i = 0; i < RBTREESIZE; i++)
       InsertElem(i);
   }
   
   ~RBTREETEST(void)
   {
   }
};


/*
This function checks if colors of nodes of a
red-black tree are correct or not.

Red-Black tree color properties:
- The root's color is always black
- The leaf's color is black
- The color of both descendents of a red
node is black
*/
TEST_F(RBTREETEST, ColorTest)
{
   std::stack<NODE *> buff;
   NODE * node;
   
   // The root's color is always black
   EXPECT_EQ(COLOR::BLACK, root->color);
   
   node = root;
   
   // The leaf's color is black
   EXPECT_EQ(COLOR::BLACK, node->parent->color);
   
   while (node->parent != NULL || (buff.size() != 0)) {
      if (node->parent != NULL) {
         if (node->right->parent != NULL)
            buff.push(node->right);
         
         //The color of both descendents of a red node is black
         if (node->color == COLOR::RED)
         {
            EXPECT_EQ(COLOR::BLACK, node->left->color);
            EXPECT_EQ(COLOR::BLACK, node->right->color);
         }
         
         node = node->left;
      } else {
         node = buff.top();
         buff.pop();
      }
   }
}

/*
This function checks if every path from a root
to any of its descendant NIL nodes contains
the same number of black nodes
*/
TEST_F(RBTREETEST, PathLengthTest)
{
   std::stack<NODE *> buff;
   std::map<int, int> colorMap; // contains the number of black nodes before and including current node
   std::vector<int> colorBuff;  // contains the number of black nodes on a path
   NODE * node;
   int cnt = -1;
   
   node = root;
   
   while (node->parent != NULL || (buff.size() != 0)) {
      if (node->parent != NULL) {
         if (node->right->parent != NULL)
            buff.push(node->right);
         
         if (node->color == COLOR::BLACK)
            cnt++;
         
         colorMap[node->data] = cnt;
         
         node = node->left;
      } else {
         colorBuff.push_back(cnt);
         node = buff.top();
         buff.pop();
         cnt = colorMap[node->parent->data];
      }
   }
   colorBuff.push_back(cnt);
   
   for (auto it = colorBuff.begin(); it != colorBuff.end(); ++it)
      EXPECT_EQ(colorBuff[0], *it);
}

/*
This function checks if findMin() function
finds minimum correctly
*/
TEST_F(RBTREETEST, FindsMinimumCorrectly)
{
   std::stack<NODE *> buff;
   NODE * node;
   int min = RBTREESIZE;
   
   node = root;
   
   while (node->parent != NULL || (buff.size() != 0)) {
      if (node->parent != NULL) {
         if (node->right->parent != NULL)
            buff.push(node->right);
         
         if (node->data < min)
            min = node->data;
         
         node = node->left;
      } else {
         node = buff.top();
         buff.pop();
      }
   }
   
   EXPECT_EQ(min, FindMin(root)->data);
}

/* END OF "tests_rbtree.cpp" FILE */
