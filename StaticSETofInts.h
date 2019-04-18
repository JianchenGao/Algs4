#include <vector>
#include <iostream>
#include <algorithm>
#include "gtest/gtest.h"

using ::testing::Test;
using ::testing::TestCase;

class StaticSETofInts {
public:
	StaticSETofInts(std::vector<int> &keys) {
		for (auto k : keys)
			a.push_back(k);
		sort(a.begin(),a.end());
	}
	bool contains(int key) {
		return rank(key) != -1;
	}
	int rank(int key)
	{
		int lo = 0;
		int hi = a.size() - 1;
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
private:
	std::vector<int> a;
};


class StaticSETofIntsTest :public ::testing::Test {

protected:
	void SetUp() override {
	}

	void TearDown() override {

	}

};

TEST_F(StaticSETofIntsTest, StaticSETofIntsAlgo) {
	std::vector<int> alist{ 9,6,7,28,45,14,25,26,1,2,4 };
	StaticSETofInts s1(alist);
	ASSERT_EQ(s1.contains(1), true);
	ASSERT_EQ(s1.contains(45), true);
	ASSERT_EQ(s1.contains(9), true);
	ASSERT_EQ(s1.contains(10), false);
	ASSERT_EQ(s1.contains(300), false);
}


