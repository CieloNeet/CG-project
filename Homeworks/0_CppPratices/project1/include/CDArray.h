#if !defined _DYNAMICARRAY_H_
#define _DYNAMICARRAY_H_

#ifdef _WIN32
#  ifdef DArray_EXPORTS
#    define DECLSPEC __declspec(dllexport)
#  else
#    define DECLSPEC __declspec(dllimport)
#  endif
#else // non windows
#  define DECLSPEC
#endif

#define TRUE	1
#define FALSE	0


class DECLSPEC CDArray
{
private:
	double	*m_pData;	// �������Ķ�̬�ڴ�ָ��
	int		m_nSize;		// �����Ԫ�ظ���
	int		m_nMax;		// Ԥ������̬������ڴ��С

private:
	void	Init();		// ��ʼ��
	void	Free();		// �ͷŶ�̬�ڴ�
	

public:
	CDArray();			// ȱʡ���캯��
	CDArray(int nSize, double dValue=0);	// �������캯��������һ�������С������������Ԫ��Ϊ0����Ȼ�����Զ���������ͬ�����Ĺ��캯�����Է����û�ʹ��
	CDArray(const CDArray& arr);	// �������캯�������Ϊ���а�����̬�����Ա���඼�ṩ�������캯����
	~CDArray();		// ��������

	void		Print();				// �����ʾ��������Ԫ�ص�ֵ
	int		GetSize();			// ��ȡ�����С��Ԫ�ظ�����
	int		SetSize(int nSize);		// ������������Ĵ�С��ע����nSizeС��ԭ�����С���ɽض�ȡǰnSize��Ԫ����Ϊ�������Ԫ�أ���nSize����ԭ�����С��������Ԫ�ص�ֵ����ȱʡֵ0����

	double	GetAt(int nIndex);				// ��ȡĳ��Ԫ��
	double 	 operator[] (int nIndex) const; 	// ����[]���������Ա���ͳ��������ͨ��a[k]����ȡԪ��ֵ
	int		SetAt(int nIndex, double dValue);	// ����ĳ��Ԫ�ص�ֵ

	int		PushBack(double dValue);		// ׷��һ���µ�Ԫ�ص�����ĩβ
	int		DeleteAt(int nIndex);			// ��������ɾ��һ��Ԫ��
	int		InsertAt(int nIndex, double dValue);	// ����һ���µ�Ԫ�ص�������

	CDArray 	& operator = (const CDArray& array);  	// ���ظ�ֵ��������"="
};

#endif // _DYNAMICARRAY_H_