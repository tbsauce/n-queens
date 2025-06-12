#include <iostream>
#include <vector>
#include <cstdlib>

class queens_board {
public:
  queens_board(int size);
  queens_board(queens_board &&) = default;
  queens_board(const queens_board &) = default;
  queens_board &operator=(queens_board &&) = default;
  queens_board &operator=(const queens_board &) = default;
  ~queens_board();

  void print_board() const;
  bool set_cell(int row, int col);
  bool remove_cell(int row, int col);
  bool valid_cell(int row, int col) const;
  int get_size() const;

private:
  const int size_;
  std::vector<std::vector<bool>> board;
};

queens_board::queens_board(int size) : size_(size), board(size, std::vector<bool>(size, false)) {}

queens_board::~queens_board() {}

int queens_board::get_size() const{
  return size_;
}

void queens_board::print_board() const {
  for (size_t i = 0; i < size_; i++) {
    for (size_t j = 0; j < size_; j++) {
      std::cout << board[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

bool queens_board::set_cell(int row, int col) {
  if(row >= 0 && row < size_ && col >= 0 && col < size_ && valid_cell(row, col)){
    board[row][col] = true;
    return true;
  }
  return false;
}

bool queens_board::remove_cell(int row, int col) {
  if(row >= 0 && row < size_ && col >= 0 && col < size_){
    board[row][col] = false;
    return true;
  }
  return false;
}

bool queens_board::valid_cell(int row, int col) const{
  for (size_t i = 0; i < size_; i++) {
    for (size_t j = 0; j < size_; j++) {
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

  if(row == board.get_size())
    return true;
  for (size_t col = 0; col < board.get_size(); col++) {
    if(board.set_cell(row, col)){
      if(backtracking_queens(board, row + 1))
        return true;
      board.remove_cell(row, col);
    } 
  }
  return false;
}

int main(int argc, char* argv[]) {

  int size = (argc == 2) ? std::atoi(argv[1]) : 8;

  if (size <= 0) {
    std::cerr << "Please enter a positive integer for board size.\n";
    return 1;
  }

  if (argc != 2) {
    std::cout << "Using default board size: " << size << "\n";
  }

  queens_board board(size);
  backtracking_queens(board, 0);
  board.print_board();
  return 0;
}
