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
//== ��������inline����compare������Ч������һ���ģ�Ч���ϾͿ��������Ƿ����inline���ˣ������������ͬ������ == �Ͷ�һ�κ������õĿ�����
//���ǿ����� ��==�� ���Ƚ������ַ�����ȡ��������ʹ�õ������Ƿ�֧�����������(c++����ʹ��)


//#include <iostream>
//#include<string>
//using namespace std;
//int main() {
//	string s1 = "Hello World";
//	s1[5] = ',';
//	s1 = "hello";     //size��С��capacity����
//	cout << s1 << endl;
//}
//c++���ַ����ǿɱ�ģ����Ա��޸�

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
	cout << "The position of last 'o' is: " << s1.rfind('o') << endl;   //7  �Ǵ����������������һ������0����size-1��ʼ
	// 3. get substr
	cout << s1.substr(6, 5) << endl;
}
//ע��find��rfind���ص�Ҫ�����Ӵ��ĵ�һ�γ��ֵ��±꣬����find�Ǵ�0��ʼ���ң���rfind�Ǵ�n-1��ʼ���ң������ַ����ܳ�����n����������������Ҫ��ʱ���ѯ���ɣ�һ��ע����Ƿ��ص����±����λ�ã��±�i��Ӧλ��i+1.
//string��find�÷���
//��1��size_t find(const string& str, size_t pos = 0) const;  //���Ҷ���--string�����
//��2��size_t find(const char* s, size_t pos = 0) const; //���Ҷ���--�ַ���
//��3��size_t find(const char* s, size_t pos, size_t n) const;  //���Ҷ���--�ַ�����ǰn���ַ�
//��4��size_t find(char c, size_t pos = 0) const;  //���Ҷ���--�ַ�
//������ҵ� -- ���� ��һ���ַ�������
//û�ҵ�--����   string::npos
