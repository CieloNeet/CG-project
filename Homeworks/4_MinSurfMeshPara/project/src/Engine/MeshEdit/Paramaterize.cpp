#include <Engine/MeshEdit/Paramaterize.h>

#include <Engine/MeshEdit/MinSurf.h>

#include <Engine/Primitive/TriMesh.h>
#include <Eigen/Sparse>
#include <Eigen/SparseLU>


using namespace Eigen;
using namespace Ubpa;

using namespace std;

Paramaterize::Paramaterize(Ptr<TriMesh> triMesh)
	: heMesh(make_shared<HEMesh<V>>()) 
{
	Init(triMesh);
}

void Paramaterize::Clear() {
	heMesh->Clear();
	triMesh = nullptr;
}

bool Paramaterize::Init(Ptr<TriMesh> triMesh) {
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
	return true;
}

bool Paramaterize::RUN(PType Mtype, bool isto2D)
{
	if (heMesh->IsEmpty() || !triMesh) {
		printf("ERROR::MinSurf::Run\n"
			"\t""heMesh->IsEmpty() || !triMesh\n");
		return false;
	}

	if (Mtype == PType::KUni)
	{
		Para();
	}
	if (Mtype == PType::KCot)
	{
		Para_2();
	}
	//Para();
	//Para_2();

	// half-edge structure -> triangle mesh
	size_t nV = heMesh->NumVertices();
	size_t nF = heMesh->NumPolygons();
	vector<pointf3> positions;
	vector<unsigned> indice;
	vector<pointf2> texcoords;
	positions.reserve(nV);
	texcoords.reserve(nV);
	indice.reserve(3 * nF);

	for (auto v : heMesh->Vertices())
		positions.push_back(v->pos.cast_to<pointf3>());
	for (auto v : heMesh->Vertices())
	{
		auto w = v->pos.cast_to<pointf3>();
		pointf2 temp;
		temp[0] = w[0]; temp[1] = w[1];
		texcoords.push_back(temp);
	}
	for (auto f : heMesh->Polygons()) { // f is triangle
		for (auto v : f->BoundaryVertice()) // vertices of the triangle
			indice.push_back(static_cast<unsigned>(heMesh->Index(v)));
	}

	if (isto2D == true){
		triMesh->Update(positions);
	}
	else {
		triMesh->Update(texcoords);
	}
	//triMesh->Update(positions);

	return true;
}



void Paramaterize::Para() {
	
	if (heMesh->Boundaries().size() != 1)
	{
		cout << "Boundary is not single" << endl;
	}

	size_t Size = heMesh->Boundaries()[0].size();  //边界包含半边数,由于为封闭边界，故为边界点数
	auto Mhe = heMesh->Boundaries()[0];
	double length = 0;      
	vector<double> Length_Bound(Size + 1, 0);  //边界点到起始点的距离，映射到多边形上尽可能保持距离比例
	vector<vector<double>> ParaResult(Size , vector<double>(2, 0));    //将边界映射到多边形边界结果
	
	//cout << Size << endl;
	for (size_t i = 0; i < Size; i++)
	{
		pointf3 ori = Mhe[i]->Origin()->pos.cast_to<pointf3>();
		pointf3 end = Mhe[i]->End()->pos.cast_to<pointf3>();
		//cout << i << endl;
		//cout << "ori: " << ori[0] << "  " << ori[1] << "  " << ori[2] << "  " << endl;
		//cout << "end: " << end[0] << "  " << end[1] << "  " << end[2] << "  " << endl;
		double L = distance(ori, end);
		//cout << L << endl;
		length += L;
		Length_Bound[i + 1] = length;
	}//计算边界长度
	
	for (size_t i = 0; i < Size + 1; i++){
		Length_Bound[i] /= length;
	}//转化为比例

	for (size_t i = 0; i < Size; i++)
	{
		if (Length_Bound[i] <= 0.25) { ParaResult[i][0] = 0.25; ParaResult[i][1] = Length_Bound[i]; }
		else if (Length_Bound[i] <= 0.5) { ParaResult[i][0] = 0.5 - Length_Bound[i]; ParaResult[i][1] = 0.25; }
		else if (Length_Bound[i] <= 0.75) { ParaResult[i][0] = 0; ParaResult[i][1] = 0.75 - Length_Bound[i]; }
		else if (Length_Bound[i] < 1) { ParaResult[i][0] =  Length_Bound[i]-0.75; ParaResult[i][1] = 0; }
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

	/*for (size_t i = 0; i < Size; i++)
	{
		if (Length_Bound[i] <= 0.25) { ParaResult[i][0] = -0.125; ParaResult[i][1] = 0.125 - Length_Bound[i]; }
		else if (Length_Bound[i] <= 0.5) { ParaResult[i][0] = -0.375 + Length_Bound[i]; ParaResult[i][1] = -0.125; }
		else if (Length_Bound[i] <= 0.75) { ParaResult[i][0] = 0.125; ParaResult[i][1] = -0.625 + Length_Bound[i]; }
		else if (Length_Bound[i] < 1) { ParaResult[i][0] = 0.875 - Length_Bound[i]; ParaResult[i][1] = 0.125; }
	}//转换为边长为0.25的正方形边界

	//优化四角
	size_t k = 0;
	while (Length_Bound[k] < 0.25) { k++; }
	if (Length_Bound[k] != 0.25) {
		if ((0.25 - Length_Bound[k - 1]) < (Length_Bound[k] - 0.25)) {
			ParaResult[k - 1][0] = -0.125; ParaResult[k - 1][1] = -0.125;
		}
		else {
			ParaResult[k][0] = -0.125; ParaResult[k][1] = -0.125;
		}
	}
	while (Length_Bound[k] < 0.5) { k++; }
	if (Length_Bound[k] != 0.5) {
		if ((0.5 - Length_Bound[k - 1]) < (Length_Bound[k] - 0.5)) {
			ParaResult[k - 1][0] = 0.125; ParaResult[k - 1][1] = -0.125;
		}
		else {
			ParaResult[k][0] = 0.125; ParaResult[k][1] = -0.125;
		}
	}
	while (Length_Bound[k] < 0.75) { k++; }
	if (Length_Bound[k] != 0.75) {
		if ((0.75 - Length_Bound[k - 1]) < (Length_Bound[k] - 0.75)) {
			ParaResult[k - 1][0] = 0.125; ParaResult[k - 1][1] = 0.125;
		}
		else {
			ParaResult[k][0] = 0.125; ParaResult[k][1] = 0.125;
		}
	}*/

	/*for (size_t j = 0; j < Size; j++)
	{
		cout << "x: " << ParaResult[j][0] << "  y: " << ParaResult[j][1] << endl;
	}*/

	size_t nV = heMesh->NumVertices();
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
		b(j, 0) = ParaResult[i][0] *4.0;
		b(j, 1) = ParaResult[i][1] *4.0;
	}//设定b

	for (auto v : heMesh->Vertices())
	{
		size_t i = heMesh->Index(v);
		if (v->IsBoundary())
		{
			tripletlist.push_back(Triplet<double>(i, i, 1));
		}
		else {
			int D = v->Degree();
			tripletlist.push_back(Triplet<double>(i, i, D));
			for (auto w : v->AdjVertices())
			{
				tripletlist.push_back(Triplet<double>(i, heMesh->Index(w), -1));
			}
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
		pointf3 Np;
		size_t i = heMesh->Index(v);
		Np[0] = Result(i, 0);
		Np[1] = Result(i, 1);
		Np[2] = 0;
		v->pos = Np.cast_to<vecf3>();
	}
}

double Paramaterize::distance(pointf3 x, pointf3 y)
{
	double res = (x[0] - y[0]) * (x[0] - y[0]) + (x[1] - y[1]) * (x[1] - y[1]) + (x[2] - y[2]) * (x[2] - y[2]);
	return sqrt(res);
}


void Paramaterize::Para_2() {

	if (heMesh->Boundaries().size() != 1)
	{
		cout << "Boundary is not single" << endl;
	}

	size_t Size = heMesh->Boundaries()[0].size();  //边界包含半边数,由于为封闭边界，故为边界点数
	auto Mhe = heMesh->Boundaries()[0];
	double length = 0;
	vector<double> Length_Bound(Size + 1, 0);  //边界点到起始点的距离，映射到多边形上尽可能保持距离比例
	vector<vector<double>> ParaResult(Size, vector<double>(2, 0));    //将边界映射到多边形边界结果

	//cout << Size << endl;
	for (size_t i = 0; i < Size; i++)
	{
		pointf3 ori = Mhe[i]->Origin()->pos.cast_to<pointf3>();
		pointf3 end = Mhe[i]->End()->pos.cast_to<pointf3>();
		//cout << i << endl;
		//cout << "ori: " << ori[0] << "  " << ori[1] << "  " << ori[2] << "  " << endl;
		//cout << "end: " << end[0] << "  " << end[1] << "  " << end[2] << "  " << endl;
		double L = distance(ori, end);
		//cout << L << endl;
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



	/*for (size_t j = 0; j < Size; j++)
	{
		cout << "x: " << ParaResult[j][0] << "  y: " << ParaResult[j][1] << endl;
	}*/

	size_t nV = heMesh->NumVertices();
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
		pointf3 Np;
		size_t i = heMesh->Index(v);
		Np[0] = Result(i, 0);
		Np[1] = Result(i, 1);
		Np[2] = 0;
		v->pos = Np.cast_to<vecf3>();

	}

}




double Paramaterize::Cot_weight(pointf3 p, pointf3 q, pointf3 a, pointf3 b)
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
	//auto Po = heMesh->Polygons();
}