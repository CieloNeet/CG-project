




#include <iostream>
#include <CDArray.h>
#include<iomanip>
#include <assert.h>

using namespace std;

#define SAFEDELETE(p)	if(p) {delete p; p=NULL; }
#define SAFEDELETES(p)  if(p) {delete []p; p=NULL; }

void CDArray::Init()
{
	m_pData = NULL;
	m_nSize = 0;
	m_nMax = 0;
}

void CDArray::Free()
{
	SAFEDELETES(m_pData);
	m_nSize = 0;
	m_nMax = 0;

}




CDArray::CDArray()
{
	Init();
}

CDArray::CDArray(int nSize, double dValue)
{
	m_pData = new double[nSize];

	for (int k = 0; k < nSize; k++)
	{
		m_pData[k] = dValue;
	}

	m_nSize = nSize;
	m_nMax = nSize;
}

CDArray::CDArray(const CDArray& arr)
{
	double *p;
	p = new double[arr.m_nSize];
	for (int k = 0; k < arr.m_nSize; k++)
	{
		p[k] = arr.m_pData[k];
	}
	m_pData = p;
	m_nSize = arr.m_nSize;
	m_nMax = arr.m_nMax;
}

CDArray::~CDArray()
{
	Free();
}

void CDArray::Print()
{
	cout << "size = " << m_nSize << "max size = " << m_nMax << endl;
	cout << "全部元素如下" << endl;
	for (int k = 0; k < m_nSize; k++)
	{
		cout << left << setw(14) << setprecision(8) << m_pData[k] << " ";
	}
	cout << defaultfloat << endl;
}

int CDArray::GetSize()
{
	return m_nSize;
}

int CDArray::SetSize(int nSize)
{
	int k;

	if (m_pData == NULL)
	{
		m_pData = new double [nSize];
		if (m_pData == NULL)
		{
			cout << "Error appears in SetSize" << endl;
			return FALSE;
		}

		for (k = 0; k < m_nSize; k++)
		{
			m_pData[k] = 0.0;
		}
		m_nSize = nSize;
		m_nMax = nSize;
		return TRUE;
	}

	else if (m_nSize == nSize)
	{
		return TRUE;
	}

	else if (m_nSize > nSize)
	{
		double *n_p = NULL;
		n_p = new double [nSize];
		for (k = 0; k < nSize; k++)
		{
			n_p[k] = m_pData[k];
		}
		SAFEDELETES(m_pData);
		m_pData = n_p;
		m_nSize = nSize;
		m_nMax = nSize;
		return TRUE;
	}

	else
	{
		double *n_p = NULL;
		n_p = new double [nSize];
		for (k = 0; k < nSize; k++)
		{
			if (k < m_nSize)
			{
				n_p[k] = m_pData[k];
			}
			else
			{
				n_p[k] = 0;
			}
		}
		SAFEDELETES(m_pData);
		m_pData = n_p;
		m_nSize = nSize;
		m_nMax = nSize;
		return TRUE;
	}
}

double CDArray::GetAt(int nIndex)
{
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
	
}

double  CDArray::operator[] (int nIndex) const
{
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
	
}

int CDArray::SetAt(int nIndex, double dValue)
{
	assert(nIndex >= 0 && nIndex < m_nSize);
	m_pData[nIndex] = dValue;
	return TRUE;
	
}

int CDArray::PushBack(double dValue)
{
	int k;
	if (m_nSize < m_nMax)
	{
		m_pData[m_nSize] = dValue;
		m_nSize += 1;
		return TRUE;
	}
	else
	{
		if (m_nMax ==0 )
		{
			m_nMax = 1;
		}
		else
		{
			m_nMax *= 2;
		}
		
		double *p = NULL;
		p = new double[m_nMax];
		if (p == NULL)
		{
			cout << "error appears in PushBack" << endl;
			return FALSE;
		}

		else
		{
			for (k = 0; k < m_nSize; k++)
			{
				p[k] = m_pData[k];
			}
			p[m_nSize] = dValue;

			SAFEDELETES(m_pData);
			m_pData = p;
			m_nSize += 1;
			return TRUE;
		}
	}
}

int CDArray::DeleteAt(int nIndex)
{
	int k;

	assert(nIndex >= 0 && nIndex < m_nSize);

		double *p = NULL;
		p = new double [m_nMax];
		if (p == NULL)
		{
			cout << "error appears in Delete" << endl;
			return FALSE;
		}

		for (k = 0; k < nIndex; k++)
		{
			p[k] = m_pData[k];
		}
		for (k = nIndex; k < m_nSize - 1; k++)
		{
			p[k] = m_pData[k + 1];
		}

		SAFEDELETES(m_pData);
		m_pData = p;
		m_nSize -= 1;
		return TRUE;
	
}

int CDArray::InsertAt(int nIndex, double dValue)
{
	int k;
	if (nIndex < 0 || nIndex>m_nSize)
	{
		cout << "nIndex is illegal in Insert" << endl;
		return FALSE;
	}
	else
	{
		if (m_nSize == 0)
		{
			m_nMax = 1;
		}
		else if (m_nSize >= m_nMax)
		{
			m_nMax *= 2;
		}

		double *p = NULL;
		p = new double[m_nMax];
		for (k = 0; k < nIndex; k++)
		{
			p[k] = m_pData[k];
		}
		p[nIndex] = dValue;
		for (k = nIndex; k < m_nSize; k++)
		{
			p[k + 1] = m_pData[k];
		}

		SAFEDELETES(m_pData);
		m_pData = p;
		m_nSize += 1;
		return TRUE;

	}
}

CDArray & CDArray::operator = (const CDArray& array)
{
	if (this != &array)
	{
		double *p = NULL;
		p = new double[array.m_nSize];
		for (int k = 0; k < array.m_nSize; k++)
		{
			p[k] = array.m_pData[k];
		}
		
		m_pData = p;
		m_nSize = array.m_nSize;
		m_nMax = array.m_nMax;
	}
	return *this;
}