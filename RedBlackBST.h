#pragma once
#ifndef REDBLACKBST_H
#define REDBLACKBST_H

#include"gtest/gtest.h"
#include<fstream>
#include<iterator>

using ::testing::Test;
using ::testing::TestCase;

template<typename Key, typename Value>
class RedBlackBST {
private:
	static const bool RED = true;
	static const bool BLACK = false;
	class Node
	{
	public:
		Key key;
		Value val;
		Node *left, *right;
		int N;
		bool color;
		Node() {}
		Node(Key key, Value val, int N,bool color)
		{
			this->key = key;
			this->val = val;
			this->N = N;
			this->color = color;
		}
	};
	Node *root;				//����������ĸ����

	bool isRed(Node *h);
	Node *rotateLeft(Node *h);
	Node *rotateRight(Node *h);
	void flipColors(Node *h);
	Node *moveRedLeft(Node *h);
	Node *moveRedRight(Node *h);
	Node *balance(Node *h);
	Node* stDelete(Node *h, Key key);
	Node* stDeleteMin(Node *h);
	Node* stDeleteMax(Node *h);
	Node* ceiling(Node *x, Key key);
	Node* floor(Node *x, Key key);
	Node* select(Node *x, int k);
	Node* min(Node *x);
	Node* max(Node *x);
	Node* put(Node *x, Key key, Value val);
public:
	RedBlackBST();
	void put(Key key, Value val);
	Value get(Key key);
	Value get(Node *x, Key key);
	int rank(Key key);
	int rank(Key key, Node *x);
	void stDeleteMin();
	void stDeleteMax();
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
	std::vector<Key> * keys(Key lo, Key hi);
	void keys(Node *x, std::vector<Key> *vec, Key lo, Key hi);

};

class RedBlackBSTTest :public ::testing::Test {
protected:
	void SetUp() override {
		st = new RedBlackBST<std::string, int>;
	}

	void TearDown() override {
		delete st;
	}

	RedBlackBST<std::string, int> *st;
};

TEST_F(RedBlackBSTTest, BSTWork)
{
	std::vector<std::string> words = { "gao","jian","chen","bei","jing","gao","gong","ye","da","da",
		"xue","xin","xi","xue","bu","kong","zhi","ke","xue","yu","gong","cheng","ok" };
	int i = 0;
	for (auto word : words)
	{
		i++;
		st->put(word, i);
	}

	//������������
	ASSERT_EQ(st->get("bei"), 4);
	ASSERT_EQ(st->get("gong"), 21);
	ASSERT_EQ(st->get("xi"), 13);
	ASSERT_EQ(st->get("zhi"), 17);
	ASSERT_EQ(st->get("nohave"), 0);

	//���Լ�ֵ����
	ASSERT_EQ(st->max(), "zhi");
	ASSERT_EQ(st->min(), "bei");



	//����floor����
	ASSERT_EQ(st->floor("chen"), "chen");
	ASSERT_EQ(st->floor("bu"), "bu");
	ASSERT_EQ(st->floor("ya"), "xue");
	ASSERT_EQ(st->floor("chan"), "bu");

	//����ceiling����
	ASSERT_EQ(st->ceiling("bu"), "bu");
	ASSERT_EQ(st->ceiling("xx"), "ye");
	ASSERT_EQ(st->ceiling("a"), "bei");

	//����contains����
	ASSERT_EQ(st->contains("yu"), true);
	ASSERT_EQ(st->contains("nohave"), false);

	//����size����
	ASSERT_EQ(st->size(), 18);


	//����select����
	ASSERT_EQ(st->select(0), "bei");
	ASSERT_EQ(st->select(3), "cheng");

	//���Է�Χ����
	std::vector<std::string> *key;
	key = st->keys();
	for (auto i : *key)
		std::cout << i << " ";

	//����ɾ������
	st->stDeleteMin();
	st->stDeleteMax();
	ASSERT_EQ(st->max(), "yu");
	ASSERT_EQ(st->min(), "bu");

}

TEST_F(RedBlackBSTTest, BSTDelete)
{
	std::vector<std::string> words = { "gao","jian","chen","bei","jing","gao","gong","ye","da","da",
		"xue","xin","xi","xue","bu","kong","zhi","ke","xue","yu","gong","cheng","ok" };
	int i = 0;
	for (auto word : words)
	{
		i++;
		st->put(word, i);
	}

	//����size����
	ASSERT_EQ(st->size(), 18);


	//����ɾ������

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
	ASSERT_EQ(st->size(), 9);

	//���Է�Χ����
	std::vector<std::string> *key;
	key = st->keys();
	for (auto i : *key)
		std::cout << i << " ";

}

TEST_F(RedBlackBSTTest, tinytaletest)
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

TEST_F(RedBlackBSTTest, FrequencyCountertTinytale)
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

TEST_F(RedBlackBSTTest, FrequencyCounterTale)
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
RedBlackBST<Key, Value>::RedBlackBST()
{

}

template<typename Key, typename Value>
bool RedBlackBST<Key, Value>::isRed(Node *x)
{
	if (x == nullptr) return false;
	return x->color == RedBlackBST::RED;
}

template<typename Key, typename Value>
typename RedBlackBST<Key, Value>::Node * RedBlackBST<Key, Value>::rotateLeft(Node *h)
{
	Node *x = h->right;
	h->right = x->left;
	x->left = h;
	x->color = h->color;
	h->color = RedBlackBST::RED;
	x->N = h->N;
	h->N = 1 + size(h->left) + size(h->right);
	return x;
}

template<typename Key, typename Value>
typename RedBlackBST<Key, Value>::Node * RedBlackBST<Key, Value>::rotateRight(Node *h)
{
	Node *x = h->left;
	h->left = x->right;
	x->right = h;
	x->color = h->color;
	h->color = RedBlackBST::RED;
	x->N = h->N;
	h->N = 1 + size(h->left) + size(h->right);
	return x;
}

template<typename Key, typename Value>
void RedBlackBST<Key, Value>::flipColors(Node *h)
{
	//h->color = RedBlackBST::RED;
	//h->left ->color = RedBlackBST::BLACK;
	//h->right->color = RedBlackBST::BLACK;

	h->color = !h->color;
	h->left ->color = !h->left->color;
	h->right->color = !h->right->color;
}

template<typename Key, typename Value>
void RedBlackBST<Key, Value>::put(Key key, Value val)
{	//����key���ҵ��������ֵ������Ϊ���½�һ�����
	root = put(root, key, val);
	root->color = RedBlackBST::BLACK;
}

template<typename Key, typename Value>
typename RedBlackBST<Key, Value>::Node * RedBlackBST<Key, Value>::put(Node *h,Key key, Value val)
{
	if (h == nullptr)	//��׼�Ĳ���������͸�����ú���������
		return new Node(key, val, 1, RedBlackBST::RED);
	if (key < h->key) h->left = put(h->left, key, val);
	else if (key > h->key) h->right = put(h->right, key, val);
	else h->val = val;

	//ͨ����ת����ʹ������ƽ��
	if (isRed(h->right) && !isRed(h->left)) h = rotateLeft(h);
	if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
	if (isRed(h->left) && isRed(h->right)) flipColors(h);

	h->N = size(h->left) + size(h->right) + 1;
	return h;
}


template<typename Key, typename Value>
Value RedBlackBST<Key, Value>::get(Key key)
{	//��ȡ��key��Ӧ��ֵ
	return get(root, key);
}

template<typename Key, typename Value>
Value RedBlackBST<Key, Value>::get(Node *x, Key key)
{	//����xΪ�����������в��Ҳ�����key����Ӧ��ֵ
	//����Ҳ����򷵻�null
	if (x == nullptr) return 0;
	if (key < x->key) return get(x->left, key);
	else if (key > x->key) return get(x->right, key);
	else return x->val;
}

template<typename Key, typename Value>
int RedBlackBST<Key, Value>::rank(Key key)
{
	return rank(key, root);
}

template<typename Key, typename Value>
int RedBlackBST<Key, Value>::rank(Key key, Node *x)
{	//������xΪ������������С��key�ļ�������
	if (x == nullptr)	return 0;
	if (key < x->key)	return rank(key, x->left);
	else if (key > x->key)	return 1 + size(x->left) + rank(key, x->right);
	else	return size(x->left);
}

template<typename Key, typename Value>
typename RedBlackBST<Key, Value>::Node * RedBlackBST<Key, Value>::moveRedLeft(Node *h)
{	//������hΪ��ɫ��h.left��h.left.left���Ǻ�ɫ
	//��h.left����h.left���ӽ��֮һ���
	flipColors(h);
	if (isRed(h->right->left))
	{
		h->right = rotateRight(h->right);
		h = rotateLeft(h);
		flipColors(h);
	}
	return h;
}

template<typename Key, typename Value>
typename RedBlackBST<Key, Value>::Node * RedBlackBST<Key, Value>::moveRedRight(Node *h)
{	//������hΪ��ɫ��h.right��h.right.left���Ǻ�ɫ
	//��h.right����h.right���ӽ��֮һ���
	flipColors(h);
	if (isRed(h->left->left))
	{
		h = rotateRight(h);
		flipColors(h);
	}
	return h;
}

template<typename Key, typename Value>
typename RedBlackBST<Key, Value>::Node* RedBlackBST<Key, Value>::balance(Node *h)
{
	if (isRed(h->right)) h = rotateLeft(h);

	//ͨ����ת����ʹ������ƽ��
	if (isRed(h->right) && !isRed(h->left)) h = rotateLeft(h);
	if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
	if (isRed(h->left) && isRed(h->right)) flipColors(h);

	h->N = size(h->left) + size(h->right) + 1;
	return h;
}

template<typename Key, typename Value>
void RedBlackBST<Key, Value>::stDeleteMin()
{
	if (!isRed(root->left) && !isRed(root->right))
		root->color = RedBlackBST::RED;
	root = stDeleteMin(root);
	if (!isEmpty()) root->color = RedBlackBST::BLACK;
}

template<typename Key, typename Value>
typename RedBlackBST<Key, Value>::Node* RedBlackBST<Key, Value>::stDeleteMin(Node *h)
{
	if (h->left == nullptr)	//h������Ϊ�գ���hΪ��Сֵ��ɾ��h���ͷ��ڴ�
	{
		delete h;
		return nullptr;		
		//�ɺ���������Կ�֪���������û����������һ��û��������
		//���Բ���������������������������
	}
	if (!isRed(h->left) && !isRed(h->left->left))
		h = moveRedLeft(h);		//��֤h->left����2-���
	h->left = stDeleteMin(h->left);
	return balance(h);
}

template<typename Key, typename Value>
void RedBlackBST<Key, Value>::stDeleteMax()
{
	if (!isRed(root->left) && !isRed(root->right))
		root->color = RedBlackBST::RED;

	root = stDeleteMax(root);
	if (!isEmpty()) root->color = RedBlackBST::BLACK;
}

template<typename Key, typename Value>
typename RedBlackBST<Key, Value>::Node* RedBlackBST<Key, Value>::stDeleteMax(Node *h)
{
	if (isRed(h->left))
		h = rotateRight(h);

	if (h->right == nullptr)	
	{
		delete h;	//�������ƽ���������û�����������ǿ϶�û����������û��2-������������
		return nullptr;
	}
	if (!isRed(h->right) && !isRed(h->right->left))
		h = moveRedRight(h);		
	
	h->right = stDeleteMax(h->right);

	return balance(h);
}

template<typename Key, typename Value>
void RedBlackBST<Key, Value>::stDelete(Key key)
{
	if (!contains(key)) return;

	if (!isRed(root->left) && !isRed(root->right))
		root->color = RedBlackBST::RED;

	root = stDelete(root, key);
	if (!isEmpty()) root->color = RedBlackBST::BLACK;
}

template<typename Key, typename Value>
typename RedBlackBST<Key, Value>::Node* RedBlackBST<Key, Value>::stDelete(Node *h, Key key)
{
	if (key < h->key) {
		if (!isRed(h->left) && !isRed(h->left->left))
			h = moveRedLeft(h);
		h->left = stDelete(h->left, key);
	}
	else {
		if (isRed(h->left))
			h = rotateRight(h);
		if (key == h->key && h->right == nullptr) {		//�ҵ�key����������Ϊ��
			delete h;	//�������ƽ���������û�����������ǿ϶�û����������û��2-������������
			return nullptr;
		}
		if (!isRed(h->right) && !isRed(h->right->left))	//h��������Ϊ2-���
			h = moveRedRight(h);
		if (key == h->key) {	//�ҵ�key��������������
			Node *x = min(h->right);
			h->key = x->key;
			h->val = x->val;
			h->right = stDeleteMin(h->right);
		}
		else
			h->right = stDelete(h->right, key);
	}
	return balance(h);
}

template<typename Key, typename Value>
bool RedBlackBST<Key, Value>::contains(Key key)
{
	return get(key) != 0;
}

template<typename Key, typename Value>
bool RedBlackBST<Key, Value>::isEmpty()
{
	return size() == 0;
}

template<typename Key, typename Value>
int RedBlackBST<Key, Value>::size()
{
	return size(root);
}

template<typename Key, typename Value>
int RedBlackBST<Key, Value>::size(Node *x)
{
	if (x == nullptr) return 0;
	else return x->N;
}

template<typename Key, typename Value>
Key  RedBlackBST<Key, Value>::min()
{
	return min(root)->key;
}

template<typename Key, typename Value>
typename RedBlackBST<Key, Value>::Node*  RedBlackBST<Key, Value>::min(Node *x)
{
	if (x->left == nullptr) return x;
	else return min(x->left);
}

template<typename Key, typename Value>
Key  RedBlackBST<Key, Value>::max()
{
	return max(root)->key;
}

template<typename Key, typename Value>
typename RedBlackBST<Key, Value>::Node*  RedBlackBST<Key, Value>::max(Node *x)
{
	if (x->right == nullptr) return x;
	else return max(x->right);
}

template<typename Key, typename Value>
Key  RedBlackBST<Key, Value>::select(int k)
{
	return select(root, k)->key;
}

template<typename Key, typename Value>
typename RedBlackBST<Key, Value>::Node*  RedBlackBST<Key, Value>::select(Node *x, int k)
{	//��������Ϊk�Ľ��
	if (x == nullptr)	return nullptr;
	int t = size(x->left);
	if (t > k)	return select(x->left, k);
	else if (t < k)	return select(x->right, k - t - 1);
	else return x;
}

template<typename Key, typename Value>
Key  RedBlackBST<Key, Value>::ceiling(Key key)
{
	Node *x = ceiling(root, key);
	if (x == nullptr)	return nullptr;
	return x->key;
}

template<typename Key, typename Value>
typename RedBlackBST<Key, Value>::Node*  RedBlackBST<Key, Value>::ceiling(Node *x, Key key)
{
	if (x == nullptr) return nullptr;
	if (key == x->key)	return x;
	if (key > x->key)	return ceiling(x->right, key);
	Node *t = ceiling(x->left, key);
	if (t != nullptr)	return t;
	else	return x;
}

template<typename Key, typename Value>
Key  RedBlackBST<Key, Value>::floor(Key key)
{
	Node *x = floor(root, key);
	if (x == nullptr)	return nullptr;
	return x->key;
}

template<typename Key, typename Value>
typename RedBlackBST<Key, Value>::Node*  RedBlackBST<Key, Value>::floor(Node *x, Key key)
{
	if (x == nullptr) return nullptr;
	if (key == x->key)	return x;
	if (key < x->key)	return floor(x->left, key);
	Node *t = floor(x->right, key);	//��right�ķ��ص�null��Ҫ��������
	if (t != nullptr)	return t;
	else	return x;
}

template<typename Key, typename Value>
std::vector<Key> * RedBlackBST<Key, Value>::keys()
{
	return keys(min(), max());
}

template<typename Key, typename Value>
std::vector<Key> * RedBlackBST<Key, Value>::keys(Key lo, Key hi)
{
	std::vector<Key> *_vec = new std::vector<Key>;
	keys(root, _vec, lo, hi);
	return _vec;
}

template<typename Key, typename Value>
void RedBlackBST<Key, Value>::keys(Node *x, std::vector<Key> *vec, Key lo, Key hi)
{
	if (x == nullptr)	return;
	if (lo < x->key)	keys(x->left, vec, lo, hi);
	if (lo <= x->key && hi >= x->key)	vec->push_back(x->key);
	if (hi > x->key)	keys(x->right, vec, lo, hi);
}



#endif // !REDBLACKBST_H
