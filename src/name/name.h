#ifndef TETRIS_NAME_NAME_H_
#define TETRIS_NAME_NAME_H_
#include <SFML/Graphics.hpp>
#include <string>

class NameUser {
 private:
  sf::Font font;
  sf::Texture lable_img;
  sf::RectangleShape box;
  int text_size;

 public:
  sf::Text text;
  NameUser(int k);
  ~NameUser() = default;
  void Text(std::string text, double k);
  sf::Text Ent(std::string text, double k);
  void Draw(sf::RenderWindow& window, int a, double k);
};
#endif //TETRIS_NAME_NAME_H_