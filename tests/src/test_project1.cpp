#include <iostream>
#include "gtest/gtest.h"

TEST(IndependentMethod, ResetsToZero) {
	int i = 3;
	EXPECT_EQ(3, i);

	i = 12;
	EXPECT_EQ(3,i);
}

