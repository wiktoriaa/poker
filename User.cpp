#include "User.h"

User::User(int user_num) {
	number = user_num;
	std::cout << "Gracz " << user_num + 1 << " dolaczyl do gry" << std::endl;
}

void User::replace_cards(Deck &deck) {
	if (!changed) {

		int cards_count;

		std::cout << "Ile kart chcesz wymienic? ";
		input::input_number_range(cards_count, 1, 5);

		changed = true;

		if (cards_count > 5) { cards_count = 5; }

		int change_index;
		bool changed_cards[5];

		for (int i = 0; i < 5; i++) {
			changed_cards[i] = false;
		}

		for (int i = 0; i < cards_count; i++) {
			std::cout << "Wybierz karte do zmiany 1-5: ";

			do {
				input::input_number_range(change_index, 1, 5);

				if (changed_cards[change_index - 1]) {
					std::cout << "Te karte juz wymieniles, wybierz inna: ";
				}

			} while (changed_cards[change_index - 1] == true);

			changed_cards[i] = true;
			
			replace_card(change_index - 1, deck);
		}
	}
	else {
		std::cout << "Nie mozesz juz wymieniac kart" << std::endl;
		input::pause();
	}
}

void User::show_cards() {
	for (auto& card : cards) {
		card.display_card();
	}
}

void User::add_card(Card card) {
	cards.push_back(card);
}

int User::get_user_number() {
	return number + 1;
}

int User::get_points() {
	return points;
}

void User::set_points(int points_sum) {
	points = points_sum;
}

void User::add_points_from_card_with_index(int index) {
	points += cards[index].figure;
}

std::vector<Card>& User::get_user_cards() {
	return cards;
}

bool User::has_card_with_figure(Figure figure) {
	for (auto& card : cards) {
		if (card.figure == figure) {
			return true;
		}
	}
	return false;
}

bool User::has_multiple_card_value(int min_occur, int how_many) {
	int count = 0;
	Figure figure;

	std::vector<Card> tmp_cards = cards;

	for (auto& card : tmp_cards) {
		figure = card.figure;

		count = std::count_if(std::begin(tmp_cards), std::end(tmp_cards),
			[&figure](const Card& obj) { return obj.figure == figure; });

		tmp_cards.erase(std::remove_if(tmp_cards.begin(), tmp_cards.end(),
			[&figure](Card const& s) { return s.figure == figure; }), tmp_cards.end());

		if (count == min_occur) {
			if (how_many == 1) {
				return true;
			}
			else {
				how_many--;
			}
		}
	}
	return false;
}

void User::sort_cards() {
	std::sort(cards.begin(), cards.end(), [](const Card& lhs, const Card& rhs)
		{
			return lhs.figure > rhs.figure;
		});
}

void User::replace_card(int index, Deck &deck) {
	deck.add_card(cards[index]);
	cards[index] = deck.get_random_card();
}