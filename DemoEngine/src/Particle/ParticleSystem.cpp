#include "ParticleSystem.h"
#include <iostream>
#include "Display/Display.h"

std::vector<Particle> ParticleSystem::particles;
Shader ParticleSystem::particleShader;
unsigned int ParticleSystem::vao;

void ParticleSystem::init()
{
	//Init shader
	particleShader = Shader("C:/Users/sammo/source/repos/DemoEngine/DemoEngine/src/Particle/particleVertex.glsl", "C:/Users/sammo/source/repos/DemoEngine/DemoEngine/src/Particle/particleFragment.glsl");

	//Init vao
	//3D cube particle
	//const float SIZE = 1.0f;

	//const float particleVerts[] = {
	//	-SIZE,  SIZE, -SIZE,
	//	-SIZE, -SIZE, -SIZE,
	//	SIZE, -SIZE, -SIZE,
	//	 SIZE, -SIZE, -SIZE,
	//	 SIZE,  SIZE, -SIZE,
	//	-SIZE,  SIZE, -SIZE,

	//	-SIZE, -SIZE,  SIZE,
	//	-SIZE, -SIZE, -SIZE,
	//	-SIZE,  SIZE, -SIZE,
	//	-SIZE,  SIZE, -SIZE,
	//	-SIZE,  SIZE,  SIZE,
	//	-SIZE, -SIZE,  SIZE,

	//	 SIZE, -SIZE, -SIZE,
	//	 SIZE, -SIZE,  SIZE,
	//	 SIZE,  SIZE,  SIZE,
	//	 SIZE,  SIZE,  SIZE,
	//	 SIZE,  SIZE, -SIZE,
	//	 SIZE, -SIZE, -SIZE,

	//	-SIZE, -SIZE,  SIZE,
	//	-SIZE,  SIZE,  SIZE,
	//	 SIZE,  SIZE,  SIZE,
	//	 SIZE,  SIZE,  SIZE,
	//	 SIZE, -SIZE,  SIZE,
	//	-SIZE, -SIZE,  SIZE,

	//	-SIZE,  SIZE, -SIZE,
	//	 SIZE,  SIZE, -SIZE,
	//	 SIZE,  SIZE,  SIZE,
	//	 SIZE,  SIZE,  SIZE,
	//	-SIZE,  SIZE,  SIZE,
	//	-SIZE,  SIZE, -SIZE,

	//	-SIZE, -SIZE, -SIZE,
	//	-SIZE, -SIZE,  SIZE,
	//	 SIZE, -SIZE, -SIZE,
	//	 SIZE, -SIZE, -SIZE,
	//	-SIZE, -SIZE,  SIZE,
	//	 SIZE, -SIZE,  SIZE
	//};

	//unsigned int vbo;
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);
	//glGenBuffers(1, &vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(particleVerts), &particleVerts, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);
	//glEnableVertexAttribArray(0);
	//glBindVertexArray(0);

	//2D particle vao

	float particleVerts[]{ -1, -1, 0,
		1, -1, 0,
		-1, 1, 0,
		1, 1, 0
	};

	unsigned int vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particleVerts), &particleVerts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

}

void ParticleSystem::addParticle(Particle& particle)
{
	particles.push_back(particle);
}

void ParticleSystem::update()
{
	//Pre draw calls
	particleShader.use();
	particleShader.setMat4("view", Display::game->mainCamera.viewMatrix);
	particleShader.setMat4("projection", Display::game->mainCamera.projectionMatrix);
	glBindVertexArray(vao);
	//Update
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].update();
		//Draw particles
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(particles[i].xPos, particles[i].yPos, particles[i].zPos));
		model = glm::scale(model, glm::vec3(particles[i].scale, particles[i].scale, particles[i].scale));
		particleShader.setMat4("model", model);
		//glDrawArrays(GL_TRIANGLES, 0, 108); //3D vao
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //2D vao
	}
	//Remove dead
	if (particles.size() >= 1)
		for (int i = particles.size() - 1; i > 0; i--)
			if (particles[i].dead)
				particles.erase(particles.begin() + i);
	//std::cout << particles.size() << "\n";
}
