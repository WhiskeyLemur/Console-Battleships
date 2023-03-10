#include "AIBoard.h"

const void AIBoard::display()
{
	for (int i = 0; i < 10; ++i)
	{
		// Vertical coordinates, fixes annoying offset with 10
		i != 9 ? std::cout << i + 1 << " | " : std::cout << i + 1 << "| ";

		for (int j = 0; j < 10; ++j)
		{
			Coordinate board_coord{ j, i };

			if (std::count(revealed_coordinates.begin(), revealed_coordinates.end(), board_coord))
			{ 
				std::cout << get_tile_char(board[j][i]) << " ";
			}
			else 
			{ 
				std::cout << "? ";
			}
		}
		std::cout << "\n";
	}
	// Horizontal coordinates
	std::cout << "    A B C D E F G H I J\n";
}

void AIBoard::place_ships()
{
	std::uniform_int_distribution rand_coord{ 0,9 };

	for (int i = 0; i < Constants::ships.size(); ++i)
	{
		const Ship& ship = Constants::ships[i];

		bool placed = false;
		while(!placed)
		{
			Coordinate coord = { rand_coord(rand),rand_coord(rand) };
			if (check_if_placeable(coord, ship.length, 'N'))
			{
				place_ship(coord, ship.length, 'N', i);
				placed = true;
			}	
		}
	}
}

Coordinate AIBoard::make_strike()
{
	std::uniform_int_distribution rand_coord{ 0,9 };
	return { rand_coord(rand),rand_coord(rand) };
}

void const AIBoard::add_revealed_coordinate(Coordinate coord)
{
	revealed_coordinates.emplace_back(coord);
}
