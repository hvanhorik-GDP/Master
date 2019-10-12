#include "GameLibrary.h"
#include "XML/XMLIndent.h"
#include <iostream>


namespace gamelibrary
{
	const std::string GameName::gName = "GameName";
	const std::string GameLibrary::gName = "GameLibrary";

	std::ostream& operator << (std::ostream& out, const GameLibrary& node)
	{
		using namespace std;
		if (node.isValid())
		{
			out << "<" << node.GetNodeName() << ">" << endl;
			out << node.GetNodeName() << ">" << endl;
			out << XMLIndent(1) << node.GetGameName() << endl;
			out << node.GetAssetGroups();
			out << "</" << node.GetNodeName() << ">" << endl;
		}
		return out;
	}

	Objects GameLibrary::GetObjects() const 
	{ 
		auto node = GetNode()->first_node("Objects");
		return Objects(node);
	}

}