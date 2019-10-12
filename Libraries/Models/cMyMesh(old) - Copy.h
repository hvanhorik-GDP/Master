#ifndef _cMyMesh_HG_
#define _cMyMesh_HG_

#include <vector>		// "smart array"


class cMyMesh
{
public:
	cMyMesh() {};			// Empty c'tor
	~cMyMesh() {};		// Empty d'tor
	// Store the vertices

	std::vector<sPlyVertexXYZ> m_vecVertices;

	// Store the triangles
	std::vector<sPlyTriangle> m_vecTriangles;

	struct property
	{
		std::string type;
		std::string name;
	};
//	typedef std::pair <std::string, std::string> property;

	bool m_hasNormals = false;
	bool m_hasColor = false;
	bool m_isValid = false;
	bool m_fileExists = false;
	std::string m_type;
	std::string m_format;
	unsigned int m_vertices = 0;
	unsigned int m_faces = 0;
	std::vector< cMyMesh::property > m_vecProperties;
};

#endif 
