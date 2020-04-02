#include <Engine/MeshEdit/Simulate.h>


#include <Eigen/Sparse>

using namespace Ubpa;

using namespace std;
using namespace Eigen;


void Simulate::Clear() {
	this->positions.clear();
	this->velocity.clear();
	this->length.clear();
	this->y.clear();
	this->x_iter.clear();
	this->coff.clear();
}

bool Simulate::Init() {
	//Clear();
	//储存长度
	

	this->velocity .resize(positions.size());
	for (int i = 0; i < positions.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->velocity[i][j] = 0;
		}
	}
	cout << "Init finished" << endl;
	//cout << edgelist.size() << "   " << length.size() << endl;


	return true;
}

bool Simulate::Run() {

	SimulateOnce();

	// half-edge structure -> triangle mesh

	return true;
}

void Ubpa::Simulate::SetLeftFix(bool istet)
{
	//固定网格x坐标最小点
	fixed_id.clear();
	old_positions.resize(positions.size());
	double x = 100000, y_min = 100000, y_max = -10000;
	for (int i = 0; i < positions.size(); i++)
	{
		if (positions[i][0] < x)
		{
			x = positions[i][0];
		}
		if (positions[i][1] < y_min)
		{
			y_min = positions[i][1];
		}
		if (positions[i][1] > y_max)
		{
			y_max = positions[i][1];
		}
	}
	if (istet)
	{
		for (int i = 0; i < positions.size(); i++)
		{
			if (abs(positions[i][0] - x) < 1e-5)
			{
				fixed_id.push_back(i);
			}
		}
	}
	else
	{

		for (int i = 0; i < positions.size(); i++)
		{
			if (abs(positions[i][0] - x) < 1e-5 && (abs(positions[i][1] - y_min) < 1e-5 || abs(positions[i][1] - y_max) < 1e-5))
			{
				fixed_id.push_back(i);
			}
		}
		
	}

	

	
	for (int i = 0; i < positions.size(); i++)
	{
		pointf3 mm;
		mm[0] = positions[i][0];
		mm[1] = positions[i][1];
		mm[2] = positions[i][2];
		old_positions[i] = mm;
		//cout << mm << endl;
	}

	this->length.resize(edgelist.size() / 2);
	for (size_t i = 0; i < edgelist.size() / 2; i++)
	{
		length[i] = distance(positions[edgelist[2 * i]], positions[edgelist[2 * i + 1]]);
	}


	Init();
}

void Simulate::SimulateOnce() {
	// TODO
	//cout << "WARNING::Simulate::SimulateOnce:" << endl;
//		<< "\t" << "not implemented" << endl;

	//cout << stiff << endl;
	y.clear(); A.resize(0, 0); x_iter.clear(); b.resize(0, 0);
	coff.clear();
	MatrixXd Result;
	Set_y();
	int times = 0;
	do {
		Set_b();
		Set_A();
		
		SparseLU<SparseMatrix<double>> A_LU;
		A_LU.compute(A);
		Result = A_LU.solve(b);
		//cout << Result.cols() << endl;
		//cout << Result << endl;

		for (size_t i = 0; i < 3 * positions.size(); i++)
		{
			x_iter[i] += Result(i,0);
		}
		//cout << "while" << endl;
		times++;
	} while (abs(Result.maxCoeff())>0.00001 && times < 10);
	

	for (int i = 0; i < positions.size(); i++)
	{
		if (!is_fixed(i))
		{
			this->velocity[i][0] = (x_iter[3 * i] - this->positions[i][0]) / h;
			this->velocity[i][1] = (x_iter[3 * i + 1] - this->positions[i][1]) / h;
			this->velocity[i][2] = (x_iter[3 * i + 2] - this->positions[i][2]) / h;
			this->positions[i][0] = x_iter[3 * i];
			this->positions[i][1] = x_iter[3 * i + 1];
			this->positions[i][2] = x_iter[3 * i + 2];
			//cout << velocity[i][0] << "  " << velocity[i][1] << "  " << velocity[i][2] << endl;
		}
		
	}
	

	
	//cout << "???" << endl;


}

bool Simulate::is_fixed(int i)
{
	vector<unsigned>::iterator itr;
	itr = find(fixed_id.begin(), fixed_id.end(), i);
	if (itr != fixed_id.end())
	{
		return true;
	}
	else {
		return false;
	}
}

double Simulate::distance(pointf3 x, pointf3 y)
{
	double sum = (x[0] - y[0]) * (x[0] - y[0]) + (x[1] - y[1]) * (x[1] - y[1]) + (x[2] - y[2]) * (x[2] - y[2]);
	return sqrt(sum);
}

void Simulate::Restore()
{
	if (!old_positions.empty())
	{
		for (size_t i = 0; i < positions.size(); i++)
		{
			positions[i] = old_positions[i];
			for (size_t j = 0; j < 3; j++)
			{
				velocity[i][j] = 0;
			}
		}
		
	}
	else {
		cout << "The old_position is empty" << endl;
	}
}

void Simulate::Set_y()
{
	y.clear(); x_iter.clear();
	size_t nV = positions.size();
	y.resize(3 * nV);
	x_iter.resize(3 * nV);
	for (size_t i = 0; i < nV; i++)
	{
		if (!is_fixed(i))
		{
			y[3 * i] = positions[i][0] + h * velocity[i][0] ;
			y[3 * i + 1] = positions[i][1] + h * velocity[i][1] ;
			y[3 * i + 2] = positions[i][2] + h * velocity[i][2] + h * h * g;
			//y[3 * i + 2] += h * h * g;     //暂定重力在z方向上
		}
		else {
			y[3 * i] = positions[i][0] ;
			y[3 * i + 1] = positions[i][1] ;
			y[3 * i + 2] = positions[i][2] ;
		}
		
		
	}
	x_iter = y;
}

void Simulate::Set_A()
{
	coff.clear();
	A.resize(0, 0);
	size_t nV = positions.size();
	A.resize(3 * nV, 3 * nV);
	A.setZero();
	for (size_t k = 0; k < edgelist.size() / 2; k++)
	{
		size_t i = edgelist[2 * k];
		size_t j = edgelist[2 * k + 1];
		//pointf3 x1 = positions[i];
		//pointf3 x2 = positions[j];
		VectorXd r(3);
		//r(0) = x1[0] - x2[0]; r(1) = x1[1] - x2[1]; r(2) = x1[2] - x2[2];
		r(0) = x_iter[3 * i] - x_iter[3 * j];
		r(1) = x_iter[3 * i + 1] - x_iter[3 * j + 1];
		r(2) = x_iter[3 * i + 2] - x_iter[3 * j + 2];
		double norm_r = r.norm();
		MatrixXd I; I.setIdentity(3, 3);
		MatrixXd Df = stiff * (length[k] / norm_r - 1.) * I - (stiff * length[k] / pow(norm_r, 3)) * (r * r.transpose());
		
		Insert_A(i, j, Df);

		/*if (k == 0)
		{
			cout << "point1 :" << x1 << endl;
			cout << "point2 :" << x2 << endl;
			cout << "r :" << r << endl;
			cout << "Df :" << Df << endl;
		}*/

	}
	for (size_t i = 0; i < 3 * nV; i++)
	{
		coff.push_back(Triplet<double>(i, i, 1.));
	}

	A.setFromTriplets(coff.begin(), coff.end());
	A.makeCompressed();
	//cout << A << endl;
}

void Simulate::Insert_A(size_t i, size_t j, Eigen::MatrixXd  D)
{
	if (D.rows() != 3 || D.cols() != 3)
	{
		cout << "Insert failed at  " << i << "  " << j << endl;
		return;
	}
	for (size_t iD = 0; iD < 3; iD++)
	{
		for (size_t jD = 0; jD < 3; jD++)
		{
			if (D(iD, jD) != 0.)
			{
				//分别插入系数df1/dx1,df2/dx2,df1/dx2,df2/dx1
				if (!is_fixed(i))
				{
					coff.push_back(Triplet<double>(3 * i + iD, 3 * i + jD, -h * h * D(iD, jD)));
					coff.push_back(Triplet<double>(3 * i + iD, 3 * j + jD, h * h * D(iD, jD)));
				}
				if (!is_fixed(j))
				{
					coff.push_back(Triplet<double>(3 * j + iD, 3 * j + jD, -h * h * D(iD, jD)));
					coff.push_back(Triplet<double>(3 * j + iD, 3 * i + jD, h * h * D(iD, jD)));
				}
				/*coff.push_back(Triplet<double>(3 * i + iD, 3 * i + jD, -h * h * D(iD, jD)));
				coff.push_back(Triplet<double>(3 * i + iD, 3 * j + jD, h * h * D(iD, jD)));
				coff.push_back(Triplet<double>(3 * j + iD, 3 * j + jD, -h * h * D(iD, jD)));
				coff.push_back(Triplet<double>(3 * j + iD, 3 * i + jD, h * h * D(iD, jD)));*/
			}
		}
	}
}

void Simulate::Set_b()
{
	b.resize(0, 0);
	size_t nV = positions.size();
	b.resize(3 * nV, 1);
	b.setZero();
	for (size_t k = 0; k < edgelist.size() / 2; k++)
	{
		size_t i = edgelist[2 * k];
		size_t j = edgelist[2 * k + 1];
		
		VectorXd r(3);
		//r(0) = x1[0] - x2[0]; r(1) = x1[1] - x2[1]; r(2) = x1[2] - x2[2];
		r(0) = x_iter[3 * j] - x_iter[3 * i];
		r(1) = x_iter[3 * j + 1] - x_iter[3 * i + 1];
		r(2) = x_iter[3 * j + 2] - x_iter[3 * i + 2];
		//double norm_r = r.norm();
		double norm_r = r(0) * r(0) + r(1) * r(1) + r(2) * r(2);
		norm_r = sqrt(norm_r);
		VectorXd f12 = (stiff * (norm_r - length[k]) / norm_r) * r;
		b(3 * i, 0) += f12(0);
		b(3 * i + 1, 0) += f12(1);
		b(3 * i + 2, 0) += f12(2);

		b(3 * j, 0) -= f12(0);
		b(3 * j + 1, 0) -= f12(1);
		b(3 * j + 2, 0) -= f12(2);
	}
	for (size_t k = 0; k < 3 * nV; k++)
	{
		b(k, 0) = (double)h * h * b(k, 0) + y[k] - x_iter[k];
	}
	for (size_t k = 0; k < fixed_id.size(); k++)
	{
		size_t i = fixed_id[k];
		b(3 * i, 0) = 0;
		b(3 * i + 1, 0) = 0;
		b(3 * i + 2, 0) = 0;
	}
}