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
		string(const char * str = "")  //����Ĭ�ϲ����Ĺ��캯����ע�ⲻ��д��nullptr����Ϊ��ֹ��ָ��Ľ����ã�����\0)
			:_str(new char[strlen(str) + 1])  //����c����ָ���ַ����󳤶�
		{
			strcpy(_str, str);    //���С�\0���Ŀ���
			_size = strlen(str);   
			_capacity = _size;    //�����ַ�ʽ,����һ����ֻ���� size��С������һ���ǽ�capacity��С������
		}


		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}


		//string copy1(s1)
		string(const string &s)//���ã���ֹ���޵ݹ�
			:_str(new char[s._size+1])  //size��capacity�Ĵ�С��ʾʵ���ַ����Ĵ�С��û������\0��
			, _size(s._size)
			, _capacity(s._size)
		{
			strcpy(_str, s._str);
		}


		string& operator=(const string& s)
		{
			if (this != &s)//�����Լ����Լ���ֵ
			{
				delete[] _str;//�ͷŵ��ɿռ䣬�����¿ռ䣬�������ݡ�
				_str = new char[s._size + 1];
				strcpy(_str, s._str);
				_size = s._size;
				_capacity = s._size;   //֮����size��С
			}
			return *this;
		}


		const char* c_str()   //c�����ַ�����δʵ��opeartor<<()֮ǰʹ�øú�������ַ�����
		{
			return _str;
		}


		//[]+�±귨��������Ԫ��
		char& operator[](size_t pos)   //�����޸ģ�����ֵ
		{
			assert(pos < _size);
			return _str[pos];
		}


		const char& operator[](size_t pos) const    //����const �����Ա��޸�
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
		 

		//����string��Ԫ�� ��������ģ��ʵ��
		typedef const char* const_iterator;
		typedef char* iterator;               //string��iterator��ԭ��ָ�롣

		const_iterator begin()const     //const������
		{
			return _str;
		}


		iterator begin()
		{
			return _str;
		}


		const_iterator end() const    //const������
		{
			return _str + _size;
		}


		iterator end()
		{
			return _str + _size;
		}


        //��ɾ�Ĳ��ģ��ʵ��
		void reserve(size_t n)
		{
			if (n > _capacity)  //���ݣ���������Ϊn�����С��ԭ�������򱣳ֲ��䡣
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}


		void push_back(char ch)    //���һ���ַ�
		{
			if (_size == _capacity)
			{
				reserve(_capacity * 2);    //����
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';     //�����Ǽӡ�\0'
		}


		void append(const char* str)      //�ڽ�β׷��һ���ַ���
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);  //ע�⣺������2���������ٶ�
			}
			strcpy(_str + _size, str);
			_size += len;
		}


		//+=��������ʽ
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


		void insert(size_t pos, char ch)    // ��ĳ��λ�ò���һ���ַ�
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
			if (_size + len > _capacity)   //����ָ���ռ�
			{
				reserve(_size + len);
			}
			int end = _size;
			while (end >= (int)pos)    //��posλ��֮���Ԫ������ƶ�
			{
				_str[end + len] = _str[end];
				--end;
			}
			while (*str)      //��posλ�ÿ�ʼ����str��Ԫ��
			{
				_str[pos++] = *str++;
			}
			_size += len;
		}


		void erase(size_t pos, size_t n)
		{
			assert(pos < _size);    //�жϲ����ĺϷ��ԣ� _size�ǺϷ��ģ���\0��Ҫɾ�����ɾ�������ж�Ϊ���Ϸ���
			if (pos + n < _size)
			{
				size_t index = pos + n;
				while (index != _size)    //����\0ֹͣѭ��
				{
					_str[pos++] = _str[index++];
				}
				_str[pos] = '\0';
				_size = pos;
			}
			else                   //��pos+n���ڵ���_sizeʱ������ɾ��pos֮�������Ԫ��
			{
				_str[pos] = '\0';
				_size = pos;
			}
		}


		static const size_t npos = -1;
		size_t find(char ch, size_t pos=0) //��posλ�ú�ʼ����һ���ַ����ҵ������ַ����ַ����е��±꣬�Ҳ�������ȫ�ֱ���npos=-1
		{
			if (pos >= _size || pos < 0)
			{
				return npos;
			}
			while (pos != _size)   //����'\0'����
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
				if (_str[index] == *str)      //�����ͷ�ַ����
				{
					size_t find = index;     //��ʾ�����Ƚϵ���ʼλ��
					size_t t = 0;            //��ʾ�ִ��Ƚϵ���ʹλ�ã�ÿ�ζ���0��ʼ
					while (1)                //�������ַ���str���ͱ�ʾ�ҵ���
					{
						if (str[t] == '\0')  //����str��
							return index;
						if (_str[find] != str[t])
							break;
						find++;
						t++;
					}                       //ѭ������
				}                           //��ʾ��ƥ���ˣ�������ˣ�������ǰ��
				index++;
			}
			return -1;      
		}


        //�����������
		string operator+(char ch)    //׷��һ���ַ�
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
	s1[0] = 'h';                        //��֤���캯��
	cout << s1.c_str() << endl;
	LY::string s2;
	cout << s2.c_str() << endl;         //ϵͳδ��

	LY::string copy1(s1);              //��֤�������캯��
	cout << copy1.c_str() << endl;

	copy1[0] = 'H';                    //֤�����ʵ�ֳɹ�������������Զ���
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
		LY::string s1("hello");           //������ַ����ĳ���ʱ5������6���ռ�
		cout << s1.capacity() << endl;
	
		s1 += "world";                    //+=��C�����ַ���ģ��ʵ�֣�����ָ���Ŀռ�
		cout << s1.capacity() << endl;
	
		s1 += '!';                        //+=���ַ�ģ��ʵ�֣�����ԭ��2���Ŀռ�
		cout << s1.capacity() << endl;
	
		cout << s1.c_str() << endl;       //��ӡ���ַ���
	
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