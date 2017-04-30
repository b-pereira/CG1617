#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "Point3d.h"
#include <vector>
#include <array>

typedef std::vector<float> RowF;

typedef std::vector<RowF> MatrixF;

typedef std::vector<Point3d> RowP;

typedef std::vector<RowP> MatrixP;

typedef enum {
	X, Y, Z
} CoordType;

typedef struct patch_file {

	int num_patches;
	int num_points;
	std::vector<std::vector<int>> index_list;
	std::vector<Point3d> points_list;

} PATCHS;

const MatrixF M = { { -1, 3, -3, 1 }, { 3, -6, 3, 0 }, { -3, 3, 0, 0 }, { 1, 0,
		0, 0 } };

std::string point3D_to_string(Point3d point) {
	std::stringstream sstm;
	sstm << point.getXCoord() << " " << point.getYCoord() << " "
			<< point.getZCoord();
	return sstm.str();
}

std::string triangle_to_string(Point3d pointA, Point3d pointB, Point3d pointC) {
	return point3D_to_string(pointA) + "\n" + point3D_to_string(pointB) + "\n"
			+ point3D_to_string(pointC);
}

using namespace std;

//void printMatrix(MatrixF mat) {
//
//	cout << "{ ";
//	for (int i = 0; i < mat.size(); ++i) {
//		cout << "{ ";
//		for (int j = 0; j < mat[0].size(); ++j) {
//			cout << mat[i][j] << " ";
//
//		}
//		cout << "}" << endl;
//	}
//	cout << "}" << endl;
//}

void readPatchFile(string file, PATCHS & pat) {

	string line;

	int reading = 0;

	int num_index = 0;

	ifstream myfile("resources/" + file, ios::in);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			std::stringstream is(line);
			if (reading < 1) {

				is >> pat.num_patches;
				reading = 1;
			} else

			if (reading == 1 && num_index < pat.num_patches) {
				int value_index = 0;
				vector<int> lst_index_tmp;

				while (is >> value_index) {
					lst_index_tmp.push_back(value_index);
				}
				pat.index_list.push_back(lst_index_tmp);
				num_index++;
				if (num_index == pat.num_patches) {
					reading = 2;
				}

			} else if (reading == 2) {
				is >> pat.num_points;
				reading = 3;
			} else {

				float x, y, z;
				is >> x;
				is >> y;
				is >> z;

				Point3d point(x, y, z);

				pat.points_list.push_back(point);

			}

		}
		myfile.close();

	}

	else
		cout << "Unable to open file";



}

MatrixF multMatrix(MatrixF m1, MatrixF m2) {

	// Dimensões M1 M*N
	int m, n;
	// Dimensões M2 P*Q
	int p, q;
	m = m1.size();
	n = m1[0].size();
	p = m2.size();
	q = m2[0].size();


	MatrixF res(m, RowF(q));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < q; j++) {
			float product = 0;
			// assumindo que n == p
			for (int k = 0; k < p; k++) {
				product += m1[i][k] * m2[k][j];
			}
			res[i][j] = product;
			product = 0;

		}

	}
	return res;
}

MatrixF matrixPointToScalar(MatrixP m1, CoordType type) {

	// Dimensões M1 M*N
	int m, n;

	m = m1.size();
	n = m1[0].size();

	MatrixF res(m, RowF(n));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			switch (type) {
			case X:
				res[i][j] = m1[i][j].getXCoord();
				break;
			case Y:
				res[i][j] = m1[i][j].getYCoord();
				break;
			case Z:
				res[i][j] = m1[i][j].getZCoord();
				break;
			default:
				break;
			}

		}

	}
	return res;
}

Point3d getBezierPatchPoint(float u, float v, MatrixP P) {

	cout << "u: " << u << " " << v << endl;

	MatrixF U = { { powf(u, 3), powf(u, 2), u, 1 } };
	MatrixF V = { { powf(v, 3) }, { powf(v, 2) }, { v }, { 1 } };



	// Compute A = U * M
	MatrixF A1 = multMatrix(U, M);



	// Compute B = M^tV = M * V
	MatrixF A2 = multMatrix(M, V);



	// Compute Px = P.getCoordX
	MatrixF PX = matrixPointToScalar(P, X);



	// Compute Py = P.getCoordY
	MatrixF PY = matrixPointToScalar(P, Y);



	// Compute Pz = P.getCoordZ
	MatrixF PZ = matrixPointToScalar(P, Z);



	// Compute U * M * P(x, y, z)
	MatrixF BXA = multMatrix(A1, PX);



	MatrixF BYA = multMatrix(A1, PY);



	MatrixF BZA = multMatrix(A1, PZ);


	// Compute B(X, Y, Z)A * M^tV

	MatrixF BX = multMatrix(BXA, A2);

	MatrixF BY = multMatrix(BYA, A2);

	MatrixF BZ = multMatrix(BZA, A2);

	Point3d point(BX[0][0], BY[0][0], BZ[0][0]);

	return point;

}

void drawPlane(float length, float width, char* filename) {

	Point3d pontoA(-length / 2, 0, width / 2);

	Point3d pontoB(length / 2, 0, width / 2);

	Point3d pontoC(length / 2, 0, -width / 2);

	Point3d pontoD(-width / 2, 0, -width / 2);

	ofstream ficheiro;
	ficheiro.open(filename);
	if (ficheiro.is_open()) {
		ficheiro.clear();
		ficheiro << triangle_to_string(pontoA, pontoD, pontoB) << endl;
		ficheiro << triangle_to_string(pontoB, pontoD, pontoA) << endl;

		ficheiro << triangle_to_string(pontoD, pontoC, pontoB) << endl;
		ficheiro << triangle_to_string(pontoB, pontoC, pontoD) << endl;
		ficheiro.close();
	} else
		cout << "Unable to open file\n";

}

void drawBox(float length, float height, float width, char* filename) {
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
		ficheiro.clear();
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

void drawSphere(float radius, int slices, int stacks, char* filename) {

	float delta_theta = (2 * M_PI) / slices;
	float delta_phi = M_PI / stacks;

	int i, j;

	float prev_theta = 0.0;
	float current_theta;

	float prev_phi = M_PI / 2;
	float current_phi = prev_phi - delta_phi;

	ofstream ficheiro;
	ficheiro.open(filename);

	if (ficheiro.is_open()) {
		ficheiro.clear();

		for (i = 0; i < stacks; i++) {
			prev_theta = 0;
			current_theta = delta_theta;
			for (j = 0; j <= slices; j++) {   // A B

				Point3d pointA(radius * cos(prev_phi) * sin(prev_theta),
						radius * sin(prev_phi),
						radius * cos(prev_phi) * cos(prev_theta));

				Point3d pointB(radius * cos(current_phi) * sin(prev_theta),
						radius * sin(current_phi),
						radius * cos(current_phi) * cos(prev_theta));

				// C D

				Point3d pointD(radius * cos(prev_phi) * sin(current_theta),
						radius * sin(prev_phi),
						radius * cos(prev_phi) * cos(current_theta));

				Point3d pointC(radius * cos(current_phi) * sin(current_theta),
						radius * sin(current_phi),
						radius * cos(current_phi) * cos(current_theta));

				ficheiro << triangle_to_string(pointA, pointB, pointD) << endl;
				ficheiro << triangle_to_string(pointB, pointC, pointD) << endl;
				prev_theta = current_theta;
				current_theta += delta_theta;
			}

			prev_phi = current_phi;

			current_phi = current_phi - delta_phi;
		}

		ficheiro.close();

	}

	else
		cout << "Unable to open file\n";
}

void drawAnel(float raioIn, float raioOut, int slices, char * filename) {

	float prev_theta, current_theta;
	int i, j;

	float delta_theta = (2 * M_PI) / slices;

	ofstream ficheiro;
	ficheiro.open(filename);
	if (ficheiro.is_open()) {
		ficheiro.clear();

		prev_theta = 0;
		current_theta = delta_theta;

		for (j = 0; j <= slices; j++) {
			Point3d pontoA(raioOut * sin(prev_theta), 0.005,
					raioOut * cos(prev_theta));

			Point3d pontoB(raioIn * sin(prev_theta), 0.005,
					raioIn * cos(prev_theta));

			Point3d pontoC(raioIn * sin(current_theta), 0.005,
					raioIn * cos(current_theta));

			Point3d pontoD(raioOut * sin(current_theta), 0.005,
					raioOut * cos(current_theta));

			Point3d pontoA2(raioOut * sin(prev_theta), -0.005,
					raioOut * cos(prev_theta));

			Point3d pontoB2(raioIn * sin(prev_theta), -0.005,
					raioIn * cos(prev_theta));

			Point3d pontoC2(raioIn * sin(current_theta), -0.005,
					raioIn * cos(current_theta));

			Point3d pontoD2(raioOut * sin(current_theta), -0.005,
					raioOut * cos(current_theta));

			// Disco de baixo
			ficheiro << triangle_to_string(pontoA2, pontoB2, pontoD2) << endl;
			ficheiro << triangle_to_string(pontoD2, pontoB2, pontoC2) << endl;

			// Disco de cima
			ficheiro << triangle_to_string(pontoD, pontoB, pontoA) << endl;
			ficheiro << triangle_to_string(pontoC, pontoB, pontoD) << endl;

			// Lado externo
			ficheiro << triangle_to_string(pontoA2, pontoA, pontoD2) << endl;
			ficheiro << triangle_to_string(pontoD, pontoD2, pontoA) << endl;

			// Lado interno
			ficheiro << triangle_to_string(pontoB, pontoC2, pontoB2) << endl;
			ficheiro << triangle_to_string(pontoC, pontoC2, pontoB) << endl;

			prev_theta = current_theta;
			current_theta += delta_theta;
		}
		ficheiro.close();

	}

	else
		cout << "Unable to open file\n";
}

void drawCone(float radius, float height, int slices, int stacks,
		char * filename) {

	float prev_theta, current_theta;
	int i, j;

	float delta_theta = (2 * M_PI) / slices;
	float delta_height = height / stacks;

	float prev_radius_aux = (radius * 0) / stacks;
	float prev_height_aux = height / 2;

	float radius_aux = (radius * 1) / stacks;
	float height_aux = prev_height_aux - delta_height;

	ofstream ficheiro;
	ficheiro.open(filename);
	if (ficheiro.is_open()) {
		ficheiro.clear();

		for (i = 0; i <= stacks; i++) {
			prev_theta = 0;
			current_theta = delta_theta;

			for (j = 0; j <= slices; j++) {

				// A B

				Point3d pointA(prev_radius_aux * sin(prev_theta),
						prev_height_aux, prev_radius_aux * cos(prev_theta));

				Point3d pointB(radius_aux * sin(prev_theta), height_aux,
						radius_aux * cos(prev_theta));

				// D C

				Point3d pointD(prev_radius_aux * sin(current_theta),
						prev_height_aux, prev_radius_aux * cos(current_theta));

				Point3d pointC(radius_aux * sin(current_theta), height_aux,
						radius_aux * cos(current_theta));

				ficheiro << triangle_to_string(pointA, pointB, pointD) << endl;
				ficheiro << triangle_to_string(pointB, pointC, pointD) << endl;

				prev_theta = current_theta;
				current_theta += delta_theta;
			}

			prev_height_aux = height_aux;
			prev_radius_aux = radius_aux;

			radius_aux = radius * (i + 2) / stacks;
			height_aux -= delta_height;
		}

		Point3d pointO(0, -height / 2, 0);

		prev_theta = 0;
		current_theta = delta_theta;

		for (j = 0; j <= slices; j++) {
			Point3d pointA2(radius * sin(prev_theta), -height / 2,
					radius * cos(prev_theta));

			Point3d pointB2(radius * sin(current_theta), -height / 2,
					radius * cos(current_theta));

			ficheiro << triangle_to_string(pointO, pointB2, pointA2) << endl;

			prev_theta = current_theta;
			current_theta += delta_theta;
		}
		ficheiro.close();

	}

	else
		cout << "Unable to open file\n";
}

void drawPatch(string file_patch, float tesselation, string out_file) {

	PATCHS pat;

	readPatchFile(file_patch, pat);

	vector<vector<Point3d>> patches;

	vector<MatrixP> ps;

	for (auto index_l : pat.index_list) {
		vector<Point3d> tmp;

		for (auto index : index_l) {
			tmp.push_back(pat.points_list[index]);

		}
		patches.push_back(tmp);
	}
	int i = 0;
	int j = 0;

	for (vector<Point3d> tm : patches) {
		MatrixP t(4, RowP(4));
		for (Point3d pt : tm) {
			//cout << i << " " << j << " " << point3D_to_string(pt) << endl;
			t[i][j] = pt;
			//t[i][j] = pt;
			j = (j + 1) % 4;
			i = (j > 0) ? i : (i + 1) % 4;

		}

		ps.push_back(t);

	}

	ofstream ficheiro;
	ficheiro.open(out_file.c_str());

	if (ficheiro.is_open()) {
		ficheiro.clear();

		for (MatrixP mat : ps) {
			for (i = 0; i < tesselation; ++i) {
				for (j = 0; j < tesselation; ++j) {
					Point3d pointA = getBezierPatchPoint(i / tesselation,
							j / tesselation, mat);
					Point3d pointB = getBezierPatchPoint(i / tesselation,
							(j + 1) / tesselation, mat);
					Point3d pointC = getBezierPatchPoint((i + 1) / tesselation,
							(j + 1) / tesselation, mat);
					Point3d pointD = getBezierPatchPoint((i + 1) / tesselation,
							j / tesselation, mat);

					ficheiro << triangle_to_string(pointA, pointB, pointD)
							<< endl;
					ficheiro << triangle_to_string(pointB, pointC, pointD)
							<< endl;

				}
			}
		}
		ficheiro.close();

	}

	else
		cout << "Unable to open file\n";

}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		cout << "ERROR :: Options: patch | plane | box | cone | sphere | anel"
				<< endl;
	}

	else if (!strcmp(argv[1], "plane")) {
		if (argc != 5) {
			cout << "ERROR :: format: 'plane' <length> <width> <file name>"
					<< endl;
		} else {
			float length = atof(argv[2]);
			float width = atof(argv[3]);
			drawPlane(length, width, argv[4]);
		}
	}

	else if (!strcmp(argv[1], "box")) {
		if (argc != 6) {
			cout
					<< "ERROR :: format: 'box' <length> <height> <width> <file name>"
					<< endl;
			return 0;
		} else {
			float length = atof(argv[2]);
			float height = atof(argv[3]);
			float width = atof(argv[4]);
			drawBox(length, height, width, argv[5]);
		}
	}

	else if (!strcmp(argv[1], "cone")) {
		if (argc != 7) {
			cout
					<< "ERROR :: format: 'cone' <radius> <height> <slices> <stacks> <file name>"
					<< endl;
			return 0;
		} else {
			float radius = atof(argv[2]);
			float height = atof(argv[3]);
			int slices = atoi(argv[4]);
			int stacks = atoi(argv[5]);
			drawCone(radius, height, slices, stacks, argv[6]);
		}
	} else if (!strcmp(argv[1], "sphere")) {
		if (argc != 6) {
			cout
					<< "ERROR :: format: 'sphere' <radius> <slices> <stacks> <file name>"
					<< endl;
			return 0;
		} else {
			float radius = atof(argv[2]);
			int slices = atoi(argv[3]);
			int stacks = atoi(argv[4]);
			drawSphere(radius, slices, stacks, argv[5]);

		}
	} else if (!strcmp(argv[1], "ring")) {
		if (argc != 6) {
			cout
					<< "ERROR :: format: 'ring' <inner radius> <exterior radius> <slices> <file name>"
					<< endl;
			return 0;
		} else {
			float raioIn = atof(argv[2]);
			float raioOut = atof(argv[3]);
			int slices = atoi(argv[4]);
			drawAnel(raioIn, raioOut, slices, argv[5]);
		}
	} else if (!strcmp(argv[1], "patch")) {
		if (argc != 5) {
			cout
					<< "ERROR :: format: 'patch' <file.patch> <tesselation> <file name>"
					<< endl;
			return 0;
		} else {
			string patch_file(argv[2]);
			float tesselation = atof(argv[3]);
			string out_file(argv[4]);
			drawPatch(patch_file, tesselation, out_file);
		}
	}

	return 0;
}

