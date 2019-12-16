#pragma once

#include "input.hpp"
#include "entity.hpp"
#include <memory>
#include <unordered_map>

namespace hlt
{
    struct Player
    {
        int id, halite;
        std::shared_ptr<Shipyard> shipyard;
        std::unordered_map<int, std::shared_ptr<Ship>> ships;
        std::unordered_map<int, std::shared_ptr<Dropoff>> dropoffs;

        Player(int player_id, int shipyard_x, int shipyard_y):
            id(player_id), halite(0),
            shipyard(std::make_shared<Shipyard>(player_id, shipyard_x, shipyard_y)) {}

        void _update(int num_ships, int num_dropoffs, int halite)
        {
            this->halite = halite;

            ships.clear();
            for (int i = 0; i < num_ships; ++i)
            {
                std::shared_ptr<hlt::Ship> ship = hlt::Ship::_generate(id);
                ships[ship->id] = ship;
            }

            dropoffs.clear();
            for (int i = 0; i < num_dropoffs; ++i)
            {
                std::shared_ptr<hlt::Dropoff> dropoff = hlt::Dropoff::_generate(id);
                dropoffs[dropoff->id] = dropoff;
            }
        }

        static std::shared_ptr<Player> _generate()
        {
            int player_id, shipyard_x, shipyard_y;
            hlt::get_sstream() >> player_id >> shipyard_x >> shipyard_y;

            return std::make_shared<hlt::Player>(player_id, shipyard_x, shipyard_y);
        }
    };
}
