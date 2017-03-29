
#ifndef SRC_GROUP_H_
#define SRC_GROUP_H_

#include <vector>
#include <string>
#include "Triangle.h"
#include "Transformation.h"
#include "Rotation.h"

#include "Translation.h"

#include "Scale.h"

using namespace std;

typedef struct gr
{

  string val;

  vector<vector<Triangle>> modelos;

  //vector<string> modelos;

  vector<Transformation*> transformations;

  vector<gr *> filhos;

} Grupo;

void applyTransformation(Grupo *, Transformation *);

#endif
