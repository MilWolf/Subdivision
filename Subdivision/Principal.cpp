#include "ObjHelper.h"
#include "Mesh.h"

#include <iostream>
using namespace std;

int main()
{
	ObjHelper objHelper;
	objHelper.lireObj("cube.obj");

	Mesh mesh(objHelper.getFaces(),objHelper.getPoints());
	mesh.subdiviser(1);
	objHelper.ecrireObj(mesh.getPoints(),mesh.getFaces());

	return 0;
}