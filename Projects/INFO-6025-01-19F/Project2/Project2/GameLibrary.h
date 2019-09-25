#pragma once
#include "XMLNodeBase.h"
#include "XMLNodeSingleBase.h"
#include "GameLibraryElements.h"

namespace gamelibrary
{

	class GameLibrary :
		public XMLNodeBase
	{
	public:
		GameLibrary();
		virtual ~GameLibrary() final {}
		GameLibrary(rapidxml::xml_node<>* node);
		GameName GetGameName();
		GameLevel GetGameLevel();
		DMName GetDMName();
		virtual const std::string& GetName() const { return gName; };

	private:
		static const std::string gName;
	};
}


