#include "Game.h"

Game::Game(int gamers_count) {
	for (int i = 0; i < gamers_count; i++) {
		add_user(i);
	}

	deal_the_cards();
}

void Game::start_game() {
	for (auto& current_user : users) {
		user_step(current_user);
	}

	get_scores();
}

void Game::add_user(int x) {
	users.emplace_back(x);
}

void Game::end_game() {
	exit(0);
}

void Game::deal_the_cards() {
	for (auto& user : users) {
		for (int i = 0; i < max_cards_count; i++) {
			user.add_card(deck.get_random_card());
		}
	}
}

void Game::user_step(User &user) {
	std::string choice;

	while (true) {
		system("cls");

		std::cout << "KARTY GRACZA " << user.get_user_number() << std::endl << std::endl;
		user.show_cards();
		std::cout << std::endl << std::endl;

		std::cout << "********************************************" << std::endl;
		std::cout << "* Wybierz, co chcesz zrobic:               *" << std::endl;
		std::cout << "* quit- zakoncz gre                        *" << std::endl;
		std::cout << "* change- wymien karty                     *" << std::endl;
		std::cout << "* cheat- podejrzyj karty innych            *" << std::endl;
		std::cout << "* play- przejdz do kolejnej fazy rozgrywki *" << std::endl;
		std::cout << "*                                          *" << std::endl;
		std::cout << "********************************************" << std::endl;

		std::cout << "GRACZ " << user.get_user_number() << "> ";
		input::input(choice);

		if (choice == "play") {
			calculate_points(user);
			return;
		}
		else if (choice == "change") {
			user.replace_cards(deck);
		}
		else if (choice == "cheat") {
			show_all_users_cards();
		}
		else if (choice == "quit") {
			end_game();
		}

	}

}

void Game::show_all_users_cards() {
	system("cls");

	for (auto& user : users) {
		std::cout << "Karty GRACZA " << user.get_user_number() << std::endl;
		user.show_cards();
		std::cout << std::endl << std::endl;
	}

	input::pause();
}

void Game::calculate_points(User &user) {

	user.sort_cards();
	int points = 0;

	if (royal_flush(user)) {
		points += royal_flush_points;
	}
	else if (straight_flush(user)) {
		points += straight_flush_points;
	}
	else if (four_of_a_kind(user)) {
		points += four_of_kind_points;
	}
	else if (full_house(user)) {
		points += full_house_points;
	}
	else if (flush(user)) {
		points += flush_points;
	}
	else if (straight(user)) {
		points += straigh_points;
	}
	else if (three_of_a_kind(user)) {
		points += three_of_kind_points;
	}
	else if (two_pair(user)) {
		points += two_pairs_points;
	}
	else if (one_pair(user)) {
		points += pair_points;
	}

	user.set_points(points);
}

bool Game::flush(User &user) {
	std::vector<Card>& curr_cards = user.get_user_cards();
	Color color = curr_cards[0].color;

	for (auto card = std::next(curr_cards.begin()); card != curr_cards.end(); ++card) {
		if (card->color != color) {
			return false;
		}
	}
	return true;
}

bool Game::royal_flush(User &user) {
	return (flush(user) &&
			user.has_card_with_figure(Figure::ace)
			&& user.has_card_with_figure(Figure::king)
			&& user.has_card_with_figure(Figure::queen)
			&& user.has_card_with_figure(Figure::jack)
			&& user.has_card_with_figure(Figure::k10)
			);
}

bool Game::straight_flush(User &user) {
	return (flush(user) &&
			user.has_card_with_figure(Figure::k7)
			&& user.has_card_with_figure(Figure::k8)
			&& user.has_card_with_figure(Figure::k9)
			&& user.has_card_with_figure(Figure::k10)
			&& user.has_card_with_figure(Figure::jack)
			);
}

bool Game::four_of_a_kind(User &user) {
	return (user.has_multiple_card_value(4));
}

bool Game::full_house(User &user) {
	return (user.has_multiple_card_value(3) && user.has_multiple_card_value(2));
}

bool Game::straight(User &user) {
	std::vector <Card> user_cards = user.get_user_cards();

	return (user_cards[0].figure == (user_cards[1].figure + 1)
			&& user_cards[1].figure == (user_cards[2].figure + 1)
			&& user_cards[2].figure == (user_cards[3].figure + 1)
			&& user_cards[3].figure == (user_cards[4].figure + 1)
			||
			user_cards[0].figure == Figure::ace
			&& user_cards[4].figure == Figure::k2
			&& user_cards[3].figure == Figure::k3
			&& user_cards[2].figure == Figure::k4
			&& user_cards[1].figure == Figure::k5);
}

bool Game::three_of_a_kind(User &user) {
	return (user.has_multiple_card_value(3));
}

bool Game::two_pair(User &user) {
	return (user.has_multiple_card_value(2, 2));
}

int Game::one_pair(User &user) {
	return (user.has_multiple_card_value(2));
}

void Game::sort_users() {
	std::sort(users.begin(), users.end(), [](User& lhs, User& rhs)
		{
			return lhs.get_points() > rhs.get_points();
		});

	for (unsigned int i = 0; i < users.size() - 1; i++) {
		int highest_card_index = 0;

		while (users[i].get_points() == users[i + 1].get_points() && highest_card_index < 5) {
			users[i].add_points_from_card_with_index(highest_card_index);
			users[i + 1].add_points_from_card_with_index(highest_card_index);
			highest_card_index++;
		}

		if (users[i].get_points() < users[i + 1].get_points()) {
			std::swap(users[i], users[i + 1]);
		}
	}
}

void Game::get_scores() {
	system("cls");

	sort_users();

	std::cout << "RANKING" << std::endl << std::endl;

	for (auto& user : users) {
		std::cout << "GRACZ " << user.get_user_number() << std::endl << std::endl;
		user.show_cards();
		std::cout << " " << " punkty: " << user.get_points() << std::endl << std::endl;
	}

	show_winner();
}

void Game::show_winner() {
	if (users.size() > 1 && users.begin()->get_points() > std::next(users.begin())->get_points()) {
		std::cout << "Wygrywa GRACZ " << users[0].get_user_number() << std::endl;
	}
	else {
		std::cout << "Brak zwyciezcy" << std::endl;
	}
}