#include "GameLibrary.h"
#include "GameLibraryElements.h"
#include <boost/make_shared.hpp>

namespace gamelibrary
{
	GameLibrary::GameLibrary(rapidxml::xml_node<>* node, const std::string& name)
		: XMLNodeBase(node, XMLNodeBase::spXMLNode(), name)
	{
	}

	void GameLibrary::Load(XMLNodeBase::spXMLNode &me)
	{
		assert(isValid());
		assert(!hasParent());			// Root so no parent
		if (!isValid())
		{
			spGameName = boost::make_shared<GameName>(GameName(me));
			spGameLevel = boost::make_shared<GameLevel>(GameLevel(me));
			spDMName = boost::make_shared<DMName>(DMName(me));
		}
	}
}