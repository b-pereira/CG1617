#ifndef SRC_GROUP_H_
#define SRC_GROUP_H_

#include <iostream>
#include <GL/glut.h>

#include <map>
#include <vector>

#include <fstream>
#include <cmath>

#include <vector>
#include <string>
#include <map>

#include "Constantes.h"

#include "Triangle.h"

#include "Transformation.h"
#include "Rotation.h"
#include "Translation.h"
#include "Scale.h"

#include "tinyxml2.h"

using namespace tinyxml2;

using namespace std;

typedef struct gr {

	vector<string> models;

	vector<Transformation*> transformations;

	vector<gr *> children;

} Group;

typedef struct modl {

	Group * g;

	map<string, vector<double>> figures;

} Models;

void drawElement(Models *, Group *);
const vector<string> explode(const string&, const char&);
void readFile(Models *, string file);
Models * readXMLDoc(const char *);
void readXMLFromRootElement(XMLElement *, Models *, Group *);
void traverseTree(Models *, Group *);

#endif

