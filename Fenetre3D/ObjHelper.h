#pragma once

#include "Vertex.h"
#include "Face.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

class ObjHelper
{
	public:
		ObjHelper(void);
		~ObjHelper(void);

		//méthodes
		void lireObj(string fichier);
		void ecrireObj(string fichier,vector<Face> *f,vector<Vertex> *v);

		//attributs
		vector<Face> *faces;
		vector<Vertex> *vertexes;

};

