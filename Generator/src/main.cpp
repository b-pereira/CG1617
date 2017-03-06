#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cmath>
#include "Point3d.h"

using namespace std;

std::string point3D_to_string(Point3d point) {
	std::stringstream sstm;
	sstm << point.getXCoord() << ", " << point.getYCoord() << ", "
			<< point.getZCoord();
	return sstm.str();
}

std::string triangle_to_string(Point3d pointA, Point3d pointB, Point3d pointC) {
	return point3D_to_string(pointA) + ";" + point3D_to_string(pointB) + ";"
			+ point3D_to_string(pointC);
}

using namespace std;

//
//  main.c
//  Projecto
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void drawPlano(double length, double width, char* filename) {

	//face superior
	Point3d pontoA(-length / 2, 0, width / 2);

	Point3d pontoB(length / 2, 0, width / 2);

	Point3d pontoC(length / 2, 0, -width / 2);

	Point3d pontoD(-width / 2, 0, -width / 2);

	ofstream ficheiro;
	ficheiro.open(filename);
	if (ficheiro.is_open()) {
		ficheiro << triangle_to_string(pontoD, pontoA, pontoB) << endl;
		ficheiro << triangle_to_string(pontoB, pontoC, pontoD);
		ficheiro.close();
	} else
		cout << "Unable to open file\n";

}

void drawBox(double length, double height, double width, char* filename) {
	Point3d pontoA1(-length / 2, -height / 2, width / 2);

	Point3d pontoB1(length / 2, -height / 2, width / 2);

	Point3d pontoC1(length / 2, -height / 2, -width / 2);

	Point3d pontoD1(-length / 2, -height / 2, -width / 2);

	Point3d pontoA2(-length / 2, height / 2, width / 2);

	Point3d pontoB2(length / 2, height / 2, width / 2);

	Point3d pontoC2(length / 2, height / 2, -width / 2);

	Point3d pontoD2(-length / 2, height / 2, -width / 2);

	ofstream ficheiro;
	ficheiro.open(filename);
	if (ficheiro.is_open()) {
		ficheiro << triangle_to_string(pontoC1, pontoA1, pontoD1) << endl;
		ficheiro << triangle_to_string(pontoA1, pontoC1, pontoB1) << endl;

		ficheiro << triangle_to_string(pontoC2, pontoD2, pontoA2) << endl;
		ficheiro << triangle_to_string(pontoA2, pontoB2, pontoC2) << endl;

		ficheiro << triangle_to_string(pontoA1, pontoB1, pontoA2) << endl;
		ficheiro << triangle_to_string(pontoB1, pontoB2, pontoA2) << endl;

		ficheiro << triangle_to_string(pontoB1, pontoC1, pontoB2) << endl;
		ficheiro << triangle_to_string(pontoC1, pontoC2, pontoB2) << endl;

		ficheiro << triangle_to_string(pontoC1, pontoD1, pontoC2) << endl;
		ficheiro << triangle_to_string(pontoD1, pontoD2, pontoC2) << endl;

		ficheiro << triangle_to_string(pontoD1, pontoA1, pontoD2) << endl;
		ficheiro << triangle_to_string(pontoA1, pontoA2, pontoD2) << endl;

		ficheiro.close();

	}

	else
		cout << "Unable to open file\n";

}

void drawSphere(double radius, int slices, int stacks, char* filename) {
	double step_theta = (2 * M_PI) / slices;
	double step_phi = M_PI / stacks;
	double prev_theta = 0.0;
	double prev_phi = -1 * ( M_PI / 2);
	int i, j;
	double theta;
	double phi;

	ofstream ficheiro;
	ficheiro.open(filename);

	if (ficheiro.is_open()) {

		for (i = 0, phi = -1 * step_phi; i < stacks; i++, phi += step_phi) {
			for (j = 0, prev_theta = 0, theta = step_theta; j <= slices;
					j++, theta += step_theta) {   // A B

				Point3d pointA(radius * cos(prev_phi) * sin(prev_theta),
						radius * sin(prev_phi),
						radius * cos(prev_phi) * cos(prev_theta));

				Point3d pointB(radius * cos(phi) * sin(prev_theta),
						radius * sin(phi), radius * cos(phi) * cos(prev_theta));

				// C D

				Point3d pointD(radius * cos(prev_phi) * sin(theta),
						radius * sin(prev_phi),
						radius * cos(prev_phi) * cos(theta));

				Point3d pointC(radius * cos(phi) * sin(theta),
						radius * sin(phi), radius * cos(phi) * cos(theta));

				ficheiro << triangle_to_string(pointA, pointB, pointD) << endl;
				ficheiro << triangle_to_string(pointB, pointC, pointD) << endl;

				prev_theta = theta;
			}

			prev_phi = phi;
		}
		ficheiro.close();

	}

	else
		cout << "Unable to open file\n";
}

void drawCone(double radius, double height, int slices, int stacks,
		char * filename) {
	double step_theta = (2 * M_PI) / slices;
	double prev_theta = 0.0;
	double height_step = height / stacks;
	int i, j;
	double theta;
	double radius_aux = (radius * 1) / stacks;
	double height_aux;
	double prev_radius_aux = (radius * 0) / stacks;
	double prev_height_aux = -1 * height / 2;


	ofstream ficheiro;
	ficheiro.open(filename);
	if (ficheiro.is_open()) {

		for (i = 0, height_aux = prev_height_aux + height_step; i < stacks;
				i++, height_aux += height_step) {
			for (j = 0, prev_theta = 0, theta = step_theta; j <= slices;
					j++, theta += step_theta) {

				// A B

				Point3d pointA(prev_radius_aux * sin(prev_theta),
						prev_height_aux, prev_radius_aux * cos(prev_theta));

				Point3d pointB(radius_aux * sin(prev_theta), height_aux,
						radius_aux * cos(prev_theta));

				Point3d pointD(prev_radius_aux * sin(theta), prev_height_aux,
						prev_radius_aux * cos(theta));

				// xC yC zC
				Point3d pointC(radius_aux * sin(theta), height_aux,
						radius_aux * cos(theta));

				ficheiro << triangle_to_string(pointA, pointB, pointD) << endl;
				ficheiro << triangle_to_string(pointB, pointC, pointD) << endl;

				prev_theta = theta;
			}

			prev_height_aux = height_aux;
			prev_radius_aux = radius_aux;
			radius_aux = radius * (i + 2) / stacks;
		}

		Point3d pointO(0, height / 2, 0);

		for (j = 0, prev_theta = 0, theta = step_theta; j <= slices;
				j++, theta += step_theta) {
			Point3d pointA2(radius * sin(prev_theta), height / 2,
					radius * cos(prev_theta));

			Point3d pointB2(radius * sin(theta), height / 2,
					radius * cos(theta));

			ficheiro << triangle_to_string(pointO, pointB2, pointA2) << endl;

			prev_theta = theta;
		}
		ficheiro.close();

	}

	else
		cout << "Unable to open file\n";
}

int main(int argc, char* argv[]) {
//	if (argc <= 1) {
//		printf("ERRO Opções: plano | paralelipipedo | cone \n");
//	}
//
//	else if (!strcmp(argv[1], "plano")) {
//		if (argc != 5) {
//			printf(
//					"ERRO Formato: 'plano' <comprimento> <largura> <nome do ficheiro>\n");
//		} else {
//			double length = atof(argv[2]);
//			double width = atof(argv[3]);
//			drawPlane(length, width, argv[4]);
//		}
//	}
//
//	else if (!strcmp(argv[1], "box")) {
//		if (argc != 6) {
//			printf(
//					"ERRO Formato: 'box' <comprimento> <altura> <largura> <nome do ficheiro>\n");
//			exit(0);
//		} else {
//			double length = atof(argv[2]);
//			double height = atof(argv[3]);
//			double width = atof(argv[4]);
//			drawBox(length, height, width, argv[5]);
//		}
//	}
//
//	else if (!strcmp(argv[1], "cone")) {
//		if (argc != 7) {
//			printf(
//					"ERRO Formato: 'cone' <raio> <altura> <fatias> <camadas> <nome do ficheiro>\n");
//			exit(0);
//		} else {
//			double radius = atof(argv[2]);
//			double height = atof(argv[3]);
//			int slices = atoi(argv[4]);
//			int stacks = atoi(argv[5]);
//			drawCone(radius, height, slices, stacks, argv[6]);
//		}
//	}
}

