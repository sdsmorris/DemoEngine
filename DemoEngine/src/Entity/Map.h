#pragma once

#include "Entity.h"

enum MapID : short
{
	MAP_GARDEN
};

class Map : public Entity
{
public:
	Map();
	Map(MapID mapID);
	void update() override;
};

