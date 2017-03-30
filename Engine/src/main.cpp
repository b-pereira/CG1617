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
#include "Group.h"

#include "Rotation.h"

#include "Translation.h"

#include "Scale.h"

#include "Group.h"

#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

#define TRANSLATE "translate"
#define SCALE     "scale"
#define ROTATE    "rotate"
#define MODELS    "models"
#define MODEL     "model"
#define GROUP     "group"
#define SCENE     "scene"
#define FILE      "file"
#define ANGLE     "angle"
#define AXIS_X    "axisX"
#define AXIS_Y    "axisY"
#define AXIS_Z    "axisZ"
#define X         "X"
#define Y         "Y"
#define Z         "Z"

float step = 0.0;

float height = 2.0f;
float x = 0.0f;
float z = 0.0f;

float camX = 00, camY = 30, camZ = 40;
int startX, startY, tracking = 0;

int alpha = 0, beta = 45, r = 50;

Grupo * g;

void changeSize(int w, int h)
{

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

void drawElement(Grupo * g)
{

    // put drawing instructions here
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < g->modelos.size(); i++)
    {

        for (Triangle t : g->modelos.at(i))
        {

            Point3d a = t.getA();
            Point3d b = t.getB();
            Point3d c = t.getC();

            glVertex3f(a.getXCoord(), a.getYCoord(), a.getZCoord());

            glVertex3f(b.getXCoord(), b.getYCoord(), b.getZCoord());

            glVertex3f(c.getXCoord(), c.getYCoord(), c.getZCoord());

            glColor3f(1, 1, 0);

        }
    }

    glEnd();

}

void traverseTree(Grupo *t)
{

    auto tmp = t;

    if (tmp == nullptr)
        return;

    glPushMatrix();
    cout << "PUSH" << endl;



    for (auto var : tmp->transformations)
    {


        var->applyTransformation();

    }

    drawElement(tmp);

    for (int nivel = 0; nivel < tmp->filhos.size(); nivel++)
    {
        if (tmp->filhos[nivel] != nullptr)
        {
            traverseTree(tmp->filhos[nivel]);
            glPopMatrix();
            cout << "POP" << endl;

        }
    }

    return;
}

void renderScene(void)
{

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();

    gluLookAt(camX, camY, camZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    traverseTree(g);

    // End of frame
    glutSwapBuffers();
}
void processKeys(unsigned char key, int xx, int yy)
{}

void processMouseButtons(int button, int state, int xx, int yy)
{

    if (state == GLUT_DOWN)
    {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else
            tracking = 0;
    }
    else if (state == GLUT_UP)
    {
        if (tracking == 1)
        {
            alpha += (xx - startX);
            beta += (yy - startY);
        }
        else if (tracking == 2)
        {

            r -= yy - startY;
            if (r < 3)
                r = 3.0;
        }
        tracking = 0;
    }
}

void processMouseMotion(int xx, int yy)
{

    int deltaX, deltaY;
    int alphaAux, betaAux;
    int rAux;

    if (!tracking)
        return;

    deltaX = xx - startX;
    deltaY = yy - startY;

    if (tracking == 1)
    {

        alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;

        if (betaAux > 85.0)
            betaAux = 85.0;
        else if (betaAux < -85.0)
            betaAux = -85.0;

        rAux = r;
    }
    else if (tracking == 2)
    {

        alphaAux = alpha;
        betaAux = beta;
        rAux = r - deltaY;
        if (rAux < 3)
            rAux = 3;
    }
    camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camY = rAux * sin(betaAux * 3.14 / 180.0);
}

void menu(int op)
{
    switch (op)
    {
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

const vector<string> explode(const string& s, const char& c)
{
    string buff { "" };
    vector<string> v;

    for (auto n : s)
    {
        if (n != c)
            buff += n;
        else if (n == c && buff != "")
        {
            v.push_back(buff);
            buff = "";
        }
    }
    if (buff != "")
        v.push_back(buff);

    return v;
}

void lerFicheiro(Grupo *g, string file)
{

    string line;

    vector<Triangle> lst;
    ifstream myfile("resources/" + file);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            vector<string> v { explode(line, ';') };
            vector<string> p1 { explode(v[0], ',') };
            vector<string> p2 { explode(v[1], ',') };
            vector<string> p3 { explode(v[2], ',') };

            Triangle t(atof(p1[0].c_str()), atof(p1[1].c_str()),
                       atof(p1[2].c_str()), atof(p2[0].c_str()),
                       atof(p2[1].c_str()), atof(p2[2].c_str()),
                       atof(p3[0].c_str()), atof(p3[1].c_str()),
                       atof(p3[2].c_str()));

            lst.push_back(t);

        }
        myfile.close();

        g->modelos.push_back(lst);

    }

    else
        cout << "Unable to open file";

}

void readXMLFromRootElement(XMLElement * root, Grupo * grupo)
{

    if (root == nullptr)
        return;

    auto tmp = root;
    auto tmp_gr = grupo;

    /**
     * Para cada irmão do elemento inicial: procurar atributos
     */
    for (auto element = tmp->FirstChildElement();
    		element;
            element = element->NextSiblingElement())
    {

        string name(element->Name());

        Transformation * tr = 0;

        if ((name.compare(TRANSLATE) == 0) || (name.compare(SCALE) == 0))
        {
            double x, y, z;


            x = (element->Attribute(X))? atof(element->Attribute(X)): 0;
            y = (element->Attribute(Y))? atof(element->Attribute(Y)): 0;
            z = (element->Attribute(Z))? atof(element->Attribute(Y)): 0;

            if (name.compare(TRANSLATE) == 0)
            {
                /**
                 * Criar Translação
                 */
                Translation * t = new Translation(x, y, z);



                tmp_gr->transformations.push_back(t);

            }
            else
            {
                /**
                 * Criar Escala
                 */
                Scale * s = new Scale(x, y, z);

                tmp_gr->transformations.push_back(s);

            }

        }
        else if (name.compare(ROTATE) == 0)
        {
            double axis_x, axis_y, axis_z, angle;


            angle  = (element->Attribute(ANGLE)) ? atof(element->Attribute(ANGLE)) : 0;

            axis_x = (element->Attribute(AXIS_X))? atof(element->Attribute(AXIS_X)): 0;
            axis_y = (element->Attribute(AXIS_Y))? atof(element->Attribute(AXIS_Y)): 0;
            axis_z = (element->Attribute(AXIS_Z))? atof(element->Attribute(AXIS_Z)): 0;

            /**
             * Criar Rotação
             */
            Rotation * r = new Rotation(angle, axis_x, axis_y, axis_z);

            tmp_gr->transformations.push_back(r);

        }
        else if (name.compare(MODELS) == 0)
        {

            /**
             * Iterar sobre os ficheiros de modelos
             */
            for (auto crawl = element->FirstChildElement(MODEL);
                    crawl != nullptr;
                    crawl = crawl->NextSiblingElement(MODEL))
            {

                string modelo(crawl->Attribute(FILE));

                lerFicheiro(tmp_gr, modelo);

                //grupo->modelos.push_back(modelo);

                //cout << "MODELO : " << crawl->Attribute(FILE) << endl;

            }
        }
        else if (name.compare(GROUP) == 0)
        {

            /**
             * Guardar ler ficheiro (forma);

             */

            Grupo * grupo = new Grupo;
            tmp_gr->filhos.push_back(grupo);
            readXMLFromRootElement(element, grupo);

        }

    }

}

Grupo * readXMLDoc(const char * path)
{

    XMLDocument doc;
    doc.LoadFile(path);

    XMLElement* modelNode = doc.FirstChildElement(SCENE);
    Grupo * parent = new Grupo;

    readXMLFromRootElement(modelNode, parent);

    return parent;

}

int main(int argc, char **argv)
{

    /** Com MAKEFILE tem que ser ../resources*/

    g = readXMLDoc("resources/planetas.xml");

    // inicializa��o
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("CG@DI-UM");

    // registo de fun��es
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

    // p�r aqui registo da fun��es do teclado e rato

    glutKeyboardFunc(processKeys);
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);


    //// menu
    //glutCreateMenu(menu);
    //glutAddMenuEntry("GL POINT", 1);
    //glutAddMenuEntry("GL LINE", 2);
    //glutAddMenuEntry("GL FILL", 3);

    //glutAttachMenu(GLUT_KEY_F2);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
