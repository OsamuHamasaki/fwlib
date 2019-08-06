/*
 * TestExample.cpp
 *
 *  Created on: 2019/07/25
 *      Author: 010880016
 */

#include <gtest/gtest.h>
#include "Ecc.hpp"

TEST(EccTest, test1)
{
	Ecc<int> target;

	target = 1;

	EXPECT_EQ(1, int(target));
}

TEST(EccTest, test2)
{
	Ecc<int> target = 1;

	EXPECT_EQ(1, int(target));
}

TEST(EccTest, test3)
{
	Ecc<int> target = 1;

	target.addNoiseToOriginal(2);

	EXPECT_EQ(1, int(target));
}

TEST(EccTest, test4)
{
	Ecc<int> target = 1;

	target.addNoiseToCopy1(3);
	EXPECT_EQ(1, int(target));

	target.addNoiseToOriginal(2);
	EXPECT_EQ(1, int(target));
}

TEST(EccTest, test5)
{
	Ecc<int> target = 1;

	target.addNoiseToCopy2(3);
	EXPECT_EQ(1, int(target));

	target.addNoiseToOriginal(2);
	EXPECT_EQ(1, int(target));
}

TEST(EccTest, test6)
{
	Ecc<int> target = 1;
	int value = int(target);

	EXPECT_EQ(1, value);
}

TEST(EccTest, test7)
{
	Ecc<int> target = 1;
	int value = target;

	EXPECT_EQ(1, value);
}

TEST(EccTest, test8)
{
	int plainValue = 1;
	Ecc<int*> target;

	target = &plainValue;

	*target = 2;
	EXPECT_EQ(2, plainValue);
}

TEST(EccTest, test9)
{
	int plainValue = 1;
	Ecc<int*> target = &plainValue;

	*target = 2;
	EXPECT_EQ(2, plainValue);
}

struct ForTest10
{
	int a;
};

TEST(EccTest, test10)
{
	ForTest10 plainValue;
	plainValue.a = 1;

	Ecc<ForTest10*> target = &plainValue;

	target->a = 2;
	EXPECT_EQ(2, plainValue.a);
}

TEST(EccTest, test11)
{
	ForTest10 plainValue;
	plainValue.a = 1;

	Ecc<ForTest10*> target = &plainValue;

	(*target).a = 2;
	EXPECT_EQ(2, plainValue.a);
}

TEST(EccTest, test12)
{
	int plainValue1 = 1;
	int plainValue2 = 2;
	Ecc<int*> target = &plainValue1;

	target.addNoiseToOriginal(&plainValue2);

	*target = 3;

	EXPECT_EQ(3, plainValue1);
	EXPECT_EQ(2, plainValue2);
}

TEST(EccTest, test13)
{
	ForTest10 plainValue1;
	ForTest10 plainValue2;
	Ecc<ForTest10*> target = &plainValue1;

	plainValue1.a = 1;
	plainValue2.a = 2;

	target.addNoiseToOriginal(&plainValue2);

	target->a = 3;

	EXPECT_EQ(3, plainValue1.a);
	EXPECT_EQ(2, plainValue2.a);
}

TEST(EccTest, test14)
{
	int plainValue1 = 1;
	Ecc<int*> target = &plainValue1;
	int* pointer = target;

	EXPECT_EQ(pointer, &plainValue1);
}

int funcForTest15(int* p)
{
	return *p;
}

TEST(EccTest, test15)
{
	int plainValue1 = 1;
	Ecc<int*> target = &plainValue1;

	EXPECT_EQ(funcForTest15(target), plainValue1);
}

TEST(EccTest, test16)
{
	Ecc<int> original = 1;
	Ecc<int> copy = original;

	EXPECT_EQ(1, int(copy));
}

TEST(EccTest, test17)
{
	Ecc<int> original = 1;
	Ecc<int> copy;

	original.addNoiseToOriginal(3);

	copy= original;

	EXPECT_EQ(1, int(copy));
}
