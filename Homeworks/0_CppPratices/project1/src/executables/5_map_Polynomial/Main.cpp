#include <map>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "CPolynomialMap.h"
#include "CPolynomial.h"
#include "Test.h"
using namespace std;

/*int main()
{
	CPolynomialMap p1("P3.txt");
	CPolynomialMap p2("P4.txt");
	CPolynomialMap p3;
	p1.Print();
	p2.Print();

	p3 = p1 + p2;
	p3.Print();
	p3 = p1 - p2;
	p3.Print();

	p3 = p1 * p2;
	p3.Print();

	system("pause");
	return 0;
}*/

int main()
{
	srand(unsigned(time(0)));
	vector<int> deg1, deg2;
	vector<double> cof1, cof2;

	RandVector(100, deg1, cof1);
	RandVector(100, deg2, cof2);

	Test1(deg1, cof1, deg2, cof2);
	Test2(deg1, cof1, deg2, cof2);

	system("pause");
	return TRUE;
}




