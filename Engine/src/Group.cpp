/*
 * Group.cpp
 *
 *  Created on: 29/03/2017
 *      Author: bpereira
 */
#include <sstream>
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

	glBegin(GL_TRIANGLES);

	for (auto file : g->modelos) {

		auto entry = models->figuras.find(file);

		if (entry != models->figuras.end()) {

			for (int i = 0; i < entry->second.size(); i += 3) {
				glVertex3f(entry->second[i], entry->second[i + 1],
						entry->second[i + 2]);

			}
		}

	}

	glEnd();

}

void lerFicheiro(Modelos * models, string file) {

	string line;

	vector<double> lst;
	ifstream myfile("resources/" + file, ios::in);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {

			std::stringstream is(line);
			double x, y, z;
			is >> x;
			is >> y;
			is >> z;

			lst.push_back(x);
			lst.push_back(y);
			lst.push_back(z);

		}
		myfile.close();

		models->figuras.insert(std::pair<string, vector<double>>(file, lst));

	}

	else
		cout << "Unable to open file";

}

void readXMLFromRootElement(XMLElement * element, Modelos * models,
		Grupo * grupo) {

	if (element == nullptr)
		return;

	/**
	 * Para cada irmão do elemento inicial: procurar atributos
	 */
	for (element = element->FirstChildElement(); element;
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

				grupo->transformations.push_back(t);

			} else {
				/**
				 * Criar Escala
				 */
				Scale * s = new Scale(x, y, z);

				grupo->transformations.push_back(s);

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

			grupo->transformations.push_back(r);

		} else if (name.compare(MODELS) == 0) {

			/**
			 * Iterar sobre os ficheiros de modelos
			 */
			for (auto crawl = element->FirstChildElement(MODEL);
					crawl != nullptr;
					crawl = crawl->NextSiblingElement(MODEL)) {

				string modelo(crawl->Attribute(FILE_D));

				grupo->modelos.push_back(modelo);

				lerFicheiro(models, modelo);

			}

		} else if (name.compare(GROUP) == 0) {

			Grupo * novo_grupo = new Grupo;
			grupo->filhos.push_back(novo_grupo);
			readXMLFromRootElement(element, models, novo_grupo);

		}

	}

}

Modelos * readXMLDoc(const char * path) {

	XMLDocument doc;
	doc.LoadFile(path);

	XMLElement* modelNode = doc.FirstChildElement(SCENE);
	Modelos * models = new Modelos;
	models->g = new Grupo;

	readXMLFromRootElement(modelNode, models, models->g);

	return models;

}

void traverseTree(Modelos * models, Grupo *grupo) {

	glPushMatrix();
	cout << "PUSH" << endl;

	for (auto transformation : grupo->transformations) {

		transformation->applyTransformation();

	}

	drawElement(models, grupo);

	for (int i = 0; i < grupo->filhos.size(); i++) {

		traverseTree(models, grupo->filhos[i]);
		glPopMatrix();
		cout << "POP" << endl;

	}

}

