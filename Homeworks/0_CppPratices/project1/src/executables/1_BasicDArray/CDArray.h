#if !defined _DYNAMICARRAY_H_
#define _DYNAMICARRAY_H_

#define TRUE	1
#define FALSE	0


class CDArray
{
private:
	double	*m_pData;	// 存放数组的动态内存指针
	int		m_nSize;		// 数组的元素个数

private:
	void	Init();		// 初始化
	void	Free();		// 释放动态内存
	

public:
	CDArray();			// 缺省构造函数
	CDArray(int nSize, double dValue=0);	// 其他构造函数，设置一定数组大小，并设置所有元素为0；当然还可以定义其他不同参数的构造函数，以方便用户使用
	CDArray(const CDArray& arr);	// 拷贝构造函数（最好为所有包含动态分配成员的类都提供拷贝构造函数）
	~CDArray();		// 析构函数

	void		Print();				// 输出显示所有数组元素的值
	int		GetSize();			// 获取数组大小（元素个数）
	int		SetSize(int nSize);		// 重新设置数组的大小。注：若nSize小于原数组大小，可截断取前nSize个元素作为新数组的元素；若nSize大于原数组大小，新增的元素的值设置缺省值0即可

	double	GetAt(int nIndex);				// 获取某个元素
	double 	 operator[] (int nIndex) const; 	// 重载[]操作符，以便像传统数组那样通过a[k]来获取元素值
	int		SetAt(int nIndex, double dValue);	// 设置某个元素的值

	int		PushBack(double dValue);		// 追加一个新的元素到数组末尾
	int		DeleteAt(int nIndex);			// 从数组中删除一个元素
	int		InsertAt(int nIndex, double dValue);	// 插入一个新的元素到数组中

	CDArray 	& operator = (const CDArray& array);  	// 重载赋值操作符号"="
};

#endif // _DYNAMICARRAY_H_
