#pragma once

#include "../Libraries/ObjectManager/cObjectManager.h"
#include "rapidxml/rapidxml.hpp"

void CreatePyramids(int number, cObjectManager& objectManager, rapidxml::xml_node<>* parent);
void CreateDropBalls (int number, cObjectManager& objectManager, rapidxml::xml_node<>* parent);
