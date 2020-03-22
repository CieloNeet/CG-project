#include <Engine/MeshEdit/Paramaterize.h>
#include <Engine/MeshEdit/ARAP.h>


#include <Engine/Primitive/TriMesh.h>
#include <Eigen/Sparse>
#include <Eigen/SparseLU>
#include <Eigen/Core>
#include <Eigen/SVD>


using namespace Eigen;
using namespace Ubpa;

using namespace std;

ARAP::ARAP(Ptr<TriMesh> triMesh)
	: heMesh(make_shared<HEMesh<V>>())
{
	Init(triMesh);
}

void ARAP::Clear() {
	heMesh->Clear();
	
	triMesh = nullptr;
	//ParaMesh = nullptr;
	Reference_triangles.clear();
	Para_Res.clear();
	COT_Theta.setZero();
	COT_Theta.resize(0, 0);
	A.resize(0, 0);
	b.resize(0, 0);
	Fix1 = Fix2 =Fix3= 0;
	Area.clear();
}

bool ARAP::Init(Ptr<TriMesh> triMesh) {
	Clear();

	if (triMesh == nullptr)
		return true;

	if (triMesh->GetType() == TriMesh::INVALID) {
		printf("ERROR::MinSurf::Init:\n"
			"\t""trimesh is invalid\n");
		return false;
	}

	// init half-edge structure
	size_t nV = triMesh->GetPositions().size();
	vector<vector<size_t>> triangles;
	triangles.reserve(triMesh->GetTriangles().size());
	for (auto triangle : triMesh->GetTriangles())
		triangles.push_back({ triangle->idx[0], triangle->idx[1], triangle->idx[2] });
	heMesh->Reserve(nV);
	heMesh->Init(triangles);

	if (!heMesh->IsTriMesh() || !heMesh->HaveBoundary()) {
		printf("ERROR::MinSurf::Init:\n"
			"\t""trimesh is not a triangle mesh or hasn't a boundaries\n");
		heMesh->Clear();
		return false;
	}

	// triangle mesh's positions ->  half-edge structure's positions
	for (int i = 0; i < nV; i++) {
		auto v = heMesh->Vertices().at(i);
		v->pos = triMesh->GetPositions()[i].cast_to<vecf3>();
	}

	this->triMesh = triMesh;
	//this->ParaMesh = triMesh;
	return true;
}

bool ARAP::ARAP_RUN(bool isto2D)
{
	if (heMesh->IsEmpty() || !triMesh) {
		printf("ERROR::ARPR::ARPR_Run\n"
			"\t""heMesh->IsEmpty() || !triMesh\n");
		return false;
	}
	double sum_old, sum_new ;
	sum_new = sum_old = -1.0;
	flatten();
	Set_Fix();
	InitPara(triMesh);
	//Para_2();
	Set_A_b();
	do {
		Get_Lt_SV();
		Update_Para_Res();
		sum_old = (sum_new == -1.0) ? -1.0 : sum_new;
		sum_new = Energy();
		
		cout << sum_old << "  and  " << sum_new << endl;
	} while (abs(sum_new-sum_old) > 0.000001);
	

	// half-edge structure -> triangle mesh
	size_t nV = heMesh->NumVertices();
	size_t nF = heMesh->NumPolygons();
	vector<pointf3> positions;
	vector<unsigned> indice;
	vector<pointf2> texcoords;
	positions.reserve(nV);
	texcoords.reserve(nV);
	indice.reserve(3 * nF);

	for (auto v : heMesh->Vertices()) {
		//positions.push_back(v->pos.cast_to<pointf3>());
		size_t i = heMesh->Index(v);
		pointf3 temp;
		temp[0] = Para_Res[i][0];
		temp[1] = Para_Res[i][1]; temp[2] = 0;
		positions.push_back(temp);
	}
		
	for (auto v : heMesh->Vertices())
	{
		auto w = v->pos.cast_to<pointf3>();
		pointf2 temp;
		//temp[0] = w[0]; temp[1] = w[1];
		size_t i = heMesh->Index(v);
		temp[0] = Para_Res[i][0];temp[1] = Para_Res[i][1];
		texcoords.push_back(temp);
	}
	for (auto f : heMesh->Polygons()) { // f is triangle
		for (auto v : f->BoundaryVertice()) // vertices of the triangle
			indice.push_back(static_cast<unsigned>(heMesh->Index(v)));
	}

	if (isto2D == true) {
		triMesh->Update(positions);
	}
	else {
		triMesh->Update(texcoords);
	}
	//triMesh->Update(positions);

	return true;
}

void ARAP::InitPara(Ptr<TriMesh> triMesh)
{
	auto paramaterize = Paramaterize::New(triMesh);
	paramaterize->RUN(PType::KCot, false);
	auto texcoord = triMesh->GetTexcoords();
	size_t nV = heMesh->NumVertices();
	Para_Res.resize(nV);
	for (auto v : heMesh->Vertices())
	{
		size_t i = heMesh->Index(v);
		Para_Res[i][0] = texcoord[i][0];
		Para_Res[i][1] = texcoord[i][1];
	}
}

void ARAP::flatten()
{
	if (heMesh->IsEmpty() || !triMesh) {
		printf("ERROR::ARPR::flatten\n"
			"\t""heMesh->IsEmpty() || !triMesh\n");
		return ;
	}

	Reference_triangles.clear();
	size_t nP = heMesh->Polygons().size();
	Reference_triangles.resize(3 * nP);
	COT_Theta.resize(nP, 3);
	COT_Theta.setZero();
	Area.resize(nP);
	
	for (auto poly : heMesh->Polygons())
	{
		if (poly != nullptr)
		{
			size_t N = heMesh->Index(poly);
			pointf3 x0 = poly->BoundaryVertice()[0]->pos.cast_to<pointf3>();
			pointf3 x1 = poly->BoundaryVertice()[1]->pos.cast_to<pointf3>();
			pointf3 x2 = poly->BoundaryVertice()[2]->pos.cast_to<pointf3>();
			vecf3 x0x1 = x1 - x0;
			vecf3 x1x2 = x2 - x1;
			vecf3 x2x0 = x0 - x2;

			double a = x0x1.norm(); double b = x1x2.norm(); double c = x2x0.norm();
			double p = (a + b + c) / 2.;
			double area = sqrt(p * (p - a) * (p - b) * (p - c));
			Area[N] = area;

			double COS0 = x2x0.cos_theta(-x1x2);       //半边x0x1对应角
			double COS1 = x0x1.cos_theta(-x2x0);       //半边x1x2对应角  
			double COS2 = x1x2.cos_theta(-x0x1);       //半边x2x0对应角

			COT_Theta(N, 0) = COS0 / sqrt(1 - COS0 * COS0);
			COT_Theta(N, 1) = COS1 / sqrt(1 - COS1 * COS1);
			COT_Theta(N, 2) = COS2 / sqrt(1 - COS2 * COS2);

			//将三角形映射到临时参数空间，x0为原点，x0x1为x轴
			Reference_triangles[3 * N][0] = 0; Reference_triangles[3 * N][1] = 0;
			//Reference_triangles[3 * N + 1][0] = x0x1.norm(); Reference_triangles[3 * N + 1][1] = 0;
			//Reference_triangles[3 * N + 2][0] = x2x0.norm() * COS1;  Reference_triangles[3 * N + 2][1] = x2x0.norm() * sqrt(1 - COS1 * COS1);
			Reference_triangles[3 * N + 1][0] = 0; Reference_triangles[3 * N + 1][1] = x0x1.norm();
			Reference_triangles[3 * N + 2][0] = x2x0.norm() * sqrt(1 - COS1 *COS1);  Reference_triangles[3 * N + 2][1] = x2x0.norm() * COS1;
		}
	}
}

void ARAP::Get_Lt_SV()
{
	size_t nP = heMesh->Polygons().size();
	Lt.clear();
	Singular_Value.clear();
	Lt.resize(nP);
	

	for (auto poly : heMesh->Polygons())
	{
		if (poly != nullptr) {
			size_t N = heMesh->Index(poly);
			
			MatrixXd St(2, 2);
			St.setZero();
			for (size_t i = 0; i < 3; i++) {
				size_t j = (i == 2) ? 0 : i + 1;  //j为i+1相对坐标

				size_t ki = heMesh->Index(poly->BoundaryVertice()[i]);
				size_t kj = heMesh->Index(poly->BoundaryVertice()[j]);
				

				St(0, 0) += COT_Theta(N, i) * (Para_Res[ki][0] - Para_Res[kj][0]) * (Reference_triangles[3 * N + i][0] - Reference_triangles[3 * N + j][0]);
				St(0, 1) += COT_Theta(N, i) * (Para_Res[ki][0] - Para_Res[kj][0]) * (Reference_triangles[3 * N + i][1] - Reference_triangles[3 * N + j][1]);
				St(1, 0) += COT_Theta(N, i) * (Para_Res[ki][1] - Para_Res[kj][1]) * (Reference_triangles[3 * N + i][0] - Reference_triangles[3 * N + j][0]);
				St(1, 1) += COT_Theta(N, i) * (Para_Res[ki][1] - Para_Res[kj][1]) * (Reference_triangles[3 * N + i][1] - Reference_triangles[3 * N + j][1]);
			}

			JacobiSVD<Eigen::MatrixXd> svd(St, ComputeFullU | ComputeFullV);
			MatrixXd U = svd.matrixU();
			MatrixXd V = svd.matrixV();
			MatrixXd Sigma = svd.singularValues();

			pointf2 SV = { Sigma(0,0),Sigma(1,0) };
			MatrixXd L_T = U * V.transpose();
			//Lt.push_back(L_T);
			/*if (L_T.determinant() < 0) {
				U(0, 1) *= -1;
				U(1, 1) *= -1;
				L_T = U * V.transpose();
			}*/
			Lt[N] = L_T;
			Singular_Value.push_back(SV);
		}
	}
}

void ARAP::Update_Para_Res()
{
	
	
	pointf3 Mp;
	Upfate_b();
	//Set_A_b();
	//cout << A << endl;
	
	//A_LU.compute(A);
	//SimplicialCholesky<SparseMatrix<double>> A_Cho;
	//A_Cho.compute(A);
	
	MatrixXd Result;
	//cout << b << endl;
	Result = A_LU.solve(b);
	//Result = A_Cho.solve(b);
	//cout << Result << endl;

	for (auto v : heMesh->Vertices()) {
		size_t i = heMesh->Index(v);
		Para_Res[i][0] = Result(i, 0);
		Para_Res[i][1] = Result(i, 1);
	}
	
}

double ARAP::Energy()
{
	double result = 0.0;
	for (auto poly : heMesh->Polygons()) {
		int N = heMesh->Index(poly);
		result += Area[N] * ((Singular_Value[N][0] - 1) * (Singular_Value[N][0]) + (Singular_Value[N][1] - 1) * (Singular_Value[N][1] - 1));
	}
	return result;
}

void ARAP::Set_A_b()
{
	size_t nV = heMesh->NumVertices();
	Para_Res.resize(nV);
	//SparseMatrix<double> A;
	//MatrixXd b;
	A.resize(nV, nV);
	b.resize(nV, 2); b.setZero();

	MatrixXd Lt_;
	double Sum, ijSum;
	double delta_x, delta_y;
	size_t k,m;
	vector<Triplet<double>> tripletlist;
	for (auto v : heMesh->Vertices())
	{
		Sum = 0;
		size_t i = heMesh->Index(v);
		if (i != Fix1 && i != Fix2 && i != Fix3)
		{
			for (auto w : v->AdjVertices())
			{
				ijSum = 0; 
				size_t j = heMesh->Index(w);
				auto heij = v->HalfEdgeTo(w);   auto heji = w->HalfEdgeTo(v);
				auto polyij = heij->Polygon();  auto polyji = heji->Polygon();


				if (polyij != nullptr) {
					k = -1; m = -1;
					size_t N = heMesh->Index(polyij);
					for (size_t n = 0; n < 3; n++) {
						if (v == polyij->BoundaryVertice()[n])
							k = n;
						if (w == polyij->BoundaryVertice()[n])
							m = n;
					}
					if (k == -1) { cout << "Error in Set" << i << j << endl; return; }
					ijSum += COT_Theta(N, k);

					//Lt_ = Lt[N];
					//delta_x = Reference_triangles[3 * N + k][0] - Reference_triangles[3 * N + m][0];
					//delta_y = Reference_triangles[3 * N + k][1] - Reference_triangles[3 * N + m][1];
					//b(i, 0) += COT_Theta(N, k) * (Lt_(0, 0) * delta_x + Lt_(0, 1) * delta_y);
					//b(i, 1) += COT_Theta(N, k) * (Lt_(1, 0) * delta_x + Lt_(1, 1) * delta_y);
				}


				if (polyji != nullptr){
					k = -1; m = -1;
					size_t N = heMesh->Index(polyji);
					for (size_t n = 0; n < 3; n++) {
						if (w == polyji->BoundaryVertice()[n])
							k = n;
						if (v == polyji->BoundaryVertice()[n])
							m = n;
					}
					if (k == -1) { cout << "Error in Set" << j << i << endl; return; }
					ijSum += COT_Theta(N, k);

					//Lt_ = Lt[N];
					//delta_x = Reference_triangles[3 * N + m][0] - Reference_triangles[3 * N + k][0];
					//delta_y = Reference_triangles[3 * N + m][1] - Reference_triangles[3 * N + k][1];
					//b(i, 0) += COT_Theta(N, k) * (Lt_(0, 0) * delta_x + Lt_(0, 1) * delta_y);
					//b(i, 1) += COT_Theta(N, k) * (Lt_(1, 0) * delta_x + Lt_(1, 1) * delta_y);
				}


				tripletlist.push_back(Triplet<double>(i, j, -ijSum));
				Sum += ijSum;
			}
			tripletlist.push_back(Triplet<double>(i, i, Sum));
		}
		else {
			tripletlist.push_back(Triplet<double>(i, i, 1));
			//b(i, 0) = Para_Res[i][0];
			//b(i, 1) = Para_Res[i][1];
		}
	}
	

	A.setFromTriplets(tripletlist.begin(), tripletlist.end());

	A.makeCompressed();
	A_LU.compute(A);
	//cout << A << endl;
}

void ARAP::Upfate_b() 
{
	size_t nV = heMesh->NumVertices();
	
	//SparseMatrix<double> A;
	//MatrixXd b;
	
	b.resize(nV, 2); b.setZero();

	MatrixXd Lt_;
	double Sum, ijSum;
	double delta_x, delta_y;
	size_t k, m;
	vector<Triplet<double>> tripletlist;
	for (auto v : heMesh->Vertices())
	{
		Sum = 0;
		size_t i = heMesh->Index(v);
		if (i != Fix1 && i != Fix2 && i != Fix3)
		{
			for (auto w : v->AdjVertices())
			{
				ijSum = 0;
				size_t j = heMesh->Index(w);
				auto heij = v->HalfEdgeTo(w);   auto heji = w->HalfEdgeTo(v);
				auto polyij = heij->Polygon();  auto polyji = heji->Polygon();


				if (polyij != nullptr) {
					k = -1; m = -1;
					size_t N = heMesh->Index(polyij);
					for (size_t n = 0; n < 3; n++) {
						if (v == polyij->BoundaryVertice()[n])
							k = n;
						if (w == polyij->BoundaryVertice()[n])
							m = n;
					}
					if (k == -1) { cout << "Error in Set" << i << j << endl; return; }
					
					Lt_ = Lt[N];
					delta_x = Reference_triangles[3 * N + k][0] - Reference_triangles[3 * N + m][0];
					delta_y = Reference_triangles[3 * N + k][1] - Reference_triangles[3 * N + m][1];
					b(i, 0) += COT_Theta(N, k) * (Lt_(0, 0) * delta_x + Lt_(0, 1) * delta_y);
					b(i, 1) += COT_Theta(N, k) * (Lt_(1, 0) * delta_x + Lt_(1, 1) * delta_y);
				}


				if (polyji != nullptr) {
					k = -1; m = -1;
					size_t N = heMesh->Index(polyji);
					for (size_t n = 0; n < 3; n++) {
						if (w == polyji->BoundaryVertice()[n])
							k = n;
						if (v == polyji->BoundaryVertice()[n])
							m = n;
					}
					if (k == -1) { cout << "Error in Set" << j << i << endl; return; }
					

					Lt_ = Lt[N];
					delta_x = Reference_triangles[3 * N + m][0] - Reference_triangles[3 * N + k][0];
					delta_y = Reference_triangles[3 * N + m][1] - Reference_triangles[3 * N + k][1];
					b(i, 0) += COT_Theta(N, k) * (Lt_(0, 0) * delta_x + Lt_(0, 1) * delta_y);
					b(i, 1) += COT_Theta(N, k) * (Lt_(1, 0) * delta_x + Lt_(1, 1) * delta_y);
				}
				
			}
			
		}
		else {
			
			b(i, 0) = Para_Res[i][0];
			b(i, 1) = Para_Res[i][1];
		}
	}



}

void ARAP::Set_Fix()
{
	/*auto Bound = heMesh->Boundaries()[0];
	size_t Num = heMesh->Boundaries()[0].size();
	size_t No2 = Num / 2;
	Fix1 = heMesh->Index(Bound[0]->Origin());
	Fix2 = heMesh->Index(Bound[0]->End());
	//Fix2 = heMesh->Index(Bound[No2]->Origin());
	//Fix1 = Fix2 = -1;*/
	auto poly = heMesh->Polygons()[0];
	Fix1 = heMesh->Index(poly->BoundaryVertice()[0]);
	Fix2 = heMesh->Index(poly->BoundaryVertice()[1]);
	Fix3 = heMesh->Index(poly->BoundaryVertice()[2]);
}

double ARAP::distance(pointf3 x, pointf3 y)
{
	double res = (x[0] - y[0]) * (x[0] - y[0]) + (x[1] - y[1]) * (x[1] - y[1]) + (x[2] - y[2]) * (x[2] - y[2]);
	return sqrt(res);
}

double ARAP::Cot_weight(pointf3 p, pointf3 q, pointf3 a, pointf3 b)
{
	vecf3 ap, aq, bp, bq;
	for (size_t i = 0; i < 3; i++)
	{
		ap[i] = a[i] - p[i];
		aq[i] = a[i] - q[i];
		bp[i] = b[i] - p[i];
		bq[i] = b[i] - q[i];
	}
	double cos1 = ap.cos_theta(aq);
	double cos2 = bp.cos_theta(bq);
	return cos1 / sqrt(1. - cos1 * cos1) + cos2 / sqrt(1. - cos2 * cos2);
	
}

void ARAP::Para_2()
{
	if (heMesh->Boundaries().size() != 1)
	{
		cout << "Boundary is not single" << endl;
	}

	size_t Size = heMesh->Boundaries()[0].size();  //边界包含半边数,由于为封闭边界，故为边界点数
	auto Mhe = heMesh->Boundaries()[0];
	double length = 0;
	vector<double> Length_Bound(Size + 1, 0);  //边界点到起始点的距离，映射到多边形上尽可能保持距离比例
	vector<vector<double>> ParaResult(Size, vector<double>(2, 0));    //将边界映射到多边形边界结果

	
	for (size_t i = 0; i < Size; i++)
	{
		pointf3 ori = Mhe[i]->Origin()->pos.cast_to<pointf3>();
		pointf3 end = Mhe[i]->End()->pos.cast_to<pointf3>();
		
		double L = distance(ori, end);
		
		length += L;
		Length_Bound[i + 1] = length;
	}//计算边界长度

	for (size_t i = 0; i < Size + 1; i++) {
		Length_Bound[i] /= length;
	}//转化为比例

	for (size_t i = 0; i < Size; i++)
	{
		if (Length_Bound[i] <= 0.25) { ParaResult[i][0] = 0.25; ParaResult[i][1] = Length_Bound[i]; }
		else if (Length_Bound[i] <= 0.5) { ParaResult[i][0] = 0.5 - Length_Bound[i]; ParaResult[i][1] = 0.25; }
		else if (Length_Bound[i] <= 0.75) { ParaResult[i][0] = 0; ParaResult[i][1] = 0.75 - Length_Bound[i]; }
		else if (Length_Bound[i] < 1) { ParaResult[i][0] = Length_Bound[i] - 0.75; ParaResult[i][1] = 0; }
	}//转换为边长为0.25的正方形边界

	//优化四角
	size_t k = 0;
	while (Length_Bound[k] < 0.25) { k++; }
	if (Length_Bound[k] != 0.25) {
		if ((0.25 - Length_Bound[k - 1]) < (Length_Bound[k] - 0.25)) {
			ParaResult[k - 1][0] = 0.25; ParaResult[k - 1][1] = 0.25;
		}
		else {
			ParaResult[k][0] = 0.25; ParaResult[k][1] = 0.25;
		}
	}
	while (Length_Bound[k] < 0.5) { k++; }
	if (Length_Bound[k] != 0.5) {
		if ((0.5 - Length_Bound[k - 1]) < (Length_Bound[k] - 0.5)) {
			ParaResult[k - 1][0] = 0; ParaResult[k - 1][1] = 0.25;
		}
		else {
			ParaResult[k][0] = 0; ParaResult[k][1] = 0.25;
		}
	}
	while (Length_Bound[k] < 0.75) { k++; }
	if (Length_Bound[k] != 0.75) {
		if ((0.75 - Length_Bound[k - 1]) < (Length_Bound[k] - 0.75)) {
			ParaResult[k - 1][0] = 0; ParaResult[k - 1][1] = 0;
		}
		else {
			ParaResult[k][0] = 0; ParaResult[k][1] = 0;
		}
	}



	

	size_t nV = heMesh->NumVertices();
	Para_Res.resize(nV);
	SparseMatrix<double> A;
	MatrixXd b;
	A.resize(nV, nV);
	b.resize(nV, 2); b.setZero();
	vector<Triplet<double>> tripletlist;
	pointf3 Mp;

	for (size_t i = 0; i < Size; i++)
	{
		auto w = Mhe[i]->Origin();
		size_t j = heMesh->Index(w);
		b(j, 0) = ParaResult[i][0] * 4.0;
		b(j, 1) = ParaResult[i][1] * 4.0;
	}//设定b

	for (auto v : heMesh->Vertices())
	{
		size_t i = heMesh->Index(v);
		if (v->IsBoundary())
		{
			tripletlist.push_back(Triplet<double>(i, i, 1));
		}
		else {
			double Weight_Sum = 0.0;
			size_t Size_V = v->AdjVertices().size();
			for (size_t j = 0; j < Size_V; j++)
			{
				auto p_ = v->pos.cast_to<pointf3>();
				auto q_ = v->AdjVertices()[j]->pos.cast_to<pointf3>();

				//寻找邻点
				size_t pre = (j == 0) ? (Size_V - 1) : j - 1;
				size_t next = (j == Size_V - 1) ? 0 : j + 1;
				auto a_ = v->AdjVertices()[pre]->pos.cast_to<pointf3>();
				auto b_ = v->AdjVertices()[next]->pos.cast_to<pointf3>();

				double weight = Cot_weight(p_, q_, a_, b_);
				auto w = v->AdjVertices()[j];
				tripletlist.push_back(Triplet<double>(i, heMesh->Index(w), -weight));
				Weight_Sum += weight;
			}
			tripletlist.push_back(Triplet<double>(i, i, Weight_Sum));
		}
	}
	A.setFromTriplets(tripletlist.begin(), tripletlist.end());
	A.makeCompressed();

	SparseLU<SparseMatrix<double>> A_LU;

	A_LU.compute(A);

	MatrixXd Result;

	Result = A_LU.solve(b);

	for (auto v : heMesh->Vertices())
	{
		
		size_t i = heMesh->Index(v);
		Para_Res[i][0] = Result(i, 0);
		Para_Res[i][1] = Result(i, 1);
	}
}