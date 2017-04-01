/*
 * Group.cpp
 *
 *  Created on: 29/03/2017
 *      Author: bpereira
 */

#include "Group.h"
#include "Constantes.h"

const vector<string> explode(const string& s, const char& c) {
	string buff { "" };
	vector<string> v;

	for (auto n : s) {
		if (n != c)
			buff += n;
		else if (n == c && buff != "") {
			v.push_back(buff);
			buff = "";
		}
	}
	if (buff != "")
		v.push_back(buff);

	return v;
}

void drawElement(Modelos * models, Grupo * g) {

	// put drawing instructions here
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < g->modelos.size(); i++) {

		for (string file : g->modelos.at(i)) {


			for (Triangle t : models->figuras.find(file)->second) {

				Point3d a = t.getA();
				Point3d b = t.getB();
				Point3d c = t.getC();

				glVertex3f(a.getXCoord(), a.getYCoord(), a.getZCoord());

				glVertex3f(b.getXCoord(), b.getYCoord(), b.getZCoord());

				glVertex3f(c.getXCoord(), c.getYCoord(), c.getZCoord());

				glColor3f(1, 1, 0);

			}
		}
	}

	glEnd();

}

void lerFicheiro(Modelos * models, string file) {

	string line;

	vector<Triangle> lst;
	ifstream myfile("..\resources\" + file);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			vector<string> v { explode(line, ';') };
			vector<string> p1 { explode(v[0], ',') };
			vector<string> p2 { explode(v[1], ',') };
			vector<string> p3 { explode(v[2], ',') };

			Triangle t(atof(p1[0].c_str()), atof(p1[1].c_str()),
					atof(p1[2].c_str()), atof(p2[0].c_str()),
					atof(p2[1].c_str()), atof(p2[2].c_str()),
					atof(p3[0].c_str()), atof(p3[1].c_str()),
					atof(p3[2].c_str()));

			lst.push_back(t);

		}
		myfile.close();

		//models.

		///if (!(models.figuras.find(file) == models.figuras.end())) {



		std::pair<std::map<string, vector<Triangle>>::iterator,bool> ret;
		  ret = models->figuras.insert ( std::pair<string, vector<Triangle>>(file, lst));
		  if (ret.second==false) {
		    std::cout << "element 'z' already existed";
		    std::cout << " with a value of " << ret.first->second.at(0).getA().getXCoord() << '\n';
		  }


	}

	else
		cout << "Unable to open file";

}

void readXMLFromRootElement(XMLElement * root, Modelos * models, Grupo * grupo) {

	if (root == nullptr)
		return;

	auto tmp = root;
	auto tmp_gr = grupo;

	/**
	 * Para cada irmão do elemento inicial: procurar atributos
	 */
	for (auto element = tmp->FirstChildElement(); element;
			element = element->NextSiblingElement()) {

		string name(element->Name());

		Transformation * tr = 0;

		if ((name.compare(TRANSLATE) == 0) || (name.compare(SCALE) == 0)) {
			double x, y, z;

			x = (element->Attribute(X)) ? atof(element->Attribute(X)) : 0;
			y = (element->Attribute(Y)) ? atof(element->Attribute(Y)) : 0;
			z = (element->Attribute(Z)) ? atof(element->Attribute(Y)) : 0;

			if (name.compare(TRANSLATE) == 0) {
				/**
				 * Criar Translação
				 */
				Translation * t = new Translation(x, y, z);

				tmp_gr->transformations.push_back(t);

			} else {
				/**
				 * Criar Escala
				 */
				Scale * s = new Scale(x, y, z);

				tmp_gr->transformations.push_back(s);

			}

		} else if (name.compare(ROTATE) == 0) {
			double axis_x, axis_y, axis_z, angle;

			angle = (element->Attribute(ANGLE)) ?
					atof(element->Attribute(ANGLE)) : 0;

			axis_x =
					(element->Attribute(AXIS_X)) ?
							atof(element->Attribute(AXIS_X)) : 0;
			axis_y =
					(element->Attribute(AXIS_Y)) ?
							atof(element->Attribute(AXIS_Y)) : 0;
			axis_z =
					(element->Attribute(AXIS_Z)) ?
							atof(element->Attribute(AXIS_Z)) : 0;

			/**
			 * Criar Rotação
			 */
			Rotation * r = new Rotation(angle, axis_x, axis_y, axis_z);

			tmp_gr->transformations.push_back(r);

		} else if (name.compare(MODELS) == 0) {

			vector<string> lst;

			/**
			 * Iterar sobre os ficheiros de modelos
			 */
			for (auto crawl = element->FirstChildElement(MODEL);
					crawl != nullptr;
					crawl = crawl->NextSiblingElement(MODEL)) {

				string modelo(crawl->Attribute(FILE_D));

				lst.push_back(modelo);

				lerFicheiro(models, modelo);

			}
			grupo->modelos.push_back(lst);

		} else if (name.compare(GROUP) == 0) {

			/**
			 * Guardar ler ficheiro (forma);

			 */

			Grupo * grupo = new Grupo;
			tmp_gr->filhos.push_back(grupo);
			readXMLFromRootElement(element,models,  grupo);

		}

	}

}

Modelos * readXMLDoc(const char * path) {

	XMLDocument doc;
	doc.LoadFile(path);

	XMLElement* modelNode = doc.FirstChildElement(SCENE);
	Modelos *  models = new Modelos;
	models->g = new Grupo;

	readXMLFromRootElement(modelNode, models,  models->g);

	return models;

}


void traverseTree(Modelos * models, Grupo *t) {

	auto tmp = t;

	if (tmp == nullptr)
		return;

	glPushMatrix();
	cout << "PUSH" << endl;

	for (auto var : tmp->transformations) {

		var->applyTransformation();

	}

	drawElement(models, tmp);

	for (int nivel = 0; nivel < tmp->filhos.size(); nivel++) {
		if (tmp->filhos[nivel] != nullptr) {
			traverseTree(models, tmp->filhos[nivel]);
			glPopMatrix();
			cout << "POP" << endl;

		}
	}

	return;
}



