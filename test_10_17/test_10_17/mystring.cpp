#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
namespace LY
{
	class string
	{
	public:
		string(const char * str = "")  //带有默认参数的构造函数，注意不能写成nullptr，因为防止空指针的解引用（访问\0)
			:_str(new char[strlen(str) + 1])  //采用c风格的指针字符串求长度
		{
			strcpy(_str, str);    //带有‘\0’的拷贝
			_size = strlen(str);   
			_capacity = _size;    //有两种方式,其中一种是只拷贝 size大小，另外一种是将capacity大小拷贝。
		}


		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}


		//string copy1(s1)
		string(const string &s)//引用，防止无限递归
			:_str(new char[s._size+1])  //size和capacity的大小表示实际字符串的大小，没包含‘\0’
			, _size(s._size)
			, _capacity(s._size)
		{
			strcpy(_str, s._str);
		}


		string& operator=(const string& s)
		{
			if (this != &s)//考虑自己给自己赋值
			{
				delete[] _str;//释放掉旧空间，开辟新空间，拷贝内容。
				_str = new char[s._size + 1];
				strcpy(_str, s._str);
				_size = s._size;
				_capacity = s._size;   //之开辟size大小
			}
			return *this;
		}


		const char* c_str()   //c风格的字符串，未实现opeartor<<()之前使用该函数输出字符串。
		{
			return _str;
		}


		//[]+下标法访问数组元素
		char& operator[](size_t pos)   //可以修改，做左值
		{
			assert(pos < _size);
			return _str[pos];
		}


		const char& operator[](size_t pos) const    //返回const 不可以被修改
		{
			assert(pos < _size);
			return _str[pos];
		}


		size_t size()
		{
			return _size;
		}


		size_t capacity()
		{
			return _capacity;
		}
		 

		//遍历string的元素 迭代器的模拟实现
		typedef const char* const_iterator;
		typedef char* iterator;               //string的iterator是原生指针。

		const_iterator begin()const     //const迭代器
		{
			return _str;
		}


		iterator begin()
		{
			return _str;
		}


		const_iterator end() const    //const迭代器
		{
			return _str + _size;
		}


		iterator end()
		{
			return _str + _size;
		}


        //增删改查的模拟实现
		void reserve(size_t n)
		{
			if (n > _capacity)  //增容，所增容量为n，如果小于原有容量则保持不变。
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}


		void push_back(char ch)    //后插一个字符
		{
			if (_size == _capacity)
			{
				reserve(_capacity * 2);    //扩容
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';     //别忘记加‘\0'
		}


		void append(const char* str)      //在结尾追加一个字符串
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);  //注意：不能以2倍的增长速度
			}
			strcpy(_str + _size, str);
			_size += len;
		}


		//+=的三种形式
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}


		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}


		string& operator+=(const string& s)
		{
			append(s._str);
			return *this;
		}


		void insert(size_t pos, char ch)    // 在某个位置插入一个字符
		{
			assert(pos <= _size);
			if (_size == _capacity)
			{
				reserve(_capacity * 2);
			}
			int end = _size;
			while (end >= (int)pos)
			{
				_str[end + 1] = _str[end];
				--end;
			}
			_str[pos] = ch;
			++_size;
		}


		void insert(size_t pos, const char* str)
		{
			assert(pos <= _size);
			size_t len = strlen(str);
			if (_size + len > _capacity)   //扩容指定空间
			{
				reserve(_size + len);
			}
			int end = _size;
			while (end >= (int)pos)    //将pos位置之后的元素向后移动
			{
				_str[end + len] = _str[end];
				--end;
			}
			while (*str)      //从pos位置开始向后放str的元素
			{
				_str[pos++] = *str++;
			}
			_size += len;
		}


		void erase(size_t pos, size_t n)
		{
			assert(pos < _size);    //判断参数的合法性， _size是合法的，但\0不要删，如果删了这里判断为不合法。
			if (pos + n < _size)
			{
				size_t index = pos + n;
				while (index != _size)    //遇到\0停止循环
				{
					_str[pos++] = _str[index++];
				}
				_str[pos] = '\0';
				_size = pos;
			}
			else                   //当pos+n大于等于_size时，都是删除pos之后的所有元素
			{
				_str[pos] = '\0';
				_size = pos;
			}
		}


		static const size_t npos = -1;
		size_t find(char ch, size_t pos=0) //从pos位置后开始查找一个字符，找到返回字符在字符串中的下标，找不到返回全局变量npos=-1
		{
			if (pos >= _size || pos < 0)
			{
				return npos;
			}
			while (pos != _size)   //到达'\0'结束
			{
				if (_str[pos] == ch)
					return pos;
				else pos++;
			}
			return npos;
		}


		size_t find(const char *str)
		{
			size_t index =0;
			while (_str[index] != '\0')
			{
				if (_str[index] == *str)      //如果开头字符相等
				{
					size_t find = index;     //表示父串比较的起始位置
					size_t t = 0;            //表示字串比较的起使位置，每次都是0开始
					while (1)                //遍历完字符串str，就表示找到了
					{
						if (str[t] == '\0')  //走完str了
							return index;
						if (_str[find] != str[t])
							break;
						find++;
						t++;
					}                       //循环结束
				}                           //表示不匹配了，不相等了，父串向前走
				index++;
			}
			return -1;      
		}


        //运算符的重载
		string operator+(char ch)    //追加一个字符
		{
			string tmp(_str);
			tmp.insert(_size, ch);
			return tmp;
		}


		string operator+(const char* str)
		{
			string tmp(_str);
			tmp.insert(_size, str);
			return tmp;
		}


		bool operator>(const string& s)  const
		{
			const char* str1 = _str;
			const char* str2 = s._str;
			while (*str1 && *str2)
			{
				if (*str1 > *str2)
				{
					return true;
				}
				else if (*str1 < *str2)
				{
					return false;
				}
				else
				{
					++str1;
					++str2;
				}
			}
			if (*str1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}


		bool operator==(const string& s) const
		{
			const char* str1 = _str;
			const char* str2 = s._str;
			while (*str1 && *str2)
			{
				if (*str1 != *str2)
				{
					return false;
				}
				else
				{
					++str1;
					++str2;
				}
			}
			if (*str1 || *str2)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		bool operator >=(const string &s)const
		{
			return *this > s || *this == s;
		}


		bool operator<(const string &s)const
		{
			return !(*this >= s);
		}


		bool operator<=(const string &s)
		{
			return *this < s || *this == s;
		}

		bool operator!=(const string &s)
		{
			return !(*this == s);
		}

		friend ostream& operator<<(ostream& _cout, const LY::string& s);
		friend istream& operator>>(istream& _cin, const LY::string& s);


	private:
		char *_str;
		size_t _size;
		size_t _capacity;
	};
}

//ostream& operator<<(ostream& _cout, const LY::string& s)
//{
//	_cout << s.c_str;
//	return _cout;
//}
//
//
//istream& operator>>(istream& _cin, const LY::string& s)
//{
//	
//}


void Teststring()
{
	LY::string s1("Hello");
	s1[0] = 'h';                        //验证构造函数
	cout << s1.c_str() << endl;
	LY::string s2;
	cout << s2.c_str() << endl;         //系统未崩

	LY::string copy1(s1);              //验证拷贝构造函数
	cout << copy1.c_str() << endl;

	copy1[0] = 'H';                    //证明深拷贝实现成功，两个对象相对独立
	cout << s1.c_str() << endl;
	cout << copy1.c_str() << endl;

	for (size_t i = 0; i < s1.size(); i++)
	{
		s1[i] = 'a';
		cout << s1[i] << " ";
	}
	cout << endl;

	LY::string::iterator it1 = s1.begin();
	while (it1 != s1.end())
	{
		cout << *it1 << " ";
		++it1;
	}
	cout << endl;

	for (auto e : s1)
	{
		cout << e << " ";
	}
	cout << endl;
}

void Teststring2()
{
		LY::string s1("hello");           //计算出字符串的长度时5，申请6个空间
		cout << s1.capacity() << endl;
	
		s1 += "world";                    //+=的C语言字符串模拟实现，开辟指定的空间
		cout << s1.capacity() << endl;
	
		s1 += '!';                        //+=的字符模拟实现，增大原先2倍的空间
		cout << s1.capacity() << endl;
	
		cout << s1.c_str() << endl;       //打印出字符串
	
		LY::string s2("world");
		s2.insert(0, ' ');
		cout << s2.c_str() << endl;
		s2.insert(0, "hello");
		cout << s2.c_str() << endl;
		s2.push_back('!');
		cout << s2.c_str() << endl;
		s2.append("come on!");
		cout << s2.c_str() << endl;
		size_t pos = s2.find('!');
		s2.erase(pos, 13);
		cout << s2.c_str() << endl;
		size_t pos2 = s2.find("world");
		cout << pos2 << endl;

}

void Teststring3()
{
	LY::string s1("hello");
	LY::string s2("hello");
	LY::string s3 = s1 + " world";
	cout << s3.c_str() << endl;
	
	if ((s1 == s2) == 1)
		cout << "TRUE" << endl;
	else
		cout << "FALSE" << endl;
}

int main()
{
	//Teststring();
	//Teststring2();
	Teststring3();
	system("pause");
	return 0;
}