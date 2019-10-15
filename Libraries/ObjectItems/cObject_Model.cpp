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
