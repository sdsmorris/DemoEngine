#include "ParticleEmitter.h"
#include "Particle/ParticleSystem.h"
#include "Math/Random.h"
#include <glfw/glfw3.h>
#include <ctime>

ParticleEmitter::ParticleEmitter(float x, float y, float z)
{
	xPos = x;
	yPos = y;
	zPos = z;
}

void ParticleEmitter::update()
{	
	srand(time(NULL));
	//std::cout << Random::randFloatInRange(1, 5) << "\n";
	srand(glfwGetTimerValue());
	float xVel = Random::randFloatInRange(0.1, 1);
	srand(glfwGetTimerValue());
	float yVel = Random::randFloatInRange(1, 3);
	srand(glfwGetTimerValue());
	float zVel = Random::randFloatInRange(0.05, 3);
	//std::cout << xVel << " " << yVel << " " << zVel << "\n";

	if (Random::randBool())
		xVel = -xVel;
	//if (Random::randBool())
		//yVel = -yVel;
	if (Random::randBool())
		zVel = -zVel;

	float pScale = Random::randFloatInRange(minScaleRange, maxScaleRange);
	pScale = scale;

	Particle p(xPos, yPos, zPos, xVel, yVel, zVel, pScale, Random::randFloatInRange(0.5, 1));
	ParticleSystem::addParticle(p);
}
