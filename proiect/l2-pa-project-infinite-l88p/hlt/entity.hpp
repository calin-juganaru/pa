#pragma once

#include "input.hpp"
#include "position.hpp"
#include "constants.hpp"

#include <memory>
#include <vector>

using std::string;
using std::to_string;
using std::shared_ptr;
using std::make_shared;

namespace hlt
{
    struct Entity
    {
        int owner, id;
        Position position;

        Entity(int owner, int id, int x, int y):
            owner(owner), id(id), position(x, y) {}
    };

    struct Ship: Entity
    {
        int halite;
        std::vector<Position> moves;
        bool return_to_shipyard;
        Position last_position;

        Ship(int player_id, int ship_id, int x, int y, int halite):
            Entity(player_id, ship_id, x, y),
            halite(halite), return_to_shipyard(false) {}

        bool is_full() const
        {
            return halite >= constants::MAX_HALITE;
        }

        string make_dropoff() const
        {
            return "c " + to_string(id);
        }

        string move(Direction direction)
        {
            return "m " + to_string(id) + ' ' +
                    static_cast<char>(direction);
        }

        string stay_still()
        {
            return "m " + to_string(id) + ' ' +
                    static_cast<char>(Direction::STILL);
        }

        static shared_ptr<Ship> _generate(int player_id)
        {
            int ship_id, x, y, halite;
            get_sstream() >> ship_id >> x >> y >> halite;
            return make_shared<Ship>(player_id, ship_id, x, y, halite);
        }
    };

    struct Shipyard: Entity
    {
        Shipyard(int owner, int x, int y):
            Entity(owner, -1, x, y) {}

        string spawn()
        {
            return string(1, 'g');
        }
    };

    struct Dropoff: Entity
    {
        using Entity::Entity;
        static shared_ptr<Dropoff> _generate(int player_id)
        {
            int dropoff_id, x, y;
            hlt::get_sstream() >> dropoff_id >> x >> y;

            return make_shared<Dropoff>(player_id, dropoff_id, x, y);
        }
    };
}
