#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Actor
{
public:
	Actor() {}
	Actor(glm::vec3 position, glm::quat rotation, glm::vec3 scale = { 1.0f, 1.0f, 1.0f });
	~Actor() {}

	virtual bool start() { return true; }
	virtual bool update(double deltaTime) { return true; }
	virtual bool draw() { return true; }
	virtual bool end() { return true; }

	glm::vec3 getPosition() { return m_position; }
	void setPosition(glm::vec3 position) { m_position = position; }

	glm::quat getRotation() { return m_rotation; }
	void setRotation(glm::quat rotation) { m_rotation = rotation; }

	glm::vec3 getScale() { return m_scale; }
	void setScale(glm::vec3 scale) { m_scale = scale; }

	glm::mat4 getTransform();

	Actor* getParent() { return m_parent; }
	void setParent(Actor* parent) { m_parent = parent; }

	glm::vec3 getParentPosition();
	glm::quat getParentRotation();

protected:
	glm::vec3 m_position{ 0.0f, 0.0f, 0.0f };
	glm::quat m_rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3 m_scale{ 1.0f, 1.0f, 1.0f };

private:
	Actor* m_parent = nullptr;
};

