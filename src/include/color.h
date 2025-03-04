#ifndef TETRIS__COLOR_H_
#define TETRIS__COLOR_H_
#include <SFML/Graphics.hpp>
#include <vector>

const sf::Color board = sf::Color::Black;
const sf::Color red = sf::Color::Red;
const sf::Color yellow = sf::Color::Yellow;
const sf::Color orange = {255, 140, 0, 255};
const sf::Color green = sf::Color::Green;
const sf::Color lightBlue = sf::Color::Cyan;
const sf::Color blue = sf::Color::Blue;
const sf::Color purple = {128, 0, 128, 255};

static std::vector<sf::Color> CellColors() {
  return {board, red, yellow, orange, green, lightBlue, blue, purple};
}

#endif //TETRIS__COLOR_H_
