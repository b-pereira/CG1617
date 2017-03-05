#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#define FILL 1
#define LINE 2
#define POINT 3

float angle = 0, x = 0, z = 5, lx = 0, lz = -1;
float alpha = 0, beta = 0, raio = 10;
int flag = 0;

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

//Referencial
void referencial(float x, float y, float z)
{
	glBegin(GL_LINES);

	//eixo dos xx (vermelho) linha que vai de -x a x
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x, 0.0f, 0.0f);
	glVertex3f(-x, 0.0f, 0.0f);

	//eixo dos yy (verde) linha que vai de -y  a y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, y, 0.0f);
	glVertex3f(0.0f, -y, 0.0f);

	//eixo dos zz (azul) linha que vai de -z a z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, z);
	glVertex3f(0.0f, 0.0f, -z);

	glEnd();
}



void drawCylinder(float raio, float altura, int slices, int stacks)
{
	float slice = (360 / slices)*(M_PI / 180);
	float doisPi = 2 * M_PI;
	float stack = altura/stacks;
	double r = raio / stacks;
	for (float i = 0; i < doisPi; i += slice)
	{
		for (i = 0; i < doisPi; i += slice) { //base
			glBegin(GL_TRIANGLES);

			glVertex3f(0, 0, 0);
			glVertex3f(sin(i + slice)*raio, 0, cos(i + slice)*raio);
			glVertex3f(sin(i)*raio, 0, cos(i)*raio);

			glEnd();
		}

		double r1 = 0;
		double j;			//corpo
		for (j = 0; j < altura; j += stack) {
			for (i = 0; i < doisPi; i += slice) {
				glBegin(GL_TRIANGLES);

				glVertex3f(sin(i)*raio, j , cos(i)*raio);
				glVertex3f(sin(i+slice)*raio, j, cos(i + slice)*raio);
				glVertex3f(sin(i+slice)*raio, j+stack, cos(i + slice)*raio);

				glVertex3f(sin(i)*raio, j, cos(i)*raio);
				glVertex3f(sin(i + slice)*raio, j+stack, cos(i + slice)*raio);
				glVertex3f(sin(i)*raio, j + stack, cos(i)*raio);

				glEnd();
			}
			r1 += r;
		}
					//topo
		for (i = 0; i < doisPi; i += slice) {
			glBegin(GL_TRIANGLES);

			glVertex3f(0.0, altura, 0.0);
			glVertex3f(sin(i)*raio, altura, cos(i)*raio);
			glVertex3f(sin(i + slice)*raio, altura, cos(i + slice)*raio);

			glEnd();
		}

	}


}

void drawEsfera(double r, int slices, int stacks)
{
	double slice = (360 / slices)*(M_PI / 180);
	double stack = (180 / stacks)*(M_PI / 180);
	double metadePI = M_PI / 2;
	double doisPI = 2 * M_PI;


	for (double j = -metadePI; j < metadePI; j += stack)
	{
		for (double i = 0; i <= doisPI; i += slice)
		{
			glBegin(GL_TRIANGLES);


			glVertex3f(cos(j + stack)*sin(i)*r, sin(j + stack)*r, cos(j + stack)*cos(i)*r);
			glVertex3f(cos(j)*sin(i)*r, sin(j)*r, cos(j)*cos(i)*r);
			glVertex3f(cos(j)*sin(i + slice)*r, sin(j)*r, cos(j)*cos(i + slice)*r);

			glVertex3f(cos(j + stack)*sin(i)*r, sin(j + stack)*r, cos(j + stack)*cos(i)*r);
			glVertex3f(cos(j)*sin(i + slice)*r, sin(j)*r, cos(j)*cos(i + slice)*r);
			glVertex3f(cos(j + stack)*sin(i + slice)*r, sin(j + stack)*r, cos(j + stack)*cos(i + slice)*r);
			
			glEnd();
		}

	}
}

	

void drawCone(float raio, float altura, int slices, int stacks) {
	double slice = (360 / slices)*(M_PI / 180);
	double stack = altura / stacks;
	double r = raio / stacks;
	double doisPi = 2 * M_PI;
	double i = 0;

	for (i = 0; i < doisPi; i += slice) { //base
		glBegin(GL_TRIANGLES);
		glVertex3f(0, 0, 0);
		glVertex3f(sin(i + slice)*raio, 0, cos(i + slice)*raio);
		glVertex3f(sin(i)*raio, 0, cos(i)*raio);
		glEnd();
	}

	double r1 = 0;
	double j;
	for (j = 0; j < altura; j += stack) {
		for (i = 0; i < doisPi; i += slice) {
			glBegin(GL_TRIANGLES);
			glVertex3f(sin(i)*(raio - (r1 + r)), j + stack, cos(i)*(raio - (r1 + r)));
			glVertex3f(sin(i)*(raio - r1), j, cos(i)*(raio - r1));
			glVertex3f(sin(i + slice)*(raio - r1), j, cos(i + slice)*(raio - r1));

			glVertex3f(sin(i)*(raio - (r1 + r)), j + stack, cos(i)*(raio - (r1 + r)));
			glVertex3f(sin(i + slice)*(raio - r1), j, cos(i + slice)*(raio - r1));
			glVertex3f(sin(i + slice)*(raio - (r1 + r)), j + stack, cos(i + slice)*(raio - (r1 + r)));

			glEnd();
		}
		r1 += r;
	}
}



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(
		cos(beta)*sin(alpha)*raio, sin(beta)*raio, cos(beta)*cos(alpha)*raio, //  coordenadas esfericas inicialmente (0,0,1)
		0, 0, 0,
		0, 1, 0);

	//drawCone(2, 2, 10, 10);
	//drawCylinder(1, 3, 10,10);
	drawEsfera(2, 10, 10);
	referencial(2, 2, 3);
	glutPostRedisplay();
	// End of frame
	glutSwapBuffers();
}

void processFillMenu(int option)
{
	switch (option)
	{
	case FILL: glPolygonMode(GL_FRONT, GL_FILL); break;
	case LINE: glPolygonMode(GL_FRONT, GL_LINE); break;
	case POINT: glPolygonMode(GL_FRONT, GL_POINT); break;
	}
}

void createGLUTMenus()
{
	int menu;
	menu = glutCreateMenu(processFillMenu);

	glutAddMenuEntry("Fill", FILL);
	glutAddMenuEntry("Line", LINE);
	glutAddMenuEntry("Point", POINT);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void processNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 27: exit(0); break;

	}
}

void processSpecialKeys(int key, int x1, int y1)
{
	switch (key)
	{
	case 27: exit(0); break;
	case GLUT_KEY_LEFT:  alpha -= 0.1; break;
	case GLUT_KEY_RIGHT:  alpha += 0.1; break;
	case GLUT_KEY_UP:  if (beta < M_PI / 2) beta += 0.1; break; // condição para não se ficar de pernas para o ar
	case GLUT_KEY_DOWN:  if (beta > -M_PI / 2) beta -= 0.1; break;
	}
}



int main(int argc, char **argv) {

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// Callback registration for keyboard processing
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	createGLUTMenus();
	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}