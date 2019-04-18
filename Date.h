#pragma once
#ifndef DATE_H
#define DATE_H

#include"gtest/gtest.h"
#include<string>

using ::testing::Test;
using ::testing::TestCase;

//bool operator!=(const Date &lhs, const Date &rhs);
//bool operator==(const Date &lhs, const Date &rhs);

class Date {
public:
	Date() {}	//一定要有默认构造函数，否则无法定义默认的（无参数）类对象
	Date(int month, int day, int year):_month(month),_day(day),_year(year) {}
	Date(std::string date) {
		std::vector<std::string> units;
		std::string::size_type cur_pos = 0;
		std::string::size_type pre_pos = 0;
		//将date按/符号来划分
		while ((cur_pos = date.find_first_of("/", pre_pos)) != std::string::npos) {
			units.push_back(date.substr(pre_pos, cur_pos));
			pre_pos = cur_pos+1;
		}
		units.push_back(date.substr(pre_pos, date.size()));

		_month = std::stoi(units.at(0));
		_day = std::stoi(units.at(1));
		_year = std::stoi(units.at(2));
	}
	int month() const { return _month; }
	int day() const { return _day; }
	int year() const { return _year; }
	std::string toString() const {
		return std::to_string(_month) + "/" + std::to_string(_day) + "/" + std::to_string(_year);
	}
	bool equals(const Date &d) const {
		if (_month != d.month()) return false;
		if (_day != d.day()) return false;
		if (_year != d.year()) return false;
		return true;
	}
	int compareTo(const Date &that) const { return this->equals(that); }
	int hashCode() const {}

private:
	int _month;
	int _day;
	int _year;
};
bool operator!= (const Date &lhs, const Date &rhs) { return !(lhs.equals(rhs)); }
bool operator==(const Date &lhs, const Date &rhs) { return lhs.equals(rhs); }


TEST(DateTest,DateCreate1)
{
	Date d(3,21,2019);
	ASSERT_EQ(d.day(),21);
	ASSERT_EQ(d.month(), 3);
	ASSERT_EQ(d.year(), 2019);

	ASSERT_EQ(d.toString(), "3/21/2019");
}

TEST(DateTest, DateCreate2)
{
	Date d("3/21/2019");
	ASSERT_EQ(d.day(), 21);
	ASSERT_EQ(d.month(), 3);
	ASSERT_EQ(d.year(), 2019);

	ASSERT_EQ(d.toString(), "3/21/2019");
}

TEST(DateTest, DateEquals)
{
	Date d1(3, 21, 2019);
	Date d2(3, 21, 2019);
	Date d3(4, 21, 2019);

	ASSERT_EQ(d1.equals(d2), true);
	ASSERT_EQ(d1.equals(d3), false);

	ASSERT_EQ(d1.compareTo(d2), true);
	ASSERT_EQ(d1.compareTo(d3), false);
}


#endif // !TEST_H
