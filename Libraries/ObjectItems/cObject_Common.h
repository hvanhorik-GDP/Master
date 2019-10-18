#pragma once
#include "iObject.h"
#include "../MessageManager/iMessageInterface.h"
#include <rapidxml/rapidxml.hpp>
#include <glm/glm.hpp>

#include <string>
#include <vector>

class iItem;

class cObject_Common : public iObject, public iMessageInterface
{
public:
	cObject_Common( const std::string &type,
					const std::string &name,
					const std::string &asset_id,
					rapidxml::xml_node<>* node);

	virtual ~cObject_Common();

	// From iObject
	// Information about the object
	virtual const std::string& GetType() const final;
	virtual const std::string& GetName() const final;
	virtual const std::string& GetAssetID() const final;
	virtual bool IsVisable() const final;
	virtual void SetVisable(bool to) final;

	virtual iObject* Clone(const std::string& newName) 
		{ assert(false); return NULL; }

	virtual iItem* GetItem() const final; 

	virtual iObject* GetParentObject() const final;
	virtual void SetParentObject(iObject* in) final;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Common& val);

	// from iMessageInterface
	// Everyone has a universal ID
	virtual const std::string& GetMyUID() const;

	//TODO - for now just implement them here.
	// need to implement them in every class of iObject
	// Recieve a message
	virtual bool RecieveMessage(const iMessage& message);

	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply);


protected:
	// XML stuff
	rapidxml::xml_node<>* GetNode() const;
	void SetNode(rapidxml::xml_node<>* in);
	bool IsXMLValid() const;

protected :
	cObject_Common();
	std::string m_type;
	std::string m_name;
	std::string m_assetID;
	bool m_isVisable = true;

// Point to original XML parent node and Index
	rapidxml::xml_node<>* m_node;		// Offset into the asset tree so we can add properties to it

	//Points to the actual item (NULL if no physical representation)
	iItem* m_Item;
	iObject* m_ParentObject;
};

