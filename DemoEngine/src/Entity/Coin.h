#pragma once

#include "Entity.h"

class Coin : public Entity
{
public:
	bool collected;
	Coin(float x, float y, float z);
	void update() override;
};

