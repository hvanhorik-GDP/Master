#pragma once
#include <string>	

#include "cMesh_old.h"

#pragma comment (lib, "Models.lib")

class cModelLoader
{
public:
	cModelLoader();			// constructor
	~cModelLoader();		// destructor

	// Takes the filename to load
	// Returns by ref the mesh
	bool LoadPlyModel(const std::string &filename,
		              cMesh &theMesh);

	// Just read the header to see if it is valid
	bool LoadPlyModelInfo(const std::string &filename,
		cMesh& theMesh);
};

