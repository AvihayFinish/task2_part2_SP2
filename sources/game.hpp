#pragma once
#include "player.hpp"
#include "card.hpp"

namespace ariel {
    const int FOR_COUNTER = 25;

    class Game {
        Player& pO;
        Player& pT;
        std::vector<Card> package;
        std::vector<std::string> saveTurns;
        std::vector<Card>::size_type counter;
        int draw;
        int winPo;
        int winPt;
        int counterCardsToTakePerTurn;
        bool DrawIsHappen = true;
    public:
        Game(Player& pl1, Player& pl2); // constructor
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
        void removeFromStack(int ind);
    };
}