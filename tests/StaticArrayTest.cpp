/*
 * StaticArrayTest.cpp
 *
 *  Created on: 2017/05/19
 *      Author: 010880016
 */

#include "gtest/gtest.h"
#include "StaticArray.hpp"

class StaticArrayTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    StaticArray<int, 10> array;
};

TEST_F(StaticArrayTest, constructer)
{
    EXPECT_EQ(0, static_cast<int>(array.size()));
//	EXPECT_EQ(0, array.back());
}

TEST_F(StaticArrayTest, pop_backFromEmptyArray)
{
    array.pop_back();

    EXPECT_EQ(0, static_cast<int>(array.size()));
//	EXPECT_EQ(0, array.back());
}

TEST_F(StaticArrayTest, addOneItem)
{
    array.push_back(10);

    EXPECT_EQ(1, static_cast<int>(array.size()));
    EXPECT_EQ(10, array.back());
    EXPECT_EQ(10, array.front());
}

TEST_F(StaticArrayTest, push_frontOneItemToEmptyArray)
{
    array.push_front(10);

    EXPECT_EQ(1, static_cast<int>(array.size()));
    EXPECT_EQ(10, array.front());
    EXPECT_EQ(10, array.back());
}

TEST_F(StaticArrayTest, pop_backFromSizeOne)
{
    array.push_back(10);

    array.pop_back();

    EXPECT_EQ(0, static_cast<int>(array.size()));
//	EXPECT_EQ(10, array.back());
}

TEST_F(StaticArrayTest, frontFromOneItem)
{
    array.push_back(10);
    int result = array.front();

    EXPECT_EQ(1, static_cast<int>(array.size()));
    EXPECT_EQ(10, result);
}

TEST_F(StaticArrayTest, frontFromTwoItem)
{
    array.push_back(10);
    array.push_back(20);

    int result = array.front();

    EXPECT_EQ(2, static_cast<int>(array.size()));
    EXPECT_EQ(10, result);
}

TEST_F(StaticArrayTest, pop_frontFromTwoItem)
{
    array.push_back(10);
    array.push_back(20);

    array.pop_front();

    int result = array.front();

    EXPECT_EQ(1, static_cast<int>(array.size()));
    EXPECT_EQ(20, result);
}

TEST_F(StaticArrayTest, push_backMaxNumberOfItems)
{
    for (int i = 0; i < 10; i++)
    {
        array.push_back(i + 1);
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ((10 - i), static_cast<int>(array.size()));
        EXPECT_EQ((i + 1), array.front());
        array.pop_front();
    }
    EXPECT_EQ(0, static_cast<int>(array.size()));
}

TEST_F(StaticArrayTest, push_frontMaxNumberOfItems)
{
    for (int i = 0; i < 10; i++)
    {
        array.push_front(i + 1);
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ((10 - i), static_cast<int>(array.size()));
        EXPECT_EQ((i + 1), array.back());
        array.pop_back();
    }
    EXPECT_EQ(0, static_cast<int>(array.size()));
}

TEST_F(StaticArrayTest, push_frontToFullArray)
{
    for (int i = 0; i < 10; i++)
    {
        array.push_front(i + 1);
    }

    array.push_front(11);

    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ((10 - i), static_cast<int>(array.size()));
        EXPECT_EQ((i + 1), array.back());
        array.pop_back();
    }

    EXPECT_EQ(0, static_cast<int>(array.size()));
}

TEST_F(StaticArrayTest, push_backToFullArray)
{
    for (int i = 0; i < 10; i++)
    {
        array.push_front(i + 1);
    }

    array.push_back(11);

    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ((10 - i), static_cast<int>(array.size()));
        EXPECT_EQ((i + 1), array.back());
        array.pop_back();
    }
    EXPECT_EQ(0, static_cast<int>(array.size()));
}

TEST_F(StaticArrayTest, doForEachWithLambda)
{
    for (int i = 1; i <= 10; i++)
    {
        array.push_back(i);
    }

    int sum = 0;
    array.doForEach([&sum](int x)
    {   sum += x;});

    EXPECT_EQ(55, sum);
}

TEST_F(StaticArrayTest, doForEachWithFunctionObject)
{
    for (int i = 1; i <= 10; i++)
    {
        array.push_back(i);
    }

    class FunctionA
    {
    private:
        int& sum;
    public:
        FunctionA(int& sum)
                : sum { sum }
        {
        }

        void operator()(int x)
        {
            sum += x;
        }
    };

    int sum = 0;
    array.doForEach(FunctionA { sum });

    EXPECT_EQ(55, sum);
}

TEST_F(StaticArrayTest, RangeBasedFor)
{
    for (int i = 1; i <= 10; i++)
    {
        array.push_back(i);
    }

    int sum = 0;
    for (const auto& each : array)
    {
        sum += each;
    }

    EXPECT_EQ(55, sum);
}

TEST_F(StaticArrayTest, loopByConstIterator)
{
    for (int i = 1; i <= 10; i++)
    {
        array.push_back(i);
    }

    int sum = 0;
    for (auto position = array.cbegin(); position != array.cend(); ++position)
    {
        sum += *position;
    }

    EXPECT_EQ(55, sum);
}

TEST_F(StaticArrayTest, loopByIterator)
{
    for (int i = 1; i <= 10; i++)
    {
        array.push_back(i);
    }

    int sum = 0;
    for (auto position = array.begin(); position != array.end(); ++position)
    {
        sum += *position;
        *position *= 2;
    }

    EXPECT_EQ(55, sum);

    int i = 1;
    for (const auto& each : array)
    {
        EXPECT_EQ(i * 2, each);
        i += 1;
    }
}

// End of File
