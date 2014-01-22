#include "ObjHelper.h"


ObjHelper::ObjHelper(void)
{
}

void ObjHelper::lireObj(string fichier)
{
	faces=new vector<Face>();
	vertexes=new vector<Vertex>();

	ifstream file(fichier);
 
    if (file)
    {
        string ligne;
		
        while (getline( file, ligne ))
        {
			
			if(ligne.find("v ")==0)
			{
				int posEspace1=ligne.find(' ',2);
				int posEspace2=ligne.find(' ',posEspace1+1);

				Vertex v;
				v.x=strtod(ligne.substr(2,posEspace1-1).c_str(),NULL);
				v.y=strtod(ligne.substr(posEspace1+1,posEspace2-1).c_str(),NULL);
				v.z=strtod(ligne.substr(posEspace2+1,ligne.length()).c_str(),NULL);
				vertexes->push_back(v);
			}
			else if(ligne.find("f ")==0) //ligne décrivant des faces
			{
				int posEspace1,posEspace2,posEspace3;
				int sommet1,sommet2,sommet3,sommet4;
				int indice1,indice2,indice3;
				
				
				posEspace1=ligne.find(' ',2);
				posEspace2=ligne.find(' ',posEspace1+1);
				posEspace3=ligne.find(' ',posEspace2+1);

				Face f;
				f.v1=atoi(ligne.substr(2,posEspace1-1).c_str());
				f.v2=atoi(ligne.substr(posEspace1+1,posEspace2-1).c_str());
				f.v3=atoi(ligne.substr(posEspace2+1,posEspace3-1).c_str());

				if(posEspace3==-1)
				{
					f.v4=-1;
				}
				else
				{
					f.v4=atoi(ligne.substr(posEspace3+1,ligne.length()).c_str());
				}


				faces->push_back(f);
			}
        }

    }
}

void ObjHelper::ecrireObj(string fichier,vector<Face> *f,vector<Vertex> *v)
{
	ofstream file(fichier, ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
 
    if(file)
    {
		//on écrit les vertices
		for(int i=0;i<v->size();i++)
		{
			file<<fixed<<setprecision(6)<<"v "<<v->at(i).x<<" "<<v->at(i).y<<" "<<v->at(i).z<<endl;
		}

		//on écrit les faces
		for(int i=0;i<f->size();i++)
		{
			file<<"f "<<f->at(i).v1<<" "<<f->at(i).v2<<" "<<f->at(i).v3<<" "<<f->at(i).v4<<endl;
		}
 
        file.close();
    }
    else
	{
			cerr << "Impossible d'ouvrir le fichier !" << endl;
	}
}

ObjHelper::~ObjHelper(void)
{
	delete faces;
	delete vertexes;
}
