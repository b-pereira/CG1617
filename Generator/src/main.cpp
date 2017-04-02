#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "Point3d.h"

std::string
point3D_to_string (Point3d point)
{
    std::stringstream sstm;
    sstm << point.getXCoord () << ", " << point.getYCoord () << ", "
    << point.getZCoord ();
    return sstm.str ();
}

std::string
triangle_to_string (Point3d pointA, Point3d pointB, Point3d pointC)
{
    return point3D_to_string (pointA) + ";" + point3D_to_string (pointB) + ";"
           + point3D_to_string (pointC);
}

using namespace std;

void
drawPlane (double length, double width, char* filename)
{

    Point3d pontoA (-length / 2, 0, width / 2);

    Point3d pontoB (length / 2, 0, width / 2);

    Point3d pontoC (length / 2, 0, -width / 2);

    Point3d pontoD (-width / 2, 0, -width / 2);

    ofstream ficheiro;
    ficheiro.open (filename);
    if (ficheiro.is_open ())
    {
        ficheiro.clear ();
        ficheiro << triangle_to_string (pontoA, pontoD, pontoB) << endl;
        ficheiro << triangle_to_string (pontoB, pontoD, pontoA) << endl;

        ficheiro << triangle_to_string (pontoD, pontoC, pontoB) << endl;
        ficheiro << triangle_to_string (pontoB, pontoC, pontoD) << endl;
        ficheiro.close ();
    }
    else
        cout << "Unable to open file\n";

}

void
drawBox (double length, double height, double width, char* filename)
{
    Point3d pontoA1 (-length / 2, -height / 2, width / 2);

    Point3d pontoB1 (length / 2, -height / 2, width / 2);

    Point3d pontoC1 (length / 2, -height / 2, -width / 2);

    Point3d pontoD1 (-length / 2, -height / 2, -width / 2);

    Point3d pontoA2 (-length / 2, height / 2, width / 2);

    Point3d pontoB2 (length / 2, height / 2, width / 2);

    Point3d pontoC2 (length / 2, height / 2, -width / 2);

    Point3d pontoD2 (-length / 2, height / 2, -width / 2);

    ofstream ficheiro;
    ficheiro.open (filename);
    if (ficheiro.is_open ())
    {
        ficheiro.clear ();
        ficheiro << triangle_to_string (pontoC1, pontoA1, pontoD1) << endl;
        ficheiro << triangle_to_string (pontoA1, pontoC1, pontoB1) << endl;

        ficheiro << triangle_to_string (pontoC2, pontoD2, pontoA2) << endl;
        ficheiro << triangle_to_string (pontoA2, pontoB2, pontoC2) << endl;

        ficheiro << triangle_to_string (pontoA1, pontoB1, pontoA2) << endl;
        ficheiro << triangle_to_string (pontoB1, pontoB2, pontoA2) << endl;

        ficheiro << triangle_to_string (pontoB1, pontoC1, pontoB2) << endl;
        ficheiro << triangle_to_string (pontoC1, pontoC2, pontoB2) << endl;

        ficheiro << triangle_to_string (pontoC1, pontoD1, pontoC2) << endl;
        ficheiro << triangle_to_string (pontoD1, pontoD2, pontoC2) << endl;

        ficheiro << triangle_to_string (pontoD1, pontoA1, pontoD2) << endl;
        ficheiro << triangle_to_string (pontoA1, pontoA2, pontoD2) << endl;

        ficheiro.close ();

    }

    else
        cout << "Unable to open file\n";

}

void
drawSphere (double radius, int slices, int stacks, char* filename)
{

    double delta_theta = (2 * M_PI) / slices;
    double delta_phi = M_PI / stacks;

    int i, j;

    double prev_theta = 0.0;
    double current_theta;

    double prev_phi = M_PI / 2;
    double current_phi = prev_phi - delta_phi;

    ofstream ficheiro;
    ficheiro.open (filename);

    if (ficheiro.is_open ())
    {
        ficheiro.clear ();

        for (i = 0; i <= stacks; i++)
        {
            prev_theta = 0;
            current_theta = delta_theta;
            for (j = 0; j <= slices; j++)
            {   // A B

                Point3d pointA (radius * cos (prev_phi) * sin (prev_theta),
                                radius * sin (prev_phi),
                                radius * cos (prev_phi) * cos (prev_theta));

                Point3d pointB (radius * cos (current_phi) * sin (prev_theta),
                                radius * sin (current_phi),
                                radius * cos (current_phi) * cos (prev_theta));

                // C D

                Point3d pointD (radius * cos (prev_phi) * sin (current_theta),
                                radius * sin (prev_phi),
                                radius * cos (prev_phi) * cos (current_theta));

                Point3d pointC (radius * cos (current_phi) * sin (current_theta),
                                radius * sin (current_phi),
                                radius * cos (current_phi) * cos (current_theta));

                ficheiro << triangle_to_string (pointA, pointB, pointD) << endl;
                ficheiro << triangle_to_string (pointB, pointC, pointD) << endl;
                prev_theta = current_theta;
                current_theta += delta_theta;
            }

            prev_phi = current_phi;

            current_phi = current_phi - delta_phi;
        }

        ficheiro.close ();

    }

    else
        cout << "Unable to open file\n";
}

void
drawAnel(double raioIn, double raioOut, int slices, char* filename)
{
    float slice = (360 / slices)*(M_PI / 180);
    float doisPi = 2 * M_PI;
    double delta_theta = (2 * M_PI) / slices;
    double prev_theta = 0.0;
    double current_theta = delta_theta;
    int i = 0;

    ofstream ficheiro;
    ficheiro.open (filename);

    if(ficheiro.is_open ())
    {
        ficheiro.clear ();

        for (float i = 0; i < doisPi; i += slice)
        {
            for (i = 0; i < slices; i += slice)
            {

                Point3d pontoA(raioOut*sin(prev_theta),
                               0.005,
                               raioOut*cos(prev_theta));

                Point3d pontoB(raioIn*sin(prev_theta),
                               0.005,
                               raioIn*cos(prev_theta));

                Point3d pontoC(raioIn*sin(current_theta),
                               0.005,
                               raioIn*cos(current_theta));

                Point3d pontoD(raioOut*sin(current_theta),
                               0.005,
                               raioOut*cos(current_theta));

                Point3d pontoA2(raioOut*sin(prev_theta),
                                -0.005,
                                raioOut*cos(prev_theta));

                Point3d pontoB2(raioIn*sin(prev_theta),
                                -0.005,
                                raioIn*cos(prev_theta));

                Point3d pontoC2(raioIn*sin(current_theta),
                                -0.005,
                                raioIn*cos(current_theta));

                Point3d pontoD2(raioOut*sin(current_theta),
                                -0.005,
                                raioOut*cos(current_theta));

                // Disco de baixo
                ficheiro << triangle_to_string (pontoA2, pontoB2, pontoD2) << endl;
                ficheiro << triangle_to_string (pontoD2, pontoB2, pontoC2) << endl;

                // Disco de cima
                ficheiro << triangle_to_string (pontoD, pontoB, pontoA) << endl;
                ficheiro << triangle_to_string (pontoC, pontoB, pontoD) << endl;

                // Lado externo
                ficheiro << triangle_to_string (pontoA2, pontoA, pontoD2) << endl;
                ficheiro << triangle_to_string (pontoD, pontoD2, pontoA) << endl;

                // Lado interno
                ficheiro << triangle_to_string (pontoB, pontoC2, pontoB2) << endl;
                ficheiro << triangle_to_string (pontoC, pontoC2, pontoB) << endl;

                prev_theta = current_theta;
                current_theta += delta_theta;
            }
        }
        ficheiro.close ();
    }
    else
        cout << "Unable to open file\n";
}


void
drawCone (double radius, double height, int slices, int stacks, char * filename)
{

    double prev_theta, current_theta;
    int i, j;

    double delta_theta = (2 * M_PI) / slices;
    double delta_height = height / stacks;

    double prev_radius_aux = (radius * 0) / stacks;
    double prev_height_aux = height / 2;

    double radius_aux = (radius * 1) / stacks;
    double height_aux = prev_height_aux - delta_height;

    ofstream ficheiro;
    ficheiro.open (filename);
    if (ficheiro.is_open ())
    {
        ficheiro.clear ();

        for (i = 0; i < stacks; i++)
        {
            prev_theta = 0;
            current_theta = delta_theta;

            for (j = 0; j <= slices; j++)
            {

                // A B

                Point3d pointA (prev_radius_aux * sin (prev_theta),
                                prev_height_aux,
                                prev_radius_aux * cos (prev_theta));

                Point3d pointB (radius_aux * sin (prev_theta), height_aux,
                                radius_aux * cos (prev_theta));

                // D C

                Point3d pointD (prev_radius_aux * sin (current_theta),
                                prev_height_aux,
                                prev_radius_aux * cos (current_theta));

                Point3d pointC (radius_aux * sin (current_theta), height_aux,
                                radius_aux * cos (current_theta));

                ficheiro << triangle_to_string (pointA, pointB, pointD) << endl;
                ficheiro << triangle_to_string (pointB, pointC, pointD) << endl;

                prev_theta = current_theta;
                current_theta += delta_theta;
            }

            prev_height_aux = height_aux;
            prev_radius_aux = radius_aux;

            radius_aux = radius * (i + 2) / stacks;
            height_aux -= delta_height;
        }

        Point3d pointO (0, -height / 2, 0);

        prev_theta = 0;
        current_theta = delta_theta;

        for (j = 0; j <= slices; j++)
        {
            Point3d pointA2 (radius * sin (prev_theta), -height / 2,
                             radius * cos (prev_theta));

            Point3d pointB2 (radius * sin (current_theta), -height / 2,
                             radius * cos (current_theta));

            ficheiro << triangle_to_string (pointO, pointB2, pointA2) << endl;

            prev_theta = current_theta;
            current_theta += delta_theta;
        }
        ficheiro.close ();

    }

    else
        cout << "Unable to open file\n";
}

int
main (int argc, char* argv[])
{
    if (argc <= 1)
    {
        cout << "ERROR :: Options: plane | box | cone | sphere | anel" << endl;
    }

    else if (!strcmp (argv[1], "plane"))
    {
        if (argc != 5)
        {
            cout << "ERROR :: format: 'plane' <length> <width> <file name>"
            << endl;
        }
        else
        {
            double length = atof (argv[2]);
            double width = atof (argv[3]);
            drawPlane (length, width, argv[4]);
        }
    }

    else if (!strcmp (argv[1], "box"))
    {
        if (argc != 6)
        {
            cout << "ERROR :: format: 'box' <length> <height> <width> <file name>"
            << endl;
            return 0;
        }
        else
        {
            double length = atof (argv[2]);
            double height = atof (argv[3]);
            double width = atof (argv[4]);
            drawBox (length, height, width, argv[5]);
        }
    }

    else if (!strcmp (argv[1], "cone"))
    {
        if (argc != 7)
        {
            cout
            << "ERROR :: format: 'cone' <radius> <height> <slices> <stacks> <file name>"
            << endl;
            return 0;
        }
        else
        {
            double radius = atof (argv[2]);
            double height = atof (argv[3]);
            int slices = atoi (argv[4]);
            int stacks = atoi (argv[5]);
            drawCone (radius, height, slices, stacks, argv[6]);
        }
    }
    else if (!strcmp (argv[1], "sphere"))
    {
        if (argc != 6)
        {
            cout
            << "ERROR :: format: 'sphere' <radius> <slices> <stacks> <file name>"
            << endl;
            return 0;
        }
        else
        {
            double radius = atof (argv[2]);
            int slices = atoi (argv[3]);
            int stacks = atoi (argv[4]);
            drawSphere (radius, slices, stacks, argv[5]);

        }
    }
    else if (!strcmp (argv[1], "anel"))
    {
        if(argc != 6)
        {
            cout
            << "ERROR :: format: 'anel' <raio interior> <raio exterior> <slices> <file name>"
            << endl;
            return 0;
        }
        else
        {
            double raioIn = atof(argv[2]);
            double raioOut = atof(argv[3]);
            int slices = atoi(argv[4]);
            drawAnel(raioIn,raioOut,slices,argv[5]);
        }
    }

    return 0;
}

