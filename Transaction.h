#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include"gtest/gtest.h"
#include"Date.h"
#include<string>

class Transaction;
using ::testing::Test;
using ::testing::TestCase;


class Transaction {
public:
	Transaction(std::string who, Date when, double amount):_name(who),_time(when),_amount(amount) {}
	Transaction(std::string transaction) { 
		std::vector<std::string> units;
		std::string::size_type cur_pos = 0;
		std::string::size_type pre_pos = 0;
		//将date按/符号来划分
		while ((cur_pos = transaction.find_first_of("/", pre_pos)) != std::string::npos) {
			units.push_back(transaction.substr(pre_pos, cur_pos));
			pre_pos = cur_pos + 1;
		}
		units.push_back(transaction.substr(pre_pos, transaction.size()));

		_name = units.at(0);
		Date d(units.at(1));
		_time = d;
		_amount = std::stod(units.at(2));
	}
	std::string who() const { return _name; }
	Date when() const { return _time; }
	double amount() const { return _amount; }
	std::string toString() const {}
	bool equals(const Transaction &that) const {
		if (_name != that.who()) return false;
		if (_time != that.when()) return false;
		if (_amount != that.amount()) return false;
		return true;
	}
	int compareTo(Date that) const {}
	int hashCode() const {}

private:
	std::string _name;
	Date _time;
	double _amount;
};

#endif // !TEST_H
