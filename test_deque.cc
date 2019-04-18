#include "deque.h"
#include <gtest/gtest.h>

TEST(Deque, Empty) {
Deque<int> dq;

/* Should be fully empty */
EXPECT_EQ(dq.Empty(), true);
EXPECT_EQ(dq.Size(), 0);
EXPECT_THROW(dq.PopFront(), std::exception);
}

TEST(Deque, DoubleInsertionBack) {
Deque<int> dq;
/* Test some insertion */
dq.PushBack(23);
dq.PushBack(42);
EXPECT_EQ(dq.Empty(), false);
EXPECT_EQ(dq.Size(), 2);
EXPECT_EQ(dq[0], 23);
EXPECT_EQ(dq[1], 42);
EXPECT_EQ(dq.Back(), 42);
}

TEST(Deque, DoubleInsertionBackFront) {
Deque<int> dq;
/* Test some insertion */
dq.PushBack(23);
dq.PushFront(42);
EXPECT_EQ(dq.Empty(), false);
EXPECT_EQ(dq.Size(), 2);
EXPECT_EQ(dq[0], 42);
EXPECT_EQ(dq[1], 23);
EXPECT_EQ(dq.Back(), 23);
}


// Check the Front & Back Insertion of the Program.
TEST(Deque, Deque_Circular_Array_Front_Test) {
  Deque<int> dq;
/* Test some insertion */
  dq.PushBack(11);
  dq.PushFront(22);
  dq.PushBack(33);
  dq.PushFront(44);
  dq.PushBack(55);
  dq.PushFront(66);
  EXPECT_EQ(dq[0], 66);
  EXPECT_EQ(dq[1], 44);
  EXPECT_EQ(dq[2], 22);
  EXPECT_EQ(dq[3], 11);
  EXPECT_EQ(dq[4], 33);
  EXPECT_EQ(dq[5], 55);
  dq.PopFront();
  EXPECT_EQ(dq.Front(), 44);
  dq.PushBack(233);
  EXPECT_EQ(dq.Front(), 44);
  EXPECT_EQ(dq.Back(), 233);
}

// Check the Circular function of the Deque
TEST(Deque, Deque_Circular_Array_Back_Test) {
  Deque<int> dq;
/* Test some insertion */
  dq.PushBack(11);
  dq.PushFront(22);
  dq.PushBack(33);
  dq.PushFront(44);
  dq.PushBack(55);
  dq.PushFront(66);
  EXPECT_EQ(dq[0], 66);
  EXPECT_EQ(dq[1], 44);
  EXPECT_EQ(dq[2], 22);
  EXPECT_EQ(dq[3], 11);
  EXPECT_EQ(dq[4], 33);
  EXPECT_EQ(dq[5], 55);
  dq.PopBack();
  EXPECT_EQ(dq.Back(), 33);
  dq.PushFront(233);
  EXPECT_EQ(dq.Front(), 233);
  EXPECT_EQ(dq.Back(), 33);
}

// Check if there is any issue with memory
TEST(Deque, Deque_Circular_Array_Extreme_Push_Test) {
  Deque<int> dq;
/* Test some insertion */
  for(int i = 0; i < 10000; i++) {
    dq.PushBack(11);
    dq.PushFront(22);
  }
  EXPECT_EQ(dq.Front(), 22);
  EXPECT_EQ(dq.Back(), 11);
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

