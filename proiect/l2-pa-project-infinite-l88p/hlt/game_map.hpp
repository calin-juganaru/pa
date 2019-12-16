#pragma once

#include "map_cell.hpp"

#include <vector>
#include <memory>
#include <unordered_map>

constexpr auto MAX_MOVES = 10;

using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::pair;

namespace hlt
{
    struct GameMap
    {
        int width, height;
        vector<vector<MapCell>> cells;

        MapCell* at(const Position& position)
        {
            Position normalized = normalize(position);
            return &cells[normalized.y][normalized.x];
        }

        MapCell* at(const Entity& entity)
        {
            return at(entity.position);
        }

        MapCell* at(const Entity* entity)
        {
            return at(entity->position);
        }

        MapCell* at(const std::shared_ptr<Entity>& entity)
        {
            return at(entity->position);
        }

        int calculate_distance(const Position& source, const Position& target)
        {
            const auto& normalized_source = normalize(source);
            const auto& normalized_target = normalize(target);

            const int dx = std::abs(normalized_source.x - normalized_target.x);
            const int dy = std::abs(normalized_source.y - normalized_target.y);

            const int toroidal_dx = std::min(dx, width - dx);
            const int toroidal_dy = std::min(dy, height - dy);

            return toroidal_dx + toroidal_dy;
        }

        int calculate_distance(const std::shared_ptr<Entity>& source,
                               const std::shared_ptr<Entity>& target)
        {
            return calculate_distance(source->position, target->position);
        }

        Position normalize(const Position& position)
        {
            const int x = ((position.x % width) + width) % width;
            const int y = ((position.y % height) + height) % height;
            return {x, y};
        }

        vector<Direction> get_unsafe_moves(const Position& source, const Position& destination)
        {
            const auto& normalized_source = normalize(source);
            const auto& normalized_destination = normalize(destination);

            const int dx = std::abs(normalized_source.x - normalized_destination.x);
            const int dy = std::abs(normalized_source.y - normalized_destination.y);
            const int wrapped_dx = width - dx;
            const int wrapped_dy = height - dy;

            auto possible_moves = vector<Direction>();

            if (normalized_source.x < normalized_destination.x)
            {
                possible_moves.push_back(dx > wrapped_dx ? Direction::WEST : Direction::EAST);
            }
            else if (normalized_source.x > normalized_destination.x)
            {
                possible_moves.push_back(dx < wrapped_dx ? Direction::WEST : Direction::EAST);
            }

            if (normalized_source.y < normalized_destination.y)
            {
                possible_moves.push_back(dy > wrapped_dy ? Direction::NORTH : Direction::SOUTH);
            }
            else if (normalized_source.y > normalized_destination.y)
            {
                possible_moves.push_back(dy < wrapped_dy ? Direction::NORTH : Direction::SOUTH);
            }

            return possible_moves;
        }

        Direction naive_navigate(shared_ptr<Ship>& ship, const Position& destination)
        {
            for (auto direction : get_unsafe_moves(ship->position, destination))
            {
                Position target_pos = ship->position.directional_offset(direction);
                if (!at(target_pos)->is_occupied() &&
                    target_pos != ship->last_position)
                {
                    at(target_pos)->mark_unsafe(ship);
                    return direction;
                }
            }

            return Direction::STILL;
        }

        pair<bool, Direction> is_near(shared_ptr<Ship>& ship, const Position& destination)
        {
            for (auto&& direction: ALL_CARDINALS)
            {
                auto new_position = normalize(ship->position.directional_offset(direction));
                if (new_position == destination)
                    return {true, direction};
            }
            return {false, Direction::STILL};
        }

        void _update();
        static unique_ptr<GameMap> _generate();

        int halite_around(const Position& position, const int& depth = 1)
        {
            auto halites = 0;
            for (auto x = -depth; x <= depth; ++x)
                for (auto y = -depth; y <= depth; ++y)
                    halites += this->at(position + Position(x, y))->halite;
            return halites;
        }

        int halite_density(const Position& position, const int& depth = 1)
        {
            auto cells = depth * 2 + 1; cells *= cells;
            return halite_around(position, depth) / cells;
        }

        Direction best_cell(const shared_ptr<Ship>& ship, vector<vector<int>>& map)
        {
            auto max_halite = 0;
            auto best_direction = Direction::STILL;
            auto position = ship->position;

            for (auto&& direction: ALL_CARDINALS)
            {
                auto new_position = normalize(position.directional_offset(direction));
                if (!this->at(new_position)->is_occupied()
                    && new_position != ship->last_position
                    && map[new_position.x][new_position.y] < MAX_MOVES)
                {
                    auto halites = halite_density(new_position);
                    if (halites > max_halite)
                    {
                        max_halite = halites;
                        best_direction = direction;
                    }
                }
            }

            auto&& [x, y] = normalize(position.directional_offset(best_direction));
            map[x][y]++;

            return best_direction;
        }

        bool is_safe_around(const Position& position, const int& depth = 1)
        {
            for (auto x = -depth; x <= depth; ++x)
                for (auto y = -depth; y <= depth; ++y)
                    if (at(position + Position{x, y})->is_occupied())
                        return false;
            return true;
        }

        bool is_safe_around(const shared_ptr<Entity>& entity)
        {
            return is_safe_around(entity->position);
        }

        Position closest_dropoff(const shared_ptr<Ship>& ship,
            std::unordered_map<int, shared_ptr<Dropoff>>& dropoffs,
            const Position& shipyard_position = Position())
        {
            auto closest = shipyard_position;
            auto min_dist = ship->position.distance(closest);

            if (!dropoffs.empty())
            for (auto&& [id, dropoff]: dropoffs)
            {
                auto dist = ship->position.distance(dropoff->position);
                if (dist < min_dist)
                {
                    min_dist = dist;
                    closest = dropoff->position;
                }
            }
            return closest;
        }
    };
}
