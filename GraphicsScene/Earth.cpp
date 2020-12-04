#include "Earth.h"

Earth::Earth(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
{
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
}

bool Earth::start()
{
	////Load Earth texture
	//if (!m_texture.load("soulspear_normal.tga"))
	//{
	//	printf("Failed to load earth_diffuse.jpg.\n");
	//	return false;
	//}

	m_mesh.initializeQuad();

	return true;
}

bool Earth::draw()
{
	//Bind texture
	m_texture.bind(0);

	//Draw Earth mesh
	m_mesh.draw();

	return false;
}
