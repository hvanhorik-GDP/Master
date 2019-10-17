#pragma once

#include "cItem_Common.h"
#include <vector>

class cItem_Shader : public cItem_Common 
{
public:

	struct sPlyVertexXYZ
	{
		float x, y, z;
		float nx, ny, nz;		// NOW with NORMALS!!
		unsigned char red, green, blue, alpha;
	};

	typedef std::vector<sPlyVertexXYZ> vecPlyVerteciesXYZ;

	struct sPlyTriangle
	{
		unsigned int vert_index_1;
		unsigned int vert_index_2;
		unsigned int vert_index_3;
	};

	typedef std::vector<sPlyTriangle> vecPlyTriangles;

	enum type
	{
		unknown,
		vertex,
		fragment
	};

	cItem_Shader(std::string id,
		std::string path,
		rapidxml::xml_node<>* parent,
		std::size_t index);
	virtual ~cItem_Shader();

	std::string GetTypeString() const;
	cItem_Shader::type GetType() const;
	unsigned int GetID() const;
	
	const cItem_Shader::vecPlyVerteciesXYZ& GetPlyVerteciesXYZ() const;
	const cItem_Shader::vecPlyTriangles& GetPlyTriangles() const;
	bool HasNormals() const { return m_hasNormals; }
	bool HasColours() const { return m_hasColor;  }
	bool IsValid() const { return m_isValid; }
	unsigned int NumberVerticies() const { return m_vertices; }
	unsigned int NumberFaces() const { return m_faces; }
	const std::string& LastError() const { return m_error;  }

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const cItem_Shader& val);

private:
	cItem_Shader();				// Bad Consructor

	type m_shaderType = unknown;
	unsigned int m_ID = 0;
	std::vector<std::string> m_vecSource;
	bool m_valid = false;
	std::string m_error = "";

	// From cMesh
	vecPlyVerteciesXYZ m_vecVertices;
	vecPlyTriangles m_vecTriangles;

	bool m_hasNormals = false;
	bool m_hasColor = false;
	bool m_isValid = false;
	std::string m_type = "unknown";
	std::string m_format = "unknown";
	unsigned int m_vertices = 0;
	unsigned int m_faces = 0;

	friend class cAssetManager_Shaders;
	friend class cShaderLoader;
};

