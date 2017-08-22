/* START OF "tests_dsmap.cpp" FILE */

#include <map>
#include <stack>
#include <gtest/gtest.h>

#include "dsmap.h"


class MAP_TEST : public testing::Test,
                 public testing::WithParamInterface<int> {
   void SetUp(void)
   {
      size = GetParam();
      for (int i = 0; i < size; i++) {
         testMap[i] = i;
      }
   }

   void TearDown(void)
   {
   }

public:
   int size;
   dsMAP<int, int> testMap;
};


TEST_P (MAP_TEST, SizeAfterInsertion)
{
   EXPECT_EQ(size, testMap.Size());
}

TEST (MapSizeTest, IsEmptyInitially)
{
   dsMAP<int, int> testMap;
   EXPECT_EQ(0, testMap.Size());
}

TEST_P (MAP_TEST, SizeAfterRemoval)
{  
   testMap.Erase(size - 1);
   EXPECT_EQ(size - 1, testMap.Size());
}

TEST (MapEmptyTest, IsEmptyInitially)
{
   dsMAP<int, int> testMap;
   EXPECT_EQ(true, testMap.Empty());
}

TEST_P (MAP_TEST, NotEmptyAfterInsertion)
{
   EXPECT_EQ(false, testMap.Empty());
}

TEST (MapFindTest, IfElemDoesntExist)
{
   dsMAP<int, int> testMap;
   
   testMap[0] = 0;
   EXPECT_EQ(testMap.End(), testMap.Find(1));
}

TEST (MapFindTest, CorrectIfElemExists)
{
   dsMAP<int, int> testMap;
   
   testMap[0] = 0;
   auto it = testMap.Find(0);
   EXPECT_EQ(testMap[0], it->second);
}

TEST_P (MAP_TEST, ErasesCorrectly)
{
   for (int i = size - 1; i > size / 2; i--) {
      testMap.Erase(i);
      EXPECT_EQ(testMap.End(), testMap.Find(i));
   }
}

TEST (MapCountTest, CorrectIfExists)
{
   dsMAP<int, int> testMap;
   
   testMap[0] = 0;
   EXPECT_EQ(1, testMap.Count(0));
}

TEST (MapCountTest, CorrectIfDoesntExist)
{
   dsMAP<int, int> testMap;
   
   testMap[1] = 1;
   EXPECT_EQ(0, testMap.Count(-1));
}

TEST_P (MAP_TEST, ClearTestIfNotEmpty)
{
   testMap.Clear();
   EXPECT_EQ(testMap.Begin(), testMap.End());
}

TEST (IteratorTest, PassesAllVallues)
{  
   dsMAP<int, int> testMap;

   for (int i = 0; i < 1000; i++) {
      testMap[i] = 0;
   }

   int iterCnt = 0;
   for (auto it = testMap.Begin(); it != testMap.End(); ++it) {
      it->second++;
      iterCnt++;
   }
   
   EXPECT_EQ(testMap.Size(), iterCnt);

   for (auto it = testMap.Begin(); it != testMap.End(); ++it) {
      EXPECT_EQ(it->second, 1);
   }
}

INSTANTIATE_TEST_CASE_P(MapTestParameters,
   MAP_TEST,
   testing::Values(1, 100, 1000, 10000));

/* END OF "tests_dsmap.cpp" FILE */
