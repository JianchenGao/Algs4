#ifndef LINEARPROBINGHASHST_H
#define LINEARPROBINGHASHST_H

#include"gtest/gtest.h"
#include<fstream>
#include<vector>

using ::testing::Test;
using ::testing::TestCase;

template<typename Key, typename Value>
class LinearProbingHashST {
private:
	int N;		//键值对总数
	int M;		//线性探测表的大小
	std::vector<Key> *keys;		//键
	std::vector<Value> *vals;	//值
	std::hash<std::string> hash_fn;
	int hash(Key key) {
		return (hash_fn(key) & 0x7fffffff) % M;
	}
	void resize(int cap) {
		std::vector<Key> *oldkeys = keys;
		std::vector<Value> *oldvals = vals;

		//使用新大小的容器代替原有容器
		keys = new std::vector<Key>(cap, "");
		vals = new std::vector<Value>(cap, 0);

		//将原有的数据重新插入到新容器中
		int oldm = M;
		M = cap;
		N = 0;
		for (int i = 0; i < oldm; i++)
			if (oldkeys->at(i) != "")
				put(oldkeys->at(i), oldvals->at(i));
		
		//释放原有容器内存
		delete oldkeys;
		delete oldvals;

	}

public:
	LinearProbingHashST() :M(16),N(0) {
		keys = new std::vector<Key>(16,"");
		vals = new std::vector<Value>(16,0);
	}
	LinearProbingHashST(int M) {

	}

	Value get(Key key) {
		for (int i = hash(key); keys->at(i) != 0; i = (i + 1) % M)
			if (keys->at(i) == key)
				return vals->at(i);
		return 0;
	}

	void put(Key key, Value val) {
		if (N >= M / 2) resize(2 * M);	//将M加倍
		int i;
		for(i=hash(key);keys->at(i)!="";i=(i+1)%M)
			if (keys->at(i) == key) {
				vals->at(i) = val;
				return;
			}
		keys->at(i) = key;
		vals->at(i) = val;
		N++;
	}

	void stDelete(Key key) {
		if (!contains(key)) return;
		int i = hash(key);
		while (key != keys->at(i))
			i = (i + 1) % M;
		keys->at(i) = 0;
		vals->at(i) = 0;
		i = (i + 1) % M;
		while (keys->at(i) != "")
		{
			Key keyToRedo = keys->at(i);
			Value valToRedo = vals->at(i);
			keys->at(i) = 0;
			vals->at(i) = 0;
			N--;
			put(keyToRedo, valToRedo);
			i = (i + 1) % M;
		}
		N--;
		if (N > 0 && N == M / 8) resize(M / 2);
	}

	bool contains(Key key) {
		return get(key) == 0;
	}

	bool isEmpty() {
		return N == 0;
	}

	int size() {
		return N;
	}

};


class LinearProbingHashSTTest :public ::testing::Test {
protected:
	void SetUp() override {
		st = new LinearProbingHashST<std::string, int>;
	}

	void TearDown() override {
		delete st;
	}

	LinearProbingHashST<std::string, int> *st;
};

TEST_F(LinearProbingHashSTTest, tinytaletest)
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

TEST_F(LinearProbingHashSTTest, FrequencyCountertTinytale)
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

}

TEST_F(LinearProbingHashSTTest, FrequencyCounterTale)
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

}

#endif // !TEST_H
