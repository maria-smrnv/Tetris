#ifndef TETRIS__TYPES_OF_BLOCKS_H_
#define TETRIS__TYPES_OF_BLOCKS_H_
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "block.h"

class I : public Block {
 public:
  I(Board board) : Block(5, board) {
    CreateShape();
  }

  void CreateShape() override {
    blocks = {{0, this->GetWight() / 2 + 1}, {0, this->GetWight() / 2}, {0, this->GetWight() / 2 - 1}, {0, this->GetWight() / 2 - 2}};
  }

  void Rotate() override {
    rotation = (rotation + 1) % 4;
    if (rotation == 0) {
      blocks = {{blocks[0].first + 1, blocks[0].second + 2},
                {blocks[1].first, blocks[1].second + 1},
                {blocks[2].first - 1, blocks[2].second},
                {blocks[3].first - 2, blocks[3].second - 1}};
    } else if (rotation == 1) {
      blocks = {{blocks[0].first + 2, blocks[0].second - 1},
                {blocks[1].first + 1, blocks[1].second},
                {blocks[2].first, blocks[2].second + 1},
                {blocks[3].first - 1, blocks[3].second + 2}};
    } else if (rotation == 2) {
      blocks = {{blocks[0].first - 1, blocks[0].second - 2},
                {blocks[1].first, blocks[1].second - 1},
                {blocks[2].first + 1, blocks[2].second},
                {blocks[3].first + 2, blocks[3].second + 1}};
    } else if (rotation == 3) {
      blocks = {{blocks[0].first - 2, blocks[0].second + 1},
                {blocks[1].first - 1, blocks[1].second},
                {blocks[2].first, blocks[2].second - 1},
                {blocks[3].first + 1, blocks[3].second - 2}};
    }
  }

  I* Clone() const override {
    return new I(*this);
  }
};

class J : public Block {
 public:
  J(Board board) : Block(6, board) {
    CreateShape();
  }

  void CreateShape() override {
    blocks = {{0, this->GetWight() / 2 - 1}, {1, this->GetWight() / 2 - 1}, {1, this->GetWight() / 2}, {1, this->GetWight() / 2 + 1}};
  }

  void Rotate() override {
    rotation = (rotation + 1) % 4;
    if (rotation == 1) {
      blocks = {{blocks[0].first, blocks[0].second + 2},
                {blocks[1].first - 1, blocks[1].second + 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first + 1, blocks[3].second - 1}};
    } else if (rotation == 2) {
      blocks = {{blocks[0].first + 2, blocks[0].second},
                {blocks[1].first + 1, blocks[1].second + 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first - 1, blocks[3].second - 1}};
    } else if (rotation == 3) {
      blocks = {{blocks[0].first, blocks[0].second - 2},
                {blocks[1].first + 1, blocks[1].second - 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first - 1, blocks[3].second + 1}};
    } else if (rotation == 0) {
      blocks = {{blocks[0].first - 2, blocks[0].second},
                {blocks[1].first - 1, blocks[1].second - 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first + 1, blocks[3].second + 1}};
    }
  }

  J* Clone() const override {
    return new J(*this);
  }
};

class L : public Block {
 public:
  L(Board board) : Block(3, board) {
    CreateShape();
  }

  void CreateShape() override {
    blocks = {{0, this->GetWight() / 2 + 1}, {1, this->GetWight() / 2 + 1}, {1, this->GetWight() / 2}, {1, this->GetWight() / 2 - 1}};
  }

  void Rotate() override {
    rotation = (rotation + 1) % 4;
    if (rotation == 1) {
      blocks = {{blocks[0].first + 2, blocks[0].second},
                {blocks[1].first + 1, blocks[1].second - 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first - 1, blocks[3].second + 1}};
    } else if (rotation == 2) {
      blocks = {{blocks[0].first, blocks[0].second - 2},
                {blocks[1].first - 1, blocks[1].second - 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first + 1, blocks[3].second + 1}};
    } else if (rotation == 3) {
      blocks = {{blocks[0].first - 2, blocks[0].second},
                {blocks[1].first - 1, blocks[1].second + 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first + 1, blocks[3].second - 1}};
    } else if (rotation == 0) {
      blocks = {{blocks[0].first, blocks[0].second + 2},
                {blocks[1].first + 1, blocks[1].second + 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first - 1, blocks[3].second - 1}};
    }
  }

  L* Clone() const override {
    return new L(*this);
  }
};

class O : public Block {
 public:
  O(Board board) : Block(2, board) {
    CreateShape();
  }

  void CreateShape() override {
    blocks = {{0, this->GetWight() / 2 - 1}, {0, this->GetWight() / 2}, {1, this->GetWight() / 2 - 1}, {1, this->GetWight() / 2}};
  }

  void Rotate() override {
    rotation = (rotation + 1) - 1;
  }

  O* Clone() const override {
    return new O(*this);
  }
};

class T : public Block {
 public:
  T(Board board) : Block(7, board) {
    CreateShape();
  }

  void CreateShape() override {
    blocks = {{0, this->GetWight() / 2}, {1, this->GetWight() / 2 - 1}, {1, this->GetWight() / 2}, {1, this->GetWight() / 2 + 1}};
  }
  void Rotate() override {
    rotation = (rotation + 1) % 4;
    if (rotation == 1) {
      blocks = {{blocks[0].first + 1, blocks[0].second + 1},
                {blocks[1].first - 1, blocks[1].second + 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first + 1, blocks[3].second - 1}};
    } else if (rotation == 2) {
      blocks = {{blocks[0].first + 1, blocks[0].second - 1},
                {blocks[1].first + 1, blocks[1].second + 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first - 1, blocks[3].second - 1}};
    } else if (rotation == 3) {
      blocks = {{blocks[0].first - 1, blocks[0].second - 1},
                {blocks[1].first + 1, blocks[1].second - 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first - 1, blocks[3].second + 1}};
    } else if (rotation == 0) {
      blocks = {{blocks[0].first - 1, blocks[0].second + 1},
                {blocks[1].first - 1, blocks[1].second - 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first + 1, blocks[3].second + 1}};
    }
  }

  T* Clone() const override {
    return new T(*this);
  }
};

class S : public Block {
 public:
  S(Board board) : Block(4, board) {
    CreateShape();
  }

  void CreateShape() override {
    blocks = {{0, this->GetWight() / 2 + 1}, {0, this->GetWight() / 2}, {1, this->GetWight() / 2}, {1, this->GetWight() / 2 - 1}};
  }

  void Rotate() override {
    rotation = (rotation + 1) % 4;
    if (rotation == 1) {
      blocks = {{blocks[0].first + 2, blocks[0].second},
                {blocks[1].first + 1, blocks[1].second + 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first - 1, blocks[3].second + 1}};
    } else if (rotation == 2) {
      blocks = {{blocks[0].first, blocks[0].second - 2},
                {blocks[1].first + 1, blocks[1].second - 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first + 1, blocks[3].second + 1}};
    } else if (rotation == 3) {
      blocks = {{blocks[0].first - 2, blocks[0].second},
                {blocks[1].first - 1, blocks[1].second - 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first + 1, blocks[3].second - 1}};
    } else if (rotation == 0) {
      blocks = {{blocks[0].first, blocks[0].second + 2},
                {blocks[1].first - 1, blocks[1].second + 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first - 1, blocks[3].second - 1}};
    }
  }

  S* Clone() const override {
    return new S(*this);
  }
};

class Z : public Block {
 public:
  Z(Board board) : Block(1, board) {
    CreateShape();
  }

  void CreateShape() override {
    blocks = {{0, this->GetWight() / 2 - 1}, {0, this->GetWight() / 2}, {1, this->GetWight() / 2}, {1, this->GetWight() / 2 + 1}};
  }

  void Rotate() override {
    rotation = (rotation + 1) % 4;
    if (rotation == 1) {
      blocks = {{blocks[0].first, blocks[0].second + 2},
                {blocks[1].first + 1, blocks[1].second + 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first + 1, blocks[3].second - 1}};
    } else if (rotation == 2) {
      blocks = {{blocks[0].first + 2, blocks[0].second},
                {blocks[1].first + 1, blocks[1].second - 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first - 1, blocks[3].second - 1}};
    } else if (rotation == 3) {
      blocks = {{blocks[0].first, blocks[0].second - 2},
                {blocks[1].first - 1, blocks[1].second - 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first - 1, blocks[3].second + 1}};
    } else if (rotation == 0) {
      blocks = {{blocks[0].first - 2, blocks[0].second},
                {blocks[1].first - 1, blocks[1].second + 1},
                {blocks[2].first, blocks[2].second},
                {blocks[3].first + 1, blocks[3].second + 1}};
    }
  }

  Z* Clone() const override {
    return new Z(*this);
  }
};
#endif //TETRIS__TYPES_OF_BLOCKS_H_