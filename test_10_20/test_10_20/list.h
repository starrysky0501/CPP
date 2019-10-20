namespace LY
{
	template<class T>
	struct __list_node     //��ʾһ�������࣬���ڵ���з�װ
	{
		__list_node<T>* _next;  //Դ�����е�next����void*,����
		__list_node<T>* _prev;
		T _data;

		__list_node(const T&x)
			:_data(x)
			, _next(nullptr)
			, _prev(nullptr)
		{}
	};


	template<class T, class Ref, class Ptr >
	struct __list_iterator     //������ֱ����node*���У���װ���࣬���õ���������ء�
	{
		typedef __list_node<T> node;
		typedef __list_iterator<T, Ref, Ptr> Self;
		node* _node;         //�ڵ��ָ��

		__list_iterator(node *node)
			:_node(node)
		{}

		Ref operator*()         //����ģ�����ó��������������еڶ�������Ϊ�˿������ķ���ֵ
		{
			return _node->_data;
		}

		Self& operator++()    //ǰ��++   ��__list_iterator�ض���ΪSelf��������__list_iterator<T>�ᱨ������̫�١�
		{
			_node = _node->_next;
			return *this;
		}

		Self operator++(int)  //����++
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
		typedef __list_node<T> node;   //���ڵ�������

	public:
		typedef __list_iterator<T,T&,T*> iterator;
		typedef __list_iterator<T,const T&,const T*> const_iterator;  //�������͵ĵ���������ͬһ��struct __list_iterator��ģ��

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

		list()                         //��ʼ��ͷ�ڵ㣬��ͷ˫��ѭ��
		{
			_head = new node(T());
			_head->_next = _head;
			_head->_prev = _head;
		}

		void push_back(const T& x)       //���ﲻ�÷��������Ƿ��ͷ�ڵ�
		{
			node *newnode = new node(x);  //����һ�����,���ù��캯����ʼ��
			node *tail = _head->_prev;   //tail---newnode---head

			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;
		}

	private:
		node* _head;  //ָ��ͷ���ĵ�ָ��
	};


	void print_list(const list<int>& l)   //������const������������const����, ����Ӧ��begin��end�����const
	{
		list<int>::const_iterator it = l.begin();
		while (it != l.end())
		{
			std::cout << *it << " ";
			++it;                        //Ϊʲô�������ú���++
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
			++it;                          //Ϊʲô�������ú���++
		}
		print_list(h);
	}
	
}

