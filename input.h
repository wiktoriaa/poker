#pragma once
#include <string>
#include <algorithm>

namespace input {
	inline bool is_number(const std::string& s)
	{
		return !s.empty() && std::find_if(s.begin(),
			s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
	}

	inline void input(std::string &x) {
		std::cin >> x;
	}

	inline void input(int &x) {
		std::string tmp = "a";

		while (!is_number(tmp)) {
			std::cin >> tmp;
		}

		x = std::stoi(tmp);
	}

	inline void input_number_range(int& x, int min, int max) {
		while (true) {
			input(x);

			if (x >= min && x <= max) {
				break;
			}
		}
	}

	inline void pause() {
		std::cout << "Aby kontynuowac, wcisnij enter...";
		std::cin.ignore();
		std::cin.ignore();
	}
}