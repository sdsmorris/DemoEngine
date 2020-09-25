#pragma once

#include "Entity.h"

static const float PLAYER_RUN_SPEED = 4;
static const float PLAYER_TURN_SPEED = 190;

class Player : public Entity
{
public:
	Player();
	void update() override;
	float currentSpeed, currentTurnSpeed;
	int coins;
};

