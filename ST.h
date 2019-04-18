#pragma once
#ifndef ST_H
#define ST_H

#include"gtest/gtest.h"
//#include"StackIterator.h"
#include"STIterator.h"
#include<fstream>

using ::testing::Test;
using ::testing::TestCase;


template<typename Key, typename Value>
struct KeyValNode
{
	Key key;
	Value val;
	KeyValNode *next;
	KeyValNode(Key key, Value val, KeyValNode *next)
	{	//负责节点的初始化
		this->key = key;
		this->val = val;
		this->next = next;
	}
	KeyValNode() {}
};

template<typename Key, typename Value>
class STIterator;

template<typename Key,typename Value>
class ST {
public:
	typedef STIterator<Key, Value> iterator;
	ST();
	void put(Key key, Value val);
	Value get(Key key);
	void stDelete(Key key);
	bool contains(Key key);
	bool isEmpty();
	int size();
	iterator keys();
	iterator begin();
	iterator end();

private:
	void init() {
		N = 0;
		head = new KeyValNode<Key, Value>();
		tail = head;
		head->next = nullptr;
	}
	KeyValNode<Key, Value> *head;
	KeyValNode<Key, Value> *tail;
	int N;
};

class STTest :public ::testing::Test {
protected:
	void SetUp() override {
		st = new ST<std::string, int>;
	}

	void TearDown() override {
		delete st;
	}

	ST<std::string, int> *st;
};

TEST_F(STTest, TinytaleReadtest)
{
	std::ifstream input_tinytale("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\tinytale.txt");
	if (!input_tinytale.is_open())
		std::cout << "open file failure" << std::endl;
	std::string key;
	int i = 0;
	while (!input_tinytale.eof())
	{
		input_tinytale >> key;
	}
}

TEST_F(STTest, tinytaletest)
{
	std::ifstream input_tinytale("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\tinytale.txt");
	if (!input_tinytale.is_open())
		std::cout << "open file failure" << std::endl;
	std::string key;
	int i = 0;
	while (!input_tinytale.eof())
	{
		input_tinytale >> key;
		st->put(key, i);
		i++;
	}

	std::cout << st->size() << std::endl;
	input_tinytale.close();
	//ST<std::string, int>::iterator iter;
	//for (iter = st->begin(); iter != st->end(); iter++)
	//	std::cout << iter.frist() << " " << iter.second() << std::endl;
}

TEST_F(STTest, FrequencyCountertTinytale)
{
	std::ifstream input_tinytale("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\tinytale.txt");
	if (!input_tinytale.is_open())
		std::cout << "open file failure" << std::endl;
	std::string key;
	int i = 0;
	unsigned int minlen = 5;
	while (!input_tinytale.eof())
	{
		input_tinytale >> key;
		if (key.size() < minlen)
			continue;
		if (!st->contains(key)) st->put(key, 1);
		else st->put(key, st->get(key) + 1);
	}
	std::string max(" ");
	st->put(max, 0);
	ST<std::string, int>::iterator iter;
	for (iter = st->begin(); iter != st->end(); iter++)
	{
		if (iter.frist() > st->get(max))
			max = iter.second();
	}
	std::cout << max << " " << st->get(max) << std::endl;
}

TEST_F(STTest, FrequencyCounterTale)
{
	std::ifstream input_tale("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\tale.txt");
	if (!input_tale.is_open())
		std::cout << "open file failure" << std::endl;
	std::string key;
	int i = 0;
	unsigned int minlen = 5;
	while (!input_tale.eof())
	{
		input_tale >> key;
		if (key.size() < minlen)
			continue;
		if (!st->contains(key)) st->put(key, 1);
		else st->put(key, st->get(key) + 1);
	}
	std::cout << "read file over!!" << std::endl;
	std::string max(" ");
	st->put(max, 0);
	ST<std::string, int>::iterator iter;
	for (iter = st->begin(); iter != st->end(); iter++)
	{
		if (iter.frist() > st->get(max))
			max = iter.second();
	}
	std::cout << max << " " << st->get(max) << std::endl;
}


template<typename Key, typename Value>
ST<Key, Value>::ST()
{
	init();
}

template<typename Key, typename Value>
void ST<Key, Value>::put(Key key, Value val)
{	//对键key的值进行更新
	KeyValNode<Key, Value> *curNode;
	for (curNode = head; curNode != nullptr; curNode = curNode->next)
	{
		if (curNode->key == key)
		{
			curNode->val = val;
			return;
		}
	}
	//当键key不存在时，在链表头部新建一个节点
	head = new KeyValNode<Key, Value>(key, val, head);
	N++;
}

template<typename Key, typename Value>
Value ST<Key, Value>::get(Key key)
{	//获取键key对应的值
	for (KeyValNode<Key, Value> *curNode = head; curNode != NULL; curNode = curNode->next)
	{
		if (curNode->key == key)
		{
			return curNode->val;
		}
	}
	return 0;
}

template<typename Key, typename Value>
void ST<Key, Value>::stDelete(Key key)
{
	KeyValNode<Key, Value> *preNode, *curNode;
	for (preNode = head, curNode = head; curNode != nullptr; curNode = curNode->next)
	{
		if (curNode->key == key)
		{
			if (curNode == head)
			{	//如果需要删除的是头结点
				head = curNode->next;
				delete curNode;
				N--;
				return;
			}
			else {
				preNode->next = curNode->next;
				delete curNode;
				N--;
				return;
			}
		}
	}
}

template<typename Key, typename Value>
bool ST<Key, Value>::contains(Key key)
{
	return get(key) != 0;
}

template<typename Key, typename Value>
bool ST<Key, Value>::isEmpty()
{
	return size() == 0;
}

template<typename Key, typename Value>
int ST<Key, Value>::size()
{
	return N;
}


template<typename Key, typename Value>
typename ST<Key, Value>::iterator  ST<Key, Value>::keys()
//在类型名前加typename是指明后面引用的是类型名而不是静态方法
{

}

template<typename Key, typename Value>
typename ST<Key, Value>::iterator  ST<Key, Value>::begin()
{
	return iterator(head);
}

template<typename Key, typename Value>
typename ST<Key, Value>::iterator  ST<Key, Value>::end()
{
	return iterator(tail);
}


#endif // !ST_H
