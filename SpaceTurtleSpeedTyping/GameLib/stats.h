#ifndef STATS_H
#define STATS_H

//#include "player.h"
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <map>

class Stats
{
    public:
        Stats();

        void addRound();
        int getRound();
        void addTypeCount(bool isCorrectLetter);
        double getCorrectRate();
        int getTotalType();
        int getCorrectType();
        void addTotalKill();
        int getTotalKill();

        int getLongestHitStreak();
        // todo: load stats text file 3 highest scores
        bool highScore(bool isGameDone, int score);

        const std::map<std::string, double>& getAllStats();

    private:
        int round;
        int totalTypeCount;
        int correctTypeCount;
        int totalKillCount;
        int hitStreak;
        int longestHitStreak;
        std::map<std::string, double> statsMap;
        int getScore();
};

#endif // STATS_H
