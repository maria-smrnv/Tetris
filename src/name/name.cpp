#include "../name/name.h"
void NameUser::Text(std::string string, double k) {
  text.setFont(font);
  text.setCharacterSize(text_size*k);
  text.setFillColor(sf::Color::Black);
  text.setString(string);
  text.setOutlineThickness(4);
  text.setOutlineColor(sf::Color::White);
}

sf::Text NameUser::Ent(std::string string, double k) {
  sf::Text text_1;
  text_1.setFont(font);
  text_1.setCharacterSize((text_size - 2)*k);
  text_1.setFillColor(sf::Color::White);
  text_1.setString(string);
  text_1.setOutlineThickness(3);
  text_1.setOutlineColor(sf::Color::Black);
  return text_1;
}

NameUser::NameUser(int k) {
  text_size = 54;
  font.loadFromFile("../media/Gamefont.ttf");
  lable_img.loadFromFile("../media/lable.png");
  Text("", k);
}

void NameUser::Draw(sf::RenderWindow& window, int a, double k) {
  sf::Sprite sprite_lable(lable_img);
  sprite_lable.setScale(k, k);
  sprite_lable.setPosition((a - sprite_lable.getLocalBounds().width)/2*k, 40*k);
  window.draw(sprite_lable);

  sf::Text prev = Ent("enter name :", k);
  prev.setPosition((a - prev.getLocalBounds().width)/2*k,
                   20 + sprite_lable.getLocalBounds().height + prev.getLocalBounds().height);

  box.setSize(sf::Vector2f(sprite_lable.getGlobalBounds().width*1.2, (text_size*11/6)*k));
  box.setFillColor(sf::Color::White);
  box.setOutlineThickness(2);
  box.setOutlineColor(sf::Color::Black);
  box.setPosition((a - box.getLocalBounds().width)/2*k,
                  40 + sprite_lable.getLocalBounds().height + box.getLocalBounds().height);

  text.setPosition((a - text.getLocalBounds().width)/2*k,
                   40 + sprite_lable.getLocalBounds().height + box.getLocalBounds().height + text_size / 4);

  window.draw(prev);
  window.draw(box);
}