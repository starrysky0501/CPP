#include"Date.h"
int main()
{
	/*Date q(2000,5,30);
	q.PrintDate();
	Date s(q);
	s.PrintDate();
	if (q == s)
	{
		cout << "q的日期等于s" << endl;
	}
	Date g(2000, 5, 1);
	g = q;
	g -= 30;
	g.PrintDate();*/
	Date q(2019, 8, 2);
	Date g(2019, 4, 30);
	int ret = q - g;
	cout << ret << endl;
	system("pause");
	return 0;
}