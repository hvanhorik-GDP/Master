#include "iObject_Physics.h"
#include "iObject.h"

std::ostream& operator<<(std::ostream& stream, const iObject_Physics& val)
{
	stream << "Got to iAssetManager:iObject_Physicss by accident" << std::endl;
	return stream;
}

iObject_Physics* iObject_Physics::GetPhysicsInterface(iObject* in)
{
	return dynamic_cast<iObject_Physics*>(in);
}

bool iObject_Physics::HasPhysicsInterface(iObject* in)
{
	return (GetPhysicsInterface(in) != NULL);
}
