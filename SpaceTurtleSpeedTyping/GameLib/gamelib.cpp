#include "gamelib.h"


GameLib::GameLib()
{
    hitStreak = 0;
    totalShotCount = 0;
    correctShotCount = 0;
    totalKillCount = 0;
}

void GameLib::startRound()
{
    round++;
    Load::createRoundWords(round);
    QTimer::singleShot(0, this, SLOT(createEnemies()));
}

void GameLib::createEnemies()
{
    Enemy enemy(round);
    if (enemy.getWord() != "")
    {
        currentEnemies.push_back(Enemy(round));

        int enemyInterval = 2500;
        QTimer::singleShot(enemyInterval, this, SLOT(createEnemies()));
    }
}




