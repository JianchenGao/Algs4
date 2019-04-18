#ifndef MERGEBU_H
#define MERGEBU_H

#include"gtest/gtest.h"
#include<vector>
#include<fstream>

using ::testing::Test;
using ::testing::TestCase;

template<typename T>
class MergeBU
{
public:
	void sort(std::vector<T> &a) {
		for (auto d : a)
			aux.push_back(d);
		int N = a.size();
		for (int sz = 1; sz < N; sz = sz + sz)
			for (int lo = 0; lo < N - sz; lo += sz + sz)
				merge(a, lo, lo + sz - 1, std::min(lo + sz + sz - 1, N - 1));
	}
	void merge(std::vector<T> &a, int lo, int mid, int hi) {
		for (int n = lo; n <= hi; n++)
			aux.at(n) = a.at(n);
		int i = lo, j = mid + 1;
		for (int k = lo; k <= hi; k++)
			if (i > mid) a.at(k) = aux.at(j++);
			else if (j > hi) a.at(k) = aux.at(i++);
			else if (less(aux.at(j), aux.at(i))) a.at(k) = aux.at(j++);
			else a.at(k) = aux.at(i++);
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
class MergeBUSortTest :public ::testing::Test {

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

	MergeBU<double> merge_double;
	std::vector<double> a_5K;
	std::vector<double> a_10K;
	std::vector<double> a_100K;

};


TEST_F(MergeBUSortTest, 5KRandData)
{
	merge_double.sort(a_5K);
	ASSERT_EQ(merge_double.isSorted(a_5K), true);
}

TEST_F(MergeBUSortTest, 10KRandData)
{
	merge_double.sort(a_10K);
	ASSERT_EQ(merge_double.isSorted(a_10K), true);
}

TEST_F(MergeBUSortTest, 100KRandData)
{
	merge_double.sort(a_100K);
	ASSERT_EQ(merge_double.isSorted(a_100K), true);
}

#endif // !TEST_H


