#include "cPlyLoader.h"

#include <iostream>			// cin cout
#include <fstream>		    // ifstream ofstream


cPlyLoader::cPlyLoader()			// constructor
{
	return;
}

cPlyLoader::~cPlyLoader()			// destructor
{
	return;
}

bool cPlyLoader::LoadThePlyHeader(std::istream& theFile, cItem_Model& theMesh)
{
	// Scan the file until I get to "vertex", and stop
	std::string temp;

	theMesh.m_isValid = false;
	theFile >> temp;
	while (temp != "end_header")
	{
		if (temp == "ply")
			theMesh.m_type = temp;
		if (temp == "format")
			theFile >> theMesh.m_format;
		if (temp == "vertex")
			theFile >> theMesh.m_vertices;
		if (temp == "face")
			theFile >> theMesh.m_faces;
		if (temp == "property")		// Ignore properties after face
		{
			if (theMesh.m_faces == 0)
			{
				cItem_Model::property v;
				theFile >> v.type >> v.name;
				theMesh.m_vecProperties.push_back(v);
			}
		}
		theFile >> temp;
	}
	if ((theMesh.m_type != "ply") ||
		(theMesh.m_vertices == 0) ||
		(theMesh.m_faces == 0) ||
		(theMesh.m_format == "ascii"))
	{
		theMesh.m_isValid = true;
	}
	unsigned int total = 0;
	theMesh.m_hasNormals = false;
	theMesh.m_hasColor = false;
	for (auto prop : theMesh.m_vecProperties)
	{
		if (prop.name == "x")
		{
			total += 3;
		}
		if (prop.name == "nx")
		{
			theMesh.m_hasNormals = true;
			total += 3;
		}
		if (prop.name == "red")
		{
			theMesh.m_hasColor = true;
			total += 4;
		}
		if (prop.type == "last")
		{
			total++;
		}
	}
	if (theMesh.m_vecProperties.size() != total)
		theMesh.m_isValid = false;

	return theMesh.m_isValid;
}


bool cPlyLoader::LoadThePlyBody(std::istream& theFile, cItem_Model& theMesh)
{
	// Read all the vertices
	for (unsigned int index = 0; index != theMesh.m_vertices; index++)
	{
		// -0.0312216 0.126304 0.00514924
		cItem_Model::sPlyVertexXYZ tempVertex;

		theFile >> tempVertex.x >> tempVertex.y >> tempVertex.z;

		// Also load the normals if they are there
		if (theMesh.m_hasNormals)
			theFile >> tempVertex.nx >> tempVertex.ny >> tempVertex.nz;

		// Also load the colours if they are there
		if (theMesh.m_hasColor)
			theFile >> tempVertex.red >> tempVertex.green >> tempVertex.blue >> tempVertex.alpha;

		// Add this temp vertex to the vector of vertices
		// (cMesh &theMesh)
		theMesh.m_vecVertices.push_back(tempVertex);
	}

	for (unsigned int index = 0; index != theMesh.m_faces; index++)
	{
		// 3 166 210 265 
		int discardThis;
		cItem_Model::sPlyTriangle tempTriangle;

		theFile >> discardThis
			>> tempTriangle.vert_index_1
			>> tempTriangle.vert_index_2
			>> tempTriangle.vert_index_3;

		// Add this triangle
		theMesh.m_vecTriangles.push_back(tempTriangle);
	}

	return true;
}

bool cPlyLoader::LoadPlyModelInfo(const std::string& filename,
	cItem_Model& theMesh)
{

	std::ifstream theFile(filename.c_str());
	if (!theFile.is_open())
	{
		// On no! Where's the file??? 
		theMesh.m_fileExists = false;
		return false;
	}
	theMesh.m_fileExists = true;
	return LoadThePlyHeader(theFile, theMesh);
}


// Takes the filename to load
// Returns by ref the mesh
bool cPlyLoader::LoadPlyModel(
	const std::string& filename,
	cItem_Model& theMesh)
{
	std::ifstream theFile(filename.c_str());
	if (!theFile.is_open())
	{
		// On no! Where's the file??? 
		return false;
	}
	bool ret = LoadThePlyHeader(theFile, theMesh);
	if (ret)
		ret = LoadThePlyBody(theFile, theMesh);
	return ret;

}
