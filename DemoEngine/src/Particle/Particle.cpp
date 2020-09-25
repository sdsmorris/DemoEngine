#include "Particle.h"
#include "Display/Display.h"

Particle::Particle(float xPos, float yPos, float zPos, float xVelocity, float yVelocity, float zVelocity, float scale, float life) : xPos(xPos), yPos(yPos), zPos(zPos), xVelocity(xVelocity), yVelocity(yVelocity), zVelocity(zVelocity), scale(scale), life(life), dead(false)
{
}

void Particle::update()
{
	xPos += xVelocity * Display::deltaTime;
	yPos += yVelocity * Display::deltaTime;
	zPos += zVelocity * Display::deltaTime;
	life -= Display::deltaTime;
	if (life <= 0)
		dead = true;
}
