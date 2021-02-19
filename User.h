#pragma once
#include "Card.h"
#include "input.h"

#include <cstdlib>
#include <ctime>
#include <algorithm>

class User
{
public:
	User(int user_num);
	void replace_cards(Deck &deck);
	void show_cards();
	void add_card(Card card);
	int get_user_number();
	int get_points();
	void set_points(int points_sum);
	void add_points_from_card_with_index(int index);
	std::vector<Card>& get_user_cards();
	bool has_card_with_figure(Figure figure);
	bool has_multiple_card_value(int min_occur, int how_many = 1);
	void sort_cards();

private:
	std::vector<Card> cards;
	int number;
	int points = 0;
	bool changed = false;

	void replace_card(int index, Deck &deck);
};





