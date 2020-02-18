#include <iostream>
#include <algorithm>
#include <fstream>
#include "CPolynomial.h"

#define eps 1.0e-10



CPolynomial::CPolynomial()
{
	//m_Polynomial.clear();
}

CPolynomial::CPolynomial(const CPolynomial& right)
{
	m_Polynomial.clear();
	list<Node>::const_iterator p = right.m_Polynomial.begin();
	for (; p != right.m_Polynomial.end(); p++)
	{
		AddOneTerm(*p);
	}
}


CPolynomial::CPolynomial(const string& file)
{
	ReadFromFile(file);
}

CPolynomial::CPolynomial(double *cof, double *deg, int n)
{
	int k;
	for (k = 0; k < n; k++)
	{
		Node lp;
		lp.cof = cof[k];
		lp.deg = deg[k];
		AddOneTerm(lp);
	}
}

CPolynomial::CPolynomial(const vector<double>& cof, const  vector<int> & deg)
{
	int m1 = cof.size(), m2 = deg.size();
	int n = m1 < m2 ? m1 : m2;
	for (int k = 0; k < n; k++)
	{
		Node lp;
		lp.cof = cof[k];
		lp.deg = deg[k];
		AddOneTerm(lp);
	}
}

CPolynomial::~CPolynomial()
{
	m_Polynomial.clear();
	
}








CPolynomial CPolynomial::operator+(const CPolynomial &right)
{
	CPolynomial left(right);
	list<Node>::const_iterator p = m_Polynomial.begin();
	for (; p != m_Polynomial.end(); p++)
	{
		left.AddOneTerm(*p);
	}
	left.compress();
	return left;
}

/*CPolynomial CPolynomial::operator-(const CPolynomial &right)
{
	CPolynomial left(right);
	list<Node>::const_iterator p = m_Polynomial.begin();
	for (; p != m_Polynomial.end(); p++)
	{
		Node ln;
		ln.cof = - (*p).cof;
		ln.deg = (*p).deg;
		left.AddOneTerm(ln);
	}

	return left;
}*/


CPolynomial CPolynomial::operator-(const CPolynomial &right)
{
	CPolynomial r(right);
	list<Node>::const_iterator p = r.m_Polynomial.begin();
	for (; p != r.m_Polynomial.end(); p++)
	{
		Node ln;
		ln.cof = -(*p).cof;
		ln.deg = (*p).deg;
		this->AddOneTerm(ln);
	}
	this->compress();
	return *this;
}

CPolynomial CPolynomial::operator*(const CPolynomial &right)
{
	CPolynomial result;
	list<Node>  lp;

	lp = right.m_Polynomial;
	

	list<Node>::const_iterator pt1 = m_Polynomial.begin();
	list<Node>::const_iterator pt2 = lp.begin();

	for (; pt1 != m_Polynomial.end(); pt1++)
	{
		for (; pt2 != lp.end(); pt2++)
		{
			Node n1, n2;
			n1 = *pt1;
			n2 = *pt2;
			n1.cof *= n2.cof;
			n1.deg += n2.deg;
			result.AddOneTerm(n1);
		}
		pt2 = lp.begin();

	}

	return result;
}

CPolynomial & CPolynomial::operator=(const CPolynomial &right)
{
	m_Polynomial.clear();
	list<Node>::const_iterator p = right.m_Polynomial.begin();

	for (; p != right.m_Polynomial.end(); p++)
	{
		AddOneTerm(*p);
	}
	return *this;
}

void CPolynomial::Print() const
{
	list<Node>::const_iterator p = m_Polynomial.begin();
	cout << "The result is ";
	if (p == m_Polynomial.end())
	{
		cout << "0" << endl;
	}
	for (; p != m_Polynomial.end(); p++)
	{
		if ((*p).cof != 0)
		{
			if (p != m_Polynomial.begin() && (*p).cof > 0)
			{
				cout << "+";
			}
			cout << (*p).cof;
			if ((*p).deg != 0)
			{
				if ((*p).deg == 1)
				{
					cout << "x";
				}
				else
				{
					cout << "x^" << (*p).deg;
				}
			}
		}
	}
	cout << endl;
}

void CPolynomial::compress() {
	auto itr = m_Polynomial.begin();
	while (itr != m_Polynomial.end()) {
		if (fabs((*itr).cof) < eps)
			itr = m_Polynomial.erase(itr);
		else
			itr++;
	}
}

int CPolynomial::ReadFromFile(string file)
{
	m_Polynomial.clear();
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
		Node lp;
		in >> lp.deg;
		in >> lp.cof;
		AddOneTerm(lp);
	}
	in.close();
	return TRUE;
}

int CPolynomial::AddOneTerm(const Node &term)
{
	list<Node>::iterator p = m_Polynomial.begin();
	if (p == m_Polynomial.end() || (*p).deg > term.deg)
	{
		m_Polynomial.push_front(term);
		return TRUE;
	}
	for (; p != m_Polynomial.end(); p++)
	{
		if ((*p).deg >= term.deg)
			break;
	}

	if (p == m_Polynomial.end())
	{
		m_Polynomial.push_back(term);
		return TRUE;
	}

	if ((*p).deg > term.deg)
	{
		m_Polynomial.insert(p, term);
		return TRUE;
	}
	else
	{
		(*p).cof += term.cof;
		return TRUE;
	}
}
