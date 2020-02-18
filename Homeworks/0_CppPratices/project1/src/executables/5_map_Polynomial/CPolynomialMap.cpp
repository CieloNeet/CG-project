#include <iostream>
#include <algorithm>
#include <fstream>
#include "CPolynomialMap.h"

CPolynomialMap::CPolynomialMap()
{
	//m_PolynomialMap.clear();
}

CPolynomialMap::CPolynomialMap(const CPolynomialMap& right)
{
	m_PolynomialMap.clear();
	map<int, double>::const_iterator it;
	for (it = right.m_PolynomialMap.begin(); it != right.m_PolynomialMap.end(); it++)
	{
		m_PolynomialMap.insert(make_pair(it->first, it->second));
	}
}

CPolynomialMap::CPolynomialMap(const string& file)
{
	ReadFromFile(file);
}

CPolynomialMap::CPolynomialMap(double *cof, double *deg, int n)
{
	int k;
	for (k = 0; k < n; k++)
	{
		Insert(deg[k], cof[k]);
	}
}

CPolynomialMap::CPolynomialMap(const vector<double>& cof, const  vector<int> & deg)
{
	int m1 = cof.size(), m2 = deg.size();
	int n = m1 < m2 ? m1 : m2;
	for (int k = 0; k < n; k++)
	{
		Insert(deg[k], cof[k]);
	}
}

CPolynomialMap::~CPolynomialMap()
{
	m_PolynomialMap.clear();
}


CPolynomialMap CPolynomialMap::operator+(const CPolynomialMap &right)
{
	CPolynomialMap cpm(right);
	map<int, double>::const_iterator it = m_PolynomialMap.begin();
	for (; it != m_PolynomialMap.end(); it++)
	{
		cpm.Insert(it->first, it->second);
	}
	return cpm;
}

CPolynomialMap CPolynomialMap::operator-(const CPolynomialMap &right)
{
	CPolynomialMap cpm(right);
	map<int, double>::const_iterator it = cpm.m_PolynomialMap.begin();
	for (; it != cpm.m_PolynomialMap.end(); it++)
	{
		this->Insert(it->first, -(it->second));
	}

	return *this;
}

CPolynomialMap CPolynomialMap::operator*(const CPolynomialMap &right)
{
	CPolynomialMap cpm;
	int deg; double cof;
	map<int, double>::const_iterator it1 = m_PolynomialMap.begin();
	map<int, double>::const_iterator it2 = right.m_PolynomialMap.begin();
	for (; it1 != m_PolynomialMap.end(); it1++)
	{
		for (; it2 != right.m_PolynomialMap.end(); it2++)
		{
			deg = it1->first + it2->first;
			cof = it1->second*it2->second;
			cpm.Insert(deg, cof);
		}
		it2 = right.m_PolynomialMap.begin();
	}
	return cpm;
}

CPolynomialMap & CPolynomialMap::operator=(const CPolynomialMap &right)
{
	m_PolynomialMap.clear();
	map<int, double>::const_iterator it = right.m_PolynomialMap.begin();

	for (; it != right.m_PolynomialMap.end(); it++)
	{
		this->Insert(it->first, it->second);
	}
	return *this;
}

void CPolynomialMap::Print() const
{
	map<int, double>::const_iterator it = m_PolynomialMap.begin();
	cout << "the result is ";
	if (it == m_PolynomialMap.end())
	{
		cout << " 0 " << endl;
	}
	for (; it != m_PolynomialMap.end(); it++)
	{
		if (it->second != 0)
		{
			if (it != m_PolynomialMap.begin() && it->second > 0)
			{
				cout << "+";
			}
			cout << it->second;
			if (it->first != 0)
			{
				if (it->first == 1)
				{
					cout << "x";
				}
				else
				{
					cout << "x^" << it->first;
				}
			}
		}
	}
	cout << endl;
}


int CPolynomialMap::ReadFromFile(string file)
{
	int deg; double cof;
	m_PolynomialMap.clear();
	ifstream in;
	in.open(file.c_str());
	if (!in)
	{
		cout << "open failed" << endl;
		return FALSE;
	}

	char p;
	int n;
	in >> p;
	in >> n;
	for (int k = 0; k < n; k++)
	{
		in >> deg;
		in >> cof;
		Insert(deg, cof);
	}
	in.close();
	return TRUE;
}




int CPolynomialMap::Insert(int Key, double Value)
{
	map<int, double>::iterator iter;
	iter = m_PolynomialMap.find(Key);
	if (iter != m_PolynomialMap.end())
	{
		iter->second += Value;
	}
	else
	{
		m_PolynomialMap.insert(make_pair(Key, Value));
	}
	return TRUE;
}