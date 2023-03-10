#pragma once

#include <array>
#include <string>

#include "Ship.h"

namespace Constants
{
	static const std::array<Ship, 5> ships
	{ {
//		Name        Length
		{"Battleship", 4},
		{"Carrier",    5},
		{"Cruiser",    3},
		{"Destroyer",  2},
		{"Submarine",  3},
	}};
}