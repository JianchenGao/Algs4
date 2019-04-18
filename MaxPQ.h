#pragma once
#ifndef MAXPQ_H
#define MAXPQ_H

#include"gtest/gtest.h"
#include<vector>


using ::testing::Test;
using ::testing::TestCase;

template<typename Key>
class MaxPQ {
public:
	MaxPQ() {
		pq.push_back(0);	//位置0不用，先占用
	}
	MaxPQ(int max) {
		pq.push_back(0);	//位置0不用，先占用
	}
	MaxPQ(std::vector<Key> &a) {
		pq.push_back(0);
		for (auto i : a)
			Insert(i);
	}
	void Insert(Key v) {
		pq.push_back(v);
		N++;
		swim(N);
	}
	Key max() {}
	Key delMax() {
		Key max = pq.at(1);
		exch(1, N--);
		pq.pop_back();
		sink(1);
		return max;
	}
	bool isEmpty() { return N == 0; }
	int size() { return N; }

private:
	std::vector<Key> pq;
	int N = 0;
	bool less(int i, int j) { return pq.at(i) < pq.at(j); }
	void exch(int i, int j) {
		Key t = pq.at(i);
		pq.at(i) = pq.at(j);
		pq.at(j) = t;
	}
	void swim(int k) {
		while (k > 1 && less(k / 2, k)) {
			exch(k / 2, k);
			k = k / 2;
		}
	}
	void sink(int k) {
		while (2*k  <= N) {
			int j = 2*k;
			if (j < N&&less(j, j + 1)) j++;
			if (!less(k, j)) break;
			exch(k, j);
			k = j;
		}
	}
};

TEST(MaxPQTest, MaxPQWork1)
{
	std::vector<int> a{3,4,1,6,8,1,3,12,3,4,0,1};
	MaxPQ<int> p;
	ASSERT_EQ(p.isEmpty(), true);

	for (int i = 0; i < 5; i++)
		p.Insert(a.at(i));
	ASSERT_EQ(p.delMax(), 8);
	ASSERT_EQ(p.size(), 4);
	ASSERT_EQ(p.delMax(), 6);
	
	for (int i = 5; i < 10; i++)
		p.Insert(a.at(i));
	ASSERT_EQ(p.delMax(), 12);
	ASSERT_EQ(p.delMax(), 4);
	ASSERT_EQ(p.size(), 6);
}

TEST(MaxPQTest, MaxPQWork2)
{
	std::vector<int> a{3,4,1,6,8,1,3,12,3,4,0,1 };
	MaxPQ<int> p(a);
	ASSERT_EQ(p.isEmpty(), false);

	ASSERT_EQ(p.delMax(), 12);
	ASSERT_EQ(p.size(), 11);
	ASSERT_EQ(p.delMax(), 8);

	ASSERT_EQ(p.delMax(), 6);
	ASSERT_EQ(p.delMax(), 4);
	ASSERT_EQ(p.size(), 8);
}

#endif // !TEST_H
