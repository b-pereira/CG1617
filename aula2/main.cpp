#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

float alturaP=2.0f, ladoP = 2.0f, mover_x = 0.0f, mover_z = 0.0f, rodar = 0.0f, eixo_x =0.0f, eixo_y=0.0f;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
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
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(0.0,10.0,25.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

// put the geometric transformations here
	glTranslatef(mover_x, 0.0, mover_z);
	glRotatef(rodar, eixo_x, eixo_y, 0.0);

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

	//lados
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, alturaP, 0.0f);			
		glVertex3f(-ladoP, 0.0f, ladoP);
		glVertex3f(ladoP, 0.0f, ladoP);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, alturaP, 0.0f);
		glVertex3f(ladoP, 0.0f, -ladoP);
		glVertex3f(-ladoP, 0.0f, -ladoP);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, alturaP, 0.0f);
		glVertex3f(-ladoP, 0.0f, -ladoP);
		glVertex3f(-ladoP, 0.0f, +ladoP);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, alturaP, 0.0f);
		glVertex3f(ladoP, 0.0f, ladoP);
		glVertex3f(ladoP, 0.0f, -ladoP);
	glEnd();

	//base
	glColor3f(0.0f, 0.0f, 0.1f);
	glBegin(GL_TRIANGLES);
		glVertex3f(ladoP, 0.0f, -ladoP);
		glVertex3f(ladoP, 0.0f, ladoP);
		glVertex3f(-ladoP, 0.0f, ladoP);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.1f);
	glBegin(GL_TRIANGLES);
		glVertex3f(ladoP, 0.0f, -ladoP);
		glVertex3f(-ladoP, 0.0f, ladoP);
		glVertex3f(-ladoP, 0.0f, +ladoP);
	glEnd();

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
void keyboardR(unsigned char key, int x, int y) {
	switch (key){
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

		default:
			break;
	}
	glutPostRedisplay();
}

void keyboardS(int key_code, int x, int y) {
	switch (key_code)	{
		case GLUT_KEY_LEFT:
			rodar = rodar - 5.0;
			eixo_x = 0;
			eixo_y = 1;
			break;
		case GLUT_KEY_RIGHT:
			rodar = rodar + 5.0;
			eixo_x = 0;
			eixo_y = 1;
			break;
		case GLUT_KEY_UP:
			rodar = rodar + 5.0;
			eixo_x = 1;
			eixo_y = 0;
		case GLUT_KEY_DOWN:
			rodar = rodar - 5.0;
			eixo_x = 1;
			eixo_y = 0;
	
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

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
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
