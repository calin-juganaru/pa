#include <iostream>
#include <vector>

#include "reversi.h"

using namespace std;

inline int abs(int x)
{
    return x > 0 ? x : -x;
}

Move::Move() {}

Move::Move(int player, int x = -1, int y = -1):
    player(player), x(x), y(y) {}

Reversi::Reversi()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            data[i][j] = 0;
    data[N / 2 - 1][N / 2 - 1] = data[N / 2][N / 2] = 1;
    data[N / 2 - 1][N / 2] = data[N / 2][N / 2 - 1] = -1;
}

bool Reversi::ended()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            Reversi tmp(*this);
            if (tmp.apply_move(Move(1, i, j)))
                return false;
            tmp = *this;
            if (tmp.apply_move(Move(-1, i, j)))
                return false;
        }
    return true;
}

int Reversi::winner(int player)
{
    if (!ended())
        return 0;
    int s = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (data[i][j] == player)
                s++;
            else if (data[i][j] == -player)
                s--;
        }
    return s > 0 ? 1 : s == 0 ? 0 : -1;
}


int Reversi::eval(int player)
{
    if(ended())
        return winner(player) * Reversi::inf;
    return 10;
}

vector<Move> Reversi::get_moves(const int& player)
{
    auto moves = vector<Move>();
    for (auto i = 0; i < Reversi::N; ++i)
    {
        for (auto j = 0; j < Reversi::N; ++j)
        {
            auto player_has = false;
            for (auto k = 0; k < Reversi::N; ++k)
                if ((this->data[i][k] == player && k != j) ||
                    (this->data[k][j] == player && k != i))
                    {
                        player_has = true;
                        break;
                    }
            for (auto k = 1; k < Reversi::N; ++k)
                if (this->data[(i + k) % Reversi::N][(j + k) % Reversi::N] == player)
                {
                        player_has = true;
                        break;
                }
            if (!player_has) continue;

            auto enemy_has_near = false;
            for (auto&& x: {-1, 0, 1})
                for (auto&& y: {-1, 0, 1})
                {
                    if(enemy_has_near) break;
                    if (this->data[i + x][j + y] == -player)
                    {
                        enemy_has_near = true;
                        break;
                    }
                }
            if (!enemy_has_near) continue;

            moves.push_back(Move(player, i, j));
        }
    }
    return moves;
}

bool Reversi::apply_move(const Move &move)
{
    if (move.x == -1 && move.y == -1)
        return true;

    if (data[move.x][move.y] != 0)
        return false;

    bool ok = false;

    for (int x_dir = -1; x_dir <= 1; x_dir++)
        for (int y_dir = -1; y_dir <= 1; y_dir++)
        {
            if (x_dir == 0 && y_dir == 0)
                continue;

            int i = move.x + x_dir, j = move.y + y_dir;
            for (; i >= 0 && j >= 0 && i < N && j < N && data[i][j] == -move.player; i += x_dir, j += y_dir);
            if (i >= 0 && j >= 0 && i < N && j < N && data[i][j] == move.player && (abs(move.x - i) > 1 || abs(move.y - j) > 1))
            {
                ok = true;
                for (i = move.x + x_dir, j = move.y + y_dir; i >= 0 && j >= 0 && i < N && j < N && data[i][j] == -move.player; i += x_dir, j += y_dir)
                    data[i][j] = move.player;
            }
        }

    if (!ok)
        return false;

    data[move.x][move.y] = move.player;

    return true;
}

void Reversi::print()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j< N; j++)
        {
            if (data[i][j] == 0)
                std::cout << '.';
            else if (data[i][j] == 1)
                std::cout << 'O';
            else
                std::cout << 'X';
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

pair<int, Move> minimax(Reversi init, int player, int depth)
{
    auto moves = init.get_moves(player);

    if (init.ended() || depth == 0)
    {
       auto aux = moves.empty() ? Move(-1, -1) : moves.back();
       return {init.eval(player), aux};
    }

    auto max_score = -Reversi::inf;
    auto best_move = Move(-1, -1);

    for (auto&& move: moves)
    {
        auto aux = init;

        if (!init.apply_move(move))
            continue;

        auto score = -minimax(init, player, depth - 1).first;

        if (score > max_score)
        {
            max_score = score;
            best_move = move;
        }

        init = aux;
    }

    return {max_score, best_move};
}


int main()
{
    Reversi rev;
    rev.print();

    /* Choose here if you want COMP vs HUMAN or COMP vs COMP */
    bool HUMAN_PLAYER = true;
    int player = 1;

    while (!rev.ended())
    {
        std::pair<int, Move> p(0, Move(player));
        if (player == 1)
        {
            p = minimax(rev, player, 6);
            //p = minimax_abeta(rev, player, 9, -Inf, Inf);

            std::cout << "Player " << player << " evaluates to " << p.first << std::endl;
            rev.apply_move(p.second);
        }
        else
        {
            if (!HUMAN_PLAYER)
            {
                p = minimax(rev, player, 6);
                //p = minimax_abeta(rev, player, 9, -Inf, Inf);

                std::cout << "Player " << player << " evaluates to " << p.first << std::endl;
                rev.apply_move(p.second);
            }
            else
            {
                bool valid = false;
                while (!valid)
                {
                    int x, y;
                    std::cout << "Insert position [0..N - 1], [0..N - 1] ";
                    std::cin >> x >> y;
                    valid = rev.apply_move(Move(player, x, y));
                }
            }
        }

        rev.print();
        player *= -1;
    }

    int w = rev.winner(1);
    if (w == 1)
        std::cout << "Player 1 WON!" << std::endl;
    else if (w == 0)
        std::cout << "Draw" << std::endl;
    else
        std::cout << "Player -1 WON!" << std::endl;
}
