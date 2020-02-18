#include <iostream>
#include "CDArray.h"

using namespace std;
int main()
{
	CDArray<double> a;
	a.InsertAt(0, 2.1);
	a.Print();

	a.PushBack(3.0);
	a.PushBack(3.1);
	a.PushBack(3.2);
	a.Print();

	a.DeleteAt(0);
	a.Print();
	a.InsertAt(0, 4.1);
	a.Print();

	CDArray<double> acopy = a;  //�˴��õ��˿������캯��
	acopy.Print();

	CDArray<double> acopy2(a);  //������ͬ���������䣬���ǳ�ʼ��
	acopy2.Print();

	CDArray<double> acopy3;
	acopy3 = a;					//�˴��õ��˸�ֵ��������"="������
	acopy3.Print();


	CDArray<int> b;
	b.PushBack(21);
	b.Print();
	b.DeleteAt(0);
	b.Print();
	b.PushBack(22);
	b.SetSize(5);
	b.Print();

	CDArray<char> c;
	c.PushBack('a');
	c.PushBack('b');
	c.PushBack('c');
	c.InsertAt(0, 'd');
	c.Print();


	 


	//getchar();
	system("pause");

	return TRUE;
	
}


/*int main()
{
	CDArray a;
	a.PushBack(1);
	a.SetSize(10);
	a.Print();
	cout << a.GetSize() << endl;
	a.SetAt(4, 5.5);
	a.Print();
	cout << a.GetAt(4) << endl;
	cout << a[4] << endl;
	a.DeleteAt(4);
	a.Print();
	a.InsertAt(1, 99.58);
	a.Print();
	a.PushBack(8);
	CDArray b;
	b = a;
	b.Print();

	system("pause");
	return TRUE;
}*/