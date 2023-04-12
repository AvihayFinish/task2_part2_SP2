#pragma once
#include <string>
#include <vector>
#include "card.hpp"

namespace ariel {
    class Player {
        private:
            std::string name;
            std::vector<Card> packegeOfPlayer;
            int cardsTaken = 0;
            bool isPlayed = false;
        public:
            Player(std::string name); // constructor
            int stacksize();
            int cardesTaken();
            bool getIsPlayed ();
            void setIsPlayed(bool bol);
            void appendCardsTaken(int amt);
            std::string getName ();
            Card cardPerIndex (std::vector<Card>::size_type ind);
            void popFromPack();
            void pushToPack(Card crd);
            void setCardsTaken(int var);
    };
}
