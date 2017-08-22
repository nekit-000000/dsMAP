/* START OF "tests_rbtree.cpp" FILE */

#include <map>
#include <stack>
#include <vector>
#include <gtest/gtest.h>

#include "dsmap.h"


struct RB_TREE_TEST : public testing::Test,
                      testing::WithParamInterface<int>,
                      public dsRB_TREE<int> {

   void SetUp (void)
   {
      int size = GetParam();
      for (int i = 0; i < size; i++) {
         Insert(i);
      }
   }

   void TearDown (void)
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
TEST_P (RB_TREE_TEST, ColorTest)
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
         if (node->right->parent != NULL) {
            buff.push(node->right);
         }
         
         //The color of both descendents of a red node is black
         if (node->color == COLOR::RED) {
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
TEST_P (RB_TREE_TEST, PathLengthTest)
{
   std::stack<NODE *> buff;
   std::map<int, int> colorMap; // contains the number of black nodes before and including current node
   std::vector<int> colorBuff;  // contains the number of black nodes on a path
   NODE * node;
   int cnt = -1;

   node = root;
   
   while (node->parent != NULL || (buff.size() != 0)) {
      if (node->parent != NULL) {
         if (node->right->parent != NULL) {
            buff.push(node->right);
         }
         
         if (node->color == COLOR::BLACK) {
            cnt++;
         }
         
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
   
   for (auto it = colorBuff.begin(); it != colorBuff.end(); ++it) {
      EXPECT_EQ(colorBuff[0], *it);
   }
}


INSTANTIATE_TEST_CASE_P(RBTreeTestParameters,
   RB_TREE_TEST,
   testing::Values(1, 100, 1000, 10000));

/* END OF "tests_rbtree.cpp" FILE */
