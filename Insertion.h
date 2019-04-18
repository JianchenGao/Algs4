#ifndef INSERTION_H
#define INSERTION_H

#include"gtest/gtest.h"
#include<vector>
#include<fstream>

using ::testing::Test;
using ::testing::TestCase;

template<typename T>
class Insertion
{
public:
	void sort(std::vector<T> &a) {
		int N = a.size();
		for (int i = 1; i < N; i++)
		{
			for (int j = i; j > 0 && less(a.at(j), a.at(j - 1)); j--)
				exch(a, j, j-1);
		}
	}
	void sort(std::vector<T> &a,int lo,int hi) {
		for (int i = lo+1; i < hi+1; i++)
		{
			for (int j = i; j > lo && less(a.at(j), a.at(j - 1)); j--)
				exch(a, j, j - 1);
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
};

class InsertionSortTest :public ::testing::Test {

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

	Insertion<double> insertion_double;
	std::vector<double> a_5K;
	std::vector<double> a_10K;
	std::vector<double> a_100K;

};


TEST_F(InsertionSortTest, 5KRandData)
{
	insertion_double.sort(a_5K);
	ASSERT_EQ(insertion_double.isSorted(a_5K), true);
}

TEST_F(InsertionSortTest, 10KRandData)
{
	insertion_double.sort(a_10K);
	ASSERT_EQ(insertion_double.isSorted(a_10K), true);
}

//TEST_F(InsertionSortTest, 100KRandData)
//{
//	insertion_double.sort(a_100K);
//	ASSERT_EQ(insertion_double.isSorted(a_100K), true);
//}


#endif // !TEST_H


