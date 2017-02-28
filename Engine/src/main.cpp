#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>
#include <vector>

#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

float alturaP = 2.0f, ladoP = 2.0f, mover_x = 0.0f, mover_z = 0.0f;
GLfloat theta = 0;
GLfloat phi = 0;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	/**
	 * Definição da camara anterior
	 */
	//gluLookAt(0.0, 10.0, 25.0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

// put the geometric transformations here
	glTranslatef(mover_x, 0.0, mover_z);

	glRotatef(theta, 0.0f, 1.0f, 0.0f);

	glRotatef(phi, 1.0f, 0.0f, 0.0f);

// put drawing instructions here
	//eixos
	/*
	 glColor3f(1,0,0);
	 glBegin(GL_LINES);
	 glVertex3f(100.0, 0.0, 0.0);
	 glVertex3f(-100.0, 0.0, 0.0);
	 glEnd();
	 glColor3f(0, 1, 0);
	 glBegin(GL_LINES);
	 glVertex3f(0.0, 100.0, 0.0);
	 glVertex3f(0.0, -100.0, 0.0);
	 glEnd();
	 glColor3f(0, 0, 1);
	 glBegin(GL_LINES);
	 glVertex3f(0.0, 0.0, 100.0);
	 glVertex3f(0.0, 0.0, -100.0);
	 glEnd();
	 */
	// put drawing instructions here
	glBegin(GL_TRIANGLES);
	//lados
	//ACE
	//ponto E
	glVertex3f(-1.0f, 0.0f, 1.0f);

	//ponto C
	glVertex3f(1.0f, 0.0f, -1.0f);

	//ponto A
	glVertex3f(1.0f, 0.0f, 1.0f);

	glColor3f(1, 1, 1);

	//CDE

	//ponto E
	glVertex3f(-1.0f, 0.0f, 1.0f);

	//ponto D
	glVertex3f(-1.0f, 0.0f, -1.0f);

	//ponto C
	glVertex3f(1.0f, 0.0f, -1.0f);

	glColor3f(1, 1, 0);

	//ACB

	//ponto A
	glVertex3f(1.0f, 0.0f, 1.0f);

	//ponto C
	glVertex3f(1.0f, 0.0f, -1.0f);

	//ponto B
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(1, 0, 1);

	//CDB

	//ponto C
	glVertex3f(1.0f, 0.0f, -1.0f);

	//ponto D
	glVertex3f(-1.0f, 0.0f, -1.0f);

	//ponto B
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(1, 0, 0);

	//DEB

	//ponto D
	glVertex3f(-1.0f, 0.0f, -1.0f);
	//ponto E
	glVertex3f(-1.0f, 0.0f, 1.0f);

	//ponto B
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0, 1, 1);

	//EAB

	//ponto E
	glVertex3f(-1.0f, 0.0f, 1.0f);

	//ponto A
	glVertex3f(1.0f, 0.0f, 1.0f);

	//ponto B
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0, 1, 0);
	glEnd();

	// End of frame
	glutSwapBuffers();
}

// write function to process keyboard events
void keyboardR(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		mover_x = mover_x - 0.1;
		break;
	case 'd':
		mover_x = mover_x + 0.1;
		break;
	case 's':
		mover_z = mover_z + 0.1;
		break;
	case 'w':
		mover_z = mover_z - 0.1;
		break;
	case 'r':
		mover_z = 0;
		mover_x = 0;
		phi = 0;
		theta = 0;
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void keyboardS(int key_code, int x, int y) {
	switch (key_code) {
	case GLUT_KEY_LEFT:
		theta = theta - 5.0;

		break;
	case GLUT_KEY_RIGHT:
		theta = theta + 5.0;

		break;
	case GLUT_KEY_UP:
		phi = phi + 5.0;

		break;
	case GLUT_KEY_DOWN:
		phi = phi - 5.0;

		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void menu(int op) {
	switch (op) {
	case 1:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case 2:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 3:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv) {

	XMLDocument doc;
	doc.LoadFile("resources/scene.xml");

	vector<string> modelos;
	XMLElement* modelNode = doc.FirstChildElement("scene")->FirstChildElement(
			"model");

	for (auto crawl = modelNode; crawl != nullptr;
			crawl = crawl->NextSiblingElement("model")) {
		modelos.push_back(crawl->FirstAttribute()->Value());
		cout << "Modelo:" << crawl->FirstAttribute()->Value() << endl;
	}

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");

// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

// put here the registration of the keyboard callbacks
	glutKeyboardFunc(keyboardR);
	glutSpecialFunc(keyboardS);

// menu
	glutCreateMenu(menu);
	glutAddMenuEntry("GL POINT", 1);
	glutAddMenuEntry("GL LINE", 2);
	glutAddMenuEntry("GL FILL", 3);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
