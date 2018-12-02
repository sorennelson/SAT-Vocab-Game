#include "objectcontroller.h"

ObjectController::ObjectController()
{
    // TODO: Generate all enemy images
    b2Vec2 gravity(0.0f, -10.0f);
    world = new b2World(gravity);
}

ObjectController::~ObjectController()
{
    delete targetedEnemy;
    delete world;
}

GameObjects::Player ObjectController::createPlayer()
{
    // TO FIX: Position
    GameObjects::posTuple pos({0, 0});
    player = GameObjects::Player(pos);
    return player;
}

void ObjectController::createRoundOfEnemies(int round)
{
    LoadWords::createRoundWords(round);
}

GameObjects::Enemy ObjectController::createEnemy(int round)
{
    // TODO: Box2D
    // TODO: EnemyImageGenerate

//     GameObjects::Enemy enemy(round, {0,0}, LoadWords::getWord());
    // load image
//    if (enemy.getWord() != "")
//    {
//        currentEnemies.push_back(enemy); /*adding comment for claification, calling the default connstructor of enemy will give a starting pos of 0,0
//                                                                          but a position can be specified by providing a tuple<unsigned int, usigned int> - which can be done with {,}*/
//        return enemy;
//    }
//    else
//    {
//        stopCreatingEnemies = true;
//    }
}

GameObjects::Projectile ObjectController::createProjectile()
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
    GameObjects::Projectile projectile({0,0});
    projectiles.push_back(projectile);
    return projectile;
}

bool ObjectController::letterTyped(char letter)
{
    if (targetedEnemy == nullptr)
    {
        // shoot closest enemy with starting letter = letter
        double lowestDistance = DBL_MAX;
        for (unsigned int i = 0; i < currentEnemies.size(); i++)
        {
            if (currentEnemies[i].startsWith(letter))
            {
                double distance = currentEnemies[i].distanceTo(player.getPos());

                if (distance < lowestDistance)
                {
                    lowestDistance = distance;

                    targetedEnemy = new GameObjects::TargetedEnemy(currentEnemies[i]);
                    currentEnemies.erase(currentEnemies.begin() + i);
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

GameObjects::TargetedEnemy ObjectController::getTargetedEnemy()
{
    return *targetedEnemy;
}

bool ObjectController::isEnemyKilled()
{
    return targetedEnemy == nullptr;
}

bool ObjectController::isRoundEnd()
{
    return targetedEnemy == nullptr && currentEnemies.size() == 0;
}

bool ObjectController::isEndGame()
{
    return player.getHealth() == 0;
}
