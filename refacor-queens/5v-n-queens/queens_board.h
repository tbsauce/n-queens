#ifndef QUEENS_BOARD_H
#define QUEENS_BOARD_H

#include <array>
#include <bitset>

constexpr int MAX_SIZE = 50;

class queens_board {
public:
    queens_board();
    queens_board(queens_board &&) = default;
    queens_board(const queens_board &) = default;
    queens_board &operator=(queens_board &&) = default;
    queens_board &operator=(const queens_board &) = default;
    ~queens_board();

    void print_board() const;
    bool set_cell(int row, int col);
    bool remove_cell(int row, int col);
    bool valid_cell(int row, int col) const;

private:
    std::array<std::array<bool, MAX_SIZE>, MAX_SIZE> board;
    std::bitset<MAX_SIZE> rows;
    std::bitset<MAX_SIZE> cols;
    std::bitset<2 * MAX_SIZE - 1> main_diagonal;
    std::bitset<2 * MAX_SIZE - 1> reverse_diagonal;
};

bool backtracking_queens(queens_board& board, int row);

#endif
