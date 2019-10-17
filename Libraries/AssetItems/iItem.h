#pragma once
// A way to pass items around
#include <ostream>

#pragma comment (lib, "AssetItems.lib") 

class iItem
{
public:
	iItem() {};
	virtual ~iItem() {}

	virtual const std::string& GetAssetID() const = 0;
	virtual const std::string& GetAssetName() const = 0;
	virtual bool GetExists() const = 0;

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iItem& val);
};
