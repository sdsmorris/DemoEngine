#include "ResourceManager.h"

Shader ResourceManager::modelShader;
Shader ResourceManager::skyboxShader;

void ResourceManager::init()
{
	modelShader = Shader("C:/Users/sammo/source/repos/DemoEngine/DemoEngine/src/Model/staticModelVertex.glsl", "C:/Users/sammo/source/repos/DemoEngine/DemoEngine/src/Model/staticModelFragment.glsl");
	skyboxShader = Shader("C:/Users/sammo/source/repos/DemoEngine/DemoEngine/src/SkyBox/skyboxVertex.glsl", "C:/Users/sammo/source/repos/DemoEngine/DemoEngine/src/SkyBox/skyboxFragment.glsl");
}