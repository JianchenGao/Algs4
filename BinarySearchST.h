#pragma once
#ifndef BINARYSEARCHST_H
#define BINARYSEARCHST_H

#include"gtest/gtest.h"
#include<fstream>
#include<iterator>

using ::testing::Test;
using ::testing::TestCase;

template<typename Key, typename Value>
class BinarySearchST {
public:
	//typedef std::vector<Key>::iterator iterator;
	BinarySearchST();
	void put(Key key, Value val);
	Value get(Key key);
	int rank(Key key);
	void stDelete(Key key);
	bool contains(Key key);
	bool isEmpty();
	int size();
	int size(Key lo, Key hi);
	Key min();
	Key max();
	Key select(int k);
	Key ceiling(Key key);
	Key floor(Key key);

	//iterator begin();
	//iterator end();

private:
	std::vector<Key> keys;
	std::vector<Value> vals;
	int N;
};

class BinarySearchSTTest :public ::testing::Test {
protected:
	void SetUp() override {
		st = new BinarySearchST<std::string, int>;
	}

	void TearDown() override {
		delete st;
	}

	BinarySearchST<std::string, int> *st;
};

TEST_F(BinarySearchSTTest, BinarySearchSTWork)
{
	std::vector<std::string> words = {"gao","jian","chen","bei","jing","gao","gong","ye","da","da",
		"xue","xin","xi","xue","bu","kong","zhi","ke","xue","yu","gong","cheng","ok"};
	int i = 0;
	for (auto word : words)
	{
		i++;
		st->put(word, i);
	}
	std::string key;

	//抽样检索测试
	ASSERT_EQ(st->get("bei"), 4);
	ASSERT_EQ(st->get("gong"), 21);
	ASSERT_EQ(st->get("xi"), 13);
	ASSERT_EQ(st->get("zhi"), 17);
	ASSERT_EQ(st->get("nohave"), 0);

	//测试极值操作
	ASSERT_EQ(st->max(), "zhi");
	ASSERT_EQ(st->min(), "bei");

	//测试删除操作
	st->stDelete("bei");
	st->stDelete("zhi");
	st->stDelete("xi");

	ASSERT_EQ(st->get("bei"), 0);
	ASSERT_EQ(st->get("zhi"), 0);
	ASSERT_EQ(st->get("xi"), 0);
	ASSERT_EQ(st->max(), "yu");
	ASSERT_EQ(st->min(), "bu");

	//测试floor操作
	//ASSERT_EQ(st->floor("da"), "cheng");
	//ASSERT_EQ(st->floor("bu"), "");
	//ASSERT_EQ(st->floor("yu"), "ye");

	//测试ceiling操作
	//ASSERT_EQ(st->ceiling("bu"), "chen");
	//ASSERT_EQ(st->ceiling("ye"), "yu");
	//ASSERT_EQ(st->ceiling("yu"), "");

	//测试contains操作
	ASSERT_EQ(st->contains("yu"), true);
	ASSERT_EQ(st->contains("nohave"), false);

	//测试size操作
	ASSERT_EQ(st->size(), 15);
	ASSERT_EQ(st->size("da","jian"), 3);
	ASSERT_EQ(st->size("jian", "da"), -3);


	//测试select操作
	ASSERT_EQ(st->select(0), "bu");
	ASSERT_EQ(st->select(3), "da");

}

TEST_F(BinarySearchSTTest, tinytaletest)
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

TEST_F(BinarySearchSTTest, FrequencyCountertTinytale)
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

	std::cout << st->max() << " " << st->get(st->max()) << std::endl;
}

TEST_F(BinarySearchSTTest, FrequencyCounterTale)
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
	key = st->max();
	std::cout << key << " " << st->get(key) << std::endl;
}


template<typename Key, typename Value>
BinarySearchST<Key, Value>::BinarySearchST()
{

}

template<typename Key, typename Value>
void BinarySearchST<Key, Value>::put(Key key, Value val)
{	//对键key的值进行更新
	int i = rank(key);
	if ((i < N) && (keys.at(i) == key))
	{
		vals.at(i) = val;
		return;
	}
	//当键key不存在时，在keys和vals中新增一个元素，并移动原有元素使其有序
	keys.push_back(key);
	vals.push_back(val);
	for (int j = N; j > i; j--)
	{
		keys.at(j) = keys.at(j - 1);
		vals.at(j) = vals.at(j - 1);
	}
	keys.at(i) = key;
	vals.at(i) = val;
	N++;
}

template<typename Key, typename Value>
Value BinarySearchST<Key, Value>::get(Key key)
{	//获取键key对应的值
	if (isEmpty()) return 0;
	int i = rank(key);
	if ( (i < N) && (keys.at(i) == key) ) return vals.at(i);
	else return 0;
}

template<typename Key, typename Value>
int BinarySearchST<Key, Value>::rank(Key key)
{
	int lo = 0, hi = N - 1;
	while (lo <= hi)
	{
		int mid = lo + (hi - lo) / 2;
		Key midKey = keys.at(mid);
		if (key < midKey) hi = mid - 1;
		else if (key > midKey) lo = mid + 1;
		else return mid;
	}
	return lo;
}

template<typename Key, typename Value>
void BinarySearchST<Key, Value>::stDelete(Key key)
{
	int i = rank(key);
	if ((i < N) && (keys.at(i) == key))
	{	//确保要删除的对象在符号表中
		for (int j = i; j < N-1; j++)
		{	//将需要删除的键以后的所有键向前移一位
			keys.at(j) = keys.at(j + 1);
			vals.at(j) = vals.at(j + 1);
		}
		//将末尾的内存释放
		keys.pop_back();
		vals.pop_back();
		N--;
		return;
	}
	else
	{
		return;
	}
}

template<typename Key, typename Value>
bool BinarySearchST<Key, Value>::contains(Key key)
{
	return get(key) != 0;
}

template<typename Key, typename Value>
bool BinarySearchST<Key, Value>::isEmpty()
{
	return size() == 0;
}

template<typename Key, typename Value>
int BinarySearchST<Key, Value>::size()
{
	return N;
}

template<typename Key, typename Value>
int BinarySearchST<Key, Value>::size(Key lo,Key hi)
{
	int loSize = rank(lo);
	int hiSize = rank(hi);
	return hiSize - loSize;
}

template<typename Key, typename Value>
Key  BinarySearchST<Key, Value>::min()
{
	return keys.at(0);
}

template<typename Key, typename Value>
Key  BinarySearchST<Key, Value>::max()
{
	return keys.at(N-1);
}

template<typename Key, typename Value>
Key  BinarySearchST<Key, Value>::select(int k)
{
	return keys.at(k);
}

template<typename Key, typename Value>
Key  BinarySearchST<Key, Value>::ceiling(Key key)
{
	int i = rank(key);
	return keys[i];
}

template<typename Key, typename Value>
Key  BinarySearchST<Key, Value>::floor(Key key)
{
	int i = rank(key);
	if (i > 0)
		return keys[i - 1];
	return "";
}

/******************************************************
template<typename Key, typename Value>
typename BinarySearchST<Key, Value>::iterator  BinarySearchST<Key, Value>::begin()
{
	return keys.begin();
}

template<typename Key, typename Value>
typename BinarySearchST<Key, Value>::iterator  BinarySearchST<Key, Value>::end()
{
	return keys.end();
}
*******************************************************************/

#endif // !ST_H

