#include "Cube.h"
#include "Display/Display.h"

Cube::Cube(float x, float y, float z) : currentSpeed(0), currentTurnSpeed(0)
{
	this->xPos = x;
	this->yPos = y;
	this->zPos = z;
	model = Model("C:/Users/sammo/Documents/Projects/DemoEngine/models/cube/cube.dae");
	scale = 0.1;
	bboxMin = model.meshes[0].bboxMin * scale;
	bboxMax = model.meshes[0].bboxMax * scale;
	origBboxMin = model.meshes[0].bboxMin * scale;
	origBboxMax = model.meshes[0].bboxMax * scale;
}

void Cube::update()
{
	//Rotate
	yRot += currentTurnSpeed * Display::deltaTime;

	//Move forward
	float distForward = currentSpeed * Display::deltaTime;
	float dX = distForward * glm::sin(glm::radians(yRot));
	float dZ = distForward * glm::cos(glm::radians(yRot));
	move(dX, 0, dZ);

	//Recalculate bounding box
	glm::mat4 mat(1.0f);
	mat = glm::translate(mat, glm::vec3(xPos, yPos, zPos));
	glm::vec4 vecMin = mat * glm::vec4(origBboxMin.x, origBboxMin.y, origBboxMin.z, 1.0f);
	bboxMin.x = vecMin.x;
	bboxMin.y = vecMin.y;
	bboxMin.z = vecMin.z;
	glm::vec4 vecMax = mat * glm::vec4(origBboxMax.x, origBboxMax.y, origBboxMax.z, 1.0f);
	bboxMax.x = vecMax.x;
	bboxMax.y = vecMax.y;
	bboxMax.z = vecMax.z;


	//Render
	draw();
}
