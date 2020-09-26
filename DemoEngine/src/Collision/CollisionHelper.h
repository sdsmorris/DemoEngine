#pragma once

#include <glm/glm.hpp>
#include "Collision/CollisionInfo.h"
#include "Entity/Entity.h"

class CollisionHelper
{
public:
	static CollisionInfo isAABBInsideAABB(glm::vec3 aabb1Min, glm::vec3 aabb1Max, glm::vec3 aabb2Min, glm::vec3 aabb2Max, Entity* e1, Entity* e2);
	static bool isPointInsideAABB(glm::vec3 point, glm::vec3 bboxMin, glm::vec3 bboxMax);
	static bool isSphereInsideSphere(glm::vec3 sphere, float sphereRadius, glm::vec3 otherSphere, float otherSphereRadius, Entity* e1, Entity* e2);
	static bool isPointInsideSphere(glm::vec3 point, glm::vec3 sphere, float radius);
	static bool isSphereInsideAABB(glm::vec3 sphere, float radius, glm::vec3 bboxMin, glm::vec3 bboxMax, Entity* e1, Entity* e2);
	//
	static bool isAABBIntersectingTriangle(glm::vec3 bboxMin, glm::vec3 bboxMax, glm::vec3 tri1, glm::vec3 tri2, glm::vec3 tri3);
	static bool isSphereIntersectingTriangle(glm::vec3 sphere, float radius, glm::vec3 tri1, glm::vec3 tri2, glm::vec3 tri3);
	static bool isTriangleIntersectingTriangle(glm::vec3 tri1, glm::vec3 tri2, glm::vec3 tri3, glm::vec3 otherTri1, glm::vec3 otherTri2, glm::vec3 otherTri3);
};

