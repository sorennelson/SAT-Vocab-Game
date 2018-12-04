#include "objectcontroller.h"
#include <stdlib.h>
#include <QImage>


ObjectController::ObjectController()
{
    // TODO: Generate all enemy images
    b2Vec2 gravity(0.0f, 0.0f);
    world = new b2World(gravity);

    // Initializing body defs
    enemyBodyDef.type = b2_dynamicBody;
    enemyBodyDef.angle = 0;

    playerBodyDef.type = b2_staticBody;
    playerBodyDef.angle = 0;
}

ObjectController::~ObjectController()
{
    delete targetedEnemy;
    delete player;
    delete world;
}

void ObjectController::createPlayer()
{
    // TO FIX: B2D
//    GameObjects::posTuple pos({0, 0});
//    player = new GameObjects::Player(pos, nullptr);
//    objectsOnScreen.push_back(player);
}

void ObjectController::createRoundOfEnemies(int round)
{
    LoadWords::createRoundWords(round);
}

void ObjectController::createEnemy(int round)
{
    // Set starting position dynamically when creating enemy objects based on window size
    enemyBodyDef.position.Set((rand() % (int)windowSizeX*2) - windowSizeX, windowSizeY);

    b2Body *enemyBody = world->CreateBody(&enemyBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,1);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;

    enemyBody->CreateFixture(&boxFixtureDef);

    // TODO: 1) Add speed
    //       2) Add image
    GameObjects::Enemy *enemy = new GameObjects::Enemy(round, LoadWords::getWord(), QImage(), {enemyBodyDef.position.x, windowSizeY}, *enemyBody);
    if (enemy->getWord() != "")
    {
        objectsOnScreen.push_back(enemy);
    }
    else
    {
        stopCreatingEnemies = true;
    }
}

void ObjectController::createProjectile()
{
    if (targetedEnemy == nullptr)
    {
        // miss
    }
    else
    {
        // hit

        if (targetedEnemy->wasDestroyed())
        {
            targetedEnemy = nullptr;
            // TODO: create explosion
        }
    }

    // TODO: Box2D
//    GameObjects::Projectile projectile = new GameObjects::Projectile({0,0}, );
//    objectsOnScreen.push_back(projectile);
}

bool ObjectController::letterTyped(char letter)
{
    if (targetedEnemy == nullptr)
    {
        // shoot closest enemy with starting letter = letter
        double lowestDistance = DBL_MAX;
        for (unsigned int i = 0; i < objectsOnScreen.size(); i++)
        {
            if (objectsOnScreen[i]->isOfType(GameObjects::Type::enemy))
            {
                GameObjects::Enemy enemy = *(static_cast<GameObjects::Enemy *>(objectsOnScreen[i]));
                if (enemy.startsWith(letter))
                {
                    double distance = enemy.distanceTo(player->getPos());

                    if (distance < lowestDistance)
                    {
                        lowestDistance = distance;
                        targetedEnemy = new GameObjects::TargetedEnemy(enemy, i);
                        objectsOnScreen[i] = targetedEnemy;
                    }
                }
            }
        }
        if (targetedEnemy != nullptr)
        {
            targetedEnemy->shoot(letter);
        }
        return targetedEnemy == nullptr;
    }
    else
    {
        return targetedEnemy->shoot(letter);
    }
}

void ObjectController::updateObjectPositions()
{
    // All body positions within world get updates after calling Step()
    world->Step(timeStep, velocityIterations, positionIterations);

    // TO FIX: Currently creating enemies every 2 seconds
    if (!stopCreatingEnemies && ++frameCounter % 2000 == 0)
    {
        // TO FIX: Currently round is constant 1
        createEnemy(1);
    }
}

bool ObjectController::isEnemyKilled()
{
    return targetedEnemy == nullptr;
}

bool ObjectController::isRoundEnd()
{

    return targetedEnemy == nullptr && objectsOnScreen.size() == 1;
}

bool ObjectController::isEndGame()
{
    return player->getHealth() == 0;
}
