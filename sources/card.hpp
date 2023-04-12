#pragma once
#include <string>

namespace ariel {

    enum values {
        Two = 2,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Prince,
        Queen,
        King,
        Ace
    };

    enum types {
        hearts,
        spades,
        clubs,
        diamonds
    };

    class Card {
        values value;
        types type;
    public:
        Card (values val, types typ);
        values getValue ();
        types getType();
        std::string typeString();
        std::string valueString();
    };
}

