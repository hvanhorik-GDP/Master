#include "cObjectManagerPart_Physics.h"
#include "ObjectItems/cObject_Physics.h"
#include "GameLibrary/Object.h"
#include "Utilities/cFormat.h"

cObjectManagerPart_Physics::cObjectManagerPart_Physics()
{

}

cObjectManagerPart_Physics::~cObjectManagerPart_Physics()
{

}

bool cObjectManagerPart_Physics::HandleProperty(iObject* object,
	const std::string& type,
	const std::string& name,
	const std::string& value)
{
	cObject_Physics* physics = dynamic_cast<cObject_Physics*>(object);
	assert(physics);
	// Should be in physics
	if (name == "bounce")
		physics->bounce = cFormat::LoadFloat(value);
	else if (name == "inverseMass")
		physics->inverseMass = cFormat::LoadFloat(value);
	else if (name == "physicsShapeType")
		physics->physicsShapeType = cObject_Physics::StringToShapeType(value);
	else if (name == "velocity")
		physics->velocity = cFormat::LoadVec3(value);
	else if (name == "accel")
		physics->acceleration = cFormat::LoadVec3(value);
	else if (name == "AABB_min")
		physics->AABB_min = cFormat::LoadVec3(value);
	else if (name == "AABB_max")
		physics->AABB_max = cFormat::LoadVec3(value);
	else if (name == "SPHERE_radius")
		physics->SPHERE_radius = cFormat::LoadFloat(value);
	else 
		return false;
	return true;
}

// Saves all of the properties to the xml file
void cObjectManagerPart_Physics::SaveProperties(iObject* object,
	rapidxml::xml_node<>* node)
{
	cObject_Physics* physics = dynamic_cast<cObject_Physics*>(object);
	assert(physics);
	gamelibrary::Object libObject(node);

	libObject.AddProperty("bounce", "float", cFormat::PackFloat(physics->bounce));
	libObject.AddProperty("inverseMass", "float", cFormat::PackFloat(physics->inverseMass));
	libObject.AddProperty("physicsShapeType", "vec3", cObject_Physics::ShapeTypeToString(physics->physicsShapeType));
	libObject.AddProperty("velocity", "vec3", cFormat::PackVec3(physics->velocity));
	libObject.AddProperty("accel", "vec3", cFormat::PackVec3(physics->acceleration));
	libObject.AddProperty("AABB_min", "vec3", cFormat::PackVec3(physics->AABB_min));
	libObject.AddProperty("AABB_max", "vec3", cFormat::PackVec3(physics->AABB_max));
	libObject.AddProperty("SPHERE_radius", "float", cFormat::PackFloat(physics->SPHERE_radius));
}

// We need this dummy operator in case classes don't override this method.
std::ostream& operator<<(std::ostream& stream, const cObjectManagerPart_Physics& val)
{
	stream << "Got to cObjectManagerPart_Physics by accident" << std::endl;
	return stream;
}
