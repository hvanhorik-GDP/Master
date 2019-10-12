#pragma once
#include "XMLNewNodeBase.h"
#include <string>

//
//class XMLArrayBase : public XMLNewNodeBase
//{
//public:
//	XMLArrayBase() {}
//	XMLArrayBase(rapidxml::xml_node<>* parent, size_t index = 0) 
//		: XMLNewNodeBase(parent)
//		, m_index(index) {}
//	virtual ~XMLArrayBase() {};
//	std::size_t GetSize() const;
//	void Insert();
//	virtual rapidxml::xml_node<>* GetNode() const;
//protected:
//	virtual const std::string& GetName() const { return gName; };
//private:
//	static const std::string gName;
//	std::size_t m_index;
//};
