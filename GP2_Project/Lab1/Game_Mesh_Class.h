#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>

class Vertex_Class
{
public:
	Vertex_Class(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
	}

	glm::vec3 pos;
	glm::vec2 texCoord; //postion on texture to map to vertex
};

class Game_Mesh_Class
{
public:
	Game_Mesh_Class(Vertex_Class* vertices, unsigned int numVertices);
	~Game_Mesh_Class();

	void Draw();
private:

	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw
};

