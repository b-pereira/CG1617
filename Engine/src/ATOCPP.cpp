//============================================================================
// Name        : ATOCPP.cpp
// Author      : Bruno Pereira
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

int main() {


	XMLDocument doc;
	doc.LoadFile("resources/scene.xml");

	// Structure of the XML file:
	// - Element "PLAY"      the root Element, which is the
	//                       FirstChildElement of the Document
	// - - Element "TITLE"   child of the root PLAY Element
	// - - - Text            child of the TITLE Element

	// Navigate to the title, using the convenience function,
	// with a dangerous lack of error checking

	XMLElement* textNode = doc.FirstChildElement( "scene" )->FirstChildElement( "model");
	cout << "Name of play (2):"<< textNode->FirstAttribute()->Value()<< endl;
	cout << "Name of play (3):"<< textNode->NextSiblingElement("model")->FirstAttribute()->Value()<< endl;
	const char* title;
	//title = textNode->NextSibling();



string s = "kfjglafja";



	return 0;
}
