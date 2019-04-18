#pragma once
#ifndef STACK_H
#define STACK_H

#include"StackIterator.h"
#include"gtest/gtest.h"

using ::testing::Test;
using ::testing::TestCase;

template<class T>
struct Node		//������
{
	T item;
	Node *next;
};

template <typename Item> class Stack
{
public:
	typedef StackIterator<Item> iterator;		//���ֵ���������һ��
	Stack()
	{
		init();
	}
	~Stack()
	{

	}
	void push(Item item) 
	{	//��ջ����
		Node<Item> *oldhead = head;
		head = new Node<Item>;
		head->item = item;
		head->next = oldhead;
		N++;
	}
	Item pop()
	{	//��ջ����
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
	Node<Item> *head;		//ͷ���
	Node<Item> *tail;		//β���
	int N;					//�ڵ���
};

class StackTest :public ::testing::Test {

protected:
	void SetUp() override {
		stack = new Stack<int>;
	}

	void TearDown() override {

	}

	Stack<int> *stack;
};

TEST_F(StackTest, StackEmpty) {
	ASSERT_EQ(stack->isEmpty(), true);
}

TEST_F(StackTest, StackWork) {
	std::vector<int> v{1,2,3,4,5,6,7,8,9,10};
	std::vector<int> vr{10,9,8,7,6,5,4,3,2,1};

	for (auto i : v)
		stack->push(i);

	ASSERT_EQ(stack->isEmpty(),false);
	ASSERT_EQ(stack->size(), v.size());


	std::vector<int> a;
	for (auto s : *stack)
		a.push_back(s);
	ASSERT_EQ(a,vr);

	std::vector<int> b;
	int n = stack->size();		//��������ʱ��Ӧ�øı�������С
	for (int i = 0; i < n; i++)
	{
		b.push_back(stack->pop());
	}
	ASSERT_EQ(b, vr);
}

TEST_F(StackTest, StackMemoryTest) {
	for (auto i=0; i<100000;i++)
		stack->push(i);
	for (int i = 0; i < 100000; i++)
	{
		stack->pop();
	}
}

//Dijkstra��˫ջ�������ʽ��ֵ�㷨����
TEST_F(StackTest, DijkstraTest) {
	std::vector<std::string> 
		eq{"(","1","+","(","(","2","+","3",")",
		"*","(","4","*","5",")",")",")"};
	Stack<std::string> ops;
	Stack<double> vals;

	for (auto s : eq) {			//�˴����Ի��ɴ�����������
		if (s == "(");
		else if (s == "+") ops.push(s);
		else if (s == "-") ops.push(s);
		else if (s == "*") ops.push(s);
		else if (s == "/") ops.push(s);
		else if (s == ")") {	//����ַ�Ϊ')'������������Ͳ���������������ѹ��ջ
			std::string op = ops.pop();
			double v = vals.pop();
			if (op == "+") v = vals.pop() + v;
			else if (op == "-") v = vals.pop() - v;
			else if (op == "*") v = vals.pop() * v;
			else if (op == "/") v = vals.pop() / v;
			vals.push(v);
		}
		else vals.push(std::stod(s));
	}

	ASSERT_EQ(vals.pop(),101);
}


#endif // !STACK_H
