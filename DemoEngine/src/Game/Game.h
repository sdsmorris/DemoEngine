#pragma once

#include <vector>
#include "Entity/Entity.h"
#include "Camera/Camera.h"
#include "Entity/Map.h"
#include "Entity/Player.h"
#include "SkyBox/SkyBox.h"

class Game
{
public:
	Camera mainCamera;
	Map map;
	Player player;
	SkyBox skyBox;
	std::vector<Entity*> entities;
	int debugCollisionCount = 0;
	Game();
	void update();
};

