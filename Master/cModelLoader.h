#pragma once

#include <string>	

#include "cMesh.h"

class cModelLoader
{
public:
	cModelLoader();			// constructor
	~cModelLoader();		// destructor

	// Takes the filename to load
	// Returns by ref the mesh
	bool LoadPlyModel(std::string filename,
		cMesh& theMesh);		// Note the & (by reference)

};
