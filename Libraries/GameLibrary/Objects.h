#pragma once
#include "XML/XMLNewNodeBase.h"

namespace gamelibrary
{
	class Objects : public XMLNewNodeBase
	{
	public:
		Objects(rapidxml::xml_node<>* node)
			: XMLNewNodeBase(node) {}
		Objects() : XMLNewNodeBase() {}
		virtual ~Objects() final {}
		friend std::ostream& operator << (std::ostream& out, const Objects& node);

		virtual const std::string& GetName() const { return gName; };
	private:
		static const std::string gName;
	};

}