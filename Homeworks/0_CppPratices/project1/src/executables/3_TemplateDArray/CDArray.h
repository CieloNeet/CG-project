#if !defined _DYNAMICARRAY_H_
#define _DYNAMICARRAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <typeinfo.h>
#include <string.h>
#include <iostream>
#include "CDArray.h"
#include<iomanip>

using namespace std;

#define SAFEDELETE(p)	if(p) {delete p; p=NULL; }
#define SAFEDELETES(p)  if(p) {delete []p; p=NULL; }

#define TRUE	1
#define FALSE	0

template <class DataType>
class CDArray
{
private:
	DataType	*m_pData;	// 存放数组的动态内存指针
	int		m_nSize;		// 数组的元素个数
	int		m_nMax;		// 预留给动态数组的内存大小

private:
	void	Init();		// 初始化
	void	Free();		// 释放动态内存
	inline	bool	InvalidateIndex(int nIndex);	// 判断下标的合法性

public:
	CDArray();			// 缺省构造函数
	CDArray(int nSize, DataType dValue);	// 其他构造函数，设置一定数组大小，并设置所有元素为0；当然还可以定义其他不同参数的构造函数，以方便用户使用
	CDArray(const CDArray& arr);	// 拷贝构造函数（最好为所有包含动态分配成员的类都提供拷贝构造函数）
	~CDArray();		// 析构函数

	void		Print();				// 输出显示所有数组元素的值
	int		GetSize();			// 获取数组大小（元素个数）
	int		SetSize(int nSize);		// 重新设置数组的大小。注：若nSize小于原数组大小，可截断取前nSize个元素作为新数组的元素；若nSize大于原数组大小，新增的元素的值设置缺省值0即可

	DataType	GetAt(int nIndex);				// 获取某个元素
	DataType 	 operator[] (int nIndex) const; 	// 重载[]操作符，以便像传统数组那样通过a[k]来获取元素值
	int		SetAt(int nIndex, DataType dValue);	// 设置某个元素的值

	int		PushBack(DataType dValue);		// 追加一个新的元素到数组末尾
	int		DeleteAt(int nIndex);			// 从数组中删除一个元素
	int		InsertAt(int nIndex, DataType dValue);	// 插入一个新的元素到数组中

	CDArray<DataType> 	& operator = (const CDArray& array);  	// 重载赋值操作符号"="
};



template <class DataType> 
void CDArray<DataType>::Init()
{
	m_pData = NULL;
	m_nSize = 0;
	m_nMax = 0;
}

template <class DataType>
void CDArray<DataType>::Free()
{
	SAFEDELETES(m_pData);
	m_nSize = 0;
	m_nMax = 0;

}

template <class DataType>
inline bool CDArray<DataType>::InvalidateIndex(int nIndex)
{
	if (nIndex < 0 || nIndex >= m_nSize)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

template <class DataType>
CDArray<DataType>::CDArray()
{
	Init();
}


template <class DataType>
CDArray<DataType>::CDArray(int nSize, DataType dValue)
{
	m_pData = new  DataType[nSize];

	for (int k = 0; k < nSize; k++)
	{
		m_pData[k] = dValue;
	}

	m_nSize = nSize;
	m_nMax = nSize;
}

template <class DataType>
CDArray<DataType>::CDArray(const CDArray& arr)
{
	DataType *p;
	p = new DataType[arr.m_nSize];
	for (int k = 0; k < arr.m_nSize; k++)
	{
		p[k] = arr.m_pData[k];
	}
	m_pData = p;
	m_nSize = arr.m_nSize;
	m_nMax = arr.m_nMax;
}


template <class DataType>
CDArray<DataType>::~CDArray()
{
	Free();
}


template <class DataType>
void CDArray<DataType>::Print()
{
	cout << "size = " << m_nSize << "max size = " << m_nMax << endl;
	cout << "全部元素如下" << endl;
	for (int k = 0; k < m_nSize; k++)
	{
		//cout << left << setw(14) << setprecision(8) << m_pData[k] << " ";
		cout << left <<  m_pData[k] << " ";
	}
	cout << defaultfloat << endl;
}

template <class DataType>
int CDArray<DataType>::GetSize()
{
	return m_nSize;
}


template <class DataType>
int CDArray<DataType>::SetSize(int nSize)
{
	int k;

	if (m_pData == NULL)
	{
		m_pData = new DataType[nSize];
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
		DataType *n_p = NULL;
		n_p = new DataType[nSize];
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
		DataType *n_p = NULL;
		n_p = new DataType[nSize];
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

template <class DataType>
DataType CDArray< DataType>::GetAt(int nIndex)
{
	if (InvalidateIndex(nIndex))
	{
		cout << "Error appears in GetAt, nIndex is illegal" << endl;
		return FALSE;
	}
	else
	{
		return m_pData[nIndex];
	}
}

template <class DataType>
DataType  CDArray<DataType>::operator[] (int nIndex) const
{
	if (nIndex > m_nSize)
	{
		cout << "nIndex is illegal in []" << endl;
		return FALSE;
	}
	else
	{
		return m_pData[nIndex];
	}
}

template <class DataType>
int CDArray<DataType>::SetAt(int nIndex, DataType dValue)
{
	if (InvalidateIndex(nIndex))
	{
		cout << "nIndex is illegal in SetAt" << endl;
		return FALSE;
	}

	else
	{
		m_pData[nIndex] = dValue;
		return TRUE;
	}
}

template <class DataType>
int CDArray<DataType>::PushBack(DataType dValue)
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
		if (m_nMax == 0)
		{
			m_nMax = 1;
		}
		else
		{
			m_nMax *= 2;
		}

		DataType *p = NULL;
		p = new DataType[m_nMax];
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

template <class DataType>
int CDArray<DataType>::DeleteAt(int nIndex)
{
	int k;

	if (InvalidateIndex(nIndex))
	{
		cout << "nIndex is illegal in Delete" << endl;
		return FALSE;
	}
	else
	{
		DataType *p = NULL;
		p = new DataType[m_nMax];
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
}

template <class DataType>
int CDArray<DataType>::InsertAt(int nIndex, DataType dValue)
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

		DataType *p = NULL;
		p = new DataType[m_nMax];
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

template <class DataType>
CDArray<DataType> & CDArray<DataType>::operator = (const CDArray& array)
{
	if (this != &array)
	{
		DataType *p = NULL;
		p = new DataType[array.m_nSize];
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


#endif // _DYNAMICARRAY_H_