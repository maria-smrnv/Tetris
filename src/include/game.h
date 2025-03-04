#ifndef TETRIS__GAME_H_
#define TETRIS__GAME_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

#include "board.h"
#include "block.h"
#include "types_of_blocks.h"

class Game {
 private:
  std::vector<Block*> gameblocks;
  Block *current;
  Block *next;
  std::vector<int> full;
  Block* RandomBlock();

  void Lock();
  bool Collision ();

  void MoveLeft();
  void MoveRight();
  void MoveUp();
  void RotateBlock();

  sf::Font font;
  sf::Music music;
  sf::Texture score_img;
  sf::Texture best_img;
  sf::Texture pause_img;
  sf::Texture gameOver_img;
  sf::Texture mute_img;

 public:
  Board board;
  int score = 0;
  bool gameOver = false;
  bool paused = false;
  bool paused_music = false;

  Game(double k);
  ~Game();

  void Draw(sf::RenderWindow& window, int a, int b, double k, int& record);

  bool MoveDown();

  void Restart();
  void Pause();
  void PauseMusic();

  void GameKeys(sf::RenderWindow& window);

  int Score();
};
#endif //TETRIS__GAME_H_
