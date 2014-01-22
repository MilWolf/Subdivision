#ifndef HE_VERTEX_H
#define HE_VERTEX_H

class HE_HalfEdge;

class HE_Vertex
{
	public:
		HE_Vertex(void);
		~HE_Vertex(void);

		//attributs
		HE_HalfEdge *edge;
		float x,y,z;

		int index;
};

#endif
