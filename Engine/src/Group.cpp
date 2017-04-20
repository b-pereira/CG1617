/*
 * Group.cpp
 *
 *  Created on: 29/03/2017
 *      Author: bpereira
 */
#include <sstream>
#include "Group.h"
#include "Constantes.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>

void initBuffers(Models * models, VBO vbo, vector<float> array) {

	float *a = &array[0];

	/**
	 * Buffer Initialization
	 */
	glEnableClientState(GL_VERTEX_ARRAY);

	glGenBuffers(1, &models->buffers[vbo.index]);
	glBindBuffer(GL_ARRAY_BUFFER, models->buffers[vbo.index]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vbo.size, a, GL_STATIC_DRAW);





}

void drawVBO(Models * models, VBO vbo) {

	/**
	 * VBOs - Drawing
	 */

	glBindBuffer(GL_ARRAY_BUFFER, models->buffers[vbo.index]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, vbo.size);

}

void drawElement(Models * models, Group * g) {

	for (auto file : g->models) {

		auto entry = models->figures.find(file);

		if (entry != models->figures.end()) {

			drawVBO(models, entry->second);

		}

	}

}

void readFile(Models * models, string file) {

	string line;

	vector<float> lst;
	VBO vbo;
	vbo.size = 0;

	ifstream myfile("resources/" + file, ios::in);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {

			std::stringstream is(line);
			float x, y, z;
			is >> x;
			is >> y;
			is >> z;

			lst.push_back(x);
			lst.push_back(y);
			lst.push_back(z);

		}
		myfile.close();

		auto entry = models->figures.find(file);

		if (entry == models->figures.end()) {
			vbo.size = lst.size();
			vbo.index = models->n_buffers;
			models->buffers.push_back(0);

			models->figures.insert(std::pair<string, VBO>(file, vbo));

			initBuffers(models, vbo, lst);
			models->n_buffers++;

		}
	}

	else
		cout << "Unable to open file";

}

void readXMLFromRootElement(XMLElement * element, Models * models,
		Group * group) {

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
			float x, y, z;

			x = (element->Attribute(X)) ? atof(element->Attribute(X)) : 0;
			y = (element->Attribute(Y)) ? atof(element->Attribute(Y)) : 0;
			z = (element->Attribute(Z)) ? atof(element->Attribute(Y)) : 0;

			if (name.compare(TRANSLATE) == 0) {
				/**
				 * Criar Translação
				 */
				Translation * t = new Translation(x, y, z);

				group->transformations.push_back(t);

			} else {
				/**
				 * Criar Escala
				 */
				Scale * s = new Scale(x, y, z);

				group->transformations.push_back(s);

			}

		} else if (name.compare(ROTATE) == 0) {
			float axis_x, axis_y, axis_z, angle;

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

			group->transformations.push_back(r);

		} else if (name.compare(MODELS) == 0) {

			/**
			 * Iterar sobre os ficheiros de modelos
			 */
			for (auto crawl = element->FirstChildElement(MODEL);
					crawl != nullptr;
					crawl = crawl->NextSiblingElement(MODEL)) {

				string model(crawl->Attribute(FILE_D));

				group->models.push_back(model);

				readFile(models, model);

			}

		} else if (name.compare(GROUP) == 0) {

			Group * novo_group = new Group;
			group->children.push_back(novo_group);
			readXMLFromRootElement(element, models, novo_group);

		}

	}

}

Models * readXMLDoc(const char * path) {

	XMLDocument doc;
	doc.LoadFile(path);

	XMLElement* modelNode = doc.FirstChildElement(SCENE);
	Models * models = new Models;
	models->n_buffers = 0;
	models->g = new Group;

	readXMLFromRootElement(modelNode, models, models->g);

	return models;

}

void traverseTree(Models * models, Group *group) {

	glPushMatrix();


	for (auto transformation : group->transformations) {

		transformation->applyTransformation();

	}

	drawElement(models, group);

	for (int i = 0; i < group->children.size(); i++) {

		traverseTree(models, group->children[i]);
		glPopMatrix();


	}

}

