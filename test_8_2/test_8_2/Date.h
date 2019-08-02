#pragma once
#include<iostream>
#include<cstdlib>
#include<cassert>
using namespace std;

class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1);
	Date(const Date& d);
	Date& operator=(const Date& d);
	bool operator<(const Date& d);
	bool operator>(const Date& d);
	bool operator<=(const Date& d);
	bool operator>=(const Date& d);
	bool operator==(const Date& d);
	bool operator!=(const Date& d);
	Date operator+(int day);
	Date operator-(int day);
	Date& operator+=(int day);
	Date& operator-=(int day);
	int operator-(const Date& d);
	Date& operator++();
	Date operator++(int);
	void PrintDate();
	bool Invaid();
	~Date();
private:
	int _year;
	int _month;
	int _day;
};