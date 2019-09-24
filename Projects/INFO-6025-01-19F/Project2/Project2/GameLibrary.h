#pragma once
#include "XMLNodeBase.h"
#include "XMLNodeSingleBase.h"

namespace gamelibrary
{
	class GameName;
	class GameLevel;
	class DMName;

	class GameLibrary :
		public XMLNodeBase
	{
	public:
		GameLibrary();
		virtual ~GameLibrary() final {}
		GameLibrary(rapidxml::xml_node<>* node, const std::string& name);
		virtual void Load(XMLNodeBase::spXMLNode &me) final;

	private:
		boost::shared_ptr<GameName> spGameName;
		boost::shared_ptr<GameLevel> spGameLevel;
		boost::shared_ptr<DMName> spDMName;
	};
}


