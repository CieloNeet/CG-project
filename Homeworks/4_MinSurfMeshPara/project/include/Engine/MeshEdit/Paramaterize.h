#pragma once

#include <Basic/HeapObj.h>
#include <UHEMesh/HEMesh.h>
#include <UGM/UGM>

namespace Ubpa {
	class TriMesh;
	class MinSurf;

	enum PType {
		KUni = 1,
		KCot
	};

	// mesh boundary == 1
	class Paramaterize : public HeapObj {
	public:
		Paramaterize(Ptr<TriMesh> triMesh);
	public:
		static const Ptr<Paramaterize> New(Ptr<TriMesh> triMesh) {
			return Ubpa::New<Paramaterize>(triMesh);
		}
	public:
		void Clear();
		bool Init(Ptr<TriMesh> triMesh);

		bool RUN(PType Mtype, bool isto2D);


	private:
		void Para();
		void Para_2();
		double distance(pointf3 x,pointf3 y);
		double Cot_weight(pointf3 p, pointf3 q, pointf3 a, pointf3 b);

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
		friend class MinSurf;
		friend class ARAP2;
		
		Ptr<TriMesh> triMesh;
		const Ptr<HEMesh<V>> heMesh; // vertice order is same with triMesh
	};
}
