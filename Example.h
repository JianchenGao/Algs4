#ifndef EXAMPLE_H
#define EXAMPLE_H

#include"gtest/gtest.h"
#include<vector>

using ::testing::Test;
using ::testing::TestCase;

template<typename T>
class Example
{
public:
	void sort(std::vector<T> a) {

	}
	bool isSorted(std::vector<T> a){
		for (auto i = a.begin(); i != a.end() - 1;i++) {
			if (less(*(i + 1), *i))
				return false;
		}
		return true;
	}

private:
	bool less(T v, T w) {
		return v < w;
	}
	void exch(std::vector<T> a, int i, int j) {
		T t = a.at(i);
		a.at(i) = a.at(j);
		a.at(j) = t;
	}
};


#endif // !TEST_H
