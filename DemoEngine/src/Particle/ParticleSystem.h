#pragma once

#include <vector>
#include "Particle.h"
#include <OpenGL\Shader.h>

class ParticleSystem
{
public:
	static void init();
	static void addParticle(Particle& particle);
	static void update();
	static std::vector<Particle> particles;
	static Shader particleShader;
	static unsigned int vao;
};

