#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <cctype> // toupper()
#include <stdlib.h>

#include "AIBoard.h"
#include "Coordinate.h"
#include "Constants.h"

class Game
{
public:
	Game();

private:
	Board player_board;
	AIBoard enemy_board;

	void setup();
	Coordinate coordinate_prompt();
	void game_loop();
	Coordinate strike_prompt();
	void const display_boards();

	bool const validate_coord_input(const std::string& coord_input);
	char const orientation_prompt();
	Coordinate string_to_coord(const std::string& coord_input);

	bool const check_win();
};

