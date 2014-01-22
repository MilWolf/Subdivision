//GGesquière, Iut de provence, département Informatique, 2009
//gilles.gesquiere[AT]univ-provence.fr

//Squelette du cylindre. A vous de créer la suite.
//compilation barbare sous linux : g++ -Wall squelette_cylindre.cpp struct.cpp -o cylindre -lglut

#ifdef __WIN32__
//parce qu'il manque des choses aux gens qui utilisent MsWindows, où OpenGL ne peut fonctionner que s'il discute avec le gestionnaire de fenêtres ("windows.h")
	#define GLUT_DISABLE_ATEXIT_HACK	//utile si vous compilez en g++ sous windows avec le glut.lib prévu pour MsVisual
	#include <windows.h>
	#include "glut.h"	//il faut avoir le fichier "glut.h" dans le même répertoire que votre .cpp (et aussi le glut.lib et le glut.dll)
#endif

#ifdef __linux__
	#include <GL/glut.h>
#endif

#include <iostream>
#include <cstdlib>

#include <cstdio>
#include <cmath>
#include <gl\glut.h>

#include "ObjHelper.h"
#include "Mesh.h"

using namespace std;



#define WIDTH  600
#define HEIGHT 600

#define KEY_ESC 27

float angleX = 0.0f; //angle de rotation en Y de la scene
float angleY = 0.0f; //angle de rotation en X de la scene

ObjHelper objHelper;
Mesh *mesh;

bool wire = true;

float pasDeplacement = 1.25f;


//position lumiere
float xLitePos = 5.0f;
float yLitePos = 5.0f;
float zLitePos = -100.0f;

float tx = 0.0f;
float ty = 0.0f;
float tz = 0.0f;

/* initialisation d'OpenGL*/
static void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHTING);
	float pos[4]={xLitePos, yLitePos, zLitePos,GL_POINT};
	glLightfv(GL_LIGHT0,GL_POSITION, pos);
	// Si vous avez des choses à initialiser, c'est ici.
}

void rotation_souris(float& ax, float& ay) {
//rotation de la scene suivant les mouvements de la souris
	glRotatef ( -ay, 0.0f, 0.0f, 1.0f );
	glRotatef ( ax, 0.0f, 1.0f, 0.0f );
	glTranslatef ( tx, ty, tz );

	glRotatef ( -ay, 0.0f, 0.0f, 1.0f );
	glRotatef ( ax, 0.0f, 1.0f, 0.0f );
}

void affiche_repere() 
{
	//affiche les axes du repere
	glColor3f ( 0.0f, 1.0f, 0.0f ); //Y vert
	glBegin(GL_LINES);
		glVertex3f ( 0.0f, 0.0f, 0.0f );
		glVertex3f ( 0.0f, 20.0f, 0.0f );
	glEnd();

	glColor3f ( 0.0f, 0.0f, 1.0f ); //Z bleu
	glBegin(GL_LINES);
		glVertex3f ( 0.0f, 0.0f, 0.0f );
		glVertex3f ( 0.0f, 0.0f, 20.0f );
	glEnd();

	glColor3f ( 1.0f, 0.0f, 0.0f); //X rouge
	glBegin(GL_LINES);
		glVertex3f ( 0.0f, 0.0f, 0.0f );
		glVertex3f ( 20.0f, 0.0f, 0.0f );
	glEnd();
}

/* Dessin */
void display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //effacement du buffer

	//Description de la scene
	glLoadIdentity();
		rotation_souris(angleX, angleY);
		affiche_repere();

		mesh->afficher(0.0f, 0.3f, 0.8f, GL_QUADS);

		if(wire==true)
		{
			mesh->afficher(1.0f, 0.0f, 0.0f, GL_LINE_LOOP);
		}
		
	glutSwapBuffers();// echange des buffers
}

/* Au cas ou la fenetre est modifiee ou deplacee */
void reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho ( -2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
   glMatrixMode(GL_MODELVIEW);
}

GLvoid gestionSouris(int x, int y) {
	angleX = float(x) * 720.0f / float(WIDTH); //gere l'axe Oy
	angleY = - ( float(y) * 180.0f / float(HEIGHT - 90.0f) ) * 4.0f; //gere l'axe Ox

	glutPostRedisplay();
}

GLvoid gestionFleche(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP :
			tz += int(pasDeplacement);
		break;

		case GLUT_KEY_DOWN :
			tz -= int(pasDeplacement);
		break;
	}
	glutPostRedisplay();
}

GLvoid window_key_down(unsigned char key, int x, int y) 
{ //appuie des touches
	switch (key)
	{
	//deplacement de la camera
		case 'z':
			ty += int(pasDeplacement);
		break;

		case 's':
			ty -= int(pasDeplacement);
		break;

		case 'q':
			tx -= int(pasDeplacement);
		break;

		case 'd':
			tx += int(pasDeplacement);
		break;
		case 'w':
			if(wire==true)wire=false;
			else if(wire==false)wire=true;
			break;
		case '+':
			mesh->subdiviser();
			break;
	//sortie
		case KEY_ESC:
			exit(0);
			break;

		default:
			cerr << "Touche " << key << " non active.\n";
		break;
		}

	glutPostRedisplay();
}

int main(int argc, char **argv) 
{
	
	objHelper.lireObj("horse.obj");
	mesh = new Mesh(objHelper.faces, objHelper.vertexes);
	
	glutInitWindowSize(800, 800);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
	glutCreateWindow("Subdivision de Catmull-Clark");
	
	
	init();

	glutReshapeFunc(reshape);
	glutKeyboardFunc(&window_key_down);
	glutDisplayFunc(display);
	glutPassiveMotionFunc(gestionSouris);
	glutSpecialFunc(&gestionFleche);

	glutMainLoop();

	delete mesh;

	return (EXIT_SUCCESS);
}



