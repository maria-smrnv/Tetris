#include "../include/block.h"

Board::Board(int h, int w, int s) : height_(h), wight_(w), cellSize_(s) {
  board.resize(height_, std::vector<int>(wight_, 0));
}

bool Board::Inside(int r, int c) {
  return (r >= 0 && r < height_ && c >= 0 && c < wight_);
}

int Board::Draw(sf::RenderWindow& window, int b) {
  const int cell_offset = (b - height_*cellSize_)/2; //отступ вертикально для рисования сетки

  for (size_t row = 0; row < board.size(); row++) {
    for (size_t column = 0; column < board[row].size(); column++) {
      int cellcolor = board[row][column];
      sf::RectangleShape rectangle(sf::Vector2f(cellSize_ - 1, cellSize_ - 1));
      rectangle.setPosition(column * cellSize_ + cell_offset, row * cellSize_ + cell_offset);
      if (Inside(row, column)) {
        rectangle.setFillColor(colors[cellcolor]);
      } else {
        rectangle.setFillColor(sf::Color::Transparent);
      }
      window.draw(rectangle);
    }
  }

  return cell_offset;
}

void Board::Clear() {
  for (size_t row = 0; row < board.size(); row++) {
    for (size_t column = 0; column < board[row].size(); column++) {
      board[row][column] = 0;
    }
  }
}

bool Board::IsRowFull(int r) {
  for (size_t c = 0; c < board[r].size(); c++) {
    if (board[r][c] == 0) {
      return false;
    }
  }
  return true;
}

void Board::ClearRow(int r) {
  for (size_t c = 0; c < board[r].size(); c++) {
    board[r][c] = 0;
  }
}

void Board::MoveDownFull(int row) {
  for (int r = row; r > 0; r--) {
    for (size_t c = 0; c < board[r].size(); c++) {
      board[r][c] = board[r - 1][c];
    }
  }
}