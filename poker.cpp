#include "Game.h"

int main() {
    srand(time(NULL));

    int gamers_count;

    std::cout << "Podaj liczbe graczy: ";
    input::input_number_range(gamers_count, 1, 4);

    Game game(gamers_count);
    input::pause();

    game.start_game();

    return 0;
}


