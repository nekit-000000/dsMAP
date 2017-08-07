/* START OF "tests_dsmap.cpp" FILE */

#include <map>
#include <stack>
#include <gtest/gtest.h>

#include "dsmap.h"

#define MAPSIZE 100


TEST(MapSizeTest, CorrectAfterInsertion)
{
   dsMAP<int, int> testMap;
   
   for (int i = 1; i < MAPSIZE; i++) {
      testMap[i] = i;
      EXPECT_EQ(i, testMap.Size());
   }
}

TEST(MapSizeTest, IsEmptyInitially)
{
   dsMAP<int, int> testMap;
   EXPECT_EQ(0, testMap.Size());
}

TEST(MapSizeTest, CorrectAfterRemoval)
{
   dsMAP<int, int> testMap;
   
   for (int i = 0; i < MAPSIZE; i++) {
      testMap[i] = i;
   }
   
   for (int i = MAPSIZE - 1; i > MAPSIZE / 2; i--) {
      testMap.Erase(i);
      EXPECT_EQ(i, testMap.Size());
   }
}

TEST(MapEmptyTest, IsEmptyInitially)
{
   dsMAP<int, int> testMap;
   EXPECT_EQ(true, testMap.Empty());
}

TEST(MapEmptyTest, NotEmptyAfterInsertion)
{
   dsMAP<int, int> testMap;
   
   for (int i = 0; i < MAPSIZE; i++) {
      testMap[i] = i;
   }
   EXPECT_EQ(false, testMap.Empty());
}

TEST(MapFindTest, CorrectIfElemDoesntExist)
{
   dsMAP<int, int> testMap;
   
   testMap[0] = 0;
   EXPECT_EQ(testMap.End(), testMap.Find(1));
}

TEST(MapFindTest, CorrectIfElemExists)
{
   dsMAP<int, int> testMap;
   
   testMap[0] = 0;
   auto it = testMap.Find(0);
   EXPECT_EQ(testMap[0], it->second);
}

TEST(MapEraseTest, ErasesCorrectly)
{
   dsMAP<int, int> testMap;
   
   for (int i = 0; i < MAPSIZE; i++) {
      testMap[i] = i;
   }
   
   
   for (int i = MAPSIZE - 1; i > MAPSIZE / 2; i--) {
      testMap.Erase(i);
      EXPECT_EQ(testMap.End(), testMap.Find(i));
   }
}

TEST(MapCountTest, CorrectIfExists)
{
   dsMAP<int, int> testMap;
   
   testMap[0] = 0;
   EXPECT_EQ(true, testMap.Count(0));
}

TEST(MapCountTest, CorrectIfDoesntExist)
{
   dsMAP<int, int> testMap;
   
   for (int i = 0; i < MAPSIZE; i++) {
      testMap[i] = i;
   }
   EXPECT_EQ(false, testMap.Count(-1));
}

TEST(MapClearTest, CorrectIfNotEmpty)
{
   dsMAP<int, int> testMap;
   int cnt = 0;
   
   for (int i = 0; i < MAPSIZE; i++) {
      testMap[i] = i;
   }
   
   testMap.Clear();
   
   EXPECT_EQ(testMap.Begin(), testMap.End());
}

TEST(MapIteratorTest, PassesAllVallues)
{
   dsMAP<int, int> testMap;
   std::map<int, int> arr;
   
   for (int i = 0; i < MAPSIZE; i++) {
      testMap[i] = i;
      arr[i] = i;
   }
   
   for (auto it = testMap.Begin(); it != testMap.End(); ++it) {
      arr.erase(it->first);
   }
   
   EXPECT_EQ(0, arr.size());
}

/* END OF "tests_dsmap.cpp" FILE */
