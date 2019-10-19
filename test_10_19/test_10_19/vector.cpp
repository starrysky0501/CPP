#pragma once
#include <assert.h>
#include<iostream>
#include<stdlib.h>
using namespace std;

namespace LY
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;

		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{}

		vector(const vector<T>& v)
		{
			_start = new T[v.size()];
			memcpy(_start, v._start, sizeof(T)*v.size());
			_finish = _start + v.size();
			_end_of_storage = _start + v.size();
		}


		vector<T>& operator=(vector<T> v)
		{
			//this->swap(v);
			swap(v);
			return *this;
		}

		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _end_of_storage = nullptr;
			}
		}

		void swap(vector<T>& v)
		{
			swap(_start, v._start);
			swap(_finish, v._finish);
			swap(_end_of_storage, v._end_of_storage);
		}

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		void resize(size_t n, const T& val = T())
		{                              //设置有效长度，当小于当前有效长度时，缩短有效长度
			if (n < size())
			{
				_finish = _start + n;
				return;
			}

			if (n > capacity())       //当超出容量时，增容到所给参数位置
			{
				reserve(n);
			}

			while (_finish != _start + n) //当超出当前有效长度，但小于容量，将超出部分置为0
			{
				*_finish = val;
				++_finish;
			}
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t sz = size();
				T* tmp = new T[n];
				if (_start)
				{
					memcpy(tmp, _start, sizeof(T)*sz);
					delete[] _start;
				}

				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + n;
			}
		}

		void push_back(const T& x)
		{
			if (_finish == _end_of_storage)
			{
				size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
				reserve(newcapacity);
			}

			*_finish = x;
			++_finish;
			//insert(end(), x);
		}

		void pop_back()
		{
			assert(_finish > _start);
			--_finish;
			//erase(--end());
		}

		void insert(iterator pos, const T& x)
		{
			assert(pos >= _start && pos <= _finish);

			if (_finish == _end_of_storage)
			{
				size_t n = pos - _start;
				size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
				reserve(newcapacity);
				pos = _start + n;
			}

			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}

			*pos = x;
			++_finish;
		}

		void erase(iterator pos)
		{
			assert(pos < _finish && pos >= _start);
			iterator begin = pos + 1;
			while (begin < _finish)
			{
				*(begin - 1) = *begin;
				++begin;
			}

			--_finish;
		}

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _end_of_storage - _start;
		}

		T& operator[](size_t pos)
		{
			return _start[pos];
		}

		const T& operator[](size_t pos) const
		{
			return _start[pos];
		}
	private:
		iterator _start;    //指向开头地址
		iterator _finish;   //指向最后有效长度的后一个地址
		iterator _end_of_storage;  //指向开辟容量的后一个
	};

};

void test_vector1()
{
	LY::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	auto it = v.begin();
	v.insert(it, 0);
	for (size_t i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	it = v.begin();
	v.erase(it);
	for (size_t i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	LY::vector<int>::iterator iter = v.begin();
	while (iter != v.end())
	{
		cout << *iter << " ";
		++iter;
	}
	cout << endl;

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_vector2()
{
	LY::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	LY::vector<int> copy(v);
	for (auto e : copy)
	{
		cout << e << " ";
	}
	cout << endl;
}

int main()
{
	test_vector1();
	//test_vector2();
	system("pause");
	return 0;
}