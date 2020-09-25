#pragma once

#include "OpenGL/Shader.h"

class ResourceManager
{
public:
	static Shader modelShader;
	static Shader skyboxShader;
	static void init();
};

