#pragma once

#include "Entity.h"

class Cube : public Entity
{
public:
	float currentSpeed, currentTurnSpeed;
	Cube(float x, float y, float z);
	void update() override;
};

