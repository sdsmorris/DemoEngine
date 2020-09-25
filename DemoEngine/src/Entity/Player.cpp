#include "Player.h"
#include "Display/Display.h"

Player::Player() : currentSpeed(0), currentTurnSpeed(0), coins(0)
{
	model = Model("C:/Users/sammo/Documents/Projects/DemoEngine/models/mainplayer/mainplayer.dae");
	bboxMin = model.meshes[0].bboxMin;
	bboxMax = model.meshes[0].bboxMax;
}

void Player::update()
{
	//Rotate
	yRot += currentTurnSpeed * Display::deltaTime;

	//Move forward
	float distForward = currentSpeed * Display::deltaTime;
	xVelocity = distForward * glm::sin(glm::radians(yRot));
	zVelocity = distForward * glm::cos(glm::radians(yRot));

	move(xVelocity, yVelocity, zVelocity);
	
	//Render
	draw();
}