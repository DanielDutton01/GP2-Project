#include "Game_Mesh_Class.h"
#include <vector>


Game_Mesh_Class::Game_Mesh_Class(Vertex_Class* vertices, unsigned int numVertices)
{
	drawCount = numVertices;

	glGenVertexArrays(1, &vertexArrayObject); //generate a vertex array and store it in the VAO
	glBindVertexArray(vertexArrayObject); //bind the VAO (any operation that works on a VAO will work on our bound VAO - binding)

	std::vector<glm::vec3> positions; //holds the position data
	std::vector<glm::vec2> textCoords; //holds the texture coordinate data

	positions.reserve(numVertices); // reserve the all the space needed to hold our data
	textCoords.reserve(numVertices);

	for (int i = 0; i < numVertices; i++)
	{
		positions.push_back(vertices[i].pos); //store our array of vertex positon into a list vec3 positions
		textCoords.push_back(vertices[i].texCoord);
	}

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers); //generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS];
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU (determined by type)

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(textCoords[0]), &textCoords[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0); // unbind our VAO
}


Game_Mesh_Class::~Game_Mesh_Class()
{
	glDeleteVertexArrays(1, &vertexArrayObject); // delete arrays
}

void Game_Mesh_Class::Draw()
{
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, drawCount);
	glBindVertexArray(0);
}