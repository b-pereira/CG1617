

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


void drawEsfera ( float radius, int slices, int stacks )
{   double delta_theta = ( 2*M_PI ) / slices;
    double delta_phi = M_PI/ stacks;
    double prev_theta = 0.0;
    double prev_phi = 0;
    double current_phi = delta_phi;
    int i, j;
    double current_theta;


    prev_phi = M_PI/2;
    current_phi = prev_phi - delta_phi;
    for ( i = 0 ; i <=stacks ; i++)
    {   
	     prev_theta = 0; current_theta = delta_theta;
	    for ( j = 0; j <= slices; j++ )
        {   // A B
            // xA yA zA
            Point3d pointA;
            pointA.x= radius*cos ( prev_phi ) *sin ( prev_theta );
            pointA.y= radius*sin ( prev_phi );
            pointA.z= radius*cos ( prev_phi ) *cos ( prev_theta );
            //cout << "A:\t" << ( ( double ) 180/M_PI ) *prev_phi << ",\t" << ( ( double ) 180/M_PI ) *prev_theta << endl;
            // xB yB zB
            Point3d pointB;
            pointB.x= radius*cos ( current_phi ) *sin ( prev_theta );
            pointB.y= radius*sin ( current_phi );
            pointB.z= radius*cos ( current_phi ) *cos ( prev_theta );
            //cout << "B:\t" << ( ( double ) 180/M_PI ) *phi << ",\t" << ( ( double ) 180/M_PI ) *prev_theta << endl;
            // C D
            // xD yD zD
            Point3d pointD;
            pointD.x= radius*cos ( prev_phi ) *sin ( current_theta );
            pointD.y= radius*sin ( prev_phi );
            pointD.z= radius*cos ( prev_phi ) *cos ( current_theta );
            //cout << "D:\t" << ( ( double ) 180/M_PI ) *prev_phi << ",\t" << ( ( double ) 180/M_PI ) *theta << endl;
            // xC yC zC
            Point3d pointC;
            pointC.x= radius*cos ( current_phi ) *sin ( current_theta );
            pointC.y= radius*sin ( current_phi );
            pointC.z= radius*cos ( current_phi ) *cos ( current_theta );
            //cout << "C:\t" << ( ( double ) 180/M_PI ) *phi << ",\t" << ( ( double ) 180/M_PI ) *theta << endl;
            //cout << "################################"<< endl;
            //cout.precision(9);
            cout << pointA.x <<", "<<pointA.y<<", "<<pointA.z <<";"<<pointB.x <<", "<<pointB.y<<", "<<pointB.z <<";"<<pointD.x <<", "<<pointD.y<<", "<<pointD.z<<endl ;
            cout << pointB.x <<", "<<pointB.y<<", "<<pointB.z <<";"<<pointC.x <<", "<<pointC.y<<", "<<pointC.z <<";"<<pointD.x <<", "<<pointD.y<<", "<<pointD.z<<endl ;
            prev_theta = current_theta;
	    current_theta+=delta_theta;
        }

        prev_phi = current_phi;

	current_phi = current_phi - delta_phi;
    }

}
int main ( int argc, char *argv[] )
{   drawEsfera ( 1, 4 , 4 );
    return 0;
}
