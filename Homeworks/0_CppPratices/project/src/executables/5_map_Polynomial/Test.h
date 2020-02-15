#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include "CPolynomial.h"
#include "CPolynomialMap.h"

using namespace std;

clock_t start_time, end_time;

void RandVector(int n, vector<int> &deg, vector<double> &cof)
{
	int k, de, co;
	deg.clear(); cof.clear();
	for (k = 0; k < n; k++)
	{
		de = rand() % 10000;
		co = (double)(rand() % 1000);
		deg.push_back(de);
		cof.push_back(co);
	}
}

void Test1(const vector<int> &deg1, const vector<double> &cof1, const vector<int> &deg2, const vector<double> &cof2)
{
	cout << "CPolynomialList\n" << endl;
	start_time = clock();
	CPolynomial p1(cof1, deg1);
	CPolynomial p2(cof2, deg2);
	cout << "p1" << endl;
	p1.Print();
	cout << "p2" << endl;
	p2.Print();

	CPolynomial p3 = p1 + p2;     //p3.Print();
	p3 = p1 - p2;                 //p3.Print();
	p3 = p1 * p2;                 //p3.Print();
	end_time = clock();

	cout << "用时 : " << setprecision(8) << (double)(end_time - start_time) / CLOCKS_PER_SEC << "s\n" << endl;
}

void Test2(const vector<int> &deg1, const vector<double> &cof1, const vector<int> &deg2, const vector<double> &cof2)
{
	cout << "CPolynomialMap\n" << endl;
	start_time = clock();
	CPolynomialMap p1(cof1, deg1);
	CPolynomialMap p2(cof2, deg2);
	cout << "p1" << endl;
	p1.Print();
	cout << "p2" << endl;
	p2.Print();

	CPolynomialMap p3 = p1 + p2;     //p3.Print();
	p3 = p1 - p2;                    //p3.Print();
	p3 = p1 * p2;                    //p3.Print();
	end_time = clock();

	cout << "用时 : " << setprecision(8) << (double)(end_time - start_time) / CLOCKS_PER_SEC << "s\n" << endl;
}


#endif // !TEST_H

