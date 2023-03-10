#include "Game.h"

Game::Game()
{
	system("Color 02");
	std::cout << "BATTLESHIPS.\n";
	setup();
	game_loop();
}

void Game::setup()
{
	for (int i = 0; i < Constants::ships.size(); ++i)
	{
		const Ship& ship = Constants::ships[i];

		// Ship placement parameters
		Coordinate placement_coord{};
		char orientation{};

		bool placement_success = false;
		while (!placement_success)
		{
			std::cout << "== SETUP PHASE == \n\n";
			player_board.display();
			std::cout << "Place your " << ship.name << " (length " << ship.length << ").\n";

			placement_coord = coordinate_prompt();
			orientation = orientation_prompt();

			system("cls");
			if (player_board.check_if_placeable(placement_coord, ship.length, orientation)) // Room for ship?
			{
				player_board.place_ship(placement_coord, ship.length, orientation, i);
				placement_success = true;
			}
			else { std::cout << "\n [ There is no room for that ship there! ]\n"; }
		}
	}
	enemy_board.place_ships();
}

//====================================================================================================
// Prompts and validation
//====================================================================================================
Coordinate Game::coordinate_prompt()
{
	bool valid = false;
	while (!valid)
	{
		std::cout << "Coordinate (J10, E5, etc...): ";
		std::string coord_input;
		std::cin >> coord_input;

		if(validate_coord_input(coord_input))
		{
			std::cout << '\n';
			valid = true;
			return string_to_coord(coord_input);
		}
		std::cout << "\nInvalid coordinate!\n";
	}
}

bool const Game::validate_coord_input(const std::string& coord_input)
{
	char letter_coord = std::toupper(coord_input[0]);
	int number_coord{};
	std::stringstream(coord_input.substr(1)) >> number_coord;

	if (65 <= letter_coord && letter_coord <= 74	// First character between A and J?
	&&  (1 <= number_coord && number_coord <= 10))	// Rest of string a number between 1 and 10?
	{ return true; }
	  return false;
}

char const Game::orientation_prompt()
{
	bool valid = false;
	while (!valid)
	{
		std::cout << "Orientation (N, E, S, W): ";;
		char orientation{};
		std::cin >> orientation;
		orientation = std::toupper(orientation);

		if (orientation == 'N' || orientation == 'S' || orientation == 'E' || orientation == 'W')
		{
			std::cout << '\n';
			valid = true;
			return orientation;
		}
		std::cout << "\nInvalid orientation!\n";
	}
}

Coordinate Game::strike_prompt()
{
	std::cout << "\nMake your strike! ";
	return coordinate_prompt();
}
//====================================================================================================
//====================================================================================================

void Game::game_loop()
{
	display_boards();

	bool turn = true;
	bool game_over = false;
	while (!game_over)
	{	
		bool hit_success = false;
		Coordinate strike_coord{};

		if (turn) 
		{ 
			strike_coord = strike_prompt();
			hit_success = enemy_board.recieve_strike(strike_coord);
			enemy_board.add_revealed_coordinate(strike_coord);
			display_boards();

			std::cout << "\nYou strike...";
			hit_success ? std::cout << "it's a hit!\n" : std::cout << "sploosh! Miss.\n";
			system("pause");
		}
		else 
		{ 
			strike_coord = enemy_board.make_strike();
			hit_success = player_board.recieve_strike(strike_coord);
			display_boards();

			std::cout << "\nYour enemy strikes....";
			hit_success ? std::cout << "it's a hit!\n" : std::cout << "it's a miss!";
		}
		game_over = check_win();
		turn = !turn;
	}
}

Coordinate Game::string_to_coord(const std::string& coord_input)
{
	int number_coord{};
	char letter_coord = std::toupper(coord_input[0]);
	std::stringstream(coord_input.substr(1)) >> number_coord;

	//  Ex: J10 -> {9, 9}
	return { letter_coord - 65, number_coord - 1 };
}

void const Game::display_boards()
{
	system("cls");
	std::cout << "== BATTLESHIPS ==\n";

	std::cout << "[PLAYER]:\n";
	player_board.display();
	player_board.list_ships_sunk();

	std::cout << "\n|---------------------|\n";

	std::cout << "\n[ENEMY]:\n";
	enemy_board.display();
	enemy_board.list_ships_sunk();
}

bool const Game::check_win()
{
	if (enemy_board.check_loss())
	{
		std::cout << "\n\nYOU WIN!\n\n";
		return true;
	}
	else if (player_board.check_loss())
	{
		std::cout << "\n\nYOUR ENEMY WINS!\n\n";
		return true;
	}
	return false;
}
