#include "cObject_Model.h"

cObject_Model::cObject_Model(const std::string& type,
	const std::string& name,
	const std::string& asset_id,
	rapidxml::xml_node<>* node)
	: cObject_Common(type, name, asset_id, node)
{
	matWorld = glm::mat4(1.0f);
}

cObject_Model::~cObject_Model()
{
}

void cObject_Model::IntegrationStep(float deltaTime)
{

	// Forward Explicit Euler Inetegration
	//NewVelocty += Velocity + ( Ax * DeltaTime )

	// 
//	accel = this->m_Gravity;

	velocity.x += accel.x * deltaTime;
	velocity.y += accel.y * deltaTime;
	velocity.z += accel.z * deltaTime;
	//		// Or you can do this...
	//		CurObj.velocity += CurObj.accel * deltaTime;

			//NewPosition = Posistion + ( Vx * DeltaTime )

	positionXYZ.x += velocity.x * deltaTime;
	positionXYZ.y += velocity.y * deltaTime;
	positionXYZ.z += velocity.z * deltaTime;

	// See if we fell off the map
	if (positionXYZ.y < -50.0f)
	{
		{
			int min = 50;
			int max = 255;
			int r = rand() % (max - min) + min;
			int g = rand() % (max - min) + min;
			int b = rand() % (max - min) + min;
			glm::vec4 rgb = glm::vec4(float(r) / max, float(g) / max, float(b) / max, 1);
			objectColourRGBA = rgb;
		}
		{
			int min = -5;
			int max = 5;
			int x = rand() % (max - min) + min;
			int y = rand() % (50) + 20;
			int z = rand() % (max - min) + min;
			glm::vec3 pos = glm::vec3(float(x), float(y), float(z));
			positionXYZ = pos;
		}
		velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		accel = glm::vec3(0.0f, 0.0f, 0.0f);
		int newscale = rand() % 5;
		scale = float(newscale);
		SPHERE_radius = float(newscale);
	}
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Model& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Model& val)" << "Not Implemented" << std::endl;
	return stream;
}

std::string cObject_Model::ShapeTypeToString(cObject_Model::eShapeTypes in)
{
	switch (in)
	{
	case eShapeTypes::AABB:
		return "AABB";
	case eShapeTypes::CAPSULE:
		return "CAPSULE";
	case eShapeTypes::MESH:
		return "MESH";
	case eShapeTypes::PLANE:
		return "PLANE";
	case eShapeTypes::SPHERE:
		return "SPHERE";
	}
	return "UNKNOWN";
}
cObject_Model::eShapeTypes cObject_Model::StringToShapeType(std::string& in)
{
	if (in == "AABB")
		return eShapeTypes::AABB;
	if (in == "CAPSULE")
		return eShapeTypes::CAPSULE;
	if (in == "MESH")
		return eShapeTypes::MESH;
	if (in == "PLANE")
		return eShapeTypes::PLANE;
	if (in == "SPHERE")
		return eShapeTypes::SPHERE;
	return eShapeTypes::UNKNOWN;
}

iObject* cObject_Model::Clone(const std::string& newName)
{
	// Copy everything and change the name
	cObject_Model* ret =
		new cObject_Model(*this);
	ret->m_name = newName;
	ret->m_node = NULL;			// No XML so it won't update
	return ret;
}

