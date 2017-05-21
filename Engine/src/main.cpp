#include <IL/il.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>
#include <sstream>
#include <cmath>

#include "Group.h"

using namespace std;

float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;

float camX = 00, camY = 30, camZ = 40;
int startX, startY, tracking = 0;

float xx = 0, zz = 0;

float alpha = 0, beta = 0, r = 50;

int frame, fps;
float timebase, timec;


Models *models;

void printInfo()
{   frame++;
    timec = glutGet ( GLUT_ELAPSED_TIME );

    if ( timec - timebase > 1000 )
    {   fps = frame * 1000.0 / ( timec - timebase );
        timebase = timec;
        frame = 0;
    }

    std::stringstream sstm;
    sstm << "FPS: " << fps << "\t" << "TIME: " << timec / 1000 << "s\t"
         << "TIMEBASE: " << timebase / 1000 << "s\t";
    glutSetWindowTitle ( sstm.str().c_str() );
}

void changeSize ( int w, int h )
{   // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if ( h == 0 )
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;
    // Set the projection matrix as current
    glMatrixMode ( GL_PROJECTION );
    // Load Identity Matrix
    glLoadIdentity();
    // Set the viewport to be the entire window
    glViewport ( 0, 0, w, h );
    // Set perspective
    gluPerspective ( 45.0f, ratio, 1.0f, 1000.0f );
    // return to the model view matrix mode
    glMatrixMode ( GL_MODELVIEW );
}

void renderScene ( void )
{   // clear buffers
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // set the camera
    glLoadIdentity();
    printInfo();
    gluLookAt ( camX + x, camY, camZ + z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f );

    for ( auto light : models->lights )
    {   light->applyProperties();
    }

    traverseTree ( models, models->g );
    // End of frame
    glutSwapBuffers();
}

// write function to process keyboard events
void processNormalKeys ( unsigned char key, int xx, int yy )
{   switch ( key )
    {   case 27:
            exit ( 0 );
            break;
    }
}

void processSpecialKeys ( int key, int x1, int y1 )
{
}

void processMouseButtons ( int button, int state, int xx, int yy )
{   if ( state == GLUT_DOWN )
    {   startX = xx;
        startY = yy;

        if ( button == GLUT_LEFT_BUTTON )
            tracking = 1;

        else if ( button == GLUT_RIGHT_BUTTON )
            tracking = 2;

        else
            tracking = 0;
    }

    else if ( state == GLUT_UP )
    {   if ( tracking == 1 )
        {   alpha += ( xx - startX );
            beta += ( yy - startY );
        }

        else if ( tracking == 2 )
        {   r -= yy - startY;

            if ( r < 3 )
                r = 3.0;
        }

        tracking = 0;
    }
}

void processMouseMotion ( int xx, int yy )
{   int deltaX, deltaY;
    int alphaAux, betaAux;
    int rAux;

    if ( !tracking )
        return;

    deltaX = xx - startX;
    deltaY = yy - startY;

    if ( tracking == 1 )
    {   alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;

        if ( betaAux > 85.0 )
            betaAux = 85.0;

        else if ( betaAux < -85.0 )
            betaAux = -85.0;

        rAux = r;
    }

    else if ( tracking == 2 )
    {   alphaAux = alpha;
        betaAux = beta;
        rAux = r - deltaY;

        if ( rAux < 3 )
            rAux = 3;
    }

    camX = rAux * sin ( alphaAux * 3.14 / 180.0 ) * cos ( betaAux * 3.14 / 180.0 );
    camZ = rAux * cos ( alphaAux * 3.14 / 180.0 ) * cos ( betaAux * 3.14 / 180.0 );
    camY = rAux * sin ( betaAux * 3.14 / 180.0 );
}

void menu ( int op )
{   switch ( op )
    {   case 1:
            glPolygonMode ( GL_FRONT_AND_BACK, GL_POINT );
            break;

        case 2:
            glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
            break;

        case 3:
            glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
            break;

        default:
            break;
    }

    glutPostRedisplay();
}
void initGL()
{   // alguns settings para OpenGL
    glEnable ( GL_DEPTH_TEST );
    glEnable ( GL_CULL_FACE );
    glEnable ( GL_RESCALE_NORMAL );
    glEnableClientState ( GL_VERTEX_ARRAY );
    glEnableClientState ( GL_NORMAL_ARRAY );
    glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
    glClearColor ( 0, 0, 0, 0 );
    glEnable ( GL_LIGHTING );
    glEnable ( GL_TEXTURE_2D );
}

int main ( int argc, char **argv )
{   /** Com MAKEFILE tem que ser ../resources*/
    // init GLUT and the window
    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );
    glutInitWindowPosition ( 100, 100 );
    glutInitWindowSize ( 800, 800 );
    glutCreateWindow ( "CG@DI-UM" );
    GLenum err = glewInit();

    if ( GLEW_OK != err )
    {   fprintf ( stderr, "Error: %s\n", glewGetErrorString ( err ) );
    }

    fprintf ( stdout, "Status: Using GLEW %s\n", glewGetString ( GLEW_VERSION ) );
    initGL();

    if ( argv[1] == NULL )
    {   models = readXMLDoc ( "resources/sistema.xml" );
    }

    else
    {   models = readXMLDoc ( argv[1] );
    }

    // Required callback registry
    glutDisplayFunc ( renderScene );
    glutIdleFunc ( renderScene );
    glutReshapeFunc ( changeSize );
    // put here the registration of the keyboard and mouse callbacks
    glutKeyboardFunc ( processNormalKeys );
    glutSpecialFunc ( processSpecialKeys );
    glutMouseFunc ( processMouseButtons );
    glutMotionFunc ( processMouseMotion );
    // menu
    glutCreateMenu ( menu );
    glutAddMenuEntry ( "GL POINT", 1 );
    glutAddMenuEntry ( "GL LINE", 2 );
    glutAddMenuEntry ( "GL FILL", 3 );
    glutAttachMenu ( GLUT_MIDDLE_BUTTON );
    //  OpenGL settings
    glEnable ( GL_DEPTH_TEST );
    glEnable ( GL_CULL_FACE );
    printf ( "Vendor: %s\n", glGetString ( GL_VENDOR ) );
    printf ( "Renderer: %s\n", glGetString ( GL_RENDERER ) );
    printf ( "Version: %s\n", glGetString ( GL_VERSION ) );
    // enter GLUT's main cycle
    glutMainLoop();
    return 1;
}

