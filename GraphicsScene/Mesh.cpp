#include "Mesh.h"
#include <gl_core_4_4.h>

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}

void Mesh::initialize(unsigned int vertexCount,
					  const Vertex* vertices,
					  unsigned int indexCount,
					  unsigned int* indices)
{
	//Check that the mesh is not already initialized
	assert(m_vao == 0);

	//Generate buffers
	glGenBuffers(1, &m_vbo);
	glGenVertexArrays(1, &m_vao);

	//Bind buffers
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	//Fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	//Enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//Enable second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (GLvoid*)(4 * sizeof(float)));

	//Enable third element as textCoord
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(12 * sizeof(float)));

	//Enable fourth element as color
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(float)));

	//Bind indices if there are any
	if (indexCount != 0) 
	{
		//Genereate the index buffer
		glGenBuffers(1, &m_ibo);

		//Bind index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

		//Fill the index buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		m_triCount = indexCount / 3;
	}

	else 
	{
		m_triCount = vertexCount / 3;
	}

	//Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::initializeQuad()
{
	//Define 4 vertices for 2 triangles
	Vertex vertices[4];
	//Position
	vertices[0].position = { -0.5f, 0.0f, 0.5f, 1.0f }; //Front left
	vertices[1].position = { 0.5f, 0.0f, 0.5f, 1.0f }; //Front right
	vertices[2].position = { -0.5f, 0.0f, -0.5f, 1.0f }; //Back left
	vertices[3].position = { 0.5f, 0.0f, -0.5f, 1.0f }; //Back right


	//Color
	vertices[0].color = { 0.2f, 0.8f, 0.2f, 1 }; //Green
	vertices[1].color = { 0.8f, 0.2f, 0.8f, 1 }; //Magenta
	vertices[2].color = { 0.2f, 0.8f, 0.8f, 1 }; //Cyan
	vertices[3].color = { 0.8f, 0.2f, 0.2f, 1 }; //Red

	//TexCoord
	vertices[0].texCoord = { 0, 1 }; //Bottom left
	vertices[1].texCoord = { 1, 1 }; //Bottom right
	vertices[2].texCoord = { 0, 0 }; //Top left
	vertices[3].texCoord = { 1, 0 }; //Top right

	//Define 6 indices for 2 triangles
	unsigned int indices[6] =
	{
		0, 1, 2, //Triangle A
		2, 1, 3 //Triangle B
	};

	initialize(4, vertices, 6, indices);
}

void Mesh::initializeCube()
{
	//Define 8 vertices for 12 triangles
	Vertex vertices[8];

	//Bottom position
	vertices[0].position = { -0.5f, 0.0f, 0.5f, 1.0f };
	vertices[1].position = { 0.5f, 0.0f, 0.5f, 1.0f };
	vertices[2].position = { -0.5f, 0.0f, -0.5f, 1.0f };
	vertices[3].position = { 0.5f, 0.0f, -0.5f, 1.0f };

	//Top position
	vertices[4].position = { -0.5f, 1.0f, 0.5f, 1.0f };
	vertices[5].position = { 0.5f, 1.0f, 0.5f, 1.0f };
	vertices[6].position = { -0.5f, 1.0f, -0.5f, 1.0f };
	vertices[7].position = { 0.5f, 1.0f, -0.5f, 1.0f };


	//Color
	glm::vec4 green = { 0.2f, 0.8f, 0.2f, 1 };
	glm::vec4 magenta = { 0.8f, 0.2f, 0.8f, 1 };
	glm::vec4 cyan = { 0.2f, 0.8f, 0.8f, 1 };
	glm::vec4 red = { 0.8f, 0.2f, 0.2f, 1 };

	vertices[0].color = green;
	vertices[1].color = magenta;
	vertices[2].color = cyan;
	vertices[3].color = red;

	vertices[4].color = green;
	vertices[5].color = magenta;
	vertices[6].color = cyan;
	vertices[7].color = red;

	//Define 36 indices for 12 triangles
	unsigned int indices[36] =
	{
		0, 1, 2, //Bottom A
		2, 1, 3, //Bottom B
		4, 5, 6, //Top A
		6, 5, 7, //Top B
		0, 2, 6, //Left A
		0, 4, 6, //Left B
		1, 3, 5, //Right A
		3, 5, 7, //Right B
		0, 1, 4, //Front A
		1, 4, 5, //Front B
		2, 3, 7, //Back A
		2, 6, 7  //Back B
	};

	initialize(8, vertices, 36, indices);
}

void Mesh::draw()
{
	glBindVertexArray(m_vao);

	//Using indices or just vertices
	if (m_ibo != 0) 
	{
		glDrawElements(GL_TRIANGLES, 3 * m_triCount, GL_UNSIGNED_INT, 0);
	}

	else 
	{
		glDrawArrays(GL_TRIANGLES, 0, 3 * m_triCount);
	}
}