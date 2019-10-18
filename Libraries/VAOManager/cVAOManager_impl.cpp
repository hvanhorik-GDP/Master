#include "cVAOManager_impl.h"
#include "Physics/cPhysics_Henky.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <vector>

#include <sstream>

sModelDrawInfo::sModelDrawInfo()
{
	this->VAO_ID = 0;

	this->VertexBufferID = 0;
	this->VertexBuffer_Start_Index = 0;
	this->numberOfVertices = 0;

	this->IndexBufferID = 0;
	this->IndexBuffer_Start_Index = 0;
	this->numberOfIndices = 0;
	this->numberOfTriangles = 0;

	// The "local" (i.e. "CPU side" temporary array)
	this->pVertices = 0;	// or NULL
	this->pIndices = 0;		// or NULL

	this->maxX = this->maxY = this->maxZ = 0.0f;
	this->minX = this->minY = this->minZ = 0.0f;
	this->extentX = this->extentY = this->extentZ = this->maxExtent = 0.0f;

	return;
}

cVAOManager_impl::cVAOManager_impl(GLint shaderProgramID)
	: m_shaderProgID(shaderProgramID)
{

}

void sModelDrawInfo::CalcExtents(void)
{
	// See if we have any vertices loaded...
	if ( ( this->numberOfVertices == 0 ) || ( this->pVertices == 0 ) )
	{
		return;
	}

	// We're good

	// Assume the 1st vertex is the max and min (so we can compare)
	this->minX = this->maxX = this->pVertices[0].x;
	this->minY = this->maxY = this->pVertices[0].y;
	this->minZ = this->maxZ = this->pVertices[0].z;

	for ( unsigned int index = 0; index != this->numberOfVertices; index++ )
	{
		if ( this->pVertices[index].x < this->minX ) { this->minX = this->pVertices[index].x; }
		if ( this->pVertices[index].y < this->minY ) { this->minY = this->pVertices[index].y; }
		if ( this->pVertices[index].z < this->minZ ) { this->minZ = this->pVertices[index].z; }

		if ( this->pVertices[index].x < this->maxX ) { this->maxX = this->pVertices[index].x; }
		if ( this->pVertices[index].y < this->maxY ) { this->maxY = this->pVertices[index].y; }
		if ( this->pVertices[index].z < this->maxZ ) { this->maxZ = this->pVertices[index].z; }
	}

	this->extentX = this->maxX - this->minX;
	this->extentY = this->maxY - this->minY;
	this->extentZ = this->maxZ - this->minZ;
	
	this->maxExtent = this->extentX;
	if ( this->extentY > this->maxExtent ) { this->maxExtent = this->extentY; }
	if ( this->extentZ > this->maxExtent ) { this->maxExtent = this->extentZ; }
	
	return;
}


bool cVAOManager_impl::LoadModelIntoVAO(
		cItem_Model& theMesh,
		sModelDrawInfo &drawInfo)

{
	// Write some code to copy the infomation from cMesh& theMesh
	//  to the sModelDrawInfo& drawInfo...

	drawInfo.numberOfVertices = (unsigned int)theMesh.m_vecVertices.size();
	// Allocate an array big enought
	drawInfo.pVertices = new sVertex[drawInfo.numberOfVertices];

	// Copy the data from the m_vecVertices...
	for (unsigned int index = 0; index != drawInfo.numberOfVertices; index++)
	{

		drawInfo.pVertices[index].x = theMesh.m_vecVertices[index].x;
		drawInfo.pVertices[index].y = theMesh.m_vecVertices[index].y;
		drawInfo.pVertices[index].z = theMesh.m_vecVertices[index].z;
		drawInfo.pVertices[index].w = 1.0f;		// Set to 1 if not sure

		drawInfo.pVertices[index].r = 1.0f;
		drawInfo.pVertices[index].g = 1.0f;
		drawInfo.pVertices[index].b = 1.0f;
		drawInfo.pVertices[index].a = 1.0f;		// Again, if not sure, set to 1.0f

		drawInfo.pVertices[index].nx = theMesh.m_vecVertices[index].nx;
		drawInfo.pVertices[index].ny = theMesh.m_vecVertices[index].ny;
		drawInfo.pVertices[index].nz = theMesh.m_vecVertices[index].nz;
		drawInfo.pVertices[index].nw = 1.0f;		// if unsure, set to 1.0f

		// These are the "texture coordinates", and we aren't loading them, yet
		drawInfo.pVertices[index].u0 = 1.0f;
		drawInfo.pVertices[index].v0 = 1.0f;
		drawInfo.pVertices[index].u1 = 1.0f;
		drawInfo.pVertices[index].v1 = 1.0f;	

	}

	// Now copy the index information, too
	drawInfo.numberOfTriangles = (unsigned int)theMesh.m_vecTriangles.size();
	drawInfo.numberOfIndices = (unsigned int)theMesh.m_vecTriangles.size() * 3;

	// Allocate the index array
	drawInfo.pIndices = new unsigned int[drawInfo.numberOfIndices];

	unsigned int indexTri = 0;
	unsigned int indexIndex = 0;
	for ( ; indexTri != drawInfo.numberOfTriangles; indexTri++, indexIndex += 3 )
	{
		drawInfo.pIndices[indexIndex + 0] = (unsigned int)theMesh.m_vecTriangles[indexTri].vert_index_1;
		drawInfo.pIndices[indexIndex + 1] = (unsigned int)theMesh.m_vecTriangles[indexTri].vert_index_2;
		drawInfo.pIndices[indexIndex + 2] = (unsigned int)theMesh.m_vecTriangles[indexTri].vert_index_3;
	}

	drawInfo.meshName = theMesh.GetAssetID();


	// 
	// Model is loaded and the vertices and indices are in the drawInfo struct
	// 

	// Create a VAO (Vertex Array Object), which will 
	//	keep track of all the 'state' needed to draw 
	//	from this buffer...

	// Ask OpenGL for a new buffer ID...
	glGenVertexArrays( 1, &(drawInfo.VAO_ID) );
	// "Bind" this buffer:
	// - aka "make this the 'current' VAO buffer
	glBindVertexArray(drawInfo.VAO_ID);

	// Now ANY state that is related to vertex or index buffer
	//	and vertex attribute layout, is stored in the 'state' 
	//	of the VAO... 


	// NOTE: OpenGL error checks have been omitted for brevity
	glGenBuffers(1, &(drawInfo.VertexBufferID) );

	glBindBuffer(GL_ARRAY_BUFFER, drawInfo.VertexBufferID);
	// sVert vertices[3]
	glBufferData( GL_ARRAY_BUFFER, 
				  sizeof(sVertex) * drawInfo.numberOfVertices,	// ::g_NumberOfVertsToDraw,	// sizeof(vertices), 
				  (GLvoid*) drawInfo.pVertices,							// pVertices,			//vertices, 
				  GL_STATIC_DRAW );


	// Copy the index buffer into the video card, too
	// Create an index buffer.
	glGenBuffers( 1, &(drawInfo.IndexBufferID) );

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawInfo.IndexBufferID);

	glBufferData( GL_ELEMENT_ARRAY_BUFFER,			// Type: Index element array
	              sizeof( unsigned int ) * drawInfo.numberOfIndices, 
	              (GLvoid*) drawInfo.pIndices,
                  GL_STATIC_DRAW );

	// Set the vertex attributes.

	//struct sVertex
	//{
	//	float x, y, z, w;			// w coordinate	
	//	float r, g, b, a;		// a = alpha (transparency)
	//	float nx, ny, nz, nw;
	//	float u0, v0, u1, v1;
	//};
	GLint vpos_location = glGetAttribLocation(m_shaderProgID, "vPosition");	// program
	GLint vcol_location = glGetAttribLocation(m_shaderProgID, "vColour");	// program;
	GLint vnorm_location = glGetAttribLocation(m_shaderProgID, "vNormal");	// program;
	GLint vUV_location = glGetAttribLocation(m_shaderProgID, "vUVx2");	// program;

	// Set the vertex attributes for this shader
	glEnableVertexAttribArray(vpos_location);	// vPos
	glVertexAttribPointer( vpos_location, 4,		// now a vec4
						   GL_FLOAT, GL_FALSE,
						   sizeof(sVertex),						// sizeof(float) * 6,
						   ( void* )(offsetof(sVertex, x)) );

	glEnableVertexAttribArray(vcol_location);	// vCol
	glVertexAttribPointer( vcol_location, 4,		// vCol
						   GL_FLOAT, GL_FALSE,
						   sizeof(sVertex),						
						   ( void* )(offsetof(sVertex, r)) );


	//	float nx, ny, nz, nw;
	glEnableVertexAttribArray(vnorm_location);	// vNormal
	glVertexAttribPointer(vnorm_location, 4,		// vNormal
						   GL_FLOAT, GL_FALSE,
						   sizeof(sVertex),						
						   ( void* )(offsetof(sVertex, nx)) );

	//	float u0, v0, u1, v1;
	glEnableVertexAttribArray(vUV_location);		// vUVx2
	glVertexAttribPointer(vUV_location, 4,		// vUVx2
						   GL_FLOAT, GL_FALSE,
						   sizeof(sVertex),						
						   ( void* )(offsetof(sVertex, u0)) );



	// Now that all the parts are set up, set the VAO to zero
	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(vpos_location);
	glDisableVertexAttribArray(vcol_location);


	// Store the draw information into the map
	this->m_map_ModelName_to_VAOID[ drawInfo.meshName ] = drawInfo;


	return true;
}

// We don't want to return an int, likely
bool cVAOManager_impl::FindDrawInfoByModelName(
		std::string filename,
		sModelDrawInfo &drawInfo) 
{
	std::map< std::string /*model name*/,
			sModelDrawInfo /* info needed to draw*/ >::iterator 
		itDrawInfo = this->m_map_ModelName_to_VAOID.find( filename );

	// Find it? 
	if ( itDrawInfo == this->m_map_ModelName_to_VAOID.end() )
	{
		// Nope
		return false;
	}

	// Else we found the thing to draw
	// ...so 'return' that information
	drawInfo = itDrawInfo->second;
	return true;
}


void cVAOManager_impl::DrawObject(glm::mat4 m, cObject_Model* pCurrentObject)
{
	if (!pCurrentObject->IsVisable())			// Invisible so don't draw it
		return;
	// 
				//         mat4x4_identity(m);


	// This block of code, where I generate the world matrix from the 
	// position, scale, and rotation (orientation) of the object
	// has been placed into calculateWorldMatrix()

	m = cPhysics_Henky::calculateWorldMatrix(*pCurrentObject);

	//	m = glm::mat4(1.0f);
	//	
	//	
	//	
	//	// ******* TRANSLATION TRANSFORM *********
	//	glm::mat4 matTrans
	//	= glm::translate(glm::mat4(1.0f),
	//					 glm::vec3(pCurrentObject->positionXYZ.x,
	//							   pCurrentObject->positionXYZ.y,
	//							   pCurrentObject->positionXYZ.z));
	//	m = m * matTrans;
	//	// ******* TRANSLATION TRANSFORM *********
	//	
	//	
	//	
	//	// ******* ROTATION TRANSFORM *********
	//	//mat4x4_rotate_Z(m, m, (float) glfwGetTime());
	//	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f),
	//									pCurrentObject->rotationXYZ.z,					// Angle 
	//									glm::vec3(0.0f, 0.0f, 1.0f));
	//	m = m * rotateZ;
	//	
	//	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f),
	//									pCurrentObject->rotationXYZ.y,	//(float)glfwGetTime(),					// Angle 
	//									glm::vec3(0.0f, 1.0f, 0.0f));
	//	m = m * rotateY;
	//	
	//	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f),
	//									pCurrentObject->rotationXYZ.x,	// (float)glfwGetTime(),					// Angle 
	//									glm::vec3(1.0f, 0.0f, 0.0f));
	//	m = m * rotateX;
	//	// ******* ROTATION TRANSFORM *********
	//	
	//	
	//	
	//	// ******* SCALE TRANSFORM *********
	//	glm::mat4 scale = glm::scale(glm::mat4(1.0f),
	//								 glm::vec3(pCurrentObject->scale,
	//										   pCurrentObject->scale,
	//										   pCurrentObject->scale));
	//	m = m * scale;
	//	// ******* SCALE TRANSFORM *********



		//mat4x4_mul(mvp, p, m);
		//mvp = p * v * m;

		// Choose which shader to use
		//glUseProgram(program);
		//glUseProgram(shaderProgID);


		//glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
		//glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

		//uniform mat4 matModel;		// Model or World 
		//uniform mat4 matView; 		// View or camera
		//uniform mat4 matProj;
	GLint matModel_UL = glGetUniformLocation(m_shaderProgID, "matModel");

	glUniformMatrix4fv(matModel_UL, 1, GL_FALSE, glm::value_ptr(m));
	//glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(v));
	//glUniformMatrix4fv(matProj_UL, 1, GL_FALSE, glm::value_ptr(p));

	// Calcualte the inverse transpose of the model matrix and pass that...
	// Stripping away scaling and translation, leaving only rotation
	// Because the normal is only a direction, really
	GLint matModelIT_UL = glGetUniformLocation(m_shaderProgID, "matModelInverseTranspose");
	glm::mat4 matModelInverseTranspose = glm::inverse(glm::transpose(m));
	glUniformMatrix4fv(matModelIT_UL, 1, GL_FALSE, glm::value_ptr(matModelInverseTranspose));




	// Find the location of the uniform variable newColour
	GLint newColour_location = glGetUniformLocation(m_shaderProgID, "newColour");

	glUniform3f(newColour_location,
		pCurrentObject->objectColourRGBA.r,
		pCurrentObject->objectColourRGBA.g,
		pCurrentObject->objectColourRGBA.b);

	//uniform float newColourRed;
	//uniform float newColourGreen;
	//uniform float newColourBlue;
	//GLint newColourRed_UL = glGetUniformLocation(shaderProgID, "newColourRed");
	//GLint newColourGreen_UL = glGetUniformLocation(shaderProgID, "newColourGreen");
	//GLint newColourBlue_UL = glGetUniformLocation(shaderProgID, "newColourBlue");

	//glUniform1f(newColourRed_UL, pCurrentObject->objectColourRGBA.r);
	//glUniform1f(newColourGreen_UL, pCurrentObject->objectColourRGBA.g);
	//glUniform1f(newColourBlue_UL, pCurrentObject->objectColourRGBA.b);
	//GLint lighPosition_UL = glGetUniformLocation(shaderProgID, "lightPosition");
	//glUniform3f(lighPosition_UL, sexyLightLocation.x,
	//			sexyLightLocation.y, sexyLightLocation.z);

	GLint diffuseColour_UL = glGetUniformLocation(m_shaderProgID, "diffuseColour");
	glUniform4f(diffuseColour_UL,
		pCurrentObject->objectColourRGBA.r,
		pCurrentObject->objectColourRGBA.g,
		pCurrentObject->objectColourRGBA.b,
		pCurrentObject->objectColourRGBA.a);	// 

	GLint specularColour_UL = glGetUniformLocation(m_shaderProgID, "specularColour");
	glUniform4f(specularColour_UL,
		1.0f,	// R
		1.0f,	// G
		1.0f,	// B
		1000.0f);	// Specular "power" (how shinny the object is)
					// 1.0 to really big (10000.0f)


//uniform vec4 debugColour;
//uniform bool bDoNotLight;
	GLint debugColour_UL = glGetUniformLocation(m_shaderProgID, "debugColour");
	GLint bDoNotLight_UL = glGetUniformLocation(m_shaderProgID, "bDoNotLight");

	if (pCurrentObject->isWireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		// LINES
		glUniform4f(debugColour_UL,
			pCurrentObject->debugColour.r,
			pCurrentObject->debugColour.g,
			pCurrentObject->debugColour.b,
			pCurrentObject->debugColour.a);
		glUniform1f(bDoNotLight_UL, (float)GL_TRUE);
	}
	else
	{	// Regular object (lit and not wireframe)
		glUniform1f(bDoNotLight_UL, (float)GL_FALSE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		// SOLID
	}
	//glPointSize(15.0f);

	if (pCurrentObject->disableDepthBufferTest)
	{
		glDisable(GL_DEPTH_TEST);					// DEPTH Test OFF
	}
	else
	{
		glEnable(GL_DEPTH_TEST);						// Turn ON depth test
	}

	if (pCurrentObject->disableDepthBufferWrite)
	{
		glDisable(GL_DEPTH);						// DON'T Write to depth buffer
	}
	else
	{
		glEnable(GL_DEPTH);								// Write to depth buffer
	}


	sModelDrawInfo drawInfo;
	if (FindDrawInfoByModelName(pCurrentObject->GetAssetID(), drawInfo))
	{
		glBindVertexArray(drawInfo.VAO_ID);
		glDrawElements(GL_TRIANGLES,
			drawInfo.numberOfIndices,
			GL_UNSIGNED_INT,
			0);
		glBindVertexArray(0);
	}

	return;
} // DrawObject;

