#include "Patterns_MidTerm_2019_ObjectCreator.h"


#include "AssetItems/cItem_Model.h"
#include "Physics/cPhysics_Henky.h"
#include "ObjectItems/cObject_Group.h"

#include <cstdlib>
#include <time.h>

static void highPointOfbox(glm::vec3& min, glm::vec3& max)
{
	auto temp = cObjectManager().FindObjectByName("low_cube");
	cObject_Model* cubeObject = dynamic_cast<cObject_Model*>(temp);
	assert(cubeObject);
	cPhysics_Henky::boundsOfObject(*cubeObject, min, max);
}

static void CreateBases(int number_high, int number_low)
{

	std::vector<std::string> surfaces;
	surfaces.push_back("surface_output_01");
	surfaces.push_back("surface_output_02");
	surfaces.push_back("surface_output_03");
	surfaces.push_back("surface_output_04");

	cObjectManager objectManager();
	for (auto surface : surfaces)
	{
		glm::vec3 min;
		glm::vec3 max;
		auto temp = cObjectManager().FindObjectByName(surface);
		cObject_Model* cubeObject = dynamic_cast<cObject_Model*>(temp);
		assert(cubeObject);
		cPhysics_Henky::boundsOfObject(*cubeObject, min, max);
	}
}

static float gMaxHeightOfPyramid = 0.0f;

void Patterns_MidTerm_2019_CreatePyramids(int number, cObjectManager& objectManager, rapidxml::xml_node<>* parent)
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
	temp = objectManager.FindObjectByName(name);
	cObject_Model* pyramid_a = dynamic_cast<cObject_Model*>(temp);


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

		float newscale = float((rand()) % 40 + 30);
		newscale /= 120;
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

void Patterns_MidTerm_2019_CreateDropBalls(int number, cObjectManager& objectManager, rapidxml::xml_node<>* parent)
{
	srand(unsigned int(time(NULL)));


	// Make a bunch of balls
	std::string name = "Drop_Sphere";
	auto dropBall = objectManager.FindObjectByName(name);
	assert(dropBall);

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

		//TODO - HACK - turn off scale
		newBall->scale = 1.0;// float(newscale);
		newBall->SPHERE_radius = 1.0;// = float(newscale);
		objectManager.SaveObject(newBall, parent);
	}
}

void Patterns_MidTerm_2019_CloneObject(int number, const std::string& name, rapidxml::xml_node<>* parent)
{
	srand(unsigned int(time(NULL)));
	cObjectManager objectManager;

	auto object = objectManager.FindObjectByName(name);
	for (int i = 0; i < number; ++i)
	{
		std::string newName = name + "_" + std::to_string(i);
		auto temp = object->Clone(newName);
		assert(temp);
		objectManager.SaveObject(temp, parent);
	}
}
