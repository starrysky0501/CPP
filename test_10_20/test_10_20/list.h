namespace LY
{
	template<class T>
	struct __list_node     //表示一个结点的类，将节点进行封装
	{
		__list_node<T>* _next;  //源代码中的next用了void*,泛型
		__list_node<T>* _prev;
		T _data;

		__list_node(const T&x)
			:_data(x)
			, _next(nullptr)
			, _prev(nullptr)
		{}
	};


	template<class T, class Ref, class Ptr >     //代码复用性
	struct __list_iterator     //迭代器直接用node*不行，封装成类，会用到运算符重载。
	{
		typedef __list_node<T> node;
		typedef __list_iterator<T, Ref, Ptr> Self;
		node* _node;         //节点的指针

		__list_iterator(node *node)
			:_node(node)
		{}

		Ref operator*()        //将类模板设置成三个参数，其中第二个就是为了控制它的返回值
		{
			return _node->_data;   //供内置类型使用
		}

		Ptr operator->()       //由于我是用Date类调用，所以这里的返回值可以理解为Date*
		{
			return &_node->_data;  //供自定义类型使用
		}

		Self& operator++()    //前置++   将__list_iterator重定义为Self，否则用__list_iterator<T>会报错，参数太少。
		{
			_node = _node->_next;
			return *this;
		}

		Self operator++(int)  //后置++
		{
			__list_node<T> tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		Self& operator--()   
		{
			_node = _node->_prev;
			return *this;
		}

		Self operator--(int)  
		{
			__list_node<T> tmp(*this);
			_node = _node->_prev;
			return tmp;
		}

		bool operator!=(const Self& it)  //用节点的指针比较
		{
			return _node != it._node;
		}

		bool operator==(const Self& it)
		{
			return _node == it._node;
		}
	};


	template<class T>
	class list
	{
		typedef __list_node<T> node;   //将节点重命名

	public:
		typedef __list_iterator<T,T&,T*> iterator;
		typedef __list_iterator<T,const T&,const T*> const_iterator;  //两个类型的迭代器复用同一个struct __list_iterator类模板

		iterator begin()  
		{
			return iterator(_head->_next);
		}

		iterator end()  
		{
			return iterator(_head);
		}
		const_iterator begin()  const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end()   const
		{
			return const_iterator(_head);
		}

		list()                         //初始化头节点，带头双向循环
		{
			_head = new node(T());
			_head->_next = _head;
			_head->_prev = _head;
		}

		void push_back(const T& x)       //这里不用分类讨论是否带头节点
		{
			//node *newnode = new node(x);  //创建一个结点,调用构造函数初始化
			//node *tail = _head->_prev;   //tail---newnode---head

			//tail->_next = newnode;
			//newnode->_prev = tail;
			//newnode->_next = _head;
			//_head->_prev = newnode;

			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}

		void insert(iterator pos, const T& x)  //在pos位置前插入该x值
		{
			node* cur = pos._node;
			node* prev = cur->_prev;
			node* newnode = new node(x);

			prev->_next = newnode;     //prev newnode cur
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
		}

		void erase(iterator pos)   //迭代器pos失效，被delete
		{
			node* cur = pos._node;
			assert(cur != _head);

			node* prev = cur->_prev;
			node* next = cur->_next;

			prev->_next = next;
			next->_prev = prev;

			delete cur;
		}

	private:
		node* _head;  //指向头结点的的指针
	};


	void print_list(const list<int>& l)   //由于是const对象，则必须调用const函数, 所以应给begin和end后面加const
	{
		list<int>::const_iterator it = l.begin();        //只能读不能修改
		while (it != l.end())
		{
			std::cout << *it << " ";
			++it;                        //为什么不可以用后置++
		}
		std::cout << std::endl;
	}

	void Test_list1()
	{
		LY::list<int> h;
		h.push_back(1);
		h.push_back(2);
		h.push_back(3);
		h.push_back(4);
		print_list(h);                    

		list<int>::iterator it = h.begin();
		while (it != h.end())                 //可读可修改
		{
			*it *= 2;
			++it;                          //为什么不可以用后置++
		}
		print_list(h);
	}
	

	struct Date
	{
		int _year = 1900;
		int _month = 1;
		int _day = 1;
	};
	
	void Test_list2()
	{
		list<Date> l;
		l.push_back(Date());
		l.push_back(Date());
		auto it = l.begin();
		while (it != l.end())
		{
			//it->_year可以理解为：it.operator->()_year,但其实是it->->_year;但为了可读性，编译器做了特殊处理，省掉了一个箭头符号
			std::cout <<it->_year<<"-"<<it->_month<<"-"<<it->_day<< std::endl;
			++it;
		}

	}
}



