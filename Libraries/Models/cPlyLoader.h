#pragma once
#include <string>	
#include <istream>

#include "AssetItems/cItem_Model.h"

#pragma comment (lib, "Models.lib")

class cPlyLoader
{
public:
	cPlyLoader();			// constructor
	~cPlyLoader();		// destructor

	// Takes the filename to load
	// Returns by ref the mesh
	bool LoadPlyModel(const std::string& filename,
		cItem_Model& theMesh);

	// Just read the header to see if it is valid
	bool LoadPlyModelInfo(const std::string& filename,
		cItem_Model& theMesh);
private:
	bool LoadThePlyHeader(std::istream& theFile, cItem_Model& theMesh);
	bool LoadThePlyBody(std::istream& theFile, cItem_Model& theMesh);
};

