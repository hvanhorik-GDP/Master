#pragma once

#include "ObjectManager/cObjectManager.h"
#include "rapidxml/rapidxml.hpp"

void Physics_MidTerm_2019_CreatePyramids(int number, cObjectManager& objectManager, rapidxml::xml_node<>* parent);
void Physics_MidTerm_2019_CreateDropBalls (int number, cObjectManager& objectManager, rapidxml::xml_node<>* parent);

void Physics_MidTerm_2019_CloneObject(int number, const std::string &name, rapidxml::xml_node<>* parent);

void Physics_MidTerm_2019_CalculateBounds(rapidxml::xml_node<>* parent);

void Physics_MidTerm_2019_CreateNewAstroid(float deltatime, rapidxml::xml_node<>* parent);