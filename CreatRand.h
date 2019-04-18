#pragma once
#ifndef CREATRAND_H
#define CREATRAND_H

#include"gtest/gtest.h"
#include<fstream>
#include<random>
#include<type_traits>

using ::testing::Test;
using ::testing::TestCase;

template<typename Item>
class CreatRand {
public:
	CreatRand(long num){
		this->num = num;
		min = 0;
		max = 100;
		path = "D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\";
		name = "NoName";
	}
	void setRange(Item min,Item max){
		this->min = min;
		this->max = max;
	}
	void setPath(std::string path){
		this->path = path;
	}
	void setFileName(std::string name) {
		this->name = name;
	}
	void run() {
		std::fstream fstrm;
		fstrm.open(path+name,std::ofstream::out);
		std::default_random_engine e;
		std::uniform_real_distribution<Item> u(0, max - min);
		for (long i = 0; i < num; i++) {
			fstrm << u(e) + min << " ";
		}
	}

private:
	long num;
	Item min;
	Item max;
	std::string path;
	std::string name;

};

//对int参数进行特例化（类模板部分特例化、特例化成员）
template<>
void CreatRand<int>::run()
{
	std::fstream fstrm;
	fstrm.open(path + name, std::ofstream::out);
	std::default_random_engine e;
	std::uniform_int_distribution<> u(0, max - min);
	for (long i = 0; i < num; i++) {
		fstrm << u(e) + min << " ";
	}
}



TEST(CreatRandTest, CreatIntRand1) {
	CreatRand<int> r(1000);
	r.setRange(-30000,30000);
	r.setPath("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\");
	r.setFileName("1Kints.txt");
	r.run();
}

TEST(CreatRandTest, CreatIntRand2) {
	CreatRand<int> r(2000);
	r.setRange(-30000, 30000);
	r.setPath("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\");
	r.setFileName("2Kints.txt");
	r.run();
}

TEST(CreatRandTest, CreatIntRand3) {
	CreatRand<int> r(4000);
	r.setRange(-30000, 30000);
	r.setPath("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\");
	r.setFileName("4Kints.txt");
	r.run();
}

TEST(CreatRandTest, CreatIntRand4) {
	CreatRand<int> r(8000);
	r.setRange(-30000, 30000);
	r.setPath("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\");
	r.setFileName("8Kints.txt");
	r.run();
}

TEST(CreatRandTest, CreatIntRand5) {
	CreatRand<int> r(1000000);
	r.setRange(-30000, 30000);
	r.setPath("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\");
	r.setFileName("1Mints.txt");
	r.run();
}

TEST(CreatRandTest, CreatDoubleRand) {
	CreatRand<double> r(100000);
	r.setRange(0, 1);
	r.setPath("D:\\Code\\C++\\Algorithms\\myAlgorithms4\\Algs4\\Data\\");
	r.setFileName("100Kdoubles.txt");
	r.run();
}


#endif // !TEST_H