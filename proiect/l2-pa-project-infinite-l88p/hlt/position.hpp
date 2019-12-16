#pragma once

#include <iostream>
#include <array>
#include "log.hpp"

using std::string;

namespace hlt
{
    enum class Direction: char
    {
        NORTH = 'n',
        EAST = 'e',
        SOUTH = 's',
        WEST = 'w',
        STILL = 'o'
    };

    static const std::array<Direction, 4> ALL_CARDINALS =
    {
        Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST
    };

    static Direction invert_direction(Direction direction)
    {
        switch (direction)
        {
            case Direction::NORTH:
                return Direction::SOUTH;
            case Direction::SOUTH:
                return Direction::NORTH;
            case Direction::EAST:
                return Direction::WEST;
            case Direction::WEST:
                return Direction::EAST;
            case Direction::STILL:
                return Direction::STILL;
            default:
                log::log(string("Error: invert_direction: unknown direction ")
                         + static_cast<char>(direction));
                exit(1);
        }
    }

    struct Position
    {
        int x, y;

        Position(): x(0), y(0) {}
        Position(int x, int y): x(x), y(y) {}

        bool operator==(const Position& other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Position& other) const
        {
            return x != other.x || y != other.y;
        }

        Position operator+(const Position& other) const
        {
            return Position(this->x + other.x, this->y + other.y);
        }

        operator bool() const
        {
            return x && y;
        }

        bool operator<(const Position &other) const
        {
            if (y != other.y)
            {
                return y < other.y;
            }
            return x < other.x;
        }

        string to_string() const
        {
            return std::to_string(x) + ':' + std::to_string(y);
        }

        Position directional_offset(Direction d) const
        {
            auto dx = 0, dy = 0;

            switch (d)
            {
                case Direction::NORTH:
                    dy = -1; break;
                case Direction::SOUTH:
                    dy = 1; break;
                case Direction::EAST:
                    dx = 1; break;
                case Direction::WEST:
                    dx = -1; break;
                default: dx = dy = 0; break;
            }

            return Position{x + dx, y + dy};
        }

        std::array<Position, 4> get_surrounding_cardinals()
        {
            return
            {
                directional_offset(Direction::NORTH),
                directional_offset(Direction::SOUTH),
                directional_offset(Direction::EAST),
                directional_offset(Direction::WEST)
            };
        }

        int distance(const Position& dest) const
        {
            auto dx = this->x - dest.x;
            auto dy = this->y - dest.y;
            return dx * dx + dy * dy;
        }
    };

    static std::ostream& operator<<(std::ostream& out, const Position& position)
    {
        out << position.x << ' ' << position.y;
        return out;
    }

    static std::istream& operator>>(std::istream& in, Position& position)
    {
        in >> position.x >> position.y;
        return in;
    }
}

namespace std
{
    template <> struct hash<hlt::Position>
    {
        size_t operator()(const hlt::Position& position) const
        {
            return ((position.x + position.y) *
                    (position.x + position.y + 1) / 2) + position.y;
        }
    };
}
