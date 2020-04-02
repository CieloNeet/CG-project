#pragma once

#include <Basic/HeapObj.h>
//#include <Engine/Scene/CmptSimu/MassSpring.h>
//#include <Engine/Primitive/MassSpring.h>
#include <UGM/UGM>
#include <Eigen/Dense>
#include <Eigen/Sparse>

namespace Ubpa {
	class Simulate : public HeapObj {
	public:
		Simulate(const std::vector<pointf3>& plist,
			const std::vector<unsigned>& elist) {
			edgelist = elist;
			this->positions.resize(plist.size());
			for (int i = 0; i < plist.size(); i++)
			{
				for (int j = 0; j < 3; j++)
				{
					this->positions[i][j] = plist[i][j];
				}
			}
		};
	public:
		static const Ptr<Simulate> New(const std::vector<pointf3>& plist,
			const std::vector<unsigned> &elist) {
			return Ubpa::New<Simulate>(plist, elist);
		}
	public:
		// clear cache data
		void Clear();

		// init cache data (eg. half-edge structure) for Run()
		bool Init();
		//bool Init();

		// call it after Init()
		bool Run();
		
		const std::vector<pointf3>& GetPositions() const { return positions; };

		const float GetStiff() { return stiff; };
		void SetStiff(float k) { stiff = k; Init();};
		const float GetTimeStep() { return h; };
		void SetTimeStep(float k) { h = k; Init();};
		std::vector<unsigned>& GetFix() { return this->fixed_id; };
		void SetFix(const std::vector<unsigned>& f) { this->fixed_id = f; Init();};
		const std::vector<pointf3>& GetVelocity() { return velocity; };
		//void SetVelocity(const std::vector<pointf3>& v) { velocity = v; };
		void Restore();
		void SetLeftFix(bool istet);
		bool is_fixed(int i);
		double distance(pointf3 x, pointf3 y);


	private:
		// kernel part of the algorithm
		void SimulateOnce();
		void Set_y();
		void Set_A();
		void Insert_A(size_t i, size_t j, Eigen::MatrixXd  D);    //将3*3子矩阵插入到系数矩阵中
		void Set_b();

	private:
		float h = 0.03f;  //步长
		float stiff = 1.f;
		float g = 9.8f;
		std::vector<unsigned> fixed_id;  //fixed point id


		//mesh data
		std::vector<unsigned> edgelist;


		//simulation data
		std::vector<pointf3> positions;
		std::vector<pointf3> old_positions;
		std::vector<pointf3> velocity;
		std::vector<double> length;   //弹簧初始长度
		std::vector<double> y;  //迭代初值
		std::vector<double> x_iter;  //迭代x

		std::vector<Eigen::Triplet<double>>  coff;
		Eigen::SparseMatrix<double> A;
		Eigen::MatrixXd b;
	};
}
