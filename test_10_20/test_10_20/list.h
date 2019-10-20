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


	template<class T, class Ref, class Ptr >
	struct __list_iterator     //迭代器直接用node*不行，封装成类，会用到运算符重载。
	{
		typedef __list_node<T> node;
		typedef __list_iterator<T, Ref, Ptr> Self;
		node* _node;         //节点的指针

		__list_iterator(node *node)
			:_node(node)
		{}

		Ref operator*()         //将类模板设置成三个参数，其中第二个就是为了控制它的返回值
		{
			return _node->_data;
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

		bool operator!=(const Self& it)
		{
			return _node != it._node;
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
			node *newnode = new node(x);  //创建一个结点,调用构造函数初始化
			node *tail = _head->_prev;   //tail---newnode---head

			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;
		}

	private:
		node* _head;  //指向头结点的的指针
	};


	void print_list(const list<int>& l)   //由于是const对象，则必须调用const函数, 所以应给begin和end后面加const
	{
		list<int>::const_iterator it = l.begin();
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
		while (it != h.end())
		{
			*it *= 2;
			++it;                          //为什么不可以用后置++
		}
		print_list(h);
	}
	
}

