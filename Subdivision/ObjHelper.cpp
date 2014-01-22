#include "ObjHelper.h"


ObjHelper::ObjHelper(void)
{
}

void ObjHelper::lireObj(string fichier)
{
	ifstream flux(fichier);
	
	faces=new vector<int>();
	points=new vector<Vertex>();
 

    if (flux)
    {
        string ligne;
		int nombrePoints=0;
 
        while (getline(flux, ligne))
        {
			if(ligne.find("v ")==0)
			{
				int posEspace1=ligne.find(' ',2);
				int posEspace2=ligne.find(' ',posEspace1+1);

				Vertex v;
				v.x=strtod(ligne.substr(2,posEspace1-1).c_str(),NULL);
				v.y=strtod(ligne.substr(posEspace1+1,posEspace2-1).c_str(),NULL);
				v.z=strtod(ligne.substr(posEspace2+1,ligne.length()).c_str(),NULL);
				v.index=nombrePoints;
				points->push_back(v);

				nombrePoints++;
			}
			else if(ligne.find("f ")==0) //ligne décrivant des faces
			{
				int posEspace1,posEspace2,posEspace3;
				int sommet1,sommet2,sommet3,sommet4;
				int indice1,indice2,indice3;
				
				
				posEspace1=ligne.find(' ',2);
				posEspace2=ligne.find(' ',posEspace1+1);
				posEspace3=ligne.find(' ',posEspace2+1);

				faces->push_back(atoi(ligne.substr(2,posEspace1-1).c_str()));
				faces->push_back(atoi(ligne.substr(posEspace1+1,posEspace2-1).c_str()));
				faces->push_back(atoi(ligne.substr(posEspace2+1,posEspace3-1).c_str()));
				faces->push_back(atoi(ligne.substr(posEspace3+1,ligne.length()).c_str()));
				
			}
        }
		
		flux.close();

    }
}


ObjHelper::~ObjHelper(void)
{
}

void ObjHelper::ecrireObj(vector<Vertex> *points,vector<int> *faces)
{

}

vector<int>* ObjHelper::getFaces()
{
	return this->faces;
}
vector<Vertex>* ObjHelper::getPoints()
{
	return this->points;
}