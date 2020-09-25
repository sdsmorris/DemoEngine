#pragma once

#include <glm/glm.hpp>

static const float SIZE = 500.0f;

static const float SKYBOX_VERTICES[] = {
	-SIZE,  SIZE, -SIZE,
	-SIZE, -SIZE, -SIZE,
	SIZE, -SIZE, -SIZE,
	 SIZE, -SIZE, -SIZE,
	 SIZE,  SIZE, -SIZE,
	-SIZE,  SIZE, -SIZE,

	-SIZE, -SIZE,  SIZE,
	-SIZE, -SIZE, -SIZE,
	-SIZE,  SIZE, -SIZE,
	-SIZE,  SIZE, -SIZE,
	-SIZE,  SIZE,  SIZE,
	-SIZE, -SIZE,  SIZE,

	 SIZE, -SIZE, -SIZE,
	 SIZE, -SIZE,  SIZE,
	 SIZE,  SIZE,  SIZE,
	 SIZE,  SIZE,  SIZE,
	 SIZE,  SIZE, -SIZE,
	 SIZE, -SIZE, -SIZE,

	-SIZE, -SIZE,  SIZE,
	-SIZE,  SIZE,  SIZE,
	 SIZE,  SIZE,  SIZE,
	 SIZE,  SIZE,  SIZE,
	 SIZE, -SIZE,  SIZE,
	-SIZE, -SIZE,  SIZE,

	-SIZE,  SIZE, -SIZE,
	 SIZE,  SIZE, -SIZE,
	 SIZE,  SIZE,  SIZE,
	 SIZE,  SIZE,  SIZE,
	-SIZE,  SIZE,  SIZE,
	-SIZE,  SIZE, -SIZE,

	-SIZE, -SIZE, -SIZE,
	-SIZE, -SIZE,  SIZE,
	 SIZE, -SIZE, -SIZE,
	 SIZE, -SIZE, -SIZE,
	-SIZE, -SIZE,  SIZE,
	 SIZE, -SIZE,  SIZE
};

enum SkyBoxID
{
	SKYBOX_OVERCAST,
};

static const char* SKYBOX_OVERCAST_FILEPATHS[] = { "C:/Users/sammo/Documents/Projects/DemoEngine/textures/skybox/right.png", "C:/Users/sammo/Documents/Projects/DemoEngine/textures/skybox/left.png", "C:/Users/sammo/Documents/Projects/DemoEngine/textures/skybox/top.png", "C:/Users/sammo/Documents/Projects/DemoEngine/textures/skybox/bottom.png", "C:/Users/sammo/Documents/Projects/DemoEngine/textures/skybox/back.png", "C:/Users/sammo/Documents/Projects/DemoEngine/textures/skybox/front.png" };

class SkyBox
{
public:
	unsigned int VAO;
	unsigned int tex;
	SkyBox();
	SkyBox(SkyBoxID id);
	void update(glm::mat4& viewMatrix, glm::mat4& projectionMatrix);
	void draw();
};

