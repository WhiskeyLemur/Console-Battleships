#include "Board.h"

Board::Board()
{
	init_board();
}

const void Board::display()
{
	for (int i = 0; i < 10; ++i)
	{
		// Vertical coordinates, fixes annoying offset with 10
		i != 9 ? std::cout << i + 1 << " | " : std::cout << i + 1 << "| ";

		for (int j = 0; j < 10; ++j)
		{
			std::cout << get_tile_char(board[j][i]) << " ";
		}
		std::cout << "\n";
	}
	// Horizontal coordinates
	std::cout << "    A B C D E F G H I J\n";
}

void Board::init_board()
{
	for (auto& column : board)
	{
		for (auto& tile : column)
		{
			tile = Tile::water;
		}
	}
}

const char Board::get_tile_char(Tile& tile)
{
	static const std::unordered_map<Tile, char> tile_chars
	{
		{Tile::water, '.'},
		{Tile::ship, 'O' },
		{Tile::hit_ship, 'x' },
		{Tile::error, 'E'},
	};
	return tile_chars.at(tile);
}

bool const Board::check_loss()
{
	int empty_coord_vectors{};
	for (auto coord_vector : living_ship_coords)
	{
		if (coord_vector.empty()) { empty_coord_vectors++; }
	}
	return (empty_coord_vectors == 5);
}

void Board::place_ship(Coordinate origin_coord, int ship_length, char orientation, int ship_index)
{
	for (int i = 0; i < ship_length; ++i)
	{
		Coordinate placement_coord{};
		switch (orientation)
		{
		case 'N':
			placement_coord = {origin_coord.x, origin_coord.y-i};
			break;

		case 'E':
			placement_coord = {origin_coord.x+i, origin_coord.y};
			break;

		case 'S':
			placement_coord = {origin_coord.x, origin_coord.y+i};
			break;

		case 'W':
			placement_coord = {origin_coord.x-i, origin_coord.y};
			break;
		}

		board[placement_coord.x][placement_coord.y] = Tile::ship;

		// Records the coordinate of the placed ship tile in the corresponding coordinate vector
		living_ship_coords[ship_index].emplace_back(placement_coord);
	}
}

// This only cost me six aneurysms!
bool Board::check_if_placeable(Coordinate coord, int ship_length, char orientation)
{
	int clear_tiles{};
	for (int i = 0; i < ship_length; ++i)
	{
		Coordinate next_tile{};

		// If statements ensure enough board space
		switch (orientation)
		{
		case 'N':
			if (coord.y + 2 <= ship_length) { return false; };
			next_tile = { coord.x, coord.y - i };
			break;

		case 'E':
			if (coord.x > 10 - ship_length) { return false; }
			next_tile = { coord.x + i, coord.y };
			break;

		case 'S':
			if (coord.y > 10 - ship_length) { return false; }
			next_tile = { coord.x, coord.y + i };
			break;

		case 'W':
			if (coord.x + 2 <= ship_length) { return false; }
			next_tile = { coord.x - i, coord.y };
			break;
		}

		// Ensures no other ships in the way
		if (board[next_tile.x][next_tile.y] == Tile::water) { clear_tiles++; }
	}
	return { clear_tiles >= ship_length };
}

bool Board::recieve_strike(Coordinate hit_coord)
{
	if (board[hit_coord.x][hit_coord.y] == Tile::ship)
	{
		board[hit_coord.x][hit_coord.y] = Tile::hit_ship;

		// Remove the coordinate of the hit from the living ship coordinates vector
		for (int i = 0; i < living_ship_coords.size(); ++i)
		{
			auto& coord_vector = living_ship_coords[i];
			for (int j = 0; j < coord_vector.size(); ++j)
			{
				if (coord_vector[j] == hit_coord)
				{
					coord_vector.erase(coord_vector.begin() + j);
					if (coord_vector.empty())
					{
						names_of_sunk_ships.emplace_back(Constants::ships[i].name);
					}
					return true;
				}
			}
		}
	}
	return false;
}

void const Board::list_ships_sunk()
{
	std::cout << "Sunk ships: ";
	if (names_of_sunk_ships.empty())
	{
		std::cout << "None.\n";
		return;
	}

	for (const auto& name : names_of_sunk_ships)
	{
		std::cout << name << "   ";
	}
	std::cout << '\n';
}


