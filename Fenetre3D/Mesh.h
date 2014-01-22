#pragma once

#include "Face.h"
#include "Vertex.h"

#include "HE_Vertex.h"
#include "HE_HalfEdge.h"
#include "HE_Face.h"

#include "ObjHelper.h"

#include <vector>
#include <math.h>
#include <map>

#include <iostream>

#include <gl\glut.h>

using namespace std;

class Mesh
{
	public:
		Mesh(vector<Face> *faces,vector<Vertex> *vertexes);
		~Mesh(void);
		
		//attributs
		vector<HE_Face*> *faces;
		vector<HE_HalfEdge*> *half_edges;
		vector<HE_Vertex*> *vertexes;

		int nombreSommets;
		int nombreSommetsOrigine;

		//méthodes
		void subdiviser();
		void afficher(float r, float v, float b,int typeAffichage);

	private:
		void remplirStructure(vector<Face> *faces,vector<Vertex> *vertexes);
};

