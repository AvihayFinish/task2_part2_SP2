#include "player.hpp"
#include <string>
using namespace ariel;

Player::Player (std::string name) {
    this->name = name;
}

int Player::stacksize () {
    return this->packegeOfPlayer.size();
}

int Player::cardesTaken () {
    return this->cardsTaken;
}

bool Player::getIsPlayed () {
    return this->isPlayed;
}

void Player::setIsPlayed (bool b) {
    this->isPlayed = b;
}

void Player::appendCardsTaken (int x) {
    this->cardsTaken += x;
}

std::string Player::getName () {
    return this->name;
}

Card Player::cardPerIndex (std::vector<Card>::size_type x) {
    return this->packegeOfPlayer[x];
}

void Player::popFromPack () {
    this->packegeOfPlayer.pop_back();
}

void Player::pushToPack (Card c) {
    this->packegeOfPlayer.push_back(c);
}

void Player::setCardsTaken (int var) {
    this->cardsTaken = var;
}