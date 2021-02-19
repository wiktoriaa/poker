#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

enum Color : int {
    club = 0,
    diamond = 1,
    heart = 2,
    spade = 3
};

enum Figure : int {
    k2 = 0,
    k3 = 1,
    k4 = 2,
    k5 = 3,
    k6 = 4,
    k7 = 5,
    k8 = 6,
    k9 = 7,
    k10 = 8,
    jack = 9,
    queen = 10,
    king = 11,
    ace = 12
};

class Card {
    public:
        Color color;
        Figure figure;

        Card(Color x, Figure y);
        void display_card();
};

class Deck {
    public:
        Deck();
        int deck_size();
        Card get_random_card();
        void remove_card(int index);
        void add_card(Card card);

    private:
        std::vector <Card> cards;
};



