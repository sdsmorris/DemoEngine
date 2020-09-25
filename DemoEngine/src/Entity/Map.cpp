#include "Map.h"

Map::Map()
{
}

Map::Map(MapID mapID) {
	switch (mapID)
	{
	case MAP_GARDEN:
		model = Model("C:/Users/sammo/Documents/Projects/DemoEngine/models/map/map.dae");
		break;
	default:
		std::cout << "Unknown map";
		break;
	}
}

void Map::update()
{
	draw();
}