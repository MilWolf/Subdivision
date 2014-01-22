#include "HE_Face.h"


HE_Face::HE_Face(void)
{
	facePoint=new HE_Vertex();
}


HE_Face::~HE_Face(void)
{
	delete edge;
	delete facePoint;
}
