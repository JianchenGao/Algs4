#ifndef SELECTION_H
#define SELECTION_H

#include"gtest/gtest.h"
#include<vector>

using ::testing::Test;
using ::testing::TestCase;

template<typename T>
class Selection
{
public:
	void sort(std::vector<T> &a) {
		int N = a.size();
		for (int i = 0; i < N; i++)
		{
			int min = i;
			for (int j = i + 1; j < N; j++)
				if (less(a.at(j), a.at(min))) min = j;
			exch(a, i, min);
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

TEST(SelectionSort, SelectionWork)
{
	std::vector<int> a{2,5,21,5,2,6,3,7,4,1,7,8,9,34,2,1};
	Selection<int> selection;
	selection.sort(a);
	ASSERT_EQ(selection.isSorted(a), true);
}

TEST(SelectionSort, SelectionRandData)
{
	std::ifstream input("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\5Kdoubles.txt");
	if (!input.is_open())
		std::cout << "open file failure" << std::endl;
	std::vector<double> a;
	double n;
	while (!input.eof())
	{
		input >> n;
		a.push_back(n);
	}
	Selection<double> selection;
	selection.sort(a);
	ASSERT_EQ(selection.isSorted(a), true);
}

#endif // !TEST_H

