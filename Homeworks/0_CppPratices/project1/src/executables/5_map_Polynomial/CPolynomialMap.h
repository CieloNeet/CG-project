#ifndef POLYNOMIALMAP_H
#define POLYNOMIALMAP_H
#include <vector>
#include <list>
#include <string>
#include <map>

using namespace std;

#define TRUE 1;
#define FALSE 0;



class CPolynomialMap
{
private:
	map<int,double> m_PolynomialMap;
public:
	CPolynomialMap();
	CPolynomialMap(const CPolynomialMap& right);
	CPolynomialMap(const string& file);                     // initialization using file
	CPolynomialMap(double *cof, double *deg, int n);
	CPolynomialMap(const vector<double>& cof, const  vector<int> & deg);
	virtual ~CPolynomialMap();

	// overload
	CPolynomialMap operator+(const CPolynomialMap &right);	//Overload operator +
	CPolynomialMap operator-(const CPolynomialMap &right);	//Overload operator -
	CPolynomialMap operator*(const CPolynomialMap &right);	//Overload operator *
	CPolynomialMap & operator=(const CPolynomialMap &right);	//Overload operator =

	void Print() const;
private:
	int ReadFromFile(string file);
	int Insert(int Key, double Value);
	
};


#endif // POLYNOMIALMAP_H

