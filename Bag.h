#pragma once
#include "gtest/gtest.h"
#include"Stack.h"		//�ṩ��Node�ṹ
#include"StackIterator.h"	//��Stack���õ�����

using ::testing::Test;
using ::testing::TestCase;

template<class>struct Node;

template <typename Item> class Bag
{
public:
	typedef StackIterator<Item> iterator;
	Bag() { init(); }
	~Bag() {}
	void add(Item item)
	{
		Node<Item> *oldhead = head;
		head = new Node<Item>;
		head->item = item;
		head->next = oldhead;
		N++;
	}
	bool isEmpty()
	{
		return N == 0;
	}
	int size()
	{
		return N;
	}
	iterator begin() {
		return iterator(head);
	}
	iterator end() {
		return iterator(tail);
	}

private:

	void init() {
		N = 0;
		head = new Node<Item>;
		tail = head;
		head->next = nullptr;
	}
	Node<Item> *head;		//ͷ���
	Node<Item> *tail;		//β���
	int N;					//�ڵ���
};

class BagTest :public ::testing::Test {

protected:
	void SetUp() override {
		numbers = new Bag<double>;
	}

	void TearDown() override {

	}

	Bag<double> *numbers;
};

TEST_F(BagTest, isEmptyTest) {
	ASSERT_EQ(numbers->isEmpty(), true);
}

TEST_F(BagTest, BagWork) {
	std::vector<int> a{1,2,3,4,0,5,6,7,8,9,10};
	for (auto i : a)
		numbers->add(i);
	int N = numbers->size();
	ASSERT_EQ(N, 11);

	double sum = 0.0;
	for (double x : *numbers)	
		sum += x;
	double mean = sum / N;
	ASSERT_EQ(mean, 5);
}

