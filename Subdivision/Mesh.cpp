#include "Mesh.h"


Mesh::Mesh(vector<int> *faces,vector<Vertex> *points)
{
	listeVertex=new vector<Vertex>();
	listeFaces=new vector<Face>();
	listeEdges=new vector<Edge>();

	remplirListes(faces,points);
}


Mesh::~Mesh(void)
{
}

void Mesh::remplirListes(vector<int> *faces,vector<Vertex> *points)
{
	//on remplit la liste des points
	for(int i=0;i<points->size();i++)
	{
		listeVertex->push_back(points->at(i));
	}

	//on remplit la liste des arêtes
	int aretes=0;
	for(int i=0;i<faces->size();i=i+4)
	{
		int v1=faces->at(i);
		int v2=faces->at(i+1);
		int v3=faces->at(i+2);
		int v4=faces->at(i+3);

		Edge e1,e2,e3,e4;

		e1.vertex1=v1;
		e1.vertex2=v2;
		e1.index=aretes;
		aretes++;
		
		e2.vertex1=v2;
		e2.vertex2=v3;
		e2.index=aretes;
		aretes++;

		e3.vertex1=v3;
		e3.vertex2=v4;
		e3.index=aretes;
		aretes++;

		e4.vertex1=v4;
		e4.vertex2=v1;
		e4.index=aretes;
		aretes++;

		listeEdges->push_back(e1);
		listeEdges->push_back(e2);
		listeEdges->push_back(e3);
		listeEdges->push_back(e4);
	}

	
	/*******Les arêtes ne doivent être référencées qu'une seule fois*******/

	//Nettoyage des edges
	for(int i=0;i<listeEdges->size();i++)
	{
		int edge1=listeEdges->at(i).vertex1;
		int edge2=listeEdges->at(i).vertex2;
		for(int j=0;j<listeEdges->size();j++)
		{
			//si l'arête a déjà été référencée
			if((edge1==listeEdges->at(i).vertex1 && edge2==listeEdges->at(i).vertex2) || (edge1==listeEdges->at(i).vertex2 && edge2==listeEdges->at(i).vertex1))
			{
				listeEdges->erase(listeEdges->begin()+j);
			}
		}
	}

	//on remplit la liste des faces



}

void Mesh::subdiviser(int iterations)
{

}

vector<Vertex>* Mesh::getPoints()
{
	return NULL;
}

vector<int>* Mesh::getFaces()
{
	return NULL;
}