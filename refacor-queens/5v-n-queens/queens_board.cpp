#include "queens_board.h"
#include <iostream>

queens_board::queens_board() {
    for (size_t i = 0; i < MAX_SIZE; ++i) {
        for (size_t j = 0; j < MAX_SIZE; ++j) {
            board[i][j] = false;
        }
    }
}

queens_board::~queens_board() {}

void queens_board::print_board() const {
    for (size_t i = 0; i < MAX_SIZE; i++) {
        for (size_t j = 0; j < MAX_SIZE; j++) {
            std::cout << board[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

bool queens_board::set_cell(int row, int col) {
    if (row >= 0 && row < MAX_SIZE && col >= 0 && col < MAX_SIZE && valid_cell(row, col)) {
        rows.set(row);
        cols.set(col);
        main_diagonal.set(row - col + (MAX_SIZE - 1));
        reverse_diagonal.set(row + col);
        board[row][col] = true;
        return true;
    }
    return false;
}

bool queens_board::remove_cell(int row, int col) {
    if (row >= 0 && row < MAX_SIZE && col >= 0 && col < MAX_SIZE) {
        rows.reset(row);
        cols.reset(col);
        main_diagonal.reset(row - col + (MAX_SIZE - 1));
        reverse_diagonal.reset(row + col);
        board[row][col] = false;
        return true;
    }
    return false;
}

bool queens_board::valid_cell(int row, int col) const {
    return !(rows.test(row) || cols.test(col) ||
             main_diagonal.test(row - col + (MAX_SIZE - 1)) ||
             reverse_diagonal.test(row + col));
}

bool backtracking_queens(queens_board& board, int row) {
    if (row == MAX_SIZE)
        return true;
    for (size_t col = 0; col < MAX_SIZE; col++) {
        if (board.set_cell(row, col)) {
            if (backtracking_queens(board, row + 1))
                return true;
            board.remove_cell(row, col);
        }
    }
    return false;
}
