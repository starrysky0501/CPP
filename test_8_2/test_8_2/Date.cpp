#include"Date.h"

Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
	if (!Invaid())
	{
		cout << "该日期非法!" << endl;
		assert(false);
	}
}

bool LeapYear(int year)
{
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
	{
		return true;
	}
	return false;
}

int GetMonthDay(int year, int month)
{
	static int _array[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && LeapYear(year))  
	{
		return 29;   
	}
	return _array[month];
}

bool Date::Invaid()
{
	if (_year >= 1900 && _month > 0 && _month<13 && _day>0 && _day <= GetMonthDay(_year, _month))
		return true;
	return false;
}

Date::Date(const Date& d)
{
	cout << "Date(const Date&)" << endl;
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

Date::~Date()
{
	cout << "~Date()" << endl;
}

Date& Date::operator=(const Date& d)
{
	if (this != &d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	return *this;
}

bool Date::operator>=(const Date& d) //>=  >  <=  < 只用实现一个功能，另三个用实现的那一个和==函数一起实现
{
	if (_year == d._year)            
	{
		if (_month == d._month)
		{
			if (_day >= d._day)
			{
				return true;
			}
		}
		else if (_month > d._month)
		{
			return true;
		}
	}
	else if (_year > d._year)
	{
		return true;
	}
	return false;
}

bool Date::operator<(const Date& d)
{
	return !(*this >= d);
}

bool Date::operator==(const Date& d)
{
	if (_year == d._year && _month == d._month && _day == d._day)
	{
		return true;
	}
	return false;
}

bool Date::operator<=(const Date& d)
{
	return (*this < d) || (*this == d);
}

bool Date::operator>(const Date& d)
{
	return !(*this <= d);
}

bool Date::operator!=(const Date& d)
{
	if (!(*this == d))
		return true;
	return false;
}

void Date::PrintDate()
{
	cout << _year << "-" << _month << "-" << _day << endl;
}

//思想：先将要加的天数加到_day上，如果超过了该月的天数，就将月数进1，
//      并且把改月的天数减掉，如果月数已经加到大于12，则将年进1，并且将月置1。
Date& Date::operator+=(int day)    //返回如果是Date按值返回，则会出现将返回值先放到一个临时空间中，这个过程会出现拷贝构造，之后返回值后，会有析构的过程，释放掉该空间
{                                  //为了减少不必要的开销，我们返回值按类的引用返回
	_day += day;
	while (_day > GetMonthDay(_year, _month))  
	{
		_day -= GetMonthDay(_year, _month);   
		_month += 1;                         
		if (_month >= 13)
		{
			_year += 1;
			_month = 1;
		}
	}
	return *this;
}

//思想：如果天数减不够，就向上一个月借天数，如果月数借到0，就像年数借1，并且将月置为12，
//      直到天数大于要减的天数，退出循环，此时在进行天数之间的相减。
Date& Date::operator-=(int day)
{
	while (_day <= day)  //必须加上等于，因为如果相等，相减_day为0
	{
		_month -= 1;
		if (_month == 0)
		{
			_year -= 1;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}
	_day -= day;
	return *this;
}

Date Date::operator+(int day)  //和+=的区别在于:+=改变这个对象的值，+不改变该对象的值
{
	Date tmp(*this);           //创建一个临时对象
	tmp += day;
	return tmp;
}

Date Date::operator-(int day)
{
	Date tmp(*this);
	tmp -= day;
	return tmp;
}

//思想：默认第一个日期比第二个日期大，然后比较第一个和第二个日期，让max对象始终保存大的对象,min对象保存小的对象
//      如果第二个日期大于第一个日期，则将flag置-1，设置一个while循环，让min对象一直自增，直到与max相等退出循环。
//      加的天数就是相差的天数。
int Date::operator-(const Date& d)//两个日期对象之间的减法，返回值是相差的天数
{
	Date max(*this);
	Date min(d);
	int flag = 1;
	if (max < min)
	{
		max = d;
		min = *this;
		flag = -1;
	}
	int count = 0;
	while (max != min)
	{
		++count;
		++min;
	}
	return flag*count;
}

//注意区分前置++和后置++
Date& Date::operator++() //前置++
{
	*this += 1;          //通过+=实现 
	return *this;        //返回改变后的值
}

Date Date::operator++(int) //后置++
{
	Date tmp(*this);
	tmp += 1;
	return tmp;         //返回加之前的值
}

//如果，一个对象的作用域在函数之内，则返回值为赋值
//如果，一个对象的作用域出了函数仍存在，则返回值用引用
//赋值，在任何情况下都是正确的，只是有时开销比较大，要减少开销，应考虑引用。