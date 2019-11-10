#pragma once

#include "MessageManager/iMessageInterface.h"
#include "iObject_Common.h"

#include <rapidxml/rapidxml.hpp>
#include <glm/glm.hpp>

#include <string>
#include <vector>

class iItem;

class cObject_Common : public iObject_Common , public iMessageInterface
{
public:
	cObject_Common();

	virtual ~cObject_Common();

	void LoadCommon( const std::string& type,
					 const std::string& name,
					 const std::string& asset_id,
					 rapidxml::xml_node<>* node);

	// objects can clone themselves (We don't do it)
	void Copy_iObject_Common(const iObject_Common& from);

	// From iObject_Common
	// Information about the object
	virtual const std::string& GetType() const final;
	virtual const std::string& GetName() const final;
	virtual const std::string& GetAssetID() const final;

	virtual bool IsVisable() const final;
	virtual bool IsObjectLocked() const final;

	// returns a pointer to any Asset Item that is associated with this object
	virtual iItem* GetItem() const final;

	// The objects parent group (if any)
	virtual iObject* GetParentObject() const final;

	// Raw XML - Get the root node and check for validity
	virtual bool IsXMLValid() const final;
	virtual rapidxml::xml_node<>* GetNode() const final;

	virtual void SetParentObject(iObject* in) final;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cObject_Common& val);

	//TODO - Remove and move to classes that require them
	// from iMessageInterface
	// Everyone has a universal ID
	virtual const std::string& GetMyUID() const final;

	//TODO - for now just implement them here.
	// need to implement them in every class of iObject
	// Recieve a message
	virtual bool RecieveMessage(const iMessage& message) = 0;

	// Recieve a message and reply
	virtual bool RecieveAndRespond(const iMessage& in, iMessage& reply) = 0;

//hack protected:
	// Should this be removed and just allow inheritance to handle it
	virtual void SetNode(rapidxml::xml_node<>* in);
	virtual void SetVisable(bool to) final;

public:			// TODO - hack
	friend class cObjectManagerPart_Common;
	std::string m_type;
	std::string m_name;
	std::string m_assetID;
	bool m_isVisable = true;
	bool m_isObjectLocked = false;
	bool m_isAClone = false;

	// Point to original XML parent node and Index
	rapidxml::xml_node<>* m_node;
	iItem* m_Item;
	iObject* m_ParentObject;
};
