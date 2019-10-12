#pragma once

#include "XML/XMLNewNodeBase.h"
#include "XML/XMLAttribute.h"

namespace gamelibrary
{

	//<Object type = "light" name = "spotlight" id = "foo2">

	class Object_name : public XMLAttribute
	{
	public:
		Object_name() {};
		virtual ~Object_name() final {}
		Object_name(rapidxml::xml_node<>* node) : XMLAttribute(node) {}
		virtual const std::string& GetName() const { return gName; };

	private:
		static const std::string gName;
	};

	class Object_type : public XMLAttribute
	{
	public:
		Object_type() {};
		virtual ~Object_type() final {}
		Object_type(rapidxml::xml_node<>* node) : XMLAttribute(node) {}
		virtual const std::string& GetName() const { return gName; };

	private:
		static const std::string gName;
	};

	class Object_asset_id : public XMLAttribute
	{
	public:
		Object_asset_id() {};
		virtual ~Object_asset_id() final {}
		Object_asset_id(rapidxml::xml_node<>* node) : XMLAttribute(node) {}
		virtual const std::string& GetName() const { return gName; };

	private:
		static const std::string gName;
	};


	class Object : public XMLNewNodeBase
	{
	public:
		Object(rapidxml::xml_node<>* node)
			: XMLNewNodeBase(node) {}
		Object() : XMLNewNodeBase() {}
		virtual ~Object() final {}
		void AddProperty(
			const std::string& newname,
			const std::string& newtype,
			const std::string& newvalue);
		friend std::ostream& operator << (std::ostream& out, const Object& node);

	protected:
		virtual const std::string& GetName() const { return gName; };
	private:
		static const std::string gName;
	};

}
