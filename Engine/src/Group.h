#ifndef SRC_GROUP_H_
#define SRC_GROUP_H_

#include <iostream>
#include <IL/il.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include <map>
#include <vector>

#include <fstream>
#include <cmath>

#include <string>

#include "Constantes.h"

#include "Transformation.h"
#include "Rotation.h"
#include "Translation.h"
#include "Scale.h"

#include "AnimatedRotation.h"
#include "AnimatedTranslation.h"

#include "Materials.h"

#include "tinyxml2.h"

#include "Light.h"

using namespace tinyxml2;

using namespace std;

typedef struct gr {

	vector<string> models;
	vector<string> textures;
	vector<vector<Materials*>> materials;

	vector<Transformation*> transformations;

	vector<gr *> children;

} Group;

typedef struct vbos {

	int index;
	int size;

} VBO;


typedef struct modl {

	Group * g;
	int n_buffers;

	vector<GLuint> buffers;
	vector<GLuint> normals;
	vector<GLuint> textCoords;
	vector<Materials*> materials_defaults;
	vector<Light*> lights;
	map<string, VBO> figures;
	map<string, GLuint> textures;

} Models;

void initBuffers(Models *, VBO, vector<float>);
void drawVBO(Models *, VBO);
void drawElement(Models *, Group *);
void readFile(Models *, string file);
Models * readXMLDoc(const char *);
void readXMLFromRootElement(XMLElement *, Models *, Group *);
void traverseTree(Models *, Group *);

#endif

