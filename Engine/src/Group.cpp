/*
 * Group.cpp
 *
 *  Created on: 29/03/2017
 *      Author: bpereira
 */

#include <IL/il.h>
#include <sstream>
#include "Group.h"
#include "Constantes.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>

int loadTexture(std::string s) {

	unsigned int t, tw, th;
	unsigned char *texData;
	unsigned int texID;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring) s.c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1, &texID);

	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
	GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
	GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA,
	GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;

}

void initBuffers(Models * models, VBO vbo, vector<float> points,
		vector<float> normals, vector<float> textCoords) {

	float *a = &points[0];

	/**
	 * Buffer Initialization
	 */
	glEnableClientState(GL_VERTEX_ARRAY);

	glGenBuffers(1, &models->buffers[vbo.index]);
	glBindBuffer(GL_ARRAY_BUFFER, models->buffers[vbo.index]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vbo.size*3, &points[0],
	GL_STATIC_DRAW);

	glGenBuffers(1, &models->normals[vbo.index]);
	glBindBuffer(GL_ARRAY_BUFFER, models->normals[vbo.index]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vbo.size*3, &normals[0],
	GL_STATIC_DRAW);
	glGenBuffers(1, &models->textCoords[vbo.indexTextID]);
	glBindBuffer(GL_ARRAY_BUFFER, models->textCoords[vbo.index]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vbo.size * 2, &textCoords[0],
	GL_STATIC_DRAW);

}

void drawVBO(Models * models, VBO vbo) {

	/**
	 * VBOs - Drawing
	 */
	glBindTexture(GL_TEXTURE_2D, models->textIDs[vbo.indexTextID]);
	glBindBuffer(GL_ARRAY_BUFFER, models->buffers[vbo.index]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, models->normals[vbo.index]);
	glNormalPointer(GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, models->textCoords[vbo.index]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, vbo.size);
	glBindTexture(GL_TEXTURE_2D, 0);

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

	vector<float> lstPts;
	vector<float> lstNrms;
	vector<float> lstTxts;
	VBO vbo;
	vbo.size = 0;


	ifstream myfile("resources/" + file, ios::in);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {

			std::stringstream is(line);
			float x, y, z, nx, ny, nz, tx, ty;
			is >> x;
			is >> y;
			is >> z;
			is >> nx;
			is >> ny;
			is >> nz;
			is >> tx;
			is >> ty;

			lstPts.push_back(x);
			lstPts.push_back(y);
			lstPts.push_back(z);
			lstNrms.push_back(nx);
			lstNrms.push_back(ny);
			lstNrms.push_back(nz);
			lstTxts.push_back(tx);
			lstTxts.push_back(ty);
			vbo.size++;

		}
		myfile.close();

		auto entry = models->figures.find(file);

		if (entry == models->figures.end()) {

			vbo.index = models->n_buffers;

			models->buffers.push_back(0);
			models->normals.push_back(0);
			models->textCoords.push_back(0);

			models->figures.insert(std::pair<string, VBO>(file, vbo));

			initBuffers(models, vbo, lstPts, lstNrms, lstTxts);
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

			if (name.compare(TRANSLATE) == 0) {

				if (element->Attribute(TIME)) {

					float time = atof(element->Attribute(TIME));

					AnimatedTranslation * at = new AnimatedTranslation(time);

					cout << "TIME: " << time << endl;

					for (auto crawlPoint = element->FirstChildElement(POINT);
							crawlPoint != nullptr;
							crawlPoint = crawlPoint->NextSiblingElement(
							POINT)) {

						x = (crawlPoint->Attribute(X)) ?
								atof(crawlPoint->Attribute(X)) : 0;
						y = (crawlPoint->Attribute(Y)) ?
								atof(crawlPoint->Attribute(Y)) : 0;
						z = (crawlPoint->Attribute(Z)) ?
								atof(crawlPoint->Attribute(Z)) : 0;

						cout << "X: " << x << "Y: " << y << "Z: " << z << endl;

						at->addPointCoords(x, y, z);

					}
					group->transformations.push_back(at);

				} else {

					x = (element->Attribute(X)) ?
							atof(element->Attribute(X)) : 0;
					y = (element->Attribute(Y)) ?
							atof(element->Attribute(Y)) : 0;
					z = (element->Attribute(Z)) ?
							atof(element->Attribute(Z)) : 0;

					/**
					 * Criar Translação
					 */
					Translation * t = new Translation(x, y, z);

					group->transformations.push_back(t);

				}

			} else {

				x = (element->Attribute(X)) ? atof(element->Attribute(X)) : 0;
				y = (element->Attribute(Y)) ? atof(element->Attribute(Y)) : 0;
				z = (element->Attribute(Z)) ? atof(element->Attribute(Z)) : 0;
				/**
				 * Criar Escala
				 */
				Scale * s = new Scale(x, y, z);

				group->transformations.push_back(s);

			}

		} else if (name.compare(ROTATE) == 0) {
			float axis_x, axis_y, axis_z, angle;

			if (element->Attribute(TIME)) {

				float time = atof(element->Attribute(TIME));

				axis_x =
						(element->Attribute(AXIS_X)) ?
								atof(element->Attribute(AXIS_X)) : 0;
				axis_y =
						(element->Attribute(AXIS_Y)) ?
								atof(element->Attribute(AXIS_Y)) : 0;
				axis_z =
						(element->Attribute(AXIS_Z)) ?
								atof(element->Attribute(AXIS_Z)) : 0;

				AnimatedRotation *ar = new AnimatedRotation(time, axis_x,
						axis_y, axis_z);
				group->transformations.push_back(ar);

			} else {

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
			}

		} else if (name.compare(MODELS) == 0) {

			/**
			 * Iterar sobre os ficheiros de modelos
			 */

			//TODO: Adicionar elementos para texturas e materiais
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

