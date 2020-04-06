//#include <iostream>
//#include<string>
//#include<stdlib.h> 
//using namespace std;
//int main() {
//	string s1 = "Hello World";
//	cout << "s1 is \"Hello World\"" << endl;
//	string s2 = s1;
//	cout << "s2 is initialized by s1" << endl;
//	string s3(s1);
//	cout << "s3 is initialized by s1" << endl;
//	// compare by '=='
//	cout << "Compared by '==':" << endl;
//	cout << "s1 and \"Hello World\": " << (s1 == "Hello World") << endl;
//	cout << "s1 and s2: " << (s1 == s2) << endl;
//	cout << "s1 and s3: " << (s1 == s3) << endl;
//	// compare by 'compare'
//	cout << "Compared by 'compare':" << endl;
//	cout << "s1 and \"Hello World\": " << !s1.compare("Hello World") << endl;
//	cout << "s1 and s2: " << !s1.compare(s2) << endl;
//	cout << "s1 and s3: " << !s1.compare(s3) << endl;
//	system("pause");
//	return 0;
//}
//
//== 操作符是inline调用compare函数，效果上是一样的；效率上就看编译器是否真的inline化了，如果是则开销相同，否则 == 就多一次函数调用的开销。
//我们可以用 “==” 来比较两个字符串吗？取决于我们使用的语言是否支持运算符重载(c++可以使用)


//#include <iostream>
//#include<string>
//using namespace std;
//int main() {
//	string s1 = "Hello World";
//	s1[5] = ',';
//	s1 = "hello";     //size变小，capacity不变
//	cout << s1 << endl;
//}
//c++得字符串是可变的，可以被修改

#include <iostream>
#include<string>
using namespace std;
int main() {
	string s1 = "Hello World";
	// 1. concatenate
	s1 += "!";
	cout << s1 << endl;
	// 2. find
	cout << "The position of first 'o' is: " << s1.find('o') << endl;   //4
	cout << "The position of last 'o' is: " << s1.rfind('o') << endl;   //7  是从右向左数，但最后一个不是0，是size-1开始
	// 3. get substr
	cout << s1.substr(6, 5) << endl;
}
//注意find和rfind返回的要查找子串的第一次出现的下标，其中find是从0开始查找，而rfind是从n-1开始查找（假设字符串总长度是n），具体参数编程需要的时候查询即可，一定注意的是返回的是下标而非位置，下标i对应位置i+1.
//string的find用法：
//（1）size_t find(const string& str, size_t pos = 0) const;  //查找对象--string类对象
//（2）size_t find(const char* s, size_t pos = 0) const; //查找对象--字符串
//（3）size_t find(const char* s, size_t pos, size_t n) const;  //查找对象--字符串的前n个字符
//（4）size_t find(char c, size_t pos = 0) const;  //查找对象--字符
//结果：找到 -- 返回 第一个字符的索引
//没找到--返回   string::npos
