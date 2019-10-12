#pragma once
#include "iItem.h"
#include <rapidxml/rapidxml.hpp>
#include <string>

class cItem_Common : public iItem
{
public:
	cItem_Common(	std::string id,
					std::string path,
					rapidxml::xml_node<>* parent,
					std::size_t index);

	virtual ~cItem_Common();
	const std::string& GetAssetID() const;
	const std::string& GetRelativeName() const;
	rapidxml::xml_node<>* GetParent() const;
	bool IsXMLValid() const;
	std::size_t GetIndex() const;
	bool GetExists() const;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cItem_Common& val);
protected :
	cItem_Common();
private:
	std::string m_id;
	std::string m_path;
	bool m_exits;
	// Point to original XML parent node and Index
	rapidxml::xml_node<>* m_parent;		// Offset into the asset tree so we can add properties to it
	std::size_t m_index;

};

