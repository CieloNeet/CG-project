#pragma once

#include "Wraping.h"
#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;
using std::vector;


class RBF :
	public CWraping
{
public:
	RBF();
	~RBF();

	void wraping(QImage& image);
	void Fill(QImage& image);

private:
	vector<double> r;
	MatrixXd RBF_H;
	MatrixXi Hole;

	void set_r();
	void set_H();
};
