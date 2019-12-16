#pragma once

#include <vector>

struct Move
{
        int amount, heap;
        Move(int amount, int heap);
};


class Nim
{
    public:
        static constexpr int inf = 0x3f3f3f3f;
        int heaps[3];

        Nim();

        std::vector<Move> get_moves(int player);
        bool ended();
        int eval(int player);
        bool apply_move(const Move& move);
        bool undo_move(const Move& move);
        void print();
};
