#pragma once
#include "iObject.h"
#include "AssetItems/cItem_Common.h"
#include <rapidxml/rapidxml.hpp>
#include <glm/glm.hpp>

#include <string>
#include <vector>


class cObject_Common : public iObject
{
public:
	cObject_Common( const std::string &type,
					const std::string &name,
					const std::string &asset_id,
					rapidxml::xml_node<>* node);

	virtual ~cObject_Common();

	// Information about the object
	virtual const std::string& GetType() const final;
	const std::string& GetName() const;
	const std::string& GetAssetID() const;

	// XML stuff
	rapidxml::xml_node<>* GetNode() const;
	void SetNode(rapidxml::xml_node<>* in);
	bool IsXMLValid() const;
	std::size_t GetIndex() const;

	cItem_Common* GetItem(); 

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Common& val);

protected :
	cObject_Common();
	std::string m_type;
	std::string m_name;
	std::string m_assetID;

// Point to original XML parent node and Index
	rapidxml::xml_node<>* m_node;		// Offset into the asset tree so we can add properties to it

	//Points to the actual item (NULL if no physical representation)
	cItem_Common* m_Item;
};

