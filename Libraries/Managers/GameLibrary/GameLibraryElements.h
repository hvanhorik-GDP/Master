#pragma once
#include "XML/XMLNodeBase.h"
#include <string>

namespace gamelibrary
{
	class GameLevel : public XMLNodeBase
	{
	public:
		GameLevel(const XMLNodeBase& parent)
		: XMLNodeBase(parent) {}
		virtual const std::string& GetName() const { return gName; };

	private:
		static const std::string gName;
	};

	class DMName : public XMLNodeBase
	{
	public:
		DMName(const XMLNodeBase& parent)
			: XMLNodeBase(parent) {}
		virtual const std::string& GetName() const { return gName; };

	private:
		static const std::string gName;
	};

}

