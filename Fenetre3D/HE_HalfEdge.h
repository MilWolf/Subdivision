#ifndef HE_HALFEDGE_H
#define HE_HALFEDGE_H

#include "HE_Face.h"
class HE_Face;

#include "HE_Vertex.h"
class HE_Vertex;

#include "Vertex.h"

class HE_HalfEdge
{
	public:
		HE_HalfEdge(void);
		~HE_HalfEdge(void);

		//Attributs
		HE_Face *face;
		HE_HalfEdge *next;
		HE_HalfEdge *previous;
		HE_HalfEdge *pair;
		HE_Vertex *vertex;

		HE_Vertex *edgePoint;
		Vertex *milieu;
};

#endif

