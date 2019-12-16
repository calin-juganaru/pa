#pragma once

#include "game_map.hpp"
#include "player.hpp"

#include <vector>
#include <iostream>

namespace hlt
{
    struct Game
    {
        int turn_number, my_id;
        std::vector<std::shared_ptr<Player>> players;
        std::shared_ptr<Player> me;
        std::unique_ptr<GameMap> game_map;

        Game(): turn_number(0)
        {
            std::ios_base::sync_with_stdio(false);
            constants::populate_constants(get_string());

            int num_players;
            std::stringstream input(get_string());
            input >> num_players >> my_id;

            log::open(my_id);

            for (int i = 0; i < num_players; ++i)
            {
                players.push_back(Player::_generate());
            }
            me = players[my_id];
            game_map = GameMap::_generate();
        }

        void ready(const std::string& name)
        {
            std::cout << name << std::endl;
        }

        void update_frame()
        {
            get_sstream() >> turn_number;
            log::log("=============== TURN " + std::to_string(turn_number) + " ================");

            for (size_t i = 0; i < players.size(); ++i) {
                int current_player_id, num_ships, num_dropoffs, halite;
                get_sstream() >> current_player_id >> num_ships >> num_dropoffs >> halite;

                players[current_player_id]->_update(num_ships, num_dropoffs, halite);
            }

            game_map->_update();

            for (const auto& player: players)
            {
                for (auto& ship_iterator: player->ships)
                {
                    auto ship = ship_iterator.second;
                    game_map->at(ship)->mark_unsafe(ship);
                }

                game_map->at(player->shipyard)->structure = player->shipyard;

                for (auto& dropoff_iterator: player->dropoffs)
                {
                    auto dropoff = dropoff_iterator.second;
                    game_map->at(dropoff)->structure = dropoff;
                }
            }
        }

        bool end_turn(const std::vector<string>& commands)
        {
            for (const auto& command: commands)
                std::cout << command << ' ';
            std::cout << std::endl;
            return std::cout.good();
        }
    };
}
