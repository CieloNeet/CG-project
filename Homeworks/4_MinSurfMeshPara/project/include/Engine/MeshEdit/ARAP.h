#pragma once

#include <Basic/HeapObj.h>
#include <UHEMesh/HEMesh.h>
#include <UGM/UGM>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/SparseLU>

namespace Ubpa {
	class TriMesh;
	class MinSurf;


	// mesh boundary == 1
	class ARAP : public HeapObj {
	public:
		ARAP(Ptr<TriMesh> triMesh);
	public:
		static const Ptr<ARAP> New(Ptr<TriMesh> triMesh) {
			return Ubpa::New<ARAP>(triMesh);
		}
	public:
		void Clear();
		bool Init(Ptr<TriMesh> triMesh);
		bool ARAP_RUN(bool isto2D);
		

	private:
		void flatten();
		void Get_Lt_SV();
		void Update_Para_Res();
		void Set_Fix();
		void Set_A_b();
		void Upfate_b();
		double Energy();
		void InitPara(Ptr<TriMesh> triMesh);

		double distance(pointf3 x, pointf3 y);
		double Cot_weight(pointf3 p, pointf3 q, pointf3 a, pointf3 b);
		void Para_2();
	private:
		class V;
		class E;
		class P;
		class V : public TVertex<V, E, P> {
		public:
			vecf3 pos;
		};
		class E : public TEdge<V, E, P> { };
		class P :public TPolygon<V, E, P> { };
	private:
		friend class Paramaterize;

		std::vector<pointf2> Reference_triangles;          //记录将三角形全等映射到临时参数空间的坐标
		Eigen::MatrixXd COT_Theta;                         //记录原三角网格对应角的余弦值
		std::vector<pointf2> Para_Res;
		std::vector<pointf2> Singular_Value;
		std::vector<Eigen::MatrixXd> Lt;                   //确定Lt
		std::vector<double> Area;
		Eigen::SparseMatrix<double> A;
		Eigen::MatrixXd b;
		size_t Fix1, Fix2, Fix3;
		Eigen::SparseLU<Eigen::SparseMatrix<double>> A_LU;
		
		Ptr<TriMesh> triMesh;
		
		const Ptr<HEMesh<V>> heMesh; // vertice order is same with triMesh
		
	};
}

