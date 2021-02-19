#include "Card.h"

Card::Card(Color x, Figure y) {
    color = x;
    figure = y;
}

void Card::display_card() {
    std::cout << "|";

    switch (color) {
    case Color::club:
        std::cout << "trefl";
        break;
    case Color::diamond:
        std::cout << "karo";
        break;
    case Color::heart:
        std::cout << "kier";
        break;
    case Color::spade:
        std::cout << "pik";
        break;
    }
    std::cout << " ";

    switch (figure) {
    case Figure::ace:
        std::cout << "as";
        break;
    case Figure::k2:
        std::cout << "2";
        break;
    case Figure::k3:
        std::cout << "3";
        break;
    case Figure::k4:
        std::cout << "4";
        break;
    case Figure::k5:
        std::cout << "5";
        break;
    case Figure::k6:
        std::cout << "6";
        break;
    case Figure::k7:
        std::cout << "7";
        break;
    case Figure::k8:
        std::cout << "8";
        break;
    case Figure::k9:
        std::cout << "9";
        break;
    case Figure::k10:
        std::cout << "10";
        break;
    case Figure::jack:
        std::cout << "walet";
        break;
    case Figure::queen:
        std::cout << "dama";
        break;
    case Figure::king:
        std::cout << "krol";
        break;
    }
    std::cout << "|";
}

Deck::Deck() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            cards.emplace_back(static_cast<Color>(i), static_cast<Figure>(j));
        }
    }
}

int Deck::deck_size() {
    return cards.size();
}

Card Deck::get_random_card() {
    int r;
    r = rand() % cards.size();

    Card ret = cards[r];
    remove_card(r);
    return ret;
}

void Deck::remove_card(int index) {
    cards.erase(cards.begin() + index);
}

void Deck::add_card(Card card) {
    cards.push_back(card);
}