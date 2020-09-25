#include "Camera.h"
#include "Game/ResourceManager.h"
#include "Display/Display.h"

Camera::Camera()
{
}

Camera::Camera(float xPos, float yPos, float zPos, float fov, float near, float far) : xPos(xPos), yPos(yPos), zPos(zPos), pitch(20), yaw(0), roll(0), fov(fov), near(near), far(far)
{    //Init projection matrix
    projectionMatrix = glm::perspective(glm::radians(fov), (float)Display::width / (float)Display::height, near, far);
    ResourceManager::modelShader.setMat4("projection", projectionMatrix);

    //Init view matrix
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(xPos, yPos, zPos));
    ResourceManager::modelShader.setMat4("view", viewMatrix);
}

void Camera::update()
{
    /*calculatePitch(0);
    calculateAngleAroundPlayer(0);
    float horizontalDist = calculateHorizontalDist();
    float verticalDist = calculateVerticalDist();
    calculateCameraPosition(horizontalDist, verticalDist);*/
    updateShaderViewMatrix(ResourceManager::modelShader);
}

void Camera::move(float x, float y, float z)
{
    this->xPos += x;
    this->yPos += y;
    this->zPos += z;
}

void Camera::rotate(float pitch, float yaw, float roll)
{
    this->pitch += pitch;
    this->yaw += yaw;
    this->roll += roll;
}

void Camera::updateShaderViewMatrix(Shader& shader)
{
    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(xPos, yPos - CAM_PLAYER_Y_OFFSET, zPos));
    viewMatrix = glm::rotate(viewMatrix, pitch, glm::vec3(1, 0, 0));
    viewMatrix = glm::rotate(viewMatrix, yaw, glm::vec3(0, 1, 0));
    viewMatrix = glm::rotate(viewMatrix, roll, glm::vec3(0, 0, 1));
    //viewMatrix = glm::inverse(viewMatrix);
    shader.setMat4("view", viewMatrix);
}

void Camera::calculateZoom(float scroll)
{
    float zoomLevel = scroll * 0.1f;
    distFromPlayer -= zoomLevel;
}

void Camera::calculatePitch(float dY)
{
    float pitchChange = dY * 0.01;
    pitch -= pitchChange;
}

void Camera::calculateAngleAroundPlayer(float dX)
{
    float angleChange = dX * 0.01;
    angleAroundPlayer -= angleChange;
}

float Camera::calculateHorizontalDist() {
    return distFromPlayer * glm::cos(glm::radians(pitch));
}

float Camera::calculateVerticalDist() {
    return distFromPlayer * glm::sin(glm::radians(pitch));
}

void Camera::calculateCameraPosition(float horizontalDist, float verticalDist)
{
    float theta = player->yRot + angleAroundPlayer;
    float offsetX = horizontalDist * glm::sin(glm::radians(theta));
    float offsetZ = horizontalDist * glm::cos(glm::radians(theta));
    xPos = player->xPos - offsetX;
    zPos = player->zPos - offsetZ;
    yPos = player->yPos + verticalDist;
    yaw = 180.0f - (player->yRot + angleAroundPlayer);
}
