#pragma once

#include "position.hpp"
#include "entity.hpp"

using std::shared_ptr;

namespace hlt
{
    struct MapCell
    {
        Position position;
        int halite, marked;
        shared_ptr<Ship> ship;
        shared_ptr<Entity> structure;

        MapCell(int x, int y, int halite):
            position(x, y),
            halite(halite),
            marked(0) {}

        bool is_empty() const
        {
            return !ship && !structure;
        }

        bool is_occupied() const
        {
            return static_cast<bool>(ship);
        }

        bool has_structure() const
        {
            return static_cast<bool>(structure);
        }

        bool has_shipyard() const
        {
            return structure->id == -1;
        }

        void mark_unsafe(shared_ptr<Ship>& ship)
        {
            this->ship = ship;
            this->marked++;
        }
    };
}
