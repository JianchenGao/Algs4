#pragma once
#ifndef QUEUE_H
#define QUEUE_H

#include"gtest/gtest.h"
#include"Stack.h"		//提供了Node结构
#include"StackIterator.h"	//与Stack共用迭代器
#include<string>

using ::testing::Test;
using ::testing::TestCase;

template<class>struct Node;

template <typename Item> class Queue
{
public:
	typedef StackIterator<Item> iterator;		//保持迭代器名称一致

	Queue()
	{
		init();
	}
	~Queue()
	{

	}

	void enqueue(Item item)
	{	//入队操作
		Node<Item> *oldtail = tail;
		tail = new Node<Item>;
		oldtail->item = item;
		oldtail->next = tail;
		N++;
	}
	Item dequeue()
	{	//出队操作
		Node<Item> *oldhead = head;
		Item item = head->item;
		head = head->next;
		delete oldhead;
		N--;
		return item;
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
	Node<Item> *head;		//头结点
	Node<Item> *tail;		//尾结点
	int N;					//节点数
};

class QueueTest :public ::testing::Test {

protected:
	void SetUp() override {
		q = new Queue<std::string>;
	}

	void TearDown() override {
		delete q;
	}

	Queue<std::string> *q;
};

TEST_F(QueueTest, QueueisEmpty) {
	ASSERT_EQ(q->isEmpty(), true);
}

TEST_F(QueueTest, QueueWork) {
	std::vector<std::string> s{"H","e","l","l","o","!","?"};
	for (auto i : s)
		q->enqueue(i);

	ASSERT_EQ(q->isEmpty(), false);

	int N = q->size();
	ASSERT_EQ(N,7);

	std::vector<std::string> a;
	for (auto i : *q)
		a.push_back(i);
	ASSERT_EQ(a,s);
	
	a.clear();
	for (int i = 0; i < N; i++)
	{
		a.push_back(q->dequeue());
	}
	ASSERT_EQ(a, s);
	ASSERT_EQ(q->isEmpty(), true);
}

#endif // !QUEUE_H
