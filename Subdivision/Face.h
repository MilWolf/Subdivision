#ifndef FACE_H
#define FACE_H

class Face
{
	public:
		Face(void);
		~Face(void);

		bool possedeVertex(int vertex);

		
		int edge1,edge2,edge3,edge4;
		int facePoint;
};

#endif
