#include <iostream>
#include <array>
#include <cstdlib>

constexpr int MAX_SIZE = 20;

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
  std::array<bool, MAX_SIZE> rows;
  std::array<bool, MAX_SIZE> cols;
  std::array<bool, 2 * MAX_SIZE - 1> main_diagonal;
  std::array<bool, 2 * MAX_SIZE - 1> reverse_diagonal;
};

queens_board::queens_board() {
  for (size_t i = 0; i < MAX_SIZE; ++i) {
    for (size_t j = 0; j < MAX_SIZE; ++j) {
      board[i][j] = false;
    }
  }

  for (size_t i = 0; i < MAX_SIZE; ++i) {
    rows[i] = false;
    cols[i] = false;
  }

  for (size_t i = 0; i < 2 * MAX_SIZE - 1; ++i) {
    main_diagonal[i] = false;
    reverse_diagonal[i] = false;
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
  if(row >= 0 && row < MAX_SIZE && col >= 0 && col < MAX_SIZE && valid_cell(row, col)){
    rows[row] = true;
    cols[col] = true;
    main_diagonal[row - col + (MAX_SIZE - 1)] = true;
    reverse_diagonal[row + col] = true;
    board[row][col] = true;
    return true;
  }
  return false;
}

bool queens_board::remove_cell(int row, int col) {
  if(row >= 0 && row < MAX_SIZE && col >= 0 && col < MAX_SIZE){
    rows[row] = false;
    cols[col] = false;
    main_diagonal[row - col + (MAX_SIZE - 1)] = false;
    reverse_diagonal[row + col] = false;
    board[row][col] = false;
    return true;
  }
  return false;
}

bool queens_board::valid_cell(int row, int col) const{
  return !(rows[row] || cols[col] || main_diagonal[row - col + (MAX_SIZE - 1)] || reverse_diagonal[row + col]);
}

bool backtracking_queens(queens_board& board, int row){

  if(row == MAX_SIZE)
    return true;
  for (size_t col = 0; col < MAX_SIZE; col++) {
    if(board.set_cell(row, col)){
      if(backtracking_queens(board, row + 1))
        return true;
      board.remove_cell(row, col);
    } 
  }
  return false;
}

int main() {

  queens_board board;
  backtracking_queens(board, 0);
  board.print_board();
  return 0;
}
