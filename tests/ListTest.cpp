/*
 * ListTest.cpp
 *
 *  Created on: 2017/06/26
 *      Author: osamu
 */

#include "List.hpp"
#include "gtest/gtest.h"

class ListTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        list.getAllocator().resetMemory();
        list.getAllocator().initializeMemory(10);
    }

    virtual void TearDown()
    {
        list.clear();
        list.getAllocator().resetMemory();
    }

    List<int> list;
};

TEST_F(ListTest, constructer)
{
    EXPECT_EQ(0U, list.size());
    EXPECT_EQ(10U, list.getAllocator().remains());
}

TEST_F(ListTest, push_frontToEmptyList)
{
    list.push_front(1);

    EXPECT_EQ(1, static_cast<int>(list.size()));
    EXPECT_EQ(1, list.front());
    EXPECT_EQ(9U, list.getAllocator().remains());
}

TEST_F(ListTest, push_frontMaxSize)
{
    for (int i = 0; i < 10; i++)
    {
        list.push_front(i);
        EXPECT_EQ(static_cast<size_t>(10 - i - 1), list.getAllocator().remains());
    }

    for (int i = 10; i > 0; i--)
    {
        EXPECT_EQ(i - 1, list.front());
        list.pop_front();
        EXPECT_EQ(static_cast<size_t>(i - 1), list.size());
    }
    EXPECT_EQ(10U, list.getAllocator().remains());
}

TEST_F(ListTest, push_backToEmptyList)
{
    list.push_back(1);

    EXPECT_EQ(1U, list.size());
    EXPECT_EQ(1, list.back());
    EXPECT_EQ(9U, list.getAllocator().remains());
}

TEST_F(ListTest, push_backMaxSize)
{
    for (int i = 0; i < 10; i++)
    {
        list.push_back(i);
        EXPECT_EQ(static_cast<size_t>(10 - i - 1), list.getAllocator().remains());
    }

    for (int i = 10; i > 0; i--)
    {
        EXPECT_EQ(i - 1, list.back());
        list.pop_back();
        EXPECT_EQ(static_cast<size_t>(i - 1), list.size());
    }
    EXPECT_EQ(10U, list.getAllocator().remains());
}

TEST_F(ListTest, push_frontAndPop_back)
{
    for (int i = 0; i < 10; i++)
    {
        list.push_front(i);
        EXPECT_EQ(static_cast<size_t>(10 - i - 1), list.getAllocator().remains());
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ(i, list.back());
        list.pop_back();
        EXPECT_EQ(static_cast<size_t>(10 - i - 1), list.size());
    }
    EXPECT_EQ(10U, list.getAllocator().remains());
}

TEST_F(ListTest, push_backAndPop_front)
{
    for (int i = 0; i < 10; i++)
    {
        list.push_back(i);
        EXPECT_EQ(static_cast<size_t>(10 - i - 1), list.getAllocator().remains());
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ(i, list.front());
        list.pop_front();
        EXPECT_EQ(static_cast<size_t>(10 - i - 1), list.size());
    }
    EXPECT_EQ(10U, list.getAllocator().remains());
}

TEST_F(ListTest, push_backAndPop_frontAndPush_back)
{
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            list.push_back(i);
            EXPECT_EQ(static_cast<size_t>(10 - i - 1), list.getAllocator().remains());
        }

        for (int i = 0; i < 10; i++)
        {
            EXPECT_EQ(i, list.front());
            list.pop_front();
            EXPECT_EQ(static_cast<size_t>(10 - i - 1), list.size());
        }
        EXPECT_EQ(10U, list.getAllocator().remains());
    }
}

TEST_F(ListTest, pop_frontFromEmptyList)
{
    list.pop_front();

    EXPECT_EQ(0U, list.size());
    EXPECT_EQ(10U, list.getAllocator().remains());
}

TEST_F(ListTest, pop_backFromEmptyList)
{
    list.pop_back();

    EXPECT_EQ(0U, list.size());
    EXPECT_EQ(10U, list.getAllocator().remains());
}

class ListTest2 : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        list.getAllocator().initializeMemory();
    }

    virtual void TearDown()
    {
        list.clear();
        list.getAllocator().resetMemory();
    }

    List<int> list;
};

TEST_F(ListTest2, constructer)
{
    EXPECT_EQ(0U, list.size());
    EXPECT_EQ(100U, list.getAllocator().remains());
}

TEST_F(ListTest2, resetAllocatorMemoryAndGetRemains)
{
    list.getAllocator().resetMemory();
    EXPECT_EQ(0U, list.size());
    EXPECT_EQ(0U, list.getAllocator().remains());
}

TEST_F(ListTest2, resetAllocatorMemoryAndClear)
{
    for (int i = 0; i < 5; i++)
    {
        list.push_back(i);
    }
    list.getAllocator().resetMemory();

    list.clear();
    EXPECT_EQ(0U, list.size());
    EXPECT_EQ(0U, list.getAllocator().remains());
}

TEST_F(ListTest2, resetAllocatorMemoryAndPushBack)
{
    for (int i = 0; i < 5; i++)
    {
        list.push_back(i);
    }

    list.getAllocator().resetMemory();

    list.push_back(5);

    EXPECT_EQ(5U, list.size());
    EXPECT_EQ(0U, list.getAllocator().remains());
}

TEST_F(ListTest2, putbackMaxCapacityAnd1PushBack)
{
    for (int i = 0; i < 100; i++)
    {
        list.push_back(i);
    }

    list.push_back(100);

    EXPECT_EQ(100U, list.size());
    EXPECT_EQ(0U, list.getAllocator().remains());
}

TEST_F(ListTest2, iterator)
{
    for (int i = 0; i < 10; i++)
    {
        list.push_back(i + 1);
    }

    List<int> result;
    for (const auto& each : list)
    {
        result.push_back(each * 2);
    }

    int i = 1;
    for (const auto& each : result)
    {
        EXPECT_EQ(i * 2, each);
        i++;
    }
}

TEST_F(ListTest2, constIteratorDereferenceForModify)
{
    for (int i = 0; i < 10; i++)
    {
        list.push_back(i);
    }

    List<int>::const_iterator it = list.begin();
    // invoking converting constructor of const_iterator

    //*it = 100; can't compile. it's OK because it is const_iterator.

    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ(i, *it);
        it++;
    }
    EXPECT_EQ(it, list.end());
}

TEST_F(ListTest2, constIteratorDereferenceForModify2)
{
    for (int i = 0; i < 10; i++)
    {
        list.push_back(i);
    }

    List<int>::const_iterator it = const_cast<const List<int>&>(list).begin();
    // invoke const_iterator begin() const;

    //*it = 100; can't compile. it's OK because it is const_iterator.

    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ(i, *it);
        it++;
    }
    EXPECT_EQ(it, list.end());
}

class ListContents {
private:
    int x;

    ListContents(); // List need not default constructor

public:
    ListContents(int x) : x(x) {}

    ListContents(const ListContents& other) : x(other.x) {};
    ListContents& operator=(const ListContents& other) { x = other.x; return *this; }

    int getX() const { return x; }
};

TEST(ListTestXX, ListWithNoDefaultConstructorAssignment)
{
    List<ListContents> l;
    l.getAllocator().initializeMemory(20);

    EXPECT_EQ(0U, l.size());

    for (int i = 0; i < 10; i++)
    {
        l.push_back(ListContents(i));
    }

    EXPECT_EQ(10U, l.size());

    l.front() = ListContents(10);
    l.back() = ListContents(20);

    int i = 0;
    for (const ListContents& each : l)
    {
        if (i == 0)
        {
            EXPECT_EQ(10, each.getX());
        }
        else if (i == 9)
        {
            EXPECT_EQ(20, each.getX());
        }
        else
        {
            EXPECT_EQ(i , each.getX());
        }
        i++;
    }

    EXPECT_EQ(10, l.front().getX());
    EXPECT_EQ(20, l.back().getX());
}

// End of File
