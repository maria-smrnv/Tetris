#ifndef TETRIS__BLOCK_H_
#define TETRIS__BLOCK_H_
#include <SFML/Graphics.hpp>
#include <vector>
#include "board.h"
#include "color.h"

class Block {
 private:
  int color_; //цвет блока
  int wight_; //ширина сетки поля
  std::vector<sf::Color> colors = CellColors();

 public:
  std::vector<std::pair<int, int>> blocks;
  int rotation = 0;

  Block(int c, Board board) : color_(c), wight_(board.wight_) {}

  int GetColor() const {
    return color_;
  }

  int GetWight() const {
    return wight_;
  }

  virtual void CreateShape() = 0;
  virtual void Rotate() = 0;
  virtual Block* Clone() const = 0;

  //функция вывода на экран по координатам
  void Draw(sf::RenderWindow& window, Board board, int k, int m) {
    sf::RectangleShape rectangle(sf::Vector2f(board.cellSize_ - 1, board.cellSize_ - 1));
    rectangle.setFillColor(colors[color_]);

    for (const auto &miniblock : blocks) {
      int x = miniblock.first * board.cellSize_;
      int y = miniblock.second * board.cellSize_;

      rectangle.setPosition(y + k, x + m);

      window.draw(rectangle);
    }
  }

  virtual ~Block() = default;
};
#endif //TETRIS__BLOCK_H_
