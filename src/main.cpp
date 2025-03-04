#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "include/game.h"
#include "menu/menu.h"
#include "name/name.h"

void NameStart(double k, int a, int b, int x, int y, std::string& name) {
  NameUser NameMenu = NameUser(k);
  sf::RenderWindow window(sf::VideoMode(a, b), "Tetris");
  window.setPosition(sf::Vector2i(x, y));
  window.clear(sf::Color(21, 9, 92, 255));
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
        window.close();
      } else if (event.type == sf::Event::TextEntered) { //ввод текста
        if (event.text.unicode < 128) {
          if (event.text.unicode == '\b' && !NameMenu.text.getString().isEmpty()) {
            std::string currentText = NameMenu.text.getString().toAnsiString();
            currentText.pop_back();
            NameMenu.text.setString(currentText);
          } else if (event.text.unicode == '\r') {
            name =  NameMenu.text.getString();
            window.close();
          } else if (event.text.unicode != '\b') {
            if (NameMenu.text.getString().getSize() < 8) {
              std::string currentText = NameMenu.text.getString().toAnsiString();
              currentText += std::toupper(static_cast<char>(event.text.unicode));
              NameMenu.text.setString(currentText);
            }
          }
        }
      }
    }
    NameMenu.Draw(window, a, k);
    window.draw(NameMenu.text);
    window.display();
  }
}

void GameStart(double k, int a, int b, int x, int y, sf::Clock clock, sf::Time frameTime,
               float MoveDownInterval, sf::Time LastMoveDown, std::vector<int>& score, int& record) {
  Game game = Game(k);
  sf::RenderWindow window(sf::VideoMode(a, b), "Tetris");
  window.setPosition(sf::Vector2i(x, y));

  while (window.isOpen()) {
    if (!game.paused) {
      sf::Time deltaTime = clock.restart();
      if (deltaTime < frameTime) {
        sf::sleep(frameTime - deltaTime);
      }
      LastMoveDown += deltaTime;
      if (LastMoveDown >= sf::seconds(MoveDownInterval)) {
        game.MoveDown();
        LastMoveDown = sf::Time::Zero;
      }
    }
    window.clear(sf::Color(21, 9, 92, 255));
    game.GameKeys(window);
    game.Draw(window, a, b, k, record);
    if (game.gameOver) {
      score.emplace_back(game.Score());
    }
    window.display();
  }
}

int main() {
  double k = 1; //масштабирующий параметр
  int a = 555;
  int b = 614;
  a *= k;
  b *= k;

  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

  int x = (desktop.width - a) / 2;
  int y = (desktop.height - b) / 2;

  sf::RenderWindow window(sf::VideoMode(a, b), "Tetris");
  window.setPosition(sf::Vector2i(x, y));

  sf::Clock clock;
  float desiredFPS = 60.0f;
  sf::Time frameTime = sf::seconds(1.0f / desiredFPS);
  float MoveDownInterval = 0.8f;
  sf::Time LastMoveDown = sf::Time::Zero;

  std::string name = "000000000"; //здесь 9 нулей, так как мах длина имени 8
  std::vector<int> score;

  std::vector<int> rec;
  std::ifstream file("../results.csv");
  std::string line;
  std::getline(file, line);
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string value;
    std::getline(iss, value, ';');
    std::getline(iss, value, ';');
    rec.push_back(std::stoi(value));
  }
  int record = *std::max_element(rec.begin(), rec.end());
  file.close();

  GameMenu menu = GameMenu(k);

  while (window.isOpen()) {
    sf::Event event;
    window.clear(sf::Color(21, 9, 92, 255));
    menu.Draw(window, a, k);
    window.display();
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) { menu.Move(); }
        if (event.key.code == sf::Keyboard::Down) { menu.Move(); }
        if (event.key.code == sf::Keyboard::Enter) {
          switch (menu.SelectOption()) {
            case 0:
              window.close();
              NameStart(k, a, b, x, y, name);
              if (name != "000000000") {
                GameStart(k, a, b, x, y, clock, frameTime, MoveDownInterval, LastMoveDown, score, record);
              }
              break;
            case 1:
              window.close();
              break;
          }
        }
      }
    }
  }
  std::ofstream file_n;
  file_n.open("../results.csv", std::ios::app);
  file_n << name << ";" << *std::max_element(score.begin(), score.end()) << std::endl;
  file_n.close();
}