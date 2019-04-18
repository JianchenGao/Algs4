#pragma once
#ifndef BST_H
#define BST_H

#include"gtest/gtest.h"
#include<fstream>
#include<iterator>

using ::testing::Test;
using ::testing::TestCase;

template<typename Key, typename Value>
class BST {
private:
	class Node
	{
	public:
		Key key;
		Value val;
		Node *left, *right;
		int N;
		Node() {}
		Node(Key key, Value val, int N)
		{
			this->key = key;
			this->val = val;
			this->N = N;
		}
	};
	Node *root;				//二叉查找树的根结点
	Node* stDelete(Node *x, Key key);
	Node* stDeleteMin(Node *x);
	Node* ceiling(Node *x, Key key);
	Node* floor(Node *x, Key key);
	Node* select(Node *x, int k);
	Node* min(Node *x);
	Node* max(Node *x);
	Node* put(Node *x, Key key, Value val);
public:
	BST();
	void put(Key key, Value val);
	Value get(Key key);
	Value get(Node *x,Key key);
	int rank(Key key);
	int rank(Key key,Node *x);
	void stDeleteMin();
	void stDelete(Key key);
	bool contains(Key key);
	bool isEmpty();
	int size();
	int size(Node *x);
	Key min();
	Key max();
	Key select(int k);
	Key ceiling(Key key);
	Key floor(Key key);
	std::vector<Key> * keys();
	std::vector<Key> * keys(Key lo,Key hi);
	void keys(Node *x, std::vector<Key> *vec, Key lo, Key hi);

};


class BSTTest :public ::testing::Test {
protected:
	void SetUp() override {
		st = new BST<std::string, int>;
	}

	void TearDown() override {
		delete st;
	}

	BST<std::string, int> *st;
};


TEST_F(BSTTest, BSTWork)
{
	std::vector<std::string> words = { "gao","jian","chen","bei","jing","gao","gong","ye","da","da",
		"xue","xin","xi","xue","bu","kong","zhi","ke","xue","yu","gong","cheng","ok" };
	int i = 0;
	for (auto word : words)
	{
		i++;
		st->put(word, i);
	}

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
	st->stDelete("gong");
	st->stDelete("kong");
	st->stDelete("xue");
	st->stDelete("da");
	st->stDelete("ok");
	st->stDelete("ke");


	ASSERT_EQ(st->get("bei"), 0);
	ASSERT_EQ(st->get("zhi"), 0);
	ASSERT_EQ(st->get("xi"), 0);
	ASSERT_EQ(st->max(), "yu");
	ASSERT_EQ(st->min(), "bu");

	//测试floor操作
	ASSERT_EQ(st->floor("chen"), "chen");
	ASSERT_EQ(st->floor("bu"), "bu");
	ASSERT_EQ(st->floor("ya"), "xin");
	ASSERT_EQ(st->floor("chan"), "bu");


	//测试ceiling操作
	ASSERT_EQ(st->ceiling("bu"), "bu");
	ASSERT_EQ(st->ceiling("xx"), "ye");
	ASSERT_EQ(st->ceiling("a"), "bu");

	//测试contains操作
	ASSERT_EQ(st->contains("yu"), true);
	ASSERT_EQ(st->contains("nohave"), false);

	//测试size操作
	ASSERT_EQ(st->size(), 9);


	//测试select操作
	ASSERT_EQ(st->select(0), "bu");
	ASSERT_EQ(st->select(3), "gao");

	//测试范围查找
	std::vector<std::string> *key;
	key = st->keys();
	for (auto i : *key)
		std::cout << i << " ";

}

TEST_F(BSTTest, tinytaletest)
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

TEST_F(BSTTest, FrequencyCountertTinytale)
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

TEST_F(BSTTest, FrequencyCounterTale)
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
BST<Key, Value>::BST()
{

}

template<typename Key, typename Value>
void BST<Key, Value>::put(Key key, Value val)
{	//对键key的值进行更新
	root = put(root, key, val);
}

template<typename Key, typename Value>
typename BST<Key, Value>::Node* BST<Key, Value>::put(Node *x, Key key, Value val)
{	//如果key存在于以x为根结点的子树中则更新它的值
	//否则将以key和val的键值对的新结点插入到该子树中
	if (x == nullptr) return new Node(key, val, 1);
	if (key < x->key) x->left = put(x->left, key, val);
	else if (key > x->key) x->right = put(x->right, key, val);
	else x->val = val;
	x->N = size(x->left) + size(x->right) + 1;
	return x;
}


template<typename Key, typename Value>
Value BST<Key, Value>::get(Key key)
{	//获取键key对应的值
	return get(root, key);
}

template<typename Key, typename Value>
Value BST<Key, Value>::get(Node *x, Key key)
{	//在以x为根结点的子树中查找并返回key所对应的值
	//如果找不到则返回null
	if (x == nullptr) return 0;
	if (key < x->key) return get(x->left, key);
	else if (key > x->key) return get(x->right, key);
	else return x->val;
}

template<typename Key, typename Value>
int BST<Key, Value>::rank(Key key)
{
	return rank(key, root);
}

template<typename Key, typename Value>
int BST<Key, Value>::rank(Key key,Node *x)
{	//返回以x为根结点的子树中小于key的键的数量
	if (x == nullptr)	return 0;
	if (key < x->key)	return rank(key, x->left);
	else if (key > x->key)	return 1 + size(x->left) + rank(key, x->right);
	else	return size(x->left);
}

template<typename Key, typename Value>
void BST<Key, Value>::stDeleteMin()
{
	root = stDeleteMin(root);
}

template<typename Key, typename Value>
typename BST<Key, Value>::Node* BST<Key, Value>::stDeleteMin(Node *x)
{
	if (x->left == nullptr) {
		Node *tmp = x->right;
		delete x;
		return tmp;
	}
	x->left = stDeleteMin(x->left);
	x->N = size(x->left) + size(x->right) + 1;
	return x;
}

template<typename Key, typename Value>
void BST<Key, Value>::stDelete(Key key)
{
	root = stDelete(root, key);
}

template<typename Key, typename Value>
typename BST<Key, Value>::Node* BST<Key, Value>::stDelete(Node *x,Key key)
{
	if (x == nullptr)	return nullptr;
	if (key < x->key) x->left = stDelete(x->left, key);
	else if (key > x->key) x->right = stDelete(x->right, key);
	else
	{
		if (x->right == nullptr) {
			Node *tmp = x->left;
			delete x;
			return tmp;
		}
		if (x->left == nullptr) {
			Node *tmp = x->right;
			delete x;
			return tmp;
		}
		Node *t = new Node;
		*t = *x;
		*x = *min(t->right);
		x->right = stDeleteMin(t->right);
		x->left = t->left;
		delete t;
	}
	x->N = size(x->left) + size(x->right) + 1;
	return x;
}

template<typename Key, typename Value>
bool BST<Key, Value>::contains(Key key)
{
	return get(key) != 0;
}

template<typename Key, typename Value>
bool BST<Key, Value>::isEmpty()
{
	return size() == 0;
}

template<typename Key, typename Value>
int BST<Key, Value>::size()
{
	return size(root);
}

template<typename Key, typename Value>
int BST<Key, Value>::size(Node *x)
{
	if (x == nullptr) return 0;
	else return x->N;
}

template<typename Key, typename Value>
Key  BST<Key, Value>::min()
{
	return min(root)->key;
}

template<typename Key, typename Value>
typename BST<Key, Value>::Node*  BST<Key, Value>::min(Node *x)
{
	if (x->left == nullptr) return x;
	else return min(x->left);
}

template<typename Key, typename Value>
Key  BST<Key, Value>::max()
{
	return max(root)->key;
}

template<typename Key, typename Value>
typename BST<Key, Value>::Node*  BST<Key, Value>::max(Node *x)
{
	if (x->right == nullptr) return x;
	else return max(x->right);
}

template<typename Key, typename Value>
Key  BST<Key, Value>::select(int k)
{
	return select(root, k)->key;
}

template<typename Key, typename Value>
typename BST<Key, Value>::Node*  BST<Key, Value>::select(Node *x,int k)
{	//返回排名为k的结点
	if (x == nullptr)	return nullptr;
	int t = size(x->left);
	if (t > k)	return select(x->left, k);
	else if (t < k)	return select(x->right, k - t - 1);
	else return x;
}

template<typename Key, typename Value>
Key  BST<Key, Value>::ceiling(Key key)
{
	Node *x = ceiling(root, key);
	if (x == nullptr)	return nullptr;
	return x->key;
}

template<typename Key, typename Value>
typename BST<Key, Value>::Node*  BST<Key, Value>::ceiling(Node *x,Key key)
{
	if (x == nullptr) return nullptr;
	if (key == x->key)	return x;
	if (key > x->key)	return ceiling(x->right, key);
	Node *t = ceiling(x->left, key);
	if (t != nullptr)	return t;
	else	return x;
}

template<typename Key, typename Value>
Key  BST<Key, Value>::floor(Key key)
{
	Node *x = floor(root, key);
	if (x == nullptr)	return nullptr;
	return x->key;
}

template<typename Key, typename Value>
typename BST<Key, Value>::Node*  BST<Key, Value>::floor(Node *x,Key key)
{
	if (x == nullptr) return nullptr;
	if (key == x->key)	return x;
	if (key < x->key)	return floor(x->left, key);
	Node *t = floor(x->right, key);	//对right的返回的null需要单独处理
	if (t != nullptr)	return t;
	else	return x;
}

template<typename Key, typename Value>
std::vector<Key> * BST<Key, Value>::keys()
{
	return keys(min(), max());
}

template<typename Key, typename Value>
std::vector<Key> * BST<Key, Value>::keys(Key lo, Key hi)
{
	std::vector<Key> *_vec = new std::vector<Key>;
	keys(root, _vec, lo, hi);
	return _vec;
}

template<typename Key, typename Value>
void BST<Key, Value>::keys(Node *x, std::vector<Key> *vec, Key lo, Key hi)
{
	if (x == nullptr)	return;
	if (lo < x->key)	keys(x->left, vec, lo, hi);
	if (lo <= x->key && hi >= x->key)	vec->push_back(x->key);
	if (hi > x->key)	keys(x->right, vec, lo, hi);
}


#endif // !ST_H


