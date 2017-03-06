

#include <sstream>
#include <string>
#include <iostream>
#include <cmath>

typedef struct triplo
{

    double x;
    double y;
    double z;

} Point3d;


using namespace std;

std::string point3D_to_string ( Point3d point )
{   std::stringstream sstm;
    sstm <<point.x <<", "<<point.y<<", "<<point.z;
    return sstm.str();
}

std::string triangle_to_string ( Point3d pointA, Point3d pointB, Point3d   pointC )
{   return point3D_to_string ( pointA )+";"+point3D_to_string ( pointB )+";"+point3D_to_string ( pointC );
}


void drawCone ( float radius, float height, int slices, int stacks )
{   double step_theta = ( 2*M_PI ) / slices;
    double prev_theta = 0.0;
    double height_step = height/stacks;
    int i, j;
    double theta;
    double radius_aux = ( radius*1 ) /stacks;
    double height_aux;
    double prev_radius_aux = ( radius*0 ) /stacks;
    double prev_height_aux = -1*height/2;

    for ( i = 0, height_aux = prev_height_aux + height_step;  i < stacks ; i++, height_aux+=height_step )
    {   for ( j = 0, prev_theta = 0, theta = step_theta; j <= slices; j++, theta+=step_theta )
        {   // A B
            // xA yA zA
            Point3d pointA;
            pointA.x= prev_radius_aux*sin ( prev_theta );
            pointA.y= prev_height_aux;
            pointA.z= prev_radius_aux *cos ( prev_theta );
            // xB yB zB
            Point3d pointB;
            pointB.x= radius_aux*sin ( prev_theta );
            pointB.y= height_aux;
            pointB.z= radius_aux*cos ( prev_theta );
            // C D
            // xD yD zD
            Point3d pointD;
            pointD.x= prev_radius_aux*sin ( theta );
            pointD.y= prev_height_aux;
            pointD.z= prev_radius_aux*cos ( theta );
            // xC yC zC
            Point3d pointC;
            pointC.x= radius_aux*sin ( theta );
            pointC.y= height_aux;
            pointC.z= radius_aux*cos ( theta );
            cout << pointA.x <<", "<<pointA.y<<", "<<pointA.z <<";"<<pointB.x <<", "<<pointB.y<<", "<<pointB.z <<";"<<pointD.x <<", "<<pointD.y<<", "<<pointD.z<<endl ;
            cout << pointB.x <<", "<<pointB.y<<", "<<pointB.z <<";"<<pointC.x <<", "<<pointC.y<<", "<<pointC.z <<";"<<pointD.x <<", "<<pointD.y<<", "<<pointD.z<<endl ;
            prev_theta = theta;
        }

        prev_height_aux = height_aux;
        prev_radius_aux = radius_aux;
        radius_aux = radius* ( i+2 ) /stacks;
    }

    Point3d pointO;
    pointO.x= 0;
    pointO.y= height/2;
    pointO.z= 0;

    for ( j = 0, prev_theta = 0, theta = step_theta; j <= slices; j++, theta+=step_theta )
    {   Point3d pointA;
        pointA.x= radius*sin ( prev_theta );
        pointA.y= height/2;
        pointA.z= radius *cos ( prev_theta );
        // xB yB zB
        Point3d pointB;
        pointB.x= radius *sin ( theta );
        pointB.y= height/2;
        pointB.z= radius*cos ( theta );
        
        cout << pointO.x <<", "<<pointO.y<<", "<<pointO.z <<";"<<pointB.x <<", "<<pointB.y<<", "<<pointB.z <<";"<<pointA.x <<", "<<pointA.y<<", "<<pointA.z<<endl ;
        prev_theta = theta;
    }
}



int main ( int argc, char *argv[] )
{   drawCone ( 1, 4, 100, 5 );
    return 0;
}
