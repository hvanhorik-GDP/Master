#pragma once

#include "../Libraries/ObjectManager/cObjectManager.h"
#include "rapidxml/rapidxml.hpp"

void Physics_Project_01_CreatePyramids(int number, cObjectManager& objectManager, rapidxml::xml_node<>* parent);
void Physics_Project_01_CreateDropBalls (int number, cObjectManager& objectManager, rapidxml::xml_node<>* parent);

void Physics_Project_01_CloneObject(int number, const std::string &name, rapidxml::xml_node<>* parent);
