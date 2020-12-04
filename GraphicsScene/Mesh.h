#pragma once
#include <glm/glm.hpp>
#include <Texture.h>

class Mesh
{
public:
	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec4 color;
		glm::vec2 texCoord;
	};

public:
	Mesh() : m_triCount(0), m_vao(0), m_vbo(0), m_ibo(0) {}
	~Mesh();

	void initialize(unsigned int vertexCount,
					const Vertex* vertices,
					unsigned int indexCount = 0,
					unsigned int* indices = nullptr);
	void initializeQuad();
	void initializeCube();

	virtual void draw();

protected:
	unsigned int m_triCount;
	unsigned int m_vao, m_vbo, m_ibo;
};