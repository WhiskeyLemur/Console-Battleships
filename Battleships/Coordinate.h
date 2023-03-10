#pragma once
struct Coordinate
{
	int x;
	int y;

	auto operator <=>(const Coordinate& c) const = default;
};