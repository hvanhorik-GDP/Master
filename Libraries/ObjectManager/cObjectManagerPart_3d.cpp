#include "cObjectManagerPart_3d.h"
#include "ObjectItems/cObject_3d.h"
#include "GameLibrary/Object.h"
#include "Utilities/cFormat.h"

#include <cassert>

cObjectManagerPart_3d::cObjectManagerPart_3d()
{
}

cObjectManagerPart_3d::~cObjectManagerPart_3d()
{
}

bool cObjectManagerPart_3d::HandleProperty(iObject* object,
	const std::string& type,
	const std::string& name,
	const std::string& value)
{
	cObject_3d* d3 = dynamic_cast<cObject_3d*>(object);
	assert(d3);
	if (name == "positionXYZ")
		d3->positionXYZ = cFormat::LoadVec3(value);
	else if (name == "rotationXYZ")
		d3->rotationXYZ = cFormat::LoadVec3(value);
	else if (name == "scale")
		d3->scale = cFormat::LoadFloat(value);
	else
		return false;
	return true;
}

// Saves all of the properties to the xml file
void cObjectManagerPart_3d::SaveProperties(iObject* object,
	rapidxml::xml_node<>* node)
{
	cObject_3d* d3 = dynamic_cast<cObject_3d*>(object);
	assert(d3);
	gamelibrary::Object libObject(node);

	libObject.AddProperty("positionXYZ", "vec3", cFormat::PackVec3(d3->positionXYZ));
	libObject.AddProperty("rotationXYZ", "vec3", cFormat::PackVec3(d3->rotationXYZ));
	libObject.AddProperty("scale", "float", cFormat::PackFloat(d3->scale));
}

// We need this dummy operator in case classes don't override this method.
std::ostream& operator<<(std::ostream& stream, const cObjectManagerPart_3d& val)
{
	stream << "Got to cObjectManagerPart_3d by accident" << std::endl;
	return stream;
}
