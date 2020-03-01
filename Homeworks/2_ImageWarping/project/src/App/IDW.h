#pragma once

#include "Wraping.h"
#include <Eigen/Dense>

using namespace Eigen;

class IDW :
	public CWraping
{
public:
	IDW();
	~IDW();

	void wraping(QImage& image);
	int judge(int x, int y);
	void Fill(QImage& image);
	void Search(int i, int j);
	
private:
	int u;               //����Ȩ��ʱ�Ĳ���
	MatrixXi Hole;
	//int Judgei;
	//int Judgej;
};
