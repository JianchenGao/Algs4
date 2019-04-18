#ifndef PQSORT_H
#define PQSORT_H

#include"gtest/gtest.h"
#include<vector>
#include<fstream>

using ::testing::Test;
using ::testing::TestCase;

template<typename T>
class PQSort
{
public:
	void sort(std::vector<T> &a) {
		int N = a.size()-1;
		for (int k = N / 2; k >= 1; k--)
			sink(a, k, N);
		while (N > 1)
		{
			exch(a, 1, N--);
			sink(a, 1, N);
		}
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
	void sink(std::vector<T> &a, int k, int N) {
		while (2 * k <= N) {
			int j = 2 * k;
			if ( j < N && less(a.at(j), a.at(j + 1)) ) j++;
			if ( !less(a.at(k), a.at(j)) ) break;
			exch(a, k, j);
			k = j;
		}
	}
};
class PQSortTest :public ::testing::Test {

protected:
	void SetUp() override {
		a_5K.push_back(0);
		a_10K.push_back(0);
		a_100K.push_back(0);

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

	PQSort<double> PQsort_double;
	std::vector<double> a_5K;
	std::vector<double> a_10K;
	std::vector<double> a_100K;

};


TEST_F(PQSortTest, 5KRandData)
{
	PQsort_double.sort(a_5K);
	ASSERT_EQ(PQsort_double.isSorted(a_5K), true);
}

TEST_F(PQSortTest, 10KRandData)
{
	PQsort_double.sort(a_10K);
	ASSERT_EQ(PQsort_double.isSorted(a_10K), true);
}

TEST_F(PQSortTest, 100KRandData)
{
	PQsort_double.sort(a_100K);
	ASSERT_EQ(PQsort_double.isSorted(a_100K), true);
}

#endif // !TEST_H

