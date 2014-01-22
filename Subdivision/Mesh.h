#ifndef MESH_H
#define MESH_H

#include "Edge.h"
#include "Face.h"
#include "Vertex.h"

#include <vector>

using namespace std;

class Mesh
{
	public:
		Mesh(vector<int> *faces,vector<Vertex> *points);
		~Mesh(void);

		void subdiviser(int iterations);
		vector<Vertex> *getPoints();
		vector<int> *getFaces();

		
		vector <Vertex> *listeVertex;
		vector <Edge> *listeEdges;
		vector <Face> *listeFaces;

		int nombreEdgePoints;
		int nombreFacePoints;
		int nombreOldPoints;

	private:
		void remplirListes(vector<int> *faces,vector<Vertex> *points);
};

#endif
