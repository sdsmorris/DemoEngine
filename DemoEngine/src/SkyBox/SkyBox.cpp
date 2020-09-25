#include "SkyBox.h"
#include <iostream>
#include "Texture/TextureLoader.h"
#include "Game//ResourceManager.h"
//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

SkyBox::SkyBox()
{
}

SkyBox::SkyBox(SkyBoxID id)
{
	//Load cube VAO

	//Load textures to cube map
	switch (id)
	{
	case SKYBOX_OVERCAST:
		glGenTextures(1, &tex);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
		for (int i = 0; i < 6; i++)
		{
			TextureLoader::textureFromFileToTarget(SKYBOX_OVERCAST_FILEPATHS[i], GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SKYBOX_VERTICES), &SKYBOX_VERTICES, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		break;
	default:
		std::cout << "Unknown skybox";
		break;
	}
}

void SkyBox::update(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
{
	ResourceManager::skyboxShader.setMat4("view", viewMatrix);
	ResourceManager::skyboxShader.setMat4("projection", projectionMatrix);
	draw();
}

void SkyBox::draw()
{
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(SKYBOX_VERTICES) / 4);
	glBindVertexArray(0);
}
