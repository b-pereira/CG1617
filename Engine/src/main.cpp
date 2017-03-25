#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <map>
#include "Triangle.h"
#include "Point3d.h"

#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

GLfloat mover_x = 0, mover_z = 0, theta = 0, phi = 0;

vector<vector<Triangle>> figures;

int idx = 0;

float alpha = 0, beta = 0, raio = 10;


void
changeSize (int w, int h)
{

  // Prevent a divide by zero, when window is too short
  // (you cant make a window with zero width).
  if (h == 0)
    h = 1;

  // compute window's aspect ratio
  float ratio = w * 1.0 / h;

  // Set the projection matrix as current
  glMatrixMode (GL_PROJECTION);
  // Load Identity Matrix
  glLoadIdentity ();

  // Set the viewport to be the entire window
  glViewport (0, 0, w, h);

  // Set perspective
  gluPerspective (45.0f, ratio, 1.0f, 1000.0f);

  // return to the model view matrix mode
  glMatrixMode (GL_MODELVIEW);
}

void
renderScene (void)
{

  // clear buffers
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // set the camera
  glLoadIdentity ();


  gluLookAt (cos (beta) * sin (alpha) * raio, sin (beta) * raio,
	     cos (beta) * cos (alpha) * raio, //  coordenadas esfericas inicialmente (0,0,1)
	     0, 0, 0, 0, 1, 0);


// put the geometric transformations here
  glTranslatef (mover_x, 0.0, mover_z);

  glRotatef (theta, 0.0f, 1.0f, 0.0f);

  glRotatef (phi, 1.0f, 0.0f, 0.0f);

  // put drawing instructions here
  glBegin (GL_TRIANGLES);
  //lados

  for (Triangle t : figures.at (idx))
    {

      Point3d a = t.getA ();
      Point3d b = t.getB ();
      Point3d c = t.getC ();

      glVertex3f (a.getXCoord (), a.getYCoord (), a.getZCoord ());

      glVertex3f (b.getXCoord (), b.getYCoord (), b.getZCoord ());

      //ponto A
      glVertex3f (c.getXCoord (), c.getYCoord (), c.getZCoord ());

      glColor3f (1, 1, 0);

    }

  glEnd ();

  // End of frame
  glutSwapBuffers ();
}

// write function to process keyboard events
void
keyboardR (unsigned char key, int x, int y)
{
  switch (key)
    {
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
      alpha = 0, beta = 0;
      break;
    case 'n':

      idx = (idx + 1) % figures.size ();

      break;
    case 'h':
      alpha -= 0.1;
      break;
    case 'l':
      alpha += 0.1;
      break;
    case 'k':
      if (beta < M_PI / 2)
	beta += 0.1;
      break;
    case 'j':
      if (beta > -M_PI / 2)
	beta -= 0.1;
      break;

    default:
      break;
    }
  glutPostRedisplay ();
}

void
keyboardS (int key_code, int x, int y)
{
  switch (key_code)
    {
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
  glutPostRedisplay ();
}

void
menu (int op)
{
  switch (op)
    {
    case 1:
      glPolygonMode (GL_FRONT_AND_BACK, GL_POINT);
      break;
    case 2:
      glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
      break;
    case 3:
      glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
      break;
    default:
      break;
    }
  glutPostRedisplay ();
}

const vector<string>
explode (const string& s, const char& c)
{
  string buff
    { "" };
  vector<string> v;

  for (auto n : s)
    {
      if (n != c)
	buff += n;
      else if (n == c && buff != "")
	{
	  v.push_back (buff);
	  buff = "";
	}
    }
  if (buff != "")
    v.push_back (buff);

  return v;
}

int
main (int argc, char **argv)
{

	/** Com MAKEFILE tem que ser ../resources*/
  XMLDocument doc;
  doc.LoadFile ("resources/scene.xml");

  vector<string> modelos;
  XMLElement* modelNode = doc.FirstChildElement ("scene")->FirstChildElement (
      "model");

  for (auto crawl = modelNode; crawl != nullptr;
      crawl = crawl->NextSiblingElement ("model"))
    {
      modelos.push_back (crawl->FirstAttribute ()->Value ());
      cout << "Modelo:" << crawl->FirstAttribute ()->Value () << endl;
    }

  for (int i = 0; i < modelos.size (); i++)
    {
      string line;

      vector<Triangle> lst;
      /** Com MAKEFILE tem que ser ../resources*/
      ifstream myfile ("resources/" + modelos[i]);
      if (myfile.is_open ())
	{
	  while (getline (myfile, line))
	    {
	      vector<string> v
		{ explode (line, ';') };
	      vector<string> p1
		{ explode (v[0], ',') };
	      vector<string> p2
		{ explode (v[1], ',') };
	      vector<string> p3
		{ explode (v[2], ',') };

	      Triangle t (atof (p1[0].c_str ()), atof (p1[1].c_str ()),
			  atof (p1[2].c_str ()), atof (p2[0].c_str ()),
			  atof (p2[1].c_str ()), atof (p2[2].c_str ()),
			  atof (p3[0].c_str ()), atof (p3[1].c_str ()),
			  atof (p3[2].c_str ()));

	      lst.push_back (t);

	    }
	  myfile.close ();

	  figures.push_back (lst);

	}

      else
	cout << "Unable to open file";

    }

// init GLUT and the window
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition (100, 100);
  glutInitWindowSize (800, 800);
  glutCreateWindow ("CG@DI-UM");

// Required callback registry 
  glutDisplayFunc (renderScene);
  glutReshapeFunc (changeSize);

// put here the registration of the keyboard callbacks
  glutKeyboardFunc (keyboardR);
  glutSpecialFunc (keyboardS);

// menu
  glutCreateMenu (menu);
  glutAddMenuEntry ("GL POINT", 1);
  glutAddMenuEntry ("GL LINE", 2);
  glutAddMenuEntry ("GL FILL", 3);

  glutAttachMenu (GLUT_RIGHT_BUTTON);

//  OpenGL settings
  glEnable (GL_DEPTH_TEST);
  glEnable (GL_CULL_FACE);

// enter GLUT's main cycle
  glutMainLoop ();

  return 1;
}
