#pragma once

#include "Model/Model.h"
#include "OpenGL/Shader.h"

class Entity
{
public:
	float xPos, yPos, zPos, xVelocity, yVelocity, zVelocity, xRot, yRot, zRot, scale;
	glm::vec3 bboxMin, bboxMax;
	glm::vec3 origBboxMin, origBboxMax;
	float radius;
	Model model;
	Entity();
	Entity(Model& model, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float scale);
	virtual void update();
	void draw();
	void move(float x, float y, float z);
	void setPos(float x, float y, float z);
};

