#include "CPolynomial.h"
#include <list>
#include <iostream>

using namespace std;

int main()
{
	
	//vector<double> a = { 2,3,9 };
	//vector<int> b = { 1,5,3 };
	//CPolynomial p1(a, b);
	CPolynomial p1("P1.txt");
	CPolynomial p2("P2.txt");
	p1.Print();
	p2.Print();
	CPolynomial pt = p1 + p2;
	pt.Print();


	CPolynomial p3("P3.txt");
	CPolynomial p4("P4.txt");
	CPolynomial pt2 = p3 * p4;
	p3.Print();
	p4.Print();
	pt2.Print();
	system("pause");
	return TRUE;
}

/*int main()
{
	CPolynomial p1("P3.txt");
	CPolynomial p2("P4.txt");
	CPolynomial p3;
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