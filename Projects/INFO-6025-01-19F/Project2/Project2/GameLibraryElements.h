#pragma once
#include "XMLNodeSingleBase.h"
#include <string>

namespace gamelibrary
{
	class GameName : public XMLNodeSingleBase
	{
	public:
		GameName(rapidxml::xml_node<>* parent)
			: XMLNodeSingleBase(parent) {}
		virtual const std::string& GetName() const { return gName; };
	private:
		static const std::string gName;
	};

	class GameLevel : public XMLNodeSingleBase
	{
	public:
		GameLevel(rapidxml::xml_node<>* parent)
		: XMLNodeSingleBase(parent) {}
		virtual const std::string& GetName() const { return gName; };

	private:
		static const std::string gName;
	};

	class DMName : public XMLNodeSingleBase
	{
	public:
		DMName(rapidxml::xml_node<>* parent)
			: XMLNodeSingleBase(parent) {}
		virtual const std::string& GetName() const { return gName; };

	private:
		static const std::string gName;
	};

}

