#ifndef TETRIS_MENU_MENU_H_
#define TETRIS_MENU_MENU_H_
#include <SFML/Graphics.hpp>
#include <string>

class GameMenu {
 private:
  sf::Font font;
  sf::Texture lable_img;
  int option;
  std::vector<sf::Text> MenuOption;

 public:
  GameMenu(double k);
  ~GameMenu() = default;
  sf::Text Text(std::string text, double k);
  void Draw(sf::RenderWindow& window, int a, double k);
  void Move();
  int SelectOption() {
    return option;
  };
};
#endif //TETRIS_MENU_MENU_H_
