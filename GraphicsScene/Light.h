#pragma once
#include "Actor.h"

class Light
{
public:
	glm::vec3 getDirection() { return m_direction; }
	void setDirection(glm::vec3 direction) { m_direction = direction; }

	glm::vec3 getAmbient() { return m_ambient; }
	void setAmbient(glm::vec3 ambient) { m_ambient = ambient; }

	glm::vec3 getDiffuse() { return m_diffuse; }
	void setDiffuse(glm::vec3 diffuse) { m_diffuse = diffuse; }

	glm::vec3 getSpecular() { return m_specular; }
	void setSpecular(glm::vec3 specular) { m_specular = specular; }

private:
	glm::vec3 m_direction;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};

