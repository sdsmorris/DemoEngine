#include "Game.h"
#include "Entity/WoodenSlab.h"
#include "Entity/Coin.h"
#include "Collision/CollisionHelper.h"
#include "Game/ResourceManager.h"
#include "Entity/Cube.h"
#include "Collision/CollisionInfo.h"
#include "Debug/CollisionRenderer.h"
#include "Particle/ParticleSystem.h"
#include "Entity\ParticleEmitter.h"

Game::Game()
{
    //Init camera
    mainCamera = Camera(0, 0, -3);
    mainCamera.player = &player;
    mainCamera.calculatePitch(0);
    mainCamera.calculateAngleAroundPlayer(0);
    float horizontalDist = mainCamera.calculateHorizontalDist();
    float verticalDist = mainCamera.calculateVerticalDist();
    mainCamera.calculateCameraPosition(horizontalDist, verticalDist);

    //Init map
    map = Map(MAP_GARDEN);
    map.yPos -= 1;
    map.scale = 5;

    //Init player
    player.scale = 0.05;
    player.radius = 0.2;
    //player.setPos(0, 0.2, 0);

    //Init sky box
    skyBox = SkyBox(SKYBOX_OVERCAST);

    //Init other entities
    WoodenSlab* slab = new WoodenSlab();
    // VAO = 6, std::cout << "VAO " << slab->model.meshes[0].VAO << "\n";
    slab->setPos(1, 0, 0);
    slab->scale = 0.2;
    slab->bboxMin.x *= 0.2;
    slab->bboxMin.y *= 0.2;
    slab->bboxMin.z *= 0.2;
    slab->bboxMax.x *= 0.2;
    slab->bboxMax.y *= 0.2;
    slab->bboxMax.z *= 0.2;
    slab->radius = 0.3;
    entities.push_back(slab);

    Coin* coin = new Coin(0, 0, 1);
    entities.push_back(coin);

    Coin* coin2 = new Coin(1, 0, 1);
    entities.push_back(coin2);

    Cube* cube = new Cube(-1, 0, 0);
    cube->yPos -= 0.1;
    entities.push_back(cube);

    Cube* cube2 = new Cube(-1, 0, 1);
    entities.push_back(cube2);

    WoodenSlab* slab2 = new WoodenSlab();
    // VAO = 6, std::cout << "VAO " << slab->model.meshes[0].VAO << "\n";
    slab2->setPos(2, -0.05, 0);
    slab2->scale = 0.2;
    slab2->yRot += 32;
    entities.push_back(slab2);

    ParticleEmitter* pe = new ParticleEmitter(-2, 0, 0);
    pe->minScaleRange = 0.05;
    pe->maxScaleRange = 0.10;
    pe->scale = 0.005;
    entities.push_back(pe);

    ParticleEmitter* pe2 = new ParticleEmitter(-2, 0, -1);
    pe2->minScaleRange = 0.05;
    pe2->maxScaleRange = 0.10;
    pe2->scale = 0.01;
    entities.push_back(pe2);

    /*Coin* coin3 = new Coin(-1, 0, 0);
    entities.push_back(coin3);*/

}

void Game::update()
{
    ResourceManager::modelShader.use();
    map.update();
    player.update();
    mainCamera.update();
    for (Entity* entity : entities)
        entity->update();

    //Draw sky box
    glDisable(GL_CULL_FACE);
    ResourceManager::skyboxShader.use();
    skyBox.update(mainCamera.viewMatrix, mainCamera.projectionMatrix);
    

    //Update particles
    ParticleSystem::update();
    glEnable(GL_CULL_FACE);

    //AABB to AABB collision
    CollisionInfo info = CollisionHelper::isAABBInsideAABB(entities[3]->bboxMin, entities[3]->bboxMax, entities[4]->bboxMin, entities[4]->bboxMax);
    if (info.collide)
    {
        std::cout << "AABB collision\n";
    }

    //Debug draw AABB and Sphere debug collider
    //AABB and Sphere are 100% accurate
#ifdef DEBUG
    glDisable(GL_CULL_FACE);
    CollisionRenderer::debugShader.use();
    CollisionRenderer::debugShader.setFloat("transparency", 1);
    CollisionRenderer::drawAlignedBoundingBox(entities[3]->bboxMin, entities[3]->bboxMax, mainCamera.projectionMatrix, mainCamera.viewMatrix);
    CollisionRenderer::drawAlignedBoundingBox(entities[4]->bboxMin, entities[4]->bboxMax, mainCamera.projectionMatrix, mainCamera.viewMatrix);
    
    CollisionRenderer::drawAlignedBoundingBox(glm::vec3(-1, 0, -1), glm::vec3(-2, 1, -2), mainCamera.projectionMatrix, mainCamera.viewMatrix);



    CollisionRenderer::debugShader.setFloat("transparency", 0.5);
    CollisionRenderer::drawAlignedBoundingBox(glm::vec3(-1.5, 1.5, -1.5), glm::vec3(-3, -0.5, -1.5), mainCamera.projectionMatrix, mainCamera.viewMatrix);

    //-3.0 -0.5 -1.5,     0, -0.5, -1.5,       -1.5, 1.5, -1.5

    CollisionRenderer::debugShader.setFloat("transparency", 0.3);
    CollisionRenderer::drawBoundingSphere(glm::vec3(player.xPos, player.yPos, player.zPos), player.radius);
    //CollisionRenderer::drawBoundingSphere(glm::vec3(entities[8]->xPos, entities[8]->yPos, entities[8]->zPos), entities[8]->radius);
    glEnable(GL_CULL_FACE);
#endif

    //Point to AABB collision
    if (CollisionHelper::isPointInsideAABB(glm::vec3(player.xPos, 0, player.zPos), entities[3]->bboxMin, entities[3]->bboxMax))
    {
        std::cout << "bbox collide " << ++debugCollisionCount << "\n";
    }

    //Sphere to sphere collision detection
    /*if (CollisionHelper::isSphereInsideSphere(glm::vec3(player.xPos, player.yPos, player.zPos), player.radius, glm::vec3(entities[0]->xPos, entities[0]->yPos, entities[0]->zPos), entities[0]->radius))
    {
        std::cout << "Sphere collide " << ++debugCollisionCount << "\n";
    }*/

    //Sphere to sphere player coin collision detection
    if (!((Coin*)entities[1])->collected && CollisionHelper::isSphereInsideSphere(glm::vec3(player.xPos, player.yPos, player.zPos), player.radius, glm::vec3(entities[1]->xPos, entities[1]->yPos, entities[1]->zPos), entities[1]->radius))
    {
        ((Coin*)entities[1])->collected = true;
        player.coins++;
        std::cout << player.coins << "\n";
    }

    //Proof that debug colliders are accurate to the pixel
    /*if (CollisionHelper::isSphereInsideSphere(glm::vec3(player.xPos, player.yPos, player.zPos), player.radius, glm::vec3(entities[8]->xPos, entities[8]->yPos, entities[8]->zPos), entities[8]->radius))
    {
        std::cout << ++debugCollisionCount << "\n";
    }*/
    
    //Point to sphere
    if (!((Coin*)entities[2])->collected && CollisionHelper::isPointInsideSphere(glm::vec3(player.xPos, player.yPos, player.zPos), glm::vec3(entities[2]->xPos, entities[2]->yPos, entities[2]->zPos), entities[2]->radius))
    {
        ((Coin*)entities[2])->collected = true;
        player.coins++;
        std::cout << player.coins << "\n";
    }

    //Sphere to AABB collision detection
    if (CollisionHelper::isSphereInsideAABB(glm::vec3(player.xPos, 0, player.zPos), player.radius, entities[4]->bboxMin, entities[4]->bboxMax))
    {
        std::cout << "SPHERE AABB COLLISION" << "\n";
    }

    //AABB to Triangle, entities[0]->model.meshes[0].indices[0, 1, 2]

    //TODO: Getter function that returns the transformed vector

    //This performs a vertex test on the AABB
    glm::vec3 tri1 = glm::vec3(entities[0]->model.meshes[0].vertices[entities[0]->model.meshes[0].indices[0]].position.x * entities[0]->scale, entities[0]->model.meshes[0].vertices[entities[0]->model.meshes[0].indices[0]].position.y * entities[0]->scale, entities[0]->model.meshes[0].vertices[entities[0]->model.meshes[0].indices[0]].position.z * entities[0]->scale);
    glm::vec3 tri2 = glm::vec3(entities[0]->model.meshes[0].vertices[entities[0]->model.meshes[0].indices[1]].position.x * entities[0]->scale, entities[0]->model.meshes[0].vertices[entities[0]->model.meshes[0].indices[1]].position.y * entities[0]->scale, entities[0]->model.meshes[0].vertices[entities[0]->model.meshes[0].indices[1]].position.z * entities[0]->scale);
    glm::vec3 tri3 = glm::vec3(entities[0]->model.meshes[0].vertices[entities[0]->model.meshes[0].indices[2]].position.x * entities[0]->scale, entities[0]->model.meshes[0].vertices[entities[0]->model.meshes[0].indices[2]].position.y * entities[0]->scale, entities[0]->model.meshes[0].vertices[entities[0]->model.meshes[0].indices[2]].position.z * entities[0]->scale);

    //Translate these tris by the model matrix
    glm::mat4 mat(1.0f);
    mat = glm::translate(mat, glm::vec3(entities[0]->xPos, entities[0]->yPos, entities[0]->zPos));
    mat = glm::rotate(mat, glm::radians(entities[0]->xRot), glm::vec3(1, 0, 0));
    mat = glm::rotate(mat, glm::radians(entities[0]->yRot), glm::vec3(0, 1, 0));
    mat = glm::rotate(mat, glm::radians(entities[0]->zRot), glm::vec3(0, 0, 1));
    //std::cout << "Tri 1 rots " << entities[0]->xRot << " " << entities[0]->yRot << " " << entities[0]->zRot << "\n";
    //mat = glm::scale(mat, glm::vec3(entities[0]->scale, entities[0]->scale, entities[0]->scale));
    glm::vec4 tri11 = mat * glm::vec4(tri1.x, tri1.y, tri1.z, 1.0f);
    glm::vec4 tri22 = mat * glm::vec4(tri2.x, tri2.y, tri2.z, 1.0f);
    glm::vec4 tri33 = mat * glm::vec4(tri3.x, tri3.y, tri3.z, 1.0f);

    //std::cout << tri1.x << " " << tri1.y << " " << tri1.z << ", " << tri2.x << " " << tri2.y << " " << tri2.z << " " << tri3.x << " " << tri3.y << " " << tri3.z << "\n";

    //REAL
    if (CollisionHelper::isAABBIntersectingTriangle(entities[3]->bboxMin, entities[3]->bboxMax, glm::vec3(tri11.x, tri11.y, tri11.z), glm::vec3(tri22.x, tri22.y, tri22.z), glm::vec3(tri33.x, tri33.y, tri33.z)))
    {
        std::cout << ++debugCollisionCount << " AABB Tri collision\n";
    }

    //CollisionRenderer::drawAlignedBoundingBox(glm::vec3(0, 0, 0), glm::vec3(0.005, 0.005, 0.005), mainCamera.projectionMatrix, mainCamera.viewMatrix);
    glDisable(GL_CULL_FACE);
    CollisionRenderer::drawAlignedBoundingBox(glm::vec3(tri11.x, tri11.y, tri11.z), glm::vec3(tri11.x + 0.005, tri11.y + 0.005, tri11.z + 0.005), mainCamera.projectionMatrix, mainCamera.viewMatrix);
    CollisionRenderer::drawAlignedBoundingBox(glm::vec3(tri22.x, tri22.y, tri22.z), glm::vec3(tri22.x + 0.005, tri22.y + 0.005, tri22.z + 0.005), mainCamera.projectionMatrix, mainCamera.viewMatrix);
    CollisionRenderer::drawAlignedBoundingBox(glm::vec3(tri33.x, tri33.y, tri33.z), glm::vec3(tri33.x + 0.005, tri33.y + 0.005, tri33.z + 0.005), mainCamera.projectionMatrix, mainCamera.viewMatrix);
    glEnable(GL_CULL_FACE);
    //TEST
    //-3.0 -0.5 - 1.5, 0, -0.5, -1.5, -1.5, 1.5, -1.5
    /*if (CollisionHelper::isAABBIntersectingTriangle(glm::vec3(-1, 0, -1), glm::vec3(-2, 1, -2), glm::vec3(-3.0f, -0.5f, -1.5f), glm::vec3(0, -0.5f, -1.5f), glm::vec3(-1.5f, 1.5f, -1.5f)))
    {
        std::cout << "AABB Tri collision\n";
    }*/

    //Sphere to triangle, player entities[0], works I think?
    if (CollisionHelper::isSphereIntersectingTriangle(glm::vec3(player.xPos, player.yPos, player.zPos), player.radius, glm::vec3(tri11.x, tri11.y, tri11.z), glm::vec3(tri22.x, tri22.y, tri22.z), glm::vec3(tri33.x, tri33.y, tri33.z)))
    {
        std::cout << ++debugCollisionCount << " Sphere to tri\n";
    }

    glm::vec3 othertri1 = glm::vec3(entities[5]->model.meshes[0].vertices[entities[5]->model.meshes[0].indices[0]].position.x * entities[5]->scale, entities[5]->model.meshes[0].vertices[entities[5]->model.meshes[0].indices[0]].position.y * entities[5]->scale, entities[5]->model.meshes[0].vertices[entities[5]->model.meshes[0].indices[0]].position.z * entities[5]->scale);
    glm::vec3 othertri2 = glm::vec3(entities[5]->model.meshes[0].vertices[entities[5]->model.meshes[0].indices[1]].position.x * entities[5]->scale, entities[5]->model.meshes[0].vertices[entities[5]->model.meshes[0].indices[1]].position.y * entities[5]->scale, entities[5]->model.meshes[0].vertices[entities[5]->model.meshes[0].indices[1]].position.z * entities[5]->scale);
    glm::vec3 othertri3 = glm::vec3(entities[5]->model.meshes[0].vertices[entities[5]->model.meshes[0].indices[2]].position.x * entities[5]->scale, entities[5]->model.meshes[0].vertices[entities[5]->model.meshes[0].indices[2]].position.y * entities[5]->scale, entities[5]->model.meshes[0].vertices[entities[5]->model.meshes[0].indices[2]].position.z * entities[5]->scale);

    //Translate these tris by the model matrix
    glm::mat4 mat2(1.0f);
    mat2 = glm::translate(mat2, glm::vec3(entities[5]->xPos, entities[5]->yPos, entities[5]->zPos));
    mat2 = glm::rotate(mat2, glm::radians(entities[5]->xRot), glm::vec3(1, 0, 0));
    mat2 = glm::rotate(mat2, glm::radians(entities[5]->yRot), glm::vec3(0, 1, 0));
    mat2 = glm::rotate(mat2, glm::radians(entities[5]->zRot), glm::vec3(0, 0, 1));
    glm::vec4 othertri11 = mat2 * glm::vec4(othertri1.x, othertri1.y, othertri1.z, 1.0f);
    glm::vec4 othertri22 = mat2 * glm::vec4(othertri2.x, othertri2.y, othertri2.z, 1.0f);
    glm::vec4 othertri33 = mat2 * glm::vec4(othertri3.x, othertri3.y, othertri3.z, 1.0f);

    //std::cout << "Tri 2 rots " << glm::radians(entities[5]->xRot) << " " << glm::radians(entities[5]->yRot) << " " << glm::radians(entities[5]->zRot) << "\n";
    //Triangle to triangle, entities[0] and entities[5], 5 is roated +90 on y axis, normals will need to be recalculated
    if (CollisionHelper::isTriangleIntersectingTriangle(glm::vec3(tri11.x, tri11.y, tri11.z), glm::vec3(tri22.x, tri22.y, tri22.z), glm::vec3(tri33.x, tri33.y, tri33.z), glm::vec3(othertri11.x, othertri11.y, othertri11.z), glm::vec3(othertri22.x, othertri22.y, othertri22.z), glm::vec3(othertri33.x, othertri33.y, othertri33.z)))
    {
        std::cout << debugCollisionCount++ << " Triangle intersection\n";
    }
}