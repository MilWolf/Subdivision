#include "HE_Vertex.h"


HE_Vertex::HE_Vertex(void)
{
	x=0.0f;
	y=0.0f;
	z=0.0f;
}


HE_Vertex::~HE_Vertex(void)
{
	delete edge;
}
