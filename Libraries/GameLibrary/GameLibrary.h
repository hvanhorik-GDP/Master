#pragma once
#include "./XML/XMLNodeBase.h"
#include "AssetGroups.h"
#include "Objects.h"
#include <ostream>

#pragma comment (lib, "GameLibrary.lib")


// INFO6044 - Gamelibrary wraps the XML so it can easly be replace in the future

namespace gamelibrary
{
	// elements of the GameLibrary
	class GameName : public XMLNodeBase
	{
	public:
		GameName(rapidxml::xml_node<>* parent) : XMLNodeBase(parent) {}
	protected:
		virtual const std::string& GetName() const { return gName; };
	private:
		static const std::string gName;
	};

	class GameLibrary : public XMLNodeBase
	{
	public:
		GameLibrary() : XMLNodeBase() {}
		virtual ~GameLibrary() final {}
		GameLibrary(rapidxml::xml_node<>* parent) : XMLNodeBase(parent) { }
		virtual const std::string& GetName() const { return gName; };
		friend std::ostream& operator << (std::ostream& out, const GameLibrary& node);

		// Methods for elements
		GameName GetGameName() const { return GameName(GetNode()); }
		AssetGroups GetAssetGroups() const { return AssetGroups(GetNode()); }
		Objects GetObjects() const;
	private:
		static const std::string gName;
	};


}


