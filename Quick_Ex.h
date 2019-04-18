#ifndef QUICK_EX_H
#define QUICK_EX_H

#include"gtest/gtest.h"
#include<vector>
#include<fstream>
#include"Insertion.h"

using ::testing::Test;
using ::testing::TestCase;

template<typename T>
class Quick_Ex
{
public:
	void sort(std::vector<T> &a,int m) {
		insertion = new Insertion<T>;
		sort(a, 0, a.size() - 1,m);
	}
	void sort(std::vector<T> &a, int lo, int hi,int m) {
		int M = m;
		if (hi <= lo + M) {
			insertion->sort(a, lo, hi);
			return;
		}
		int j = partition(a, lo, hi);
		sort(a, lo, j - 1, M);
		sort(a, j + 1, hi, M);
	}
	int partition(std::vector<T> &a, int lo, int hi) {
		T p = a.at(lo);
		int i = lo, j = hi + 1;
		while (true) {
			while (less(a.at(++i), p))
				if (i == hi)
					break;
			while (less(p, a.at(--j)))
				if (j == lo)
					break;
			if (i >= j)
				break;
			exch(a, i, j);
		}
		exch(a, lo, j);
		return j;
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
	Insertion<T> *insertion;
	std::vector<T> aux;
	bool less(T v, T w) {
		return v < w;
	}
	void exch(std::vector<T> &a, int i, int j) {
		T t = a.at(i);
		a.at(i) = a.at(j);
		a.at(j) = t;
	}
};
class Quick_ExSortTest :public ::testing::TestWithParam<int>{

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

	Quick_Ex<double> quick_Ex_double;
	std::vector<double> a_5K;
	std::vector<double> a_10K;
	std::vector<double> a_100K;

};

INSTANTIATE_TEST_CASE_P(Mvalue, Quick_ExSortTest,::testing::Range(6,10,2));

TEST_P(Quick_ExSortTest, 5KRandData)
{
	quick_Ex_double.sort(a_5K, GetParam());
	ASSERT_EQ(quick_Ex_double.isSorted(a_5K), true);
}

TEST_P(Quick_ExSortTest, 10KRandData)
{
	quick_Ex_double.sort(a_10K, GetParam());
	ASSERT_EQ(quick_Ex_double.isSorted(a_10K), true);
}

TEST_P(Quick_ExSortTest, 100KRandData)
{
	quick_Ex_double.sort(a_100K, GetParam());
	ASSERT_EQ(quick_Ex_double.isSorted(a_100K), true);
}

#endif // !TEST_H



