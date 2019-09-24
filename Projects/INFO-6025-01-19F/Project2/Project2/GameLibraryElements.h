#pragma once
#include "XMLNodeSingleBase.h"
#include <string>

namespace gamelibrary
{
	class GameName : public XMLNodeSingleBase
	{
	public:
		GameName() : XMLNodeSingleBase() {}
		GameName(spXMLNode& parent)
			: XMLNodeSingleBase(parent, GetName()) {}
	private:
		const std::string GetName() { return std::string("GameName"); }
	};

	class GameLevel : public XMLNodeSingleBase
	{
	public:
		GameLevel() : XMLNodeSingleBase() {}
		GameLevel(spXMLNode& parent)
			: XMLNodeSingleBase(parent, GetName()) {}
	private:
		const std::string GetName() { return std::string("GameLevel"); }
	};

	class DMName : public XMLNodeSingleBase
	{
	public:
		DMName() : XMLNodeSingleBase() {}
		DMName(spXMLNode& parent)
			: XMLNodeSingleBase(parent, GetName()) {}
	private:
		const std::string GetName() { return std::string("DMName"); }
	};

}

