#include"Date.h"

Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
	if (!Invaid())
	{
		cout << "�����ڷǷ�!" << endl;
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

bool Date::operator>=(const Date& d) //>=  >  <=  < ֻ��ʵ��һ�����ܣ���������ʵ�ֵ���һ����==����һ��ʵ��
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

//˼�룺�Ƚ�Ҫ�ӵ������ӵ�_day�ϣ���������˸��µ��������ͽ�������1��
//      ���ҰѸ��µ�������������������Ѿ��ӵ�����12�������1�����ҽ�����1��
Date& Date::operator+=(int day)    //���������Date��ֵ���أ������ֽ�����ֵ�ȷŵ�һ����ʱ�ռ��У�������̻���ֿ������죬֮�󷵻�ֵ�󣬻��������Ĺ��̣��ͷŵ��ÿռ�
{                                  //Ϊ�˼��ٲ���Ҫ�Ŀ��������Ƿ���ֵ��������÷���
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

//˼�룺���������������������һ���½���������������赽0������������1�����ҽ�����Ϊ12��
//      ֱ����������Ҫ�����������˳�ѭ������ʱ�ڽ�������֮��������
Date& Date::operator-=(int day)
{
	while (_day <= day)  //������ϵ��ڣ���Ϊ�����ȣ����_dayΪ0
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

Date Date::operator+(int day)  //��+=����������:+=�ı���������ֵ��+���ı�ö����ֵ
{
	Date tmp(*this);           //����һ����ʱ����
	tmp += day;
	return tmp;
}

Date Date::operator-(int day)
{
	Date tmp(*this);
	tmp -= day;
	return tmp;
}

//˼�룺Ĭ�ϵ�һ�����ڱȵڶ������ڴ�Ȼ��Ƚϵ�һ���͵ڶ������ڣ���max����ʼ�ձ����Ķ���,min���󱣴�С�Ķ���
//      ����ڶ������ڴ��ڵ�һ�����ڣ���flag��-1������һ��whileѭ������min����һֱ������ֱ����max����˳�ѭ����
//      �ӵ�������������������
int Date::operator-(const Date& d)//�������ڶ���֮��ļ���������ֵ����������
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

//ע������ǰ��++�ͺ���++
Date& Date::operator++() //ǰ��++
{
	*this += 1;          //ͨ��+=ʵ�� 
	return *this;        //���ظı���ֵ
}

Date Date::operator++(int) //����++
{
	Date tmp(*this);
	tmp += 1;
	return tmp;         //���ؼ�֮ǰ��ֵ
}

//�����һ��������������ں���֮�ڣ��򷵻�ֵΪ��ֵ
//�����һ���������������˺����Դ��ڣ��򷵻�ֵ������
//��ֵ�����κ�����¶�����ȷ�ģ�ֻ����ʱ�����Ƚϴ�Ҫ���ٿ�����Ӧ�������á�