#pragma once
#include <vector>
#include <iostream>
#include "gtest/gtest.h"

using ::testing::Test;
using ::testing::TestCase;

class BinarySearch{
public:
	int rank(int key, std::vector<int> &a)
	{
		int lo = 0;
		int hi = a.size()-1;
		while (lo <= hi)
		{
			int mid = lo + (hi - lo) / 2;
			if (key < a.at(mid)) 
				hi = mid - 1;
			else if (key > a.at(mid))
				lo = mid + 1;
			else return mid;
		}
		return -1;
	}
};


class BinarySearchTest :public ::testing::Test {
	
protected:
	void SetUp() override {
		b1 = new BinarySearch;
	}

	void TearDown() override {

	}

	BinarySearch *b1;
};

TEST_F(BinarySearchTest, BinarySearchAlgo) {
	std::vector<int> alist{ 1,2,4,6,7,9,14,25,26,28,45 };
	ASSERT_EQ(b1->rank(1, alist), 0);
	ASSERT_EQ(b1->rank(45, alist), 10);
	ASSERT_EQ(b1->rank(9, alist), 5);
	ASSERT_EQ(b1->rank(10, alist), -1);
}


