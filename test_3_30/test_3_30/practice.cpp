//#include<iostream>     //leetcode：加一  但是由于数组元素多，并不能采取sum计算
//#include<stdlib.h>
//#include<vector>
//using namespace std;
//vector<int> plusOne(vector<int>& digits) {
//	long long sum = 0;
//	if (digits.size() == 1 && digits[0] == 0)
//	{
//		digits[0] += 1;
//		return digits;
//	}
//	for (int i = 0; i<digits.size(); ++i)
//	{
//		sum *= 10;
//		sum += digits[i];
//	}
//	sum += 1;
//	vector<int> digit;
//	while (sum != 0)
//	{
//		digit.push_back(sum % 10);
//		sum = sum / 10;
//	}
//	reverse(digit.begin(), digit.end());
//	return digit;
//}
//int main()
//{
//	vector<int> arr = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
//	plusOne(arr);
//	system("pause");
//	return 0;
//}



//int main()
//{
//	int a[5] = { 0, 1, 2, 3, 4 };
//	vector<int> arr(a, *(&a + 1));             //验证第二个参数的含义：给数组取地址，则是一个数组指针，+1，跨越一个数组，解引用则是将数组指针变成数组，也就是地址
//	vector<int>::iterator it = arr.begin();
//	for (it; it != arr.end(); it++)
//	{
//		cout << *it << " ";
//	}
//	cout << endl;
//	for (int &temp : arr)
//	{
//		cout << temp << " ";
//	}
//	system("pause");
//	return 0;
//}


//#include <iostream>
//#include <stdlib.h>
//using namespace std;
//template <size_t n, size_t m>
//void printArray(int (&a)[n][m]) {         //验证形参的含义：是一个数组的引用，注意区分：数组元素是引用类型
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < m; ++j) {
//			cout << a[i][j] << " ";
//		}
//		cout << endl;
//	}
//}
//
//int main() {
//	cout << "Example I:" << endl;
//	int a[2][5];
//	printArray(a);
//	cout << "Example II:" << endl;
//	int b[2][5] = { { 1, 2, 3 } };
//	printArray(b);
//	cout << "Example III:" << endl;
//	int c[][5] = { 1, 2, 3, 4, 5, 6, 7 };
//	printArray(c);
//	cout << "Example IV:" << endl;
//	int d[][5] = { { 1, 2, 3, 4 }, { 5, 6 }, { 7 } };
//	printArray(d);
//	system("pause");
//}

//#include<iostream>
//#include<vector>
//using namespace std;
//int main()
//{
//	vector<vector<int>> arr(0, vector<int>(0));    //size=0  capacity=0
//	return 0;
//}


//vector的assign函数
//#include<iostream>
//#include<vector>
//#include<stdlib.h>
//using namespace std;
//int main()
//{
//	vector<int> arr = { 1, 2, 3, 4, 5, 6, 7 ,8};
//	vector<int> ass;
//	ass.assign(arr.begin(), arr.end());
//	for (auto it = ass.begin(); it != ass.end(); ++it)
//	{
//		cout << *it << " ";
//	}
//	cout << endl;
//	ass.assign(3, 4);
//	for (auto it = ass.begin(); it != ass.end(); ++it)
//	{
//		cout << *it << " ";
//	}
//
//
//	vector<vector<int>>arrs(5);
//
	//vector<vector<int> > res;
	//res.assign(4, vector<int>(2));
	//for (int i = 0; i < 4; ++i)
	//{
	//	cout << res[i][0] << " " << res[i][1] << " ";
	//}
	//system("pause");
	//return 0;
//}