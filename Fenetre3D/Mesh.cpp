#include "Mesh.h"



Mesh::Mesh(vector<Face> *f,vector<Vertex> *v)
{
	remplirStructure(f,v);
}

Mesh::~Mesh(void)
{
	delete faces;
	delete half_edges;
	delete vertexes;
}

void Mesh::subdiviser()
{
	
	//algorithme de Catmull-Clark

	//création des points de faces au milieu de chaque face

		for(int i=0;i<faces->size();i++)
		{
			HE_Vertex *pointDeFace=new HE_Vertex();

			HE_HalfEdge *edgeTemp;
			HE_Vertex *pointTemp;

			edgeTemp=faces->at(i)->edge;
			int nombreEdge=0;

			do
			{
				pointTemp=edgeTemp->vertex;
				edgeTemp=edgeTemp->next;

				//on fait la somme de tous les points de la face
				pointDeFace->x=pointDeFace->x+pointTemp->x;
				pointDeFace->y=pointDeFace->y+pointTemp->y;
				pointDeFace->z=pointDeFace->z+pointTemp->z;
				nombreEdge++;

			} while(edgeTemp!=faces->at(i)->edge);

			//barycentre des points appartenant à la face
			pointDeFace->x=pointDeFace->x/nombreEdge;
			pointDeFace->y=pointDeFace->y/nombreEdge;
			pointDeFace->z=pointDeFace->z/nombreEdge;

			nombreSommets++;
			pointDeFace->index=nombreSommets;

			faces->at(i)->facePoint=pointDeFace;
			vertexes->push_back(pointDeFace);

		}

	//création des points d'arête 
		
		for(int i=0;i<half_edges->size();i++)
		{
			Vertex *milieuArete=new Vertex();

			//vérifie que le edge-point n'a pas déjà été ajouté en tant que pair
			if(half_edges->at(i)->edgePoint==0)
			{
				HE_Vertex *pointDArete=new HE_Vertex();

				//milieu de l'arête
					
					milieuArete->x=(half_edges->at(i)->vertex->x+half_edges->at(i)->next->vertex->x)/2;
					milieuArete->y=(half_edges->at(i)->vertex->y+half_edges->at(i)->next->vertex->y)/2;
					milieuArete->z=(half_edges->at(i)->vertex->z+half_edges->at(i)->next->vertex->z)/2;

				//milieu des 2 points de face adjacents à l'arête
					Vertex milieuFaces;
					milieuFaces.x=(half_edges->at(i)->face->facePoint->x+half_edges->at(i)->pair->face->facePoint->x)/2;
					milieuFaces.y=(half_edges->at(i)->face->facePoint->y+half_edges->at(i)->pair->face->facePoint->y)/2;
					milieuFaces.z=(half_edges->at(i)->face->facePoint->z+half_edges->at(i)->pair->face->facePoint->z)/2;

				//barycentre entre le milieu de l'arête et le milieu des faces
					pointDArete->x=(milieuArete->x+milieuFaces.x)/2;
					pointDArete->y=(milieuArete->y+milieuFaces.y)/2;
					pointDArete->z=(milieuArete->z+milieuFaces.z)/2;

				
				
					pointDArete->index=nombreSommets+1;

				
					half_edges->at(i)->edgePoint=pointDArete;
					half_edges->at(i)->milieu=milieuArete;

					//cette condition permet de n'avoir qu'un edge-point pour 2 half-edge
					if(half_edges->at(i)->pair->edgePoint==0)
					{
						//on assigne le edge-point au half-edge pair
						half_edges->at(i)->pair->edgePoint=pointDArete;
						half_edges->at(i)->pair->milieu=milieuArete;
						nombreSommets++;
						vertexes->push_back(pointDArete);
					}
			}
				
		}

	//Déplacement des anciens sommets
		
		for(int i=0;i<nombreSommetsOrigine;i++)
		{
			//calcul de F le barycentre des k points de face adjacents
			
				HE_Vertex *pointF=new HE_Vertex();
				HE_HalfEdge *edgeTemp;
				HE_Vertex *pointFaceTemp;

				edgeTemp=vertexes->at(i)->edge;
				int nombreEdge=0;

				do
				{
					pointFaceTemp=edgeTemp->face->facePoint;
					edgeTemp=edgeTemp->pair->next;

					//on fait la somme de tous les points de la face
					pointF->x=pointF->x+pointFaceTemp->x;
					pointF->y=pointF->y+pointFaceTemp->y;
					pointF->z=pointF->z+pointFaceTemp->z;
					nombreEdge++;

				} while(edgeTemp!=vertexes->at(i)->edge);

				pointF->x=pointF->x/nombreEdge;
				pointF->y=pointF->y/nombreEdge;
				pointF->z=pointF->z/nombreEdge;

			//Calcul de R le barycentre des k points d'arêtes adjacents

				HE_Vertex *pointR=new HE_Vertex();
				HE_HalfEdge *edgeTemp2;
				Vertex *pointAreteTemp;

				edgeTemp2=vertexes->at(i)->edge;
				int nombreEdge2=0;

				do
				{
					pointAreteTemp=edgeTemp2->milieu;
					edgeTemp2=edgeTemp2->pair->next;

					//on fait la somme de tous les points de la face
					pointR->x=pointR->x+pointAreteTemp->x;
					pointR->y=pointR->y+pointAreteTemp->y;
					pointR->z=pointR->z+pointAreteTemp->z;
					nombreEdge2++;

				} while(edgeTemp2!=vertexes->at(i)->edge);

				pointR->x=pointR->x/nombreEdge2;
				pointR->y=pointR->y/nombreEdge2;
				pointR->z=pointR->z/nombreEdge2;

			//Déplacement de P par la formule: (F+2R+(k-3)P)/k
				vertexes->at(i)->x=(pointF->x+(2*pointR->x)+((nombreEdge2-3)*vertexes->at(i)->x))/nombreEdge2;
				vertexes->at(i)->y=(pointF->y+(2*pointR->y)+((nombreEdge2-3)*vertexes->at(i)->y))/nombreEdge2;
				vertexes->at(i)->z=(pointF->z+(2*pointR->z)+((nombreEdge2-3)*vertexes->at(i)->z))/nombreEdge2;

			//on nettoie
				delete pointF;
				delete pointR;
		}
		
	//on relit les points entre eux pour créer la nouvelle structure
		
		//Pour chaque face on crée 4 faces

			vector<Face> *f=new vector<Face>();
			vector<Vertex> *v=new vector<Vertex>();

			for(int i=0;i<faces->size();i++)
			{
				HE_HalfEdge *edgeTemp;

				edgeTemp=faces->at(i)->edge;
				int nombrePoints=1;
				Face face1,face2,face3,face4;

				do
				{
					
					switch(nombrePoints)
					{
						case 1:
							//première face

								//point 1
									face1.v1=edgeTemp->vertex->index;

								//point 2
									face1.v2=edgeTemp->edgePoint->index;

								//point 3
									face1.v3=edgeTemp->face->facePoint->index;

								//point 4
									face1.v4=edgeTemp->previous->edgePoint->index;

								f->push_back(face1);
							break;
						case 2:
							//deuxième face

								//point 1
									face2.v1=edgeTemp->vertex->index;

								//point 2
									face2.v2=edgeTemp->edgePoint->index;

								//point 3
									face2.v3=edgeTemp->face->facePoint->index;

								//point 4
									face2.v4=edgeTemp->previous->edgePoint->index;

								f->push_back(face2);
							break;
						case 3:
							//troisième face

								//point 1
									face3.v1=edgeTemp->vertex->index;

								//point 2
									face3.v2=edgeTemp->edgePoint->index;

								//point 3
									face3.v3=edgeTemp->face->facePoint->index;

								//point 4
									face3.v4=edgeTemp->previous->edgePoint->index;

								f->push_back(face3);
							break;
						case 4:
							//quatrième face

								//point 1
									face4.v1=edgeTemp->vertex->index;

								//point 2
									face4.v2=edgeTemp->edgePoint->index;

								//point 3
									face4.v3=edgeTemp->face->facePoint->index;

								//point 4
									face4.v4=edgeTemp->previous->edgePoint->index;

								f->push_back(face4);
							break;
					}
					
						
					edgeTemp=edgeTemp->next;

					nombrePoints++;

				} while(edgeTemp!=faces->at(i)->edge);
				
			}
			
		//On remplit les sommets
			for(int i=0;i<nombreSommets;i++)
			{
				Vertex vertex;
				vertex.x=vertexes->at(i)->x;
				vertex.y=vertexes->at(i)->y;
				vertex.z=vertexes->at(i)->z;

				v->push_back(vertex);
			}

		//ObjHelper objHelper;
		//objHelper.ecrireObj("test.obj",f,v);

		delete faces;
		delete half_edges;
		delete vertexes;

		//On remplit la structure
			remplirStructure(f,v);

		
}

void Mesh::remplirStructure(vector<Face> *f,vector<Vertex> *v)
{
	faces=new vector<HE_Face*>();
	half_edges=new vector<HE_HalfEdge*>();
	vertexes=new vector<HE_Vertex*>();

	nombreSommets=v->size();
	nombreSommetsOrigine=v->size();

	for(int i=0;i<v->size();i++) //Ici on remplit les points
	{
		HE_Vertex *vertex=new HE_Vertex();
		vertex->x=v->at(i).x;
		vertex->y=v->at(i).y;
		vertex->z=v->at(i).z;
		vertex->index=i+1;

		vertexes->push_back(vertex);
		
	}

	//Ici on remplit une liste de half-edge pour trouver les pairs par la suite

	map<pair<HE_Vertex*,HE_Vertex*>,HE_HalfEdge*> *paires=new map<pair<HE_Vertex*,HE_Vertex*>,HE_HalfEdge*>(); 
	
	for(int i=0;i<f->size();i++)
	{
		HE_HalfEdge *he1=new HE_HalfEdge();
		HE_HalfEdge *he2=new HE_HalfEdge();
		HE_HalfEdge *he3=new HE_HalfEdge();
		HE_HalfEdge *he4=new HE_HalfEdge();

		pair<HE_Vertex*,HE_Vertex*> paire1;
		paire1.first=vertexes->at((f->at(i).v1-1));
		paire1.second=vertexes->at((f->at(i).v2-1));
		paires->insert(map<pair<HE_Vertex*,HE_Vertex*>,HE_HalfEdge*>::value_type(paire1,he1));

		pair<HE_Vertex*,HE_Vertex*> paire2;
		paire2.first=vertexes->at((f->at(i).v2-1));
		paire2.second=vertexes->at((f->at(i).v3-1));
		paires->insert(map<pair<HE_Vertex*,HE_Vertex*>,HE_HalfEdge*>::value_type(paire2,he2));

		pair<HE_Vertex*,HE_Vertex*> paire3;
		paire3.first=vertexes->at((f->at(i).v3-1));
		paire3.second=vertexes->at((f->at(i).v4-1));
		paires->insert(map<pair<HE_Vertex*,HE_Vertex*>,HE_HalfEdge*>::value_type(paire3,he3));

		pair<HE_Vertex*,HE_Vertex*> paire4;
		paire4.first=vertexes->at((f->at(i).v4-1));
		paire4.second=vertexes->at((f->at(i).v1-1));
		paires->insert(map<pair<HE_Vertex*,HE_Vertex*>,HE_HalfEdge*>::value_type(paire4,he4));



		half_edges->push_back(he1);
		half_edges->push_back(he2);
		half_edges->push_back(he3);
		half_edges->push_back(he4);
		
		
	}

	for(int i=0,j=0;i<f->size();i++,j=j+4) //Pour chaque face
	{

		//face à laquelle appartiennent les half-edge
				HE_Face *face=new HE_Face();
				face->edge=half_edges->at(j);
				faces->push_back(face);
				


		/*****premier point de la face*****/ //he1
		
			//face à laquelle appartient ce half-edge
				half_edges->at(j+0)->face=face; 
		
			//prochain half-edge dans la face
				half_edges->at(j+0)->next=half_edges->at(j+1);

			//précédent half-edge dans la face
				half_edges->at(j+0)->previous=half_edges->at(j+3);

			//une demi-arête partant de ce sommet
				vertexes->at(f->at(i).v1-1)->edge=half_edges->at(j+0);

			//sommet à partir duquel commence le half-edge
				half_edges->at(j+0)->vertex=vertexes->at(f->at(i).v1-1);


		/*****deuxième point de la face*****/ //he2
		
			//face à laquelle appartient ce half-edge
				half_edges->at(j+1)->face=face;
		
			//prochain half-edge dans la face
				half_edges->at(j+1)->next=half_edges->at(j+2);

			//précédent half-edge dans la face
				half_edges->at(j+1)->previous=half_edges->at(j+0);

			//une demi-arête partant de ce sommet
				vertexes->at(f->at(i).v2-1)->edge=half_edges->at(j+1);

			//sommet à partir duquel commence le half-edge
				half_edges->at(j+1)->vertex=vertexes->at(f->at(i).v2-1);

		


		/*****troisième point de la face*****/ //he3
		
			//face à laquelle appartient ce half-edge
				half_edges->at(j+2)->face=face;
		
			//prochain half-edge dans la face
				half_edges->at(j+2)->next=half_edges->at(j+3);

			//précédent half-edge dans la face
				half_edges->at(j+2)->previous=half_edges->at(j+1);

			//une demi-arête partant de ce sommet
				vertexes->at(f->at(i).v3-1)->edge=half_edges->at(j+2);

			//sommet à partir duquel commence le half-edge
				half_edges->at(j+2)->vertex=vertexes->at(f->at(i).v3-1);

		

		/*****quatrième point de la face*****/ //he4
		
			//face à laquelle appartient ce half-edge
				half_edges->at(j+3)->face=face;
		
			//prochain half-edge dans la face
				half_edges->at(j+3)->next=half_edges->at(j+0);

			//précédent half-edge dans la face
				half_edges->at(j+3)->previous=half_edges->at(j+2);
							
			//une demi-arête partant de ce sommet
				vertexes->at(f->at(i).v4-1)->edge=half_edges->at(j+3);

			//sommet à partir duquel commence le half-edge
				half_edges->at(j+3)->vertex=vertexes->at(f->at(i).v4-1);

		

	}

	//on détermine les pairs
	map<pair<HE_Vertex*,HE_Vertex*>,HE_HalfEdge*>::const_iterator iter;

	for(iter = paires->begin(); iter != paires->end(); iter++)
	{
		
			map<pair<HE_Vertex*,HE_Vertex*>,HE_HalfEdge*>::const_iterator iter1;
			map<pair<HE_Vertex*,HE_Vertex*>,HE_HalfEdge*>::const_iterator iter2;

			pair<HE_Vertex*,HE_Vertex*> paire1(iter->first.first,iter->first.second);
			pair<HE_Vertex*,HE_Vertex*> paire2(iter->first.second,iter->first.first);

			iter1 = paires->find(paire1);
			iter2 = paires->find(paire2);

			iter1->second->pair = iter2->second;
	}
}

void Mesh::afficher(float r, float v, float b,int typeAffichage)
{
	glColor3f(r, v, b);
	
	HE_HalfEdge *edgeTemp;
	HE_Vertex *pointTemp;
	
		for(int i=0;i<faces->size();i++)
		{	
		
			edgeTemp=faces->at(i)->edge;
			glBegin(typeAffichage);
				do
				{
						
					pointTemp=edgeTemp->vertex;
					edgeTemp=edgeTemp->next;
					glVertex3f(pointTemp->x, pointTemp->y, pointTemp->z);


				} while(edgeTemp!=faces->at(i)->edge);
			glEnd();

				
		}

}
