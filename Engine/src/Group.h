
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

typedef struct gr
{

  //string val;

  vector<vector<string>> modelos;

  //vector<string> modelos;

  vector<Transformation*> transformations;

  vector<gr *> filhos;

} Grupo;

typedef struct modl
{



  Grupo * g;

  map<string,vector<Triangle>> figuras;



} Modelos;


void drawElement(Modelos * models, Grupo * g);
const vector<string> explode(const string& s, const char& c);
void lerFicheiro(Modelos * models, string file);
Modelos * readXMLDoc(const char * path);
void readXMLFromRootElement(XMLElement * root, Modelos * models, Grupo * grupo);
void traverseTree(Modelos * models, Grupo *t);

#endif


