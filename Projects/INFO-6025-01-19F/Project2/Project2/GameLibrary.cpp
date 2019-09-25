#include "GameLibrary.h"
#include "GameLibraryElements.h"
#include <boost/make_shared.hpp>

namespace gamelibrary
{
	const std::string GameLibrary::gName = "GameLibrary";

	GameLibrary::GameLibrary()
		: XMLNodeBase()
	{
	}

	GameLibrary::GameLibrary(rapidxml::xml_node<>* node)
		: XMLNodeBase(node)
	{
	}

	GameName GameLibrary::GetGameName()
	{
		assert(isValid());
		return GameName(GetNode());
	}
	GameLevel GameLibrary::GetGameLevel()
	{
		assert(isValid());
		return GameLevel(GetNode());
	}

	DMName GameLibrary::GetDMName()
	{
		assert(isValid());
		return DMName(GetNode());
	}
}