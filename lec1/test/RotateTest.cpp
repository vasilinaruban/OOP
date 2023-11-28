#include "gtest/gtest.h"
#include "CircularBuffer.h"
#include "TestUtils.h"

TEST(RotateTest, RotateFull)
{
    CircularBuffer<int> a(5);
    for (int i = 0; i < 5; i++)
        a.push_back(i+1);
    a.rotate(2);
    EXPECT_TRUE(isBufEqVector(a,std::vector<int>{3,4,5,1,2}));
}