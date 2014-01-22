#include "HE_HalfEdge.h"


HE_HalfEdge::HE_HalfEdge(void)
{
	face=new HE_Face();
	vertex=new HE_Vertex();
	edgePoint=0;
	milieu=0;
}


HE_HalfEdge::~HE_HalfEdge(void)
{
	delete face;
	delete next;
	delete previous;
	delete pair;
	delete vertex;

	delete edgePoint;
	delete milieu;
}
