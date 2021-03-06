#include <Engine/MeshEdit/MinSurf.h>

#include <Engine/Primitive/TriMesh.h>

#include <Eigen/Sparse>
#include <Eigen/SparseLU>

using namespace Ubpa;

using namespace std;
using namespace Eigen;

MinSurf::MinSurf(Ptr<TriMesh> triMesh)
	: heMesh(make_shared<HEMesh<V>>())
{
	Init(triMesh);
}

void MinSurf::Clear() {
	heMesh->Clear();
	triMesh = nullptr;
}

bool MinSurf::Init(Ptr<TriMesh> triMesh) {
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

bool MinSurf::Run() {
	if (heMesh->IsEmpty() || !triMesh) {
		printf("ERROR::MinSurf::Run\n"
			"\t""heMesh->IsEmpty() || !triMesh\n");
		return false;
	}

	Minimize();

	// half-edge structure -> triangle mesh
	size_t nV = heMesh->NumVertices();
	size_t nF = heMesh->NumPolygons();
	vector<pointf3> positions;
	vector<unsigned> indice;
	positions.reserve(nV);
	indice.reserve(3 * nF);
	for (auto v : heMesh->Vertices())
		positions.push_back(v->pos.cast_to<pointf3>());
	for (auto f : heMesh->Polygons()) { // f is triangle
		for (auto v : f->BoundaryVertice()) // vertices of the triangle
			indice.push_back(static_cast<unsigned>(heMesh->Index(v)));
	}

	//triMesh->Init(indice, positions);
	triMesh->Update(positions);
	return true;
}

void MinSurf::Minimize() {
	// TODO
	size_t nV = heMesh->NumVertices();
	
	SparseMatrix<double> A;
	MatrixXd b;
	A.resize(nV, nV);
	b.resize(nV, 3); b.setZero();
	vector<Triplet<double>> tripletlist; 
	pointf3 Mp;

	for (auto v : heMesh->Vertices())
	{
		size_t i = heMesh->Index(v);
		if (v->IsBoundary())
		{
			tripletlist.push_back(Triplet<double>(i, i, 1));           //�̶��߽��
			Mp = v->pos.cast_to<pointf3>();
			//cout << Mp << endl;
			b(i, 0) = Mp[0];
			b(i, 1) = Mp[1];
			b(i, 2) = Mp[2];
		}
		else
		{
			int D = v->Degree();
			tripletlist.push_back(Triplet<double>(i, i, D));
			for (auto w : v->AdjVertices())
			{
				tripletlist.push_back(Triplet<double>(i, heMesh->Index(w), -1));
			}
		}
	}
	//cout << b << endl << endl << endl;
	A.setFromTriplets(tripletlist.begin(), tripletlist.end());
	A.makeCompressed();
	//cout << A << endl << endl << endl << endl;
	
	SparseLU<SparseMatrix<double>> A_LU;
	
	A_LU.compute(A);

	MatrixXd Result;
	
	Result = A_LU.solve(b);

	//cout << Result << endl << endl << endl << endl;

	

	for (auto v : heMesh->Vertices())
	{
		pointf3 Np;
		size_t i = heMesh->Index(v);
		Np[0] = Result(i, 0);
		Np[1] = Result(i, 1);
		Np[2] = Result(i, 2);
		v->pos = Np.cast_to<vecf3>();
	}
	
	cout << "WARNING::MinSurf::Minimize:" << endl
		<< "\t" << "not implemented" << endl;
}

/*void MinSurf::Minimize() {
	// TODO


	pointf3 Mp;
	size_t nV = heMesh->NumVertices();
	cout << nV << endl;

	for (auto v : heMesh->Vertices())
	{
		int i = 1;
		Mp = v->pos.cast_to<pointf3>();
		cout << v->Degree() << endl;
		cout << heMesh->Index(v) << endl;
		if (v->IsBoundary()) {
			cout << "1   ";
		}
		else {
			cout << "0    ";
		}
		cout << Mp[0] << " " << Mp[1] << " " << Mp[2] << endl;
		for (auto w : v->AdjVertices())
		{
			Mp = w->pos.cast_to<pointf3>();
			cout << "     " << i << "    " << heMesh->Index(w) << "       " << Mp[0] << " " << Mp[1] << " " << Mp[2] << endl;
			i++;
		}

	}
	cout << "WARNING::MinSurf::Minimize:" << endl
		<< "\t" << "not implemented" << endl;
}*/