#ifndef SEPARATECHAININGHASHST_H
#define SEPARATECHAININGHASHST_H

#include"gtest/gtest.h"
#include"ST.h"

using ::testing::Test;
using ::testing::TestCase;

template<typename Key, typename Value>
class SeparateChainingHashST {
private:
	int N;		//��ֵ������
	int M;		//ɢ�б�Ĵ�С
	std::vector<ST<Key, Value> *> *st;	//���������������
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
	SeparateChainingHashST(int M){	//����M������
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
		//size�Ǽ�������������Ϊ�˱����ظ����㣬��Ҫ�Ӹ��������л�ȡ
		//������putʱN++���������㵽����ִ�д������������ظ��ļ�
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