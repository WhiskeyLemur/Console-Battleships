#pragma once
#include <random>
#include <vector>
#include <algorithm>

#include "Board.h"

class AIBoard
	: public Board
{
public:
	void place_ships();
	Coordinate make_strike();
	void const add_revealed_coordinate(Coordinate coord);
	const void display() override;

private:
	std::vector<Coordinate> revealed_coordinates;
	std::mt19937 rand{ std::random_device{}() };
};

