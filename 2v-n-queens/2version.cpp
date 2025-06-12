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
};

queens_board::queens_board() {
  for (int i = 0; i < MAX_SIZE; ++i)
    for (int j = 0; j < MAX_SIZE; ++j)
      board[i][j] = false;
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
    board[row][col] = true;
    return true;
  }
  return false;
}

bool queens_board::remove_cell(int row, int col) {
  if(row >= 0 && row < MAX_SIZE && col >= 0 && col < MAX_SIZE){
    board[row][col] = false;
    return true;
  }
  return false;
}

bool queens_board::valid_cell(int row, int col) const{
  for (size_t i = 0; i < MAX_SIZE; i++) {
    for (size_t j = 0; j < MAX_SIZE; j++) {
      if(row == i && board[i][j] == true) 
        return false;
      if(col == j && board[i][j] == true)
        return false;
      if(i - j == row - col && board[i][j] == true)
        return false;
      if(i + j == row + col && board[i][j] == true)
        return false;
    }
  }
  return true;
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
