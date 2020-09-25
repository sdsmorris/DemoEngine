#include "Entity.h"
#include "Game/ResourceManager.h"

Entity::Entity() : xPos(0), yPos(0), zPos(0), xVelocity(0), yVelocity(0), zVelocity(0), xRot(0), yRot(0), zRot(0), scale(1)
{

}

Entity::Entity(Model& model, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float scale) : model(model), xPos(xPos), yPos(yPos), zPos(zPos), xVelocity(0), yVelocity(0), zVelocity(0), xRot(xRot), yRot(yRot), zRot(zRot), scale(scale)
{
}

void Entity::update()
{
	draw();
}

void Entity::draw()
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(xPos, yPos, zPos));
	model = glm::rotate(model, glm::radians(xRot), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(yRot), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(zRot), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	ResourceManager::modelShader.setMat4("model", model);
	this->model.draw(ResourceManager::modelShader);
}

void Entity::move(float x, float y, float z)
{
	this->xPos += x;
	this->yPos += y;
	this->zPos += z;
	/*bboxMin.x += x;
	bboxMin.y += y;
	bboxMin.z += z;
	bboxMax.x += x;
	bboxMax.y += y;
	bboxMax.z += z;*/
}

void Entity::setPos(float x, float y, float z)
{
	this->xPos = x;
	this->yPos = y;
	this->zPos = z;

	/*bboxMin.x = model.meshes[0].bboxMin.x;
	bboxMin.x += x;
	bboxMin.y = model.meshes[0].bboxMin.y;
	bboxMin.y += y;
	bboxMin.z = model.meshes[0].bboxMin.z;
	bboxMin.z += z;

	bboxMax.x = model.meshes[0].bboxMax.x;
	bboxMax.x += x;
	bboxMax.x = model.meshes[0].bboxMax.x;
	bboxMax.y += y;
	bboxMax.x = model.meshes[0].bboxMax.x;
	bboxMax.z += z;*/
}