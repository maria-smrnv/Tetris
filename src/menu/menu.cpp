#include "../menu/menu.h"
sf::Text GameMenu::Text(std::string point, double k) {
  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(60*k);
  text.setFillColor(sf::Color::White);
  text.setString(point);
  text.setOutlineThickness(3);
  text.setOutlineColor(sf::Color::Black);

  return text;
}

GameMenu::GameMenu(double k) {
  font.loadFromFile("../media/Gamefont.ttf");
  lable_img.loadFromFile("../media/lable.png");

  option = 1;

  sf::Text text = GameMenu::Text("START", k);
  MenuOption.push_back(text);
  text = GameMenu::Text("EXIT", k);
  MenuOption.push_back(text);
}

void GameMenu::Draw(sf::RenderWindow& window, int a, double k) {
  sf::Sprite sprite_lable(lable_img);
  sprite_lable.setScale(k, k);
  sprite_lable.setPosition((a - sprite_lable.getLocalBounds().width)/2*k, 40*k);
  window.draw(sprite_lable);

  MenuOption[0].setPosition((a - MenuOption[0].getLocalBounds().width)/2*k,
                            40 + sprite_lable.getLocalBounds().height + MenuOption[0].getLocalBounds().height);
  for (int i = 1; i < MenuOption.size(); i++) {
    MenuOption[i].setPosition((a - MenuOption[i].getLocalBounds().width)/2*k,
                              MenuOption[i - 1].getPosition().y + MenuOption[i - 1].getLocalBounds().height * 2);
  }

  for (const auto& text : MenuOption) {
    window.draw(text);
  }
}

void GameMenu::Move() {
  option = (option + 1) % 2;
  if (option == 0) {
    MenuOption[0].setFillColor(sf::Color(91, 254, 78, 255));
    MenuOption[1].setFillColor(sf::Color::White);
  } else {
    MenuOption[0].setFillColor(sf::Color::White);
    MenuOption[1].setFillColor(sf::Color(91, 254, 78, 255));
  }
}