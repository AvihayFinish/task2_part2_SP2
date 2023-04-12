#include "card.hpp"
using namespace ariel;

Card::Card (values v, types t) {
    this->value = v;
    this->type = t;
}

values Card::getValue () {
    return this->value;
}

types Card::getType () {
    return this->type;
}

std::string Card::typeString () {
    if (this->type == hearts) {
        return "hearts";
    }
    else if (this->type == spades) {
        return "spades";
    }
    else if (this->type == clubs) {
        return "clubs";
    }
    else {
        return "diamonds";
    }
}

std::string Card::valueString () {
    if (this->value == Ace) {
        return "Ace";
    }
    else if (this->value == Two) {
        return "Two";
    }
    else if (this->value == Three) {
        return "Three";
    }
    else if (this->value == Four) {
        return "Four";
    }
    else if (this->value == Five) {
        return "Five";
    }
    else if (this->value == Six) {
        return "Six";
    }
    else if (this->value == Seven) {
        return "Seven";
    }
    else if (this->value == Eight) {
        return "Eight";
    }
    else if (this->value == Nine) {
        return "Nine";
    }
    else if (this->value == Ten) {
        return "Ten";
    }
    else if (this->value == Prince) {
        return "Prince";
    }
    else if (this->value == Queen) {
        return "Queen";
    }
    else {
        return "King";
    }
}