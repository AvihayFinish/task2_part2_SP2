#include "game.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <random>
using namespace ariel;

Game::Game (Player& pl1, Player& pl2): pO(pl1), pT(pl2) {
    if (this->pO.getIsPlayed() == true || this->pT.getIsPlayed() == true) {
        throw std::runtime_error("one of the players already playing");
    }
    this->draw = 0;
    this->winPo = 0;
    this->winPt = 0;
    this->counter = FOR_COUNTER;
    this->counterCardsToTakePerTurn = 2;
    this->pO.setIsPlayed(true);
    this->pT.setIsPlayed(true);
    this->pO.setCardsTaken(0);
    this->pT.setCardsTaken(0);
    this->saveTurns.clear();
    this->package.clear();
    for (int i = 2; i < 15; i++) {
        values value = static_cast<values>(i);
        for (int j = 0; j < 4; j++) {
            types type = static_cast<types>(j);
            Card c = Card(value, type);
            this->package.push_back(c);
        }
    }

    std::mt19937 rng(std::random_device{}());
    std::shuffle(this->package.begin(), this->package.end(), rng);
    for (std::vector<Card>::size_type i = 0; i < this->package.size(); i++) {
        if (i%2 == 0) {
            this->pO.pushToPack(this->package[i]);
        }
        else if (i%2 != 0) {
            this->pT.pushToPack(this->package[i]);
        }
    }
}

void Game::playTurn() {
    if (&pO == &pT) {
        throw std::runtime_error("you try to runing game with the same player");
    }
    this->DrawIsHappen = true;
    std::string st = "";
    while (DrawIsHappen == true) {
        if ((this->pO.stacksize() == 0 || this->pT.stacksize() == 0)) {
            throw std::runtime_error("the game is over");
        }
        else if (this->pO.cardPerIndex(this->counter).getValue() == Ace && this->pT.cardPerIndex(this->counter).getValue() == Two) {
            this->pT.appendCardsTaken(this->counterCardsToTakePerTurn); 
            this->counterCardsToTakePerTurn = 2;
            this->winPt++;
            this->DrawIsHappen = false;
            st += this->pO.getName() + " played Ace of " + this->pO.cardPerIndex(this->counter).typeString() + " " + this->pT.getName() 
                + " played Two of " +  this->pT.cardPerIndex(this->counter).typeString() + ". " + this->pT.getName() + " win.";
            this->saveTurns.push_back(st);
            removeFromStack(1);
            this->counter = (std::vector<Card>::size_type)(this->pO.stacksize() - 1);
        }
        else if (this->pO.cardPerIndex(this->counter).getValue() == Two && this->pT.cardPerIndex(this->counter).getValue() == Ace) {
            this->pO.appendCardsTaken(this->counterCardsToTakePerTurn);
            this->counterCardsToTakePerTurn = 2;
            this->winPo++;
            this->DrawIsHappen = false;
            st += this->pO.getName() + " played Two of " + this->pO.cardPerIndex(this->counter).typeString() + " " + this->pT.getName() 
                + " played Ace of " + this->pT.cardPerIndex(this->counter).typeString() + ". " + this->pO.getName() + " win.";
            this->saveTurns.push_back(st);
            removeFromStack(1);
            this->counter = (std::vector<Card>::size_type)(this->pO.stacksize() - 1);
        }
        else if (this->pO.cardPerIndex(this->counter).getValue() > this->pT.cardPerIndex(this->counter).getValue()) {
            this->pO.appendCardsTaken(this->counterCardsToTakePerTurn); 
            this->counterCardsToTakePerTurn = 2;
            this->winPo++;
            this->DrawIsHappen = false;
            st += this->pO.getName() + " played " + this->pO.cardPerIndex(this->counter).valueString() + " of "  
                + this->pO.cardPerIndex(this->counter).typeString() + " " + this->pT.getName() + " played " + this->pT.cardPerIndex(this->counter).valueString() 
                + " of " + this->pT.cardPerIndex(this->counter).typeString() + ". " + this->pO.getName() + " win.";   
            this->saveTurns.push_back(st);
            removeFromStack(1);
            this->counter = (std::vector<Card>::size_type)(this->pO.stacksize() - 1);
        }
        else if (this->pO.cardPerIndex(this->counter).getValue() < this->pT.cardPerIndex(this->counter).getValue()) {
            this->pT.appendCardsTaken(this->counterCardsToTakePerTurn);
            this->counterCardsToTakePerTurn = 2;
            this->winPt++;
            this->DrawIsHappen = false;
            st += this->pO.getName() + " played " + this->pO.cardPerIndex(this->counter).valueString() + " of "  
                + this->pO.cardPerIndex(this->counter).typeString() + " " + this->pT.getName() + " played " + this->pT.cardPerIndex(this->counter).valueString() 
                + " of " + this->pT.cardPerIndex(this->counter).typeString() + ". " + this->pT.getName() + " win."; 
            this->saveTurns.push_back(st);
            removeFromStack(1);
            this->counter = (std::vector<Card>::size_type)(this->pO.stacksize() - 1);
        }
        else if (this->pO.cardPerIndex(this->counter).getValue() == this->pT.cardPerIndex(this->counter).getValue()) {
            if (this->counter == 0) {
                if (DrawIsHappen == true) { // when the draw come after another draw that mean there is more cards in the jackpot
                    this->pT.appendCardsTaken(this->counterCardsToTakePerTurn); 
                    this->pO.appendCardsTaken(this->counterCardsToTakePerTurn);
                }
                else { // when the draw come after not draw and counter is 0
                    this->pT.appendCardsTaken(1); 
                    this->pO.appendCardsTaken(1);
                }
                st += this->pO.getName() + " played " + this->pO.cardPerIndex(this->counter).valueString() + " of "  
                    + this->pO.cardPerIndex(this->counter).typeString() + " " + this->pT.getName() + " played " + this->pT.cardPerIndex(this->counter).valueString() 
                    + " of " + this->pT.cardPerIndex(this->counter).typeString() + ". draw. there is no more cards in the jackpots, the game is finished.";
                this->saveTurns.push_back(st);
                removeFromStack(1);
                this->pO.setIsPlayed(false);
                this->pT.setIsPlayed(false);
                return;
            }
            else if (this->counter == 1) {
                this->counterCardsToTakePerTurn += 2;
                st += this->pO.getName() + " played " + this->pO.cardPerIndex(this->counter).valueString() + " of "  
                    + this->pO.cardPerIndex(this->counter).typeString() + " " + this->pT.getName() + " played " + this->pT.cardPerIndex(this->counter).valueString()  
                    + " of " + this->pT.cardPerIndex(this->counter).typeString() + ". draw. ";
                removeFromStack(1);
                this->counter = (std::vector<Card>::size_type)(this->pO.stacksize() - 1);    
            }
            else {
                this->counterCardsToTakePerTurn += 4;
                st += this->pO.getName() + " played " + this->pO.cardPerIndex(this->counter).valueString() + " of "  
                    + this->pO.cardPerIndex(this->counter).typeString() + " " + this->pT.getName() + " played " + this->pT.cardPerIndex(this->counter).valueString()  
                    + " of " + this->pT.cardPerIndex(this->counter).typeString() + ". draw. ";
                removeFromStack(2);  
                this->counter = (std::vector<Card>::size_type)(this->pO.stacksize() - 1);
            }
            this->draw++;
        }
    }
    if (this->pO.stacksize() == 0 || this->pT.stacksize() == 0) {
        this->pO.setIsPlayed(false);
        this->pT.setIsPlayed(false);
    }
}

void Game::printLastTurn() {
    if (this->pO.stacksize() == 26 || this->pT.stacksize() == 26) {
        throw std::runtime_error("we dont play any turn yet");
    }
    else {
        std::cout << this->saveTurns[saveTurns.size() - 1] << std::endl;
    }
}

void Game::playAll() {
    while(this->pO.stacksize() > 0 || this->pT.stacksize() > 0) {
        playTurn();
    }
}

void Game::printWiner() {
    if (this->pO.stacksize() != 0 || this->pT.stacksize() != 0) {
        std::cout << "the game isnt over yet" << std::endl;
    }
    else if (this->pO.cardesTaken() == this->pT.cardesTaken()) {
        std::cout << "this is a draw" << std::endl;
    }
    else if (this->pO.cardesTaken() > this->pT.cardesTaken()) {
        std::cout << this->pO.getName() << std::endl;
    }
    else {
        std::cout << this->pT.getName() << std::endl;
    }
}

void Game::printLog() {
    for (std::vector<Card>::size_type i = 0; i < this->saveTurns.size(); i++) {
        std::cout << this->saveTurns[i] << std::endl;
    }
}

void Game::printStats() {
    if (this->pO.stacksize() == 26 || this->pT.stacksize() == 26) {
        throw std::runtime_error("we dont play any turn yet");
    }
    double turnsPlay = this->winPo + this->winPt + this->draw;
    double poPrecent = ((double)this->winPo / turnsPlay) * 100;
    double ptPrecent = ((double)this->winPt / turnsPlay) * 100;
    double drawPrecent = ((double)this->draw / turnsPlay) * 100;
    std::cout << turnsPlay << " turns is played " << this->pO.getName() << " win a " << this->winPo 
            << " from them, this is %" << poPrecent << " from the turns. " << this->pO.getName() << " won " << this->pO.cardesTaken() 
            << " cards." << std::endl;
    std::cout << turnsPlay << " turns is played " << this->pT.getName() << " win a " << this->winPt 
            << " from them, this is %" << ptPrecent << " from the turns." << this->pT.getName() << " won " << this->pT.cardesTaken() 
            << " cards." << std::endl;
    std::cout << turnsPlay << " turns is played " << this->draw << " draw is happen, this is %" << drawPrecent << " from the turns." << std::endl;
}

void Game::removeFromStack(int x) {
    for (int i = 0; i < x; i++) {
        this->pO.popFromPack();
        this->pT.popFromPack();
    }
}