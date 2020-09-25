#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "OpenGL/Shader.h"
#include "Entity/Player.h"

static const float CAM_PLAYER_Y_OFFSET = 0.6;

class Camera
{
public:
	Camera();
	Camera(float xPos, float yPos, float zPos, float fov = 45.0f, float near = 0.01f, float far = 1000.0f);
	void update();
	void move(float x, float y, float z);
	void rotate(float x, float y, float z);
	void updateShaderViewMatrix(Shader& shader);
	//Camera controls
	void calculateZoom(float scroll);
	void calculatePitch(float dY);
	void calculateAngleAroundPlayer(float dX);
	float calculateHorizontalDist();
	float calculateVerticalDist();
	void calculateCameraPosition(float horizontalDist, float verticalDist);
	Player* player;
	float distFromPlayer = 2;
	float angleAroundPlayer = 0;
	float xPos, yPos, zPos, pitch, yaw, roll, fov, near, far;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
};

