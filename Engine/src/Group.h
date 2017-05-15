#ifndef SRC_GROUP_H_
#define SRC_GROUP_H_

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include <map>
#include <vector>

#include <fstream>
#include <cmath>

#include <vector>
#include <string>
#include <map>

#include "Constantes.h"





#include "Transformation.h"
#include "Rotation.h"
#include "Translation.h"
#include "Scale.h"

#include "AnimatedRotation.h"
#include "AnimatedTranslation.h"

#include "tinyxml2.h"

using namespace tinyxml2;

using namespace std;

typedef struct gr {

	vector<string> models;

	vector<Transformation*> transformations;

	vector<gr *> children;

} Group;


typedef struct vbos {



	int index;
	int indexTextID;
	int size;


} VBO;

typedef struct modl {

	Group * g;
	int n_buffers;

	vector<GLuint> buffers ;
	vector<GLuint> normals ;
	vector<GLuint> textCoords ;
	vector<GLuint> textIDs ;
	map<string, VBO> figures;

} Models;

void initBuffers(Models *, VBO, vector<float>);
void drawVBO(Models *, VBO);

void drawElement(Models *, Group *);
void readFile(Models *, string file);
Models * readXMLDoc(const char *);
void readXMLFromRootElement(XMLElement *, Models *, Group *);
void traverseTree(Models *, Group *);

#endif

