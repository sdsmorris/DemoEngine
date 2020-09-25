#pragma once

#include <glm/glm.hpp>
#include "OpenGL/Shader.h"

class CollisionRenderer
{
public:
	static void init();
	static void drawAlignedBoundingBox(glm::vec3 bboxMin, glm::vec3 bboxMax, glm::mat4 projection, glm::mat4 view);
	static void drawBoundingSphere(glm::vec3 position, float radius);
	static void drawOrientedBoundingBox();
	static Shader debugShader;
};

