#ifndef QUICK_H
#define QUICK_H

#include"gtest/gtest.h"
#include<vector>
#include<fstream>

using ::testing::Test;
using ::testing::TestCase;

template<typename T>
class Quick
{
public:
	void sort(std::vector<T> &a) {
		sort(a, 0, a.size() - 1);
	}
	void sort(std::vector<T> &a, int lo, int hi) {
		if (hi <= lo)
			return;
		int j = partition(a, lo, hi);
		sort(a, lo, j-1);
		sort(a, j + 1, hi);
	}
	int partition(std::vector<T> &a, int lo, int hi) {
		T p = a.at(lo);
		int i = lo, j = hi + 1;
		while (true) {
			while (less(a.at(++i),p))
				if (i == hi)
					break;
			while (less(p,a.at(--j)))
				if (j == lo)
					break;
			if (i >= j)
				break;
			exch(a, i, j);
		}
		exch(a, lo, j);
		return j;
	}
	T select(std::vector<T> &a, int k) {
		int lo=0, hi = a.size()-1;
		while (hi > lo)
		{
			int j = partition(a, lo, hi);
			if (j == k) return a.at(k);
			else if (j > k) hi = j - 1;
			else if (j < k) lo = j + 1;
		}
		return a.at(k);
	}
	bool isSorted(std::vector<T> &a) {
		for (auto i = a.begin(); i != a.end() - 1; i++) {
			if (less(*(i + 1), *i))
				return false;
		}
		return true;
	}
	void show(std::vector<T> &a) {
		for (auto i : a)
			std::cout << i << " ";
		std::cout << std::endl;
	}

private:
	bool less(T v, T w) {
		return v < w;
	}
	void exch(std::vector<T> &a, int i, int j) {
		T t = a.at(i);
		a.at(i) = a.at(j);
		a.at(j) = t;
	}
};
class QuickSortTest :public ::testing::Test {

protected:
	void SetUp() override {
		std::ifstream input_5K("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\5Kdoubles.txt");
		if (!input_5K.is_open())
			std::cout << "open file failure" << std::endl;
		double n;
		while (!input_5K.eof())
		{
			input_5K >> n;
			a_5K.push_back(n);
		}
		std::ifstream input_10K("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\10Kdoubles.txt");
		if (!input_10K.is_open())
			std::cout << "open file failure" << std::endl;
		while (!input_10K.eof())
		{
			input_10K >> n;
			a_10K.push_back(n);
		}
		std::ifstream input_100K("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\100Kdoubles.txt");
		if (!input_100K.is_open())
			std::cout << "open file failure" << std::endl;
		while (!input_100K.eof())
		{
			input_100K >> n;
			a_100K.push_back(n);
		}
	}

	void TearDown() override {

	}

	Quick<double> quick_double;
	std::vector<double> a_5K;
	std::vector<double> a_10K;
	std::vector<double> a_100K;

};


TEST_F(QuickSortTest, 5KRandData)
{
	quick_double.sort(a_5K);
	ASSERT_EQ(quick_double.isSorted(a_5K), true);
}

TEST_F(QuickSortTest, 10KRandData)
{
	quick_double.sort(a_10K);
	ASSERT_EQ(quick_double.isSorted(a_10K), true);
}

TEST_F(QuickSortTest, 100KRandData)
{
	quick_double.sort(a_100K);
	ASSERT_EQ(quick_double.isSorted(a_100K), true);
}

TEST_F(QuickSortTest, SelectMid)
{
	
	//ASSERT_EQ(quick_double.isSorted(a_100K), true);
	std::cout << quick_double.select(a_100K, 30000) << std::endl;
}

#endif // !TEST_H



