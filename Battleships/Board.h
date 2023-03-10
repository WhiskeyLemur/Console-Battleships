#pragma once
#include <array>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "Coordinate.h"
#include "Constants.h"
#include "Ship.h"

class Board
{
public:
	Board();
	virtual void const display();
	void place_ship(Coordinate origin_coord, int ship_length, char orientation, int ship_index);
	bool check_if_placeable(Coordinate origin_coord, int ship_length, char orientation);
	bool recieve_strike(Coordinate coord);
	void const list_ships_sunk();
	bool const check_loss();

protected:
	const enum class Tile
	{
		water,
		ship,
		hit_ship,
		error,
	};

	// Keeps track of the unhit coordinates occupied by each ship on the board.
	// Ordered the same as Constants::ships.
	std::array<std::vector<Coordinate>, 5> living_ship_coords {};

	std::array<std::array<Tile, 10>, 10> board;
	std::vector<std::string> names_of_sunk_ships;
	void init_board();
	char const get_tile_char(Tile& tile);

};

