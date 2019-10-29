#pragma once
#include "cItem_Common.h"

#include <vector>

class cItem_Model : public cItem_Common 
{
public:
	// This structure matches the file, so that our life is
	//   simpler and happier, and we all get along.

	struct sPlyVertexXYZ
	{
		float x, y, z;
		float nx, ny, nz;		// NOW with NORMALS!!
		unsigned char red, green, blue, alpha;
	};

	struct sPlyTriangle
	{
		unsigned int vert_index_1;
		unsigned int vert_index_2;
		unsigned int vert_index_3;
	};

	cItem_Model() {};				// Get's filled in by physics

	cItem_Model(std::string id,
		std::string path,
		rapidxml::xml_node<>* parent,
		std::size_t index);
	virtual ~cItem_Model();
	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cItem_Model& val);

public:			// TODO - hack

	// Store the verticies
	std::vector<cItem_Model::sPlyVertexXYZ> m_vecVertices;
	// Store the triangles
	std::vector<cItem_Model::sPlyTriangle> m_vecTriangles;

	// Store the properties
	struct property
	{
		std::string type;
		std::string name;
	};

	bool m_hasNormals = false;
	bool m_hasColor = false;
	bool m_isValid = false;
	bool m_fileExists = false;
	std::string m_type;
	std::string m_format;
	unsigned int m_vertices = 0;
	unsigned int m_faces = 0;
	std::vector< cItem_Model::property > m_vecProperties;

	friend class cAssetManager_Models;
	friend class cPlyLoader;
	friend class cVAOManager_impl;
	friend class cPhysics;
	friend class cPhysics_Henky;
};

