#pragma once

#include "Entity/Entity.h"

class ParticleEmitter : public Entity
{
public:
	ParticleEmitter(float x, float y, float z);
	void update() override;
	float minScaleRange, maxScaleRange;
};

