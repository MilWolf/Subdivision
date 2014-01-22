#ifndef HE_FACE_H
#define HE_FACE_H

class HE_HalfEdge;

#include "HE_Vertex.h"
class HE_Vertex;

class HE_Face
{
	public:
		HE_Face(void);
		~HE_Face(void);

		//attributs
		HE_HalfEdge *edge;
		HE_Vertex *facePoint;
};

#endif
