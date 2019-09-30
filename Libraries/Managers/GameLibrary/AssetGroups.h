#pragma once
#include "XML/XMLArrayBase.h"
#include "XML/XMLAttribute.h"

namespace gamelibrary
{
	
	
	class GameAsset_subdir : public XMLAttribute
	{
	public:
		GameAsset_subdir() {};
		virtual ~GameAsset_subdir() final {}
		GameAsset_subdir(rapidxml::xml_node<>* node) : XMLAttribute(node) {};
		virtual const std::string& GetName() const { return gName; };

	private:
		static const std::string gName;
	};

	class GameAsset_subtype : public XMLAttribute
	{
	public:
		GameAsset_subtype() {};
		virtual ~GameAsset_subtype() final {}
		GameAsset_subtype(rapidxml::xml_node<>* node) : XMLAttribute(node) {};
		virtual const std::string& GetName() const { return gName; };

	private:
		static const std::string gName;
	};

	class GameAsset_type : public XMLAttribute
	{
	public:
		GameAsset_type() {};
		virtual ~GameAsset_type() final {}
		GameAsset_type(rapidxml::xml_node<>* node) : XMLAttribute(node) {};
		virtual const std::string& GetName() const { return gName; };

	private:
		static const std::string gName;
	};

	class GameAsset_open : public XMLAttribute
	{
	public:
		GameAsset_open() {};
		virtual ~GameAsset_open() final {}
		GameAsset_open(rapidxml::xml_node<>* node) : XMLAttribute(node) {}
		virtual const std::string& GetName() const { return gName; };

	private:
		static const std::string gName;
	};

	class AssetRoot : public XMLNodeBase
	{
	public:
		AssetRoot(rapidxml::xml_node<>* parent) : XMLNodeBase(parent) {}
	protected:
		virtual const std::string& GetName() const { return gName; };
	private:
		static const std::string gName;
	};

	class Assets_name : public XMLAttribute
	{
	public:
		Assets_name() {};
		virtual ~Assets_name() final {}
		Assets_name(rapidxml::xml_node<>* node) : XMLAttribute(node) {}
		virtual const std::string& GetName() const { return gName; };

	private:
		static const std::string gName;
	};

	class AssetFile : public XMLNodeBase
	{
	public:
		AssetFile(rapidxml::xml_node<>* parent) : XMLNodeBase(parent) {}
	protected:
		virtual const std::string& GetName() const { return gName; };
	private:
		static const std::string gName;
	};

	class Properties_type : public XMLAttribute
	{
	public:
		Properties_type() {};
		virtual ~Properties_type() final {}
		Properties_type(rapidxml::xml_node<>* node) : XMLAttribute(node) {}
		virtual const std::string& GetName() const { return gName; };

	private:
		static const std::string gName;
	};

	class Properties_value : public XMLAttribute
	{
	public:
		Properties_value() {};
		virtual ~Properties_value() final {}
		Properties_value(rapidxml::xml_node<>* node) : XMLAttribute(node) {}
		virtual const std::string& GetName() const { return gName; };

	private:
		static const std::string gName;
	};

	class Properties : public XMLArrayBase
	{
	public:
		Properties(rapidxml::xml_node<>* parent, std::size_t index = 0)
			: XMLArrayBase(parent, index) {}
		void AddProperty(const std::string& type, const std::string& value);
		friend std::ostream& operator << (std::ostream& out, const Properties& node);
	protected:
		virtual const std::string& GetName() const { return gName; };
	private:
		static const std::string gName;
	};

	class Assets : public XMLArrayBase
	{
	public:
		Assets(rapidxml::xml_node<>* parent, std::size_t index = 0)
			: XMLArrayBase(parent, index) {}
		friend std::ostream& operator << (std::ostream& out, const Assets& node);
		AssetFile GetAssetFile() const { return AssetFile(GetNode()); }
		Properties GetProperties() const { return Properties(GetNode()); }
	protected:
		virtual const std::string& GetName() const { return gName; };
	private:
		static const std::string gName;
	};

	class AssetGroups : public XMLArrayBase
	{
	public:
		AssetGroups(rapidxml::xml_node<>* parent, std::size_t index = 0)
			: XMLArrayBase(parent, index) {}
		AssetGroups() : XMLArrayBase() {}
		virtual ~AssetGroups() final {}
		friend std::ostream& operator << (std::ostream& out, const AssetGroups& node);

		AssetRoot GetAssetRoot() { return AssetRoot(GetNode()); }
		Assets GetAsset() { return Assets(GetNode()); }

	protected:
		virtual const std::string& GetName() const { return gName; };
	private:
		static const std::string gName;
	};


}
