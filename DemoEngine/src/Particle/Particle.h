#pragma once
class Particle
{
public:
	Particle(float xPos, float yPos, float zPos, float xVelocity, float yVelocity, float zVelocity, float scale, float life);
	void update();
	float xPos, yPos, zPos, xVelocity, yVelocity, zVelocity, scale; //Transform
	float life; //Life info
	bool dead;
};

