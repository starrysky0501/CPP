#include<iostream>
#include<stdlib.h>
#include"list.h"
using namespace std;
int main()
{
	LY::Test_list1();
	system("pause");
	return 0;
}



//学习笔记：
//容器的空间不是找系统要，要找空间配置器，空间配置器是一个内存池，内存池是为了提高效率
//list的iterator是一个类模板，里面的成员变量是结点指针，该类中通过实现一些运算符重载实现访问结点的值或++结点到达下一个结点
//string s赋一个字符串(含\0)，以s.c_str形式输出，则会遇到\0结束，以s输出，不会遇到\0终止，根据字符的个数输出
//istream和ostream都是一个类，cin和out分别是他们的对象
//cin.get()返回一个字符，没有参数
//string和vector的迭代器都是原生指针；list的迭代器是一个类，这个类中包含着节点的指针。解引用的时候会调用自己的运算符重载函数operator*()，++的时候同理
//空间不是重要，类型比较重要