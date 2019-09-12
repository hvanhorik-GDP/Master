#pragma once

#include "OpenGL.h"

// Will load the models and place them 
// into the vertex and index buffers to be drawn

#include <string>
#include <map>
#include "cMesh.h"				// File as loaded from the file

// The vertex structure 
//	that's ON THE GPU (eventually) 
// So dictated from THE SHADER
struct sVertex
{
	float x, y, z;
	float r, g, b;
};


struct sModelDrawInfo
{
	sModelDrawInfo();

	std::string meshName;

	unsigned int VAO_ID;

	unsigned int VertexBufferID;
	unsigned int VertexBuffer_Start_Index;
	unsigned int numberOfVertices;

	unsigned int IndexBufferID;
	unsigned int IndexBuffer_Start_Index;
	unsigned int numberOfIndices;
	unsigned int numberOfTriangles;

	// The "local" (i.e. "CPU side" temporary array)
	sVertex* pVertices;	//  = 0;
	// The index buffer (CPU side)
	unsigned int* pIndices;
};


class cVAOManager
{
public:

	// Takes a cMesh object and copies it into the GPU (as a VOA)
	bool LoadModelIntoVAO(std::string fileName,
		cMesh& theMesh,				// NEW
		sModelDrawInfo& drawInfo,
		unsigned int shaderProgramID);

	// We don't want to return an int, likely
	bool FindDrawInfoByModelName(std::string filename,
		sModelDrawInfo& drawInfo);

	std::string getLastError(bool bAndClear = true);

private:

	std::map< std::string /*model name*/,
		sModelDrawInfo /* info needed to draw*/ >
		m_map_ModelName_to_VAOID;

};

