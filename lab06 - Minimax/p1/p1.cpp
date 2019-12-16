#include <iostream>
#include <vector>
#include "nim.h"

using namespace std;

Move::Move(int amount = 0, int heap = -1):
    amount(amount), heap(heap) {}

Nim::Nim()
{
    heaps[0] = 3;
    heaps[1] = 4;
    heaps[2] = 5;
}

std::vector<Move> Nim::get_moves(int player)
{
    auto ret = vector<Move>();
    for (int i = 0; i < 3; i++)
        for (int k = 1; k <= 3; k++)
            if (k <= heaps[i])
                ret.push_back(Move(k, i));
    return ret;
}

bool Nim::ended()
{
    if (!heaps[0])
        if (!heaps[1])
            if (!heaps[2])
                return true;
    return false;
}

int Nim::eval(int player)
{
    if (heaps[0] + heaps[1] + heaps[2] == 1)
        return -Nim::inf;
    if (this->ended())
        return Nim::inf;
    return heaps[0] ^ heaps[1] ^ heaps[2];
}

bool Nim::apply_move(const Move &move)
{
    if (this->heaps[move.heap] - move.amount < 0
        || move.heap < 0 || move.heap > 2 || move.amount > 3)
    {
        return false;
    }
    else
    {
        this->heaps[move.heap] -= move.amount;
        return true;
    }
}

bool Nim::undo_move(const Move &move)
{
    this->apply_move(Move(-move.amount, move.heap));
    return false;
}

void Nim::print()
{
    for (int i = 0; i < 3; i++)
    {
        std::cout << i << ":";
        for (int j = 0; j < heaps[i]; j++)
            std::cout << " *";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

pair<int, Move> minimax(Nim init, int player, int depth)
{
    auto moves = init.get_moves(player);

    if (init.ended() || depth == 0)
    {
       auto aux = moves.empty() ? Move() : moves.back();
       return {init.eval(player), aux};
    }

    auto max_score = -Nim::inf;
    auto best_move = Move();

    for (auto&& move: moves)
    {
        if (!init.apply_move(move))
            continue;

        auto score = -minimax(init, player, depth - 1).first;

        if (score > max_score)
        {
            max_score = score;
            best_move = move;
        }

        init.undo_move(move);
    }

    return {max_score, best_move};
}

int main()
{
    Nim nim;

    nim.heaps[0] = 5;
    nim.heaps[1] = 10;
    nim.heaps[2] = 20;

    nim.print();

    /* Choose here if you want COMP vs HUMAN or COMP vs COMP */
    bool HUMAN_PLAYER = 1;//false;//true;
    int player = 1;

    while (!nim.ended())
    {
        std::pair<int, Move> p;
        if (player == 1)
        {
            p = minimax(nim, player, 6);
            //p = minimax_abeta(nim, player, 13, -Inf, Inf);

            std::cout << "Player " << player << " evaluates to " << p.first << std::endl;
            nim.apply_move(p.second);
        }
        else
        {
            if (!HUMAN_PLAYER)
            {
                p = minimax(nim, player, 6);
                //p = minimax_abeta(nim, player, 13, -Inf, Inf);

                std::cout << "Player " << player << " evaluates to " << p.first << std::endl;
                nim.apply_move(p.second);
            }
            else
            {
                bool valid = false;
                while (!valid)
                {
                    int am, h;
                    std::cout << "Insert amount [1, 2 or 3] and heap [0, 1 or 2]: ";
                    std::cin >> am >> h;
                    valid = nim.apply_move(Move(am, h));
                }
            }
        }

        nim.print();
        player *= -1;
    }

    int w = nim.heaps[0] + nim.heaps[1] + nim.heaps[2];
    if (w == 0)
        std::cout << "Player " << player << " WON!" << std::endl;
    else
        std::cout << "Player " << player << " LOST!" << std::endl;
}
