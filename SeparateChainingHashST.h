#ifndef SEPARATECHAININGHASHST_H
#define SEPARATECHAININGHASHST_H

#include"gtest/gtest.h"
#include"ST.h"

using ::testing::Test;
using ::testing::TestCase;

template<typename Key, typename Value>
class SeparateChainingHashST {
private:
	int N;		//键值对总数
	int M;		//散列表的大小
	std::vector<ST<Key, Value> *> *st;	//存放链表对象的数组
	std::hash<std::string> hash_fn;
	int hash(Key key) {
		return (hash_fn(key) & 0x7fffffff) % M;
	}

public:
	SeparateChainingHashST():M(997) {
		st = new std::vector<ST<Key, Value> *>;
		for (int i = 0; i < M; i++)
			st->push_back(new ST<Key, Value>);
	}
	SeparateChainingHashST(int M){	//创建M条链表
		this->M = M;
		st = new std::vector<ST<Key, Value> *>;
		for (int i = 0; i < M; i++)
			st->push_back(new ST<Key, Value>);
	}
	Value get(Key key) {
		return st->at(hash(key))->get(key);
	}
	void put(Key key, Value val) {
		st->at(hash(key))->put(key, val);
	}
	void stDelete(Key key) {
		st->at(hash(key))->stDelete(key);
	}
	bool contains(Key key) {
		return st->at(hash(key))->contains(key);
	}
	bool isEmpty() {
		return N == 0;
	}
	int size() {
		//size是键的数量，所以为了避免重复计算，需要从各个子链中获取
		//不能再put时N++，这样会算到插入执行次数，包含了重复的键
		int n = 0;
		for (auto i : *st)
			n = n + i->size();
		N = n;
		return N;
	}

};


class SeparateChainingHashSTTest :public ::testing::Test {
protected:
	void SetUp() override {
		st = new SeparateChainingHashST<std::string, int>;
	}

	void TearDown() override {
		delete st;
	}

	SeparateChainingHashST<std::string, int> *st;
};

TEST_F(SeparateChainingHashSTTest, tinytaletest)
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
}




#endif // !TEST_H