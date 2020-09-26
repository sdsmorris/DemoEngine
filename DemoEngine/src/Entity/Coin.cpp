#include "Coin.h"

Coin::Coin(float x, float y, float z) : collected(false)
{
	this->xPos = x;
	this->yPos = y;
	this->zPos = z;
	model = Model("C:/Users/sammo/Documents/Projects/DemoEngine/models/coin/coin.dae");
	zRot -= 90;
	scale = 0.1;
	//radius = 0.05;
	radius = 0.1;
}

void Coin::update()
{
	if (!collected)
	{
		yRot += 0.1;
		draw();
	}
}
