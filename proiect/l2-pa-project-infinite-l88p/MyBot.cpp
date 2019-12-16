#include "hlt/game.hpp"
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;
using namespace hlt;

#define cmd(x) command_queue.push_back(x)

constexpr auto TIME_TO_RETURN = 35;
constexpr auto ALMOST_FULL = 835;

int main()
{
    auto game = Game(); game.ready("MyBot");
    auto length = min(game.game_map->cells.size(), game.game_map->cells.back().size());
    auto map = vector<vector<int>>(length, vector<int>(length));
    auto command_queue = vector<string>();
    auto last_position = unordered_map<int, Position>();
    auto random_generator = mt19937(time(nullptr));
    auto MAX_DROPOFFS = length >= 40 ? length >= 56 ? 1u : 1u : 0u;
    auto STOP_SPAWNING = static_cast<int>(0.7 * constants::MAX_TURNS);
    auto cardinals = vector<Direction>(begin(ALL_CARDINALS), end(ALL_CARDINALS));

    // cât timp jocul nu s-a terminat
    while (true)
    {
        // initializarea rundei
        game.update_frame();
        auto me = game.me;
        auto& game_map = game.game_map;
        command_queue.clear();

        // crearea unei noi nave:
        //  în primele 70% din runde,
        //  atâta timp cât avem destul halite
        //  și nu este risc de coliziune în
        //      și pe lângă shipyard
        if (game.turn_number < STOP_SPAWNING
            && me->halite >= constants::SHIP_COST
            && game_map->is_safe_around(me->shipyard))
        {
            command_queue.push_back(me->shipyard->spawn());
        }

        // crearea unui dropoff:
        //  la jumătatea jocului, având destule halite
        //  și încă n-am ajuns la maximul de dropoff-uri ales
        if (game.turn_number > constants::MAX_TURNS / 2
            && me->halite > constants::DROPOFF_COST
            && me->dropoffs.size() < MAX_DROPOFFS)
        {
            auto best_ship = me->ships.begin()->first;
            auto max_halite = 0;

            // alegem nava cu cele mai multe halite în jur,
            //  pe o zonă suficient de mare (16 x 16),
            //  pentru a o converti la într-un dropoff
            for (auto&& [id, ship]: me->ships)
            {
                auto distance = game_map->halite_around(ship->position, 8);
                if (distance > max_halite)
                {
                    max_halite = distance;
                    best_ship = id;
                }
            }

            cmd(me->ships[best_ship]->make_dropoff());
            me->ships.erase(best_ship);
        }

        // mutarile navelor:
        //  în ultimele runde le trimitem către cea mai apropiată bază
        //  și le facem să se ciocnească pentru a ne reveni tot halitele lor
        if (constants::MAX_TURNS - game.turn_number < TIME_TO_RETURN)
        {
            for (auto&& [id, ship]: me->ships)
            {
                auto dest = game_map->closest_dropoff(ship, me->dropoffs, me->shipyard->position);

                if (auto [near, direction] = game_map->is_near(ship, dest); near)
                {
                    cmd(ship->move(direction));
                }
                else
                {
                    cmd(ship->move(game_map->naive_navigate(ship, dest)));
                }

            }
        }
        // până atunci, aplicăm algoritmul nostru pentru a colecta cât mai mult
        else for (auto&& [id, ship]: me->ships)
        {
            // facem o medie a halitelor din jur (o zonă de 8 x 8)
            auto avg_halite = game_map->halite_density(ship->position, 4) * 2 / 3;

            // funcțiile de mutare ne asigură că navele noastre nu se ciocnesc,
            //  dar reținem ultima poziție a fiecărei nave pentru a evita blocajele
            if (last_position.find(id) != end(last_position))
            {
                // dacă rămâne două runde consecutive pe aceeași poziție
                //  o facem să meargă pe cea mai bună direcție aleatoare
                if (ship->position == last_position[id])
                {
                    shuffle(begin(cardinals), end(cardinals), random_generator);
                    for (auto&& direction: cardinals)
                    {
                        auto new_position = ship->position.directional_offset(direction);
                        if (game_map->at(new_position)->is_empty())
                        {
                            game_map->at(new_position)->mark_unsafe(ship);
                            last_position[id] = ship->position;
                            cmd(ship->move(direction));
                            break;
                        }
                    }
                    continue;
                }
            }

            ship->last_position = last_position[id];
            auto dest = game_map->closest_dropoff(ship, me->dropoffs, me->shipyard->position);

            // dacă nava a ajuns în bază, resetăm flag-ul
            if (ship->position.distance(dest) == 0)
            {
                ship->return_to_shipyard = false;
            }

            // dacă nava trebuie să ajugă în bază
            if (ship->return_to_shipyard)
            {
                cmd(ship->move(game_map->naive_navigate(ship, dest)));
            }
            // dacă nava este trimisă la colectat
            else
            {
                // dacă pe poziția curentă sunt prea puține halite sau nava este plină
                if (game_map->at(ship)->halite < avg_halite || ship->is_full())
                {
                    // dacă este (aproape) plină, trebuie trimisă la o bază
                    if (ship->halite > ALMOST_FULL)
                    {
                        ship->return_to_shipyard = true;
                        last_position[id] = ship->position;
                        cmd(ship->move(game_map->naive_navigate(ship, dest)));
                    }
                    // altfel, o trimitem pe o poziție cu cât mai multe halite în jur
                    else
                    {
                        // dacă are suficient la bord cât să se deplaseze
                        if (ship->halite >= game_map->at(ship->position)->halite / 10)
                        {
                            auto direction = game_map->best_cell(ship, map);
                            auto new_position = ship->position.directional_offset(direction);
                            game_map->at(new_position)->mark_unsafe(ship);
                            last_position[id] = ship->position;
                            cmd(ship->move(direction));
                        }
                        // altfel trebuie să stea o rundă
                        else
                        {
                            cmd(ship->stay_still());
                        }
                    }
                }
                // dacă celula curentă e destul de bogată, colectăm
                else
                {
                    cmd(ship->stay_still());
                }
            }
        }

        // finalul jocului
        if (!game.end_turn(command_queue)) break;
    }
}