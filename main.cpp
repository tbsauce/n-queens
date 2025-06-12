#include "queens_board.h"

int main() {
    queens_board board;
    backtracking_queens(board, 0);
    board.print_board();
    return 0;
}
