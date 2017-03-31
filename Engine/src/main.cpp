
#include <GL/glut.h>



#include <iostream>
#include <cmath>


#include "Group.h"

using namespace std;


double alpha = 0, beta = 0, raio = 1;

float k = 0.5;

Point3d p(0.0f, 0.0f, 50.0f);
Point3d l(0.0f, 0.0f, -10.0f);
Point3d d(0.0f, 0.0f, 0.0f);
Point3d r(0.0f, 0.0f, 0.0f);
Point3d up(0.0f, 1.0f, 0.0f);



Modelos * modelos;

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

	//l = l.addTo(r.multiplyBy(k));

	gluLookAt(    // Ponto da camara
			p.getXCoord(), p.getYCoord(), p.getZCoord(),
			// Ponto onde está olhar
			l.getXCoord(), l.getYCoord(), l.getZCoord(),
			//up
			up.getXCoord(), up.getYCoord(), up.getZCoord());

	traverseTree(modelos, modelos->g);

	// End of frame
	glutSwapBuffers();
}

// write function to process keyboard events
void keyboardR(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':

		d.setCoord(cos(beta) * sin(alpha), sin(beta), cos(beta) * cos(alpha));
		p = p.addTo(d.multiplyBy(k));

		l = l.addTo(d.multiplyBy(k));

		break;
	case 's':

		d.setCoord(cos(beta) * sin(alpha), sin(beta), cos(beta) * cos(alpha));
		p = p.addTo(d.multiplyBy(-k));
		l = l.addTo(d.multiplyBy(-k));

		break;
	case 'a':
		d.setCoord(cos(beta) * sin(alpha), sin(beta), cos(beta) * cos(alpha));
		r = r.crossProduct(d, up);

		p = p.addTo(r.multiplyBy(k));

		l = l.addTo(r.multiplyBy(k));

		break;
	case 'd':
		d.setCoord(cos(beta) * sin(alpha), sin(beta), cos(beta) * cos(alpha));
		r = r.crossProduct(d, up);
		p = p.addTo(r.multiplyBy(-k));
		l = l.addTo(r.multiplyBy(-k));

		break;
	case 'r':
		p.setCoord(0.0f, 0.0f, 50.0f);
		l.setCoord(0.0f, 0.0f, -10.0f);

		alpha = 0, beta = 0;
		k = 0.5;
		break;
	case 't':
		alpha = 0, beta = 0;
		d.setCoord(cos(beta) * sin(alpha), sin(beta), cos(beta) * cos(alpha));


			k = 0.5;
			break;
	case 'q':
		k += 0.05;
		break;
	case 'e':
		k -= 0.05;
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void keyboardS(int key_code, int x, int y) {
	switch (key_code) {
	case GLUT_KEY_LEFT:

		alpha = alpha + 5.0;

		break;
	case GLUT_KEY_RIGHT:
		alpha = alpha - 5.0;

		break;
	case GLUT_KEY_UP:
		if (beta > -M_PI / 2) {
			beta -= 5.0;

		}

		break;
	case GLUT_KEY_DOWN:

		if (beta < M_PI / 2) {
			beta += 5.0;

		}

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

	/** Com MAKEFILE tem que ser ../resources*/

	modelos = readXMLDoc("resources/planetas.xml");

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
