#pragma once

#include "ObjectManager/cObjectManager.h"
#include "ObjectItems/cObject_Model.h"
#include "ObjectItems/cObject_Channel.h"
#include "rapidxml/rapidxml.hpp"

void CreatePyramids(int number, cObjectManager& objectManager, rapidxml::xml_node<>* parent);
void CreateDropBalls (int number, cObjectManager& objectManager, rapidxml::xml_node<>* parent);

void CloneObject(int number, const std::string &name, rapidxml::xml_node<>* parent);

cObject_Channel* FindObject(cObject_Model* model, const std::string& name);
