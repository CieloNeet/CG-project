#ifndef POLYNOMIALLIST_H
#define POLYNOMIALLIST_H
#include <vector>
#include <list>
#include <string>

using namespace std;

#define TRUE 1;
#define FALSE 0;

typedef struct Node
{
	double  cof;      // coefficient 
	int     deg;      // degree
} Node;               // the node of polynomial

class CPolynomial
{
private:
	list<Node> m_Polynomial;
public:
	CPolynomial();
	CPolynomial(const CPolynomial& right);
	CPolynomial(const string& file);                     // initialization using file
	CPolynomial(double *cof, double *deg, int n);
	CPolynomial(const vector<double>& cof, const  vector<int> & deg);
	virtual ~CPolynomial();

	// overload
	CPolynomial operator+(const CPolynomial &right);	//Overload operator +
	CPolynomial operator-(const CPolynomial &right);	//Overload operator -
	CPolynomial operator*(const CPolynomial &right);	//Overload operator *
	CPolynomial & operator=(const CPolynomial &right);	//Overload operator =

	void Print() const;
	void compress();
private:
	int ReadFromFile(string file);
	int AddOneTerm(const Node &term);   // add one term into m_Polynomial
};


#endif // POLYNOMIALLIST_H
