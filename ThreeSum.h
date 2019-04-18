#pragma once
#ifndef THREESUM_H
#define THREESUM_H

#include"gtest/gtest.h"
#include<fstream>
#include<vector>

using ::testing::Test;
using ::testing::TestCase;

class ThreeSum {
public:
	int count(std::vector<int> &a)
	{
		int cnt = 0;
		for (auto iti = a.begin(); iti != a.end()-2; iti++)
			for (auto itj = iti+1; itj != a.end()-1; itj++)
				for (auto itk = iti+2; itk != a.end(); itk++)
					if (*iti + *itj + *itk == 0)
						cnt++;
		return cnt;
	}
};

class TwoSum {
public:
	int count(std::vector<int> &a)
	{
		std::sort(a.begin(),a.end());
		BinarySearch BS;
		int cnt = 0;
		int N = a.size();
		for (int i = 0; i < N; i++)
			if (BS.rank(-a.at(i), a) > i)
				cnt++;
		return cnt;
	}
};

class NewThreeSum {
public:
	int count(std::vector<int> &a)
	{
		std::sort(a.begin(), a.end());
		BinarySearch BS;
		int cnt = 0;
		int N = a.size();
		for (int i = 0; i < N; i++)
			for (int j = i + 1; j < N; j++)
			{
				int k = BS.rank(-(a.at(i) + a.at(j)), a);
				if (k != i && k != j)
					cnt++;
			}
		return cnt;
	}
};

TEST(TwoSum, 1Kints)
{
	std::vector<int> ints;
	std::ifstream input("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\1Kints.txt");
	if (!input.is_open())
		std::cout << "open file failure" << std::endl;
	int n;
	while (!input.eof())
	{
		input >> n;
		ints.push_back(n);
	}
	input.close();
	TwoSum TS;
	std::cout << "1K : " << TS.count(ints) << std::endl;
}

TEST(NewThreeSum, 1Kints)
{
	std::vector<int> ints;
	std::ifstream input("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\1Kints.txt");
	if (!input.is_open())
		std::cout << "open file failure" << std::endl;
	int n;
	while (!input.eof())
	{
		input >> n;
		ints.push_back(n);
	}
	input.close();
	NewThreeSum TS;
	std::cout << "1K : " << TS.count(ints) << std::endl;
}

TEST(ThreeSum,1Kints)
{
	std::vector<int> ints;
	std::ifstream input("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\1Kints.txt");
	if (!input.is_open())
		std::cout << "open file failure" << std::endl;
	int n;
	while (!input.eof())
	{
		input >> n;
		ints.push_back(n);
	}
	input.close();
	ThreeSum TS;
	std::cout << "1K : " << TS.count(ints) << std::endl;
}

TEST(ThreeSum, 2Kints)
{
	std::vector<int> ints;
	std::ifstream input("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\2Kints.txt");
	if (!input.is_open())
		std::cout << "open file failure" << std::endl;
	int n;
	while (!input.eof())
	{
		input >> n;
		ints.push_back(n);
	}
	input.close();
	ThreeSum TS;
	std::cout << "2K : " << TS.count(ints) << std::endl;
}

TEST(ThreeSum, 4Kints)
{
	std::vector<int> ints;
	std::ifstream input("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\4Kints.txt");
	if (!input.is_open())
		std::cout << "open file failure" << std::endl;
	int n;
	while (!input.eof())
	{
		input >> n;
		ints.push_back(n);
	}
	input.close();
	ThreeSum TS;
	std::cout << "4K : " << TS.count(ints) << std::endl;
}

TEST(ThreeSum, 8Kints)
{
	std::vector<int> ints;
	std::ifstream input("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\8Kints.txt");
	if (!input.is_open())
		std::cout << "open file failure" << std::endl;
	int n;
	while (!input.eof())
	{
		input >> n;
		ints.push_back(n);
	}
	input.close();
	ThreeSum TS;
	std::cout << "8K : " << TS.count(ints) << std::endl;
}


#endif // !TEST_H
