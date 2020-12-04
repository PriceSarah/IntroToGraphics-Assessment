#pragma once
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <Gizmos.h>
#include "OBJMesh.h"
#include "Shader.h"
#include "Mesh.h"
#include "Light.h"
#include "Earth.h"

class Camera;

class Game
{
public:
	Game();
	Game(int width, int height, const char* title);
	~Game();

	int run();

	bool start();
	bool update(double deltaTime);
	bool draw();
	bool end();

	GLFWwindow* getWindow() { return m_window; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	const char* getTitle() { return m_title; }

protected:
	GLFWwindow* m_window;
	Camera* m_camera;

	aie::ShaderProgram m_shader;
	Mesh m_mesh;
	glm::mat4 m_meshTransform;
	aie::Texture m_texture;
	aie::OBJMesh m_objMesh;
	
	Earth* m_earth;
	Light m_light;

private:
	int m_width, m_height;
	const char* m_title;
};

