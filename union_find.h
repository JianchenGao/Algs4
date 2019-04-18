#pragma once
#ifndef UNION_FIND_H
#define UNION_FIND_H

#include"gtest/gtest.h"
#include<fstream>

using ::testing::Test;
using ::testing::TestCase;

namespace algs4 {


class UF
{
public:
	UF(int N)
	{	//��ʼ������id����
		_count = N;
		for (int i = 0; i < N; i++)
			id.push_back(i);
	}
	int count()
	{
		return _count;
	}

	bool connected(int p, int q) { return find(p) == find(q); }
	int find(int p){ return id.at(p); }
	void _union(int p, int q) {
		int pID = find(p);
		int qID = find(q);

		//���p��q�Ѿ�����ͬ�ķ���֮������Ҫ��ȡ�κ��ж�
		if (pID == qID) return;

		//��p�ķ���������Ϊq������
		for (unsigned int i = 0; i < id.size(); i++)
		{
			if (id.at(i) == pID)
				id.at(i) = qID;
		}
		_count--;
	}

private:
	std::vector<int> id;
	int _count;
};

class UF_quick_find
{
public:
	UF_quick_find(int N)
	{	//��ʼ������id����
		_count = N;
		for (int i = 0; i < N; i++)
			id.push_back(i);
	}
	int count()
	{
		return _count;
	}

	bool connected(int p, int q) { return find(p) == find(q); }
	int find(int p) { 
		//pΪ��ʼ��������id[p]��һ��������������������ʱΪ���ڵ�
		while (p != id[p])
			p = id[p];
		return p;
	}
	void _union(int p, int q) {
		int pRoot = find(p);
		int qRoot = find(q);

		//���p��q�Ѿ�����ͬ�ķ���֮������Ҫ��ȡ�κ��ж�
		if (pRoot == qRoot) return;

		//��p�ķ���������Ϊq������
		id[pRoot] = qRoot;
		_count--;
	}

private:
	std::vector<int> id;
	int _count;
};

class UF_w_quick_find
{
public:
	UF_w_quick_find(int N)
	{	//��ʼ������id����
		_count = N;
		for (int i = 0; i < N; i++)
			id.push_back(i);
		for (int i = 0; i < N; i++)
			sz.push_back(1);
	}
	int count()
	{
		return _count;
	}

	bool connected(int p, int q) { return find(p) == find(q); }
	int find(int p) {
		//pΪ��ʼ��������id[p]��һ��������������������ʱΪ���ڵ�
		while (p != id[p])
			p = id[p];
		return p;
	}
	void _union(int p, int q) {
		int pRoot = find(p);
		int qRoot = find(q);

		//���p��q�Ѿ�����ͬ�ķ���֮������Ҫ��ȡ�κ��ж�
		if (pRoot == qRoot) return;

		//
		if (sz.at(pRoot) < sz.at(qRoot)) {
			id[pRoot] = qRoot;
			sz.at(qRoot) += sz.at(pRoot);
		}
		else {
			id[qRoot] = pRoot;
			sz.at(pRoot) += sz.at(qRoot);
		}
		_count--;
	}

private:
	std::vector<int> id;
	std::vector<int> sz;
	int _count;
};

TEST(UFTest, tinyUFWork)
{
	std::ifstream input("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\tinyUF.txt");
	if (!input.is_open())
		std::cout << "open file failure" << std::endl;
	int p;
	int q;
	int N;
	input >> N;
	UF uf(N);
	while (!input.eof())
	{
		input >> p;
		input >> q;
		if (uf.connected(p, q)) continue;
		uf._union(p, q);
		//std::cout << p << " " << q << std::endl;
	}
	std::cout << uf.count() << "components" << std::endl;
}

TEST(UFTest, mediumUFWork)
{
	std::ifstream input("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\mediumUF.txt");
	if (!input.is_open())
		std::cout << "open file failure" << std::endl;
	int p;
	int q;
	int N;
	input >> N;
	UF uf(N);
	while (!input.eof())
	{
		input >> p;
		input >> q;
		if (uf.connected(p, q)) continue;
		uf._union(p, q);
		//std::cout << p << " " << q << std::endl;
	}
	std::cout << uf.count() << "components" << std::endl;
}

TEST(UF_quick_findTest, mediumUF_quick_findWork)
{
	std::ifstream input("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\mediumUF.txt");
	if (!input.is_open())
		std::cout << "open file failure" << std::endl;
	int p;
	int q;
	int N;
	input >> N;
	UF_quick_find uf(N);
	while (!input.eof())
	{
		input >> p;
		input >> q;
		if (uf.connected(p, q)) continue;
		uf._union(p, q);
		//std::cout << p << " " << q << std::endl;
	}
	std::cout << uf.count() << "components" << std::endl;
}

TEST(UF_w_quick_findTest, mediumUF_w_quick_findWork)
{
	std::ifstream input("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\mediumUF.txt");
	if (!input.is_open())
		std::cout << "open file failure" << std::endl;
	int p;
	int q;
	int N;
	input >> N;
	UF_w_quick_find uf(N);
	while (!input.eof())
	{
		input >> p;
		input >> q;
		if (uf.connected(p, q)) continue;
		uf._union(p, q);
		//std::cout << p << " " << q << std::endl;
	}
	std::cout << uf.count() << "components" << std::endl;
}

TEST(UF_w_quick_findTest, largeUF_w_quick_findWork)
{
	std::ifstream input("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\largeUF.txt");
	if (!input.is_open())
		std::cout << "open file failure" << std::endl;
	int p;
	int q;
	int N;
	input >> N;
	UF_w_quick_find uf(N);
	while (!input.eof())
	{
		input >> p;
		input >> q;
		if (uf.connected(p, q)) continue;
		uf._union(p, q);
		//std::cout << p << " " << q << std::endl;
	}
	std::cout << uf.count() << "components" << std::endl;
}

}

#endif // !TEST_H
