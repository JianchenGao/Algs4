#pragma once
#include "gtest/gtest.h"
#include<string>

using ::testing::Test;
using ::testing::TestCase;

class Counter
{
private:
	std::string name;
	int count;
public:
	Counter() {}
	Counter(std::string id) :count(0){ name = id; }
	void increment() { count++; }
	int tally() { return count; }
	std::string toString() { return std::to_string(count) + " " + name; }
};

class CounterTest :public ::testing::Test {
public:
	CounterTest(){}
protected:
	void SetUp() override {
		heads = new Counter("heads");
		tails = new Counter("tails");
	}
	void TearDown() override {
	}
	Counter *heads;
	Counter *tails;
};

TEST_F(CounterTest, CounterInitValue) {
	ASSERT_EQ(heads->tally(), 0);
	ASSERT_EQ(tails->tally(), 0);
	ASSERT_EQ(heads->tally(), tails->tally());
}

TEST_F(CounterTest, CounterWork) {
	for (auto i = 0; i < 1000; i++) {
		heads->increment();
		tails->increment();
	}
	ASSERT_EQ(heads->tally(), tails->tally());
	ASSERT_EQ(heads->tally(), 1000);
}

TEST_F(CounterTest, CounterCout) {
	for (auto i = 0; i < 100; i++) {
		heads->increment();
		tails->increment();
	}
	ASSERT_EQ(heads->toString(), "100 heads");
	ASSERT_EQ(tails->toString(), "100 tails");
}