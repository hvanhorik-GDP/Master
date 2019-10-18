#include "ObjectCreator.h"

#include "Common/pFindObjectByFriendlyName.h"
#include "AssetItems/cItem_Model.h"
#include "Physics/cPhysics_Henky.h"
#include "ObjectItems/cObject_Group.h"

#include <cstdlib>
#include <time.h>

void highPointOfbox(glm::vec3& min, glm::vec3& max)
{
	// Make a bunch of pyramids
	auto cubeObject = pFindObjectByFriendlyName("low_cube");
	assert(cubeObject);
	cPhysics_Henky::boundsOfObject(*cubeObject, min, max);
}

float gMaxHeightOfPyramid = 0.0f;

void CreatePyramids(int number, cObjectManager& objectManager, rapidxml::xml_node<>* parent)
{
	srand(unsigned int(time(NULL)));

	iObject* temp = objectManager.FindObjectByName("ground_plane");
	assert(temp);
	cObject_Group* groundGroup = dynamic_cast<cObject_Group*> (temp);
	assert(groundGroup);

	// See where to place the pyrmids
	glm::vec3 minBox;
	glm::vec3 maxBox;
	highPointOfbox(minBox, maxBox);
	float surface = maxBox.y;

	// Make a bunch of pyramids
	std::string name = "pyramid_a";
	auto pyramid_a = pFindObjectByFriendlyName(name);


	// How big is the pyramid
	glm::vec3 minPyramid;
	glm::vec3 maxPyramid;
	cPhysics_Henky::boundsOfObject(*pyramid_a, minPyramid, maxPyramid);
	float pyramidHeight = maxPyramid.y;

	for (int i = 0; i < number; ++i)
	{
		std::string newName = name + "_" + std::to_string(i);
		auto temp = pyramid_a->Clone(newName);
		assert(temp);
		cObject_Model* newPyramid = dynamic_cast<cObject_Model*>(temp);
		assert(newPyramid);

		float newscale = float((rand()) % 100 + 1);
		newscale /= 90;
		newPyramid->scale = newscale;
		if (pyramidHeight * newscale > gMaxHeightOfPyramid)
			gMaxHeightOfPyramid = pyramidHeight * newscale;
		{
			int min = 50;
			int max = 255;
			int r = rand() % (max - min) + min;
			int g = rand() % (max - min) + min;
			int b = rand() % (max - min) + min;
			glm::vec4 rgb = glm::vec4(float(r) / max, float(g) / max, float(b) / max, 1);
			newPyramid->objectColourRGBA = rgb;
		}
		{
			int minx = ceil(minBox.x) + ceil(newscale * maxPyramid.x);
			int maxx = floor(maxBox.x) + ceil(newscale * minPyramid.x);
			int minz = ceil(minBox.z) + ceil(newscale * maxPyramid.z);
			int maxz = floor(maxBox.z) + ceil(newscale * minPyramid.z);
			int x = rand() % (maxx - minx) + minx;
			int y = surface;
			int z = rand() % (maxz - minz) + minz;
			glm::vec3 pos = glm::vec3(float(x), float(y), float(z));
			newPyramid->positionXYZ = pos;
		}
		newPyramid->SetVisable(true);

		// Save the object to the object array
		objectManager.SaveObject(newPyramid, parent);

		// parent/child pointers
		newPyramid->SetParentObject(groundGroup);
		groundGroup->AddChildObject(newPyramid);
	}
}

void CreateDropBalls(int number, cObjectManager& objectManager, rapidxml::xml_node<>* parent)
{
	srand(unsigned int(time(NULL)));


	// Make a bunch of balls
	auto dropBall = pFindObjectByFriendlyName("Drop_Sphere");
	std::string name = "Drop_Ball";

	for (int i = 0; i < number; ++i)
	{
		std::string newName = name + "_" + std::to_string(i);
		auto temp = dropBall->Clone(newName);
		assert(temp);
		cObject_Model* newBall = dynamic_cast<cObject_Model*>(temp);
		assert(newBall);
		// Add in but don't do the XML
		{
			int min = 50;
			int max = 255;
			int r = rand() % (max - min) + min;
			int g = rand() % (max - min) + min;
			int b = rand() % (max - min) + min;
			glm::vec4 rgb = glm::vec4(float(r) / max, float(g) / max, float(b) / max, 1);
			newBall->objectColourRGBA = rgb;
		}
		{
			int min = -50;
			int max = 50;
			int x = rand() % (max - min) + min;
			int y = rand() % 50 + gMaxHeightOfPyramid;		// Minimum 50 above pyramid
			int z = rand() % (max - min) + min;
			glm::vec3 pos = glm::vec3(float(x), float(y), float(z));
			newBall->positionXYZ = pos;
		}
		int newscale = rand() % 5;
		newBall->scale = float(newscale);
		newBall->SPHERE_radius = float(newscale);
		objectManager.SaveObject(newBall, parent);
	}
}
