#pragma once

#include <vector>

struct Move
{
        int player, x, y;
        Move();
        Move(int player, int x, int y);
};

/**
 * Reprezinta starea jocului
 */
struct Reversi
{
        constexpr static int N = 6;
        constexpr static int inf = 0x3f3f3f3f;
        int data[N][N];

        Reversi();

        bool ended();
        int eval(int player);

        /**
         * Aplica o mutare a jucatorului, modificand starea jocului
         * Plaseaza piesa jucatorului move.player in pozitia move.x, move.y
         * Mutarea move.x == -1, move.y == -1 semnifica ca jucatorul
         * paseaza randul la mutare
         * Returneaza true daca mutarea este valida
         */
        bool apply_move(const Move &move);
        std::vector<Move> get_moves(const int& player);
        /**
         * Returns 1 if player won, 0 if draw and -1 if lost
         */
        int winner(int player);
        void print();
};
