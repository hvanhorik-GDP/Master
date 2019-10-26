#include "cObject_Alias.h"
#include "iObject.h"

#include <cassert>


cObject_Alias::cObject_Alias()
{
}

cObject_Alias::~cObject_Alias()
{
}

void Copy_iObject_Alias(const iObject_Alias& from)
{
	// TODO - finish this off
	assert(false);
}

void cObject_Alias::AddChildObject(iObject* child)
{
	m_mapObjects[child->GetName()] = child;
}

cObject_Alias::mapObjectsInAlias& cObject_Alias::GetObjectsInAlias()
{
	return m_mapObjects;
}

// For debugging purposes - dumps the contents in human readable form
std::ostream& operator<<(std::ostream& stream, const cObject_Alias& val)
{
	stream << "std::ostream& operator<<(std::ostream& stream, const cObject_Alias& val)" << "Not Implemented" << std::endl;
	return stream;
}

// TODO - Moved to new class

//
//bool cObject_Alias::RecieveMessage(const iMessage& message)
//{
//	rapidxml::xml_node<>* node = GetNode();
//	gamelibrary::Object libObject(GetNode());
//
//	std::string text = message.GetMessageString();
//	std::vector<std::string> tokens;
//	cFormat::Tokens(text, tokens, ", ");
//	assert(tokens.size() >= 2);
//	if (tokens[0] == "rotate")
//	{
//		int plane = cFormat::LoadInt(tokens[1]);
//		float value = cFormat::LoadFloat(tokens[2]);
//		rotationXYZ[plane] += value;
//		if (node)
//			libObject.AddProperty("rotationXYZ", "vec3", cFormat::PackVec3(rotationXYZ));
//
//		std::stringstream ssTitle;
//		ssTitle << std::fixed << std::setprecision(4)
//			<< "Alias : "
//			<< "Rotation: "
//			<< "Object: " << GetName().substr(0, 8)
//			<< " x: " << rotationXYZ.x
//			<< " y: " << rotationXYZ.y
//			<< " z: " << rotationXYZ.z;
//		glfwSetWindowTitle(window, ssTitle.str().c_str());
//
//	}
//	else if (tokens[0] == "move")
//	{
//		int plane = cFormat::LoadInt(tokens[1]);
//		float value = cFormat::LoadFloat(tokens[2]);
//		positionXYZ[plane] += value;
//		if (node)
//			libObject.AddProperty("positionXYZ", "vec3", cFormat::PackVec3(positionXYZ));
//
//		std::stringstream ssTitle;
//		ssTitle << std::fixed << std::setprecision(4)
//			<< "Alias : "
//			<< "Move: "
//			<< "Object: " << GetName().substr(0, 8)
//			<< " x: " << positionXYZ.x
//			<< " y: " << positionXYZ.y
//			<< " z: " << positionXYZ.z;
//		glfwSetWindowTitle(window, ssTitle.str().c_str());
//
//	}
//	else if (tokens[0] == "color")
//	{
//
//		std::cout << "cObject_Alias::RecieveMessage - color not supported" << std::endl;
//
//		std::stringstream ssTitle;
//		ssTitle << std::fixed << std::setprecision(4)
//			<< "Alias : "
//			<< "Color: "
//			<< "Object: " << GetName().substr(0, 8)
//			<< " c: " << "NOT supported";
//
//		glfwSetWindowTitle(window, ssTitle.str().c_str());
//	}
//	else if (tokens[0] == "scale")
//	{
//		float value = cFormat::LoadFloat(tokens[1]);
//		scale += value;
//		libObject.AddProperty("scale", "float", cFormat::PackFloat(scale));
//
//		std::stringstream ssTitle;
//		ssTitle << std::fixed << std::setprecision(4)
//			<< "Alias : "
//			<< "Scale: "
//			<< "Object: " << GetName().substr(0, 8)
//			<< " s: " << scale;
//		glfwSetWindowTitle(window, ssTitle.str().c_str());
//	}
//	else
//	{
//		std::cout << "cObject_Alias::RecieveMessage(): "
//			<< "Invalid Message command: " << tokens[0]
//			<< ", " << tokens[1]
//			<< ", " << tokens[2] << std::endl;
//		return false;
//	}
//	return true;
//}
//
//// Recieve a message and reply
//bool cObject_Alias::RecieveAndRespond(const iMessage& in, iMessage& reply)
//{
//	assert(false);			// Not implmented yet
//	return false;
//}
