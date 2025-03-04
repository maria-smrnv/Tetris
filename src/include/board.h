#ifndef TETRIS__BOARD_H_
#define TETRIS__BOARD_H_
#include <SFML/Graphics.hpp>
#include <vector>
#include "color.h"

class Board {
 private:
  std::vector<sf::Color> colors = CellColors();

 public:
  std::vector<std::vector<int>> board;
  int height_;
  int wight_;
  int cellSize_;

  Board(int h, int w, int s);

  bool Inside(int r, int c);

  //вывод сетки поля, b - высота окна вывода
  int Draw(sf::RenderWindow& window, int b);

  void Clear();

  bool IsRowFull(int r);
  void ClearRow(int r);
  void MoveDownFull(int r);
};

#endif //TETRIS__BOARD_H_