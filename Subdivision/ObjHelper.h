#ifndef OBJHELPER_H
#define OBJHELPER_H

#include "Vertex.h"

#include <vector>
#include <fstream>
#include <string>
using namespace std;

class ObjHelper
{
	public:
		ObjHelper(void);
		~ObjHelper(void);

		//attributs
		vector<int> *faces;
		vector<Vertex> *points;

		//méthodes
		void ecrireObj(vector<Vertex> *points,vector<int> *faces);
		void lireObj(string fichier);
		vector<int>* getFaces();
		vector<Vertex>* getPoints();
};

#endif
