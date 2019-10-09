#pragma once
#include <string>	

#include "cMyMesh.h"

#pragma comment (lib, "Models.lib")

class cPlyLoader
{
public:
	cPlyLoader();			// constructor
	~cPlyLoader();		// destructor

	// Takes the filename to load
	// Returns by ref the mesh
	bool LoadPlyModel(const std::string& filename,
		cMyMesh& theMesh);

	// Just read the header to see if it is valid
	bool LoadPlyModelInfo(const std::string& filename,
		cMyMesh& theMesh);
};

