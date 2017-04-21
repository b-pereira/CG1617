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

#include "AnimatedRotation.h"
#include "AnimatedTranslation.h"
#include "Rotation.h"
#include "Translation.h"
#include "Constantes.h"

#include "Triangle.h"

#include "Transformation.h"
#include "Scale.h"

#include "tinyxml2.h"

using namespace tinyxml2;

using namespace std;

typedef struct gr {

	vector<string> modelos;

	vector<Transformation*> transformations;

	vector<gr *> filhos;

} Grupo;

typedef struct modl {

	Grupo * g;

	map<string, vector<Triangle>> figuras;

} Modelos;

void drawElement(Modelos *, Grupo *);
const vector<string> explode(const string&, const char&);
void lerFicheiro(Modelos *, string file);
Modelos * readXMLDoc(const char *);
void readXMLFromRootElement(XMLElement *, Modelos *, Grupo *);
void traverseTree(Modelos *, Grupo *);

#endif

