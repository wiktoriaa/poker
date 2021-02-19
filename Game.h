#pragma once
#include "User.h"

class Game
{
	public:
		explicit Game(int gamers_count);
		void start_game();
		void add_user(int x);
		void end_game();

	private:
		std::vector<User> users;
		Deck deck;
		int max_cards_count = 5;

		const int pair_points			= 50;
		const int two_pairs_points		= 100;
		const int three_of_kind_points  = 150;
		const int straigh_points		= 200;
		const int flush_points			= 250;
		const int full_house_points		= 300;
		const int four_of_kind_points   = 350;
		const int straight_flush_points = 400;
		const int royal_flush_points    = 450;

		void deal_the_cards();
		void user_step(User &user);
		void show_all_users_cards();
		void calculate_points(User &user);
		bool flush(User &user);
		bool royal_flush(User &user);
		bool straight_flush(User &user);
		bool four_of_a_kind(User &user);
		bool full_house(User &user);
		bool straight(User &user);
		bool three_of_a_kind(User &user);
		bool two_pair(User &user);
		int one_pair(User &user);
		void sort_users();
		void get_scores();
		void show_winner();
};

