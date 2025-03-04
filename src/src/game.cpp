#include "../include/game.h"

Game::Game(double k) : board(20, 10, 30*k) {
  gameblocks.push_back(new I(board));
  gameblocks.push_back(new J(board));
  gameblocks.push_back(new L(board));
  gameblocks.push_back(new O(board));
  gameblocks.push_back(new T(board));
  gameblocks.push_back(new S(board));
  gameblocks.push_back(new Z(board));

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(gameblocks.begin(), gameblocks.end(), g);

  current = RandomBlock();
  next = RandomBlock();

  sf::Listener::setGlobalVolume(60);
  if (!music.openFromFile("../media/Tetris_Theme.ogg")) {
    std::cout << "Failed to load music file!" << std::endl;
    return;
  }
  music.play();
  music.setLoop(true);

  font.loadFromFile("../media/Gamefont.ttf");

  score_img.loadFromFile("../media/score.png");
  best_img.loadFromFile("../media/best.png");
  pause_img.loadFromFile("../media/pause.png");
  mute_img.loadFromFile("../media/mute.png");
  gameOver_img.loadFromFile("../media/gameover.png");
}

Game::~Game() {
  music.stop();
  for (auto block : gameblocks) {
    delete block;
  }
}

Block* Game::RandomBlock() {
  int randomIndex = rand() % gameblocks.size();
  return gameblocks[randomIndex]->Clone();
}

void Game::Draw(sf::RenderWindow& window, int a, int b, double k, int& record) {
  int cell_offset = board.Draw(window, b);

  current->Draw(window, board, cell_offset, cell_offset);
  next->Draw(window, board, 270*k, 330*k);

  sf::Sprite sprite(score_img);
  sprite.setScale(k, k);
  sprite.setPosition(326*k, 40*k);
  window.draw(sprite);

  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(42*k);
  text.setFillColor(sf::Color::White);
  text.setString(std::to_string(score));
  text.setPosition(396 + (a - 468 - text.getLocalBounds().width)/2*k,
                   20 + sprite.getLocalBounds().height + text.getLocalBounds().height);
  window.draw(text);


  sf::Sprite sprite2(best_img);
  sprite2.setScale(sprite.getGlobalBounds().width / sprite2.getLocalBounds().width,
                   sprite.getGlobalBounds().height / sprite2.getLocalBounds().height);
  sprite2.setPosition(326*k, 170*k);
  window.draw(sprite2);

  sf::Text rec;
  rec.setFont(font);
  rec.setCharacterSize(42*k);
  rec.setFillColor(sf::Color::White);
  if (record > score) {
    rec.setString(std::to_string(record));
  } else {
    rec.setString(std::to_string(score));
  }
  rec.setPosition(396 + (a - 468 - rec.getLocalBounds().width)/2*k,
                  150 + sprite.getLocalBounds().height + text.getLocalBounds().height);
  window.draw(rec);


  if (paused) {
    sf::Sprite sprite_pause(pause_img);
    double k1 = k/2;
    sprite_pause.setScale(k1, k1);
    sprite_pause.setPosition((a - sprite_pause.getLocalBounds().width * k1) / 2, (b - sprite_pause.getLocalBounds().height * k1) / 2);
    window.draw(sprite_pause);
  }

  if (gameOver) {
    sf::Sprite sprite_over(gameOver_img);
    sprite_over.setScale(k, k);
    sprite_over.setPosition((a - sprite_over.getLocalBounds().width * k) / 2, (b - sprite_over.getLocalBounds().height * k) / 2);
    window.draw(sprite_over);
  }

  if(paused_music) {
    sf::Sprite sprite_mute(mute_img);
    double k1 = k/2.5;
    sprite_mute.setScale(k1, k1);
    sprite_mute.setPosition(396*k, 470*k);
    window.draw(sprite_mute);
  }
}

void Game::Lock() {
  for (auto& cell : current->blocks) {
    board.board[cell.first][cell.second] = current->GetColor();
  }
  score += 10;

  full.clear();
  for (auto& cell : current->blocks) {
    if (board.IsRowFull(cell.first)) {
      full.push_back(cell.first);
    }
  }
  std::sort(full.begin(), full.end());
  full.erase(std::unique(full.begin(), full.end()), full.end());
  for (auto& row : full) {
    board.MoveDownFull(row);
    board.ClearRow(0);
  }
  score += 100 * full.size();

  current = next;
  if (Collision()) {
    gameOver = true;
    music.pause();
  }
  next = RandomBlock();
}

bool Game::Collision () {
  for (auto& cell : current->blocks) {
    if (board.board[cell.first][cell.second] != 0) {
      return true;
    }
  }
  return false;
}

void Game::MoveLeft() {
  if (!gameOver && !paused) {
    bool outside = false;
    for (size_t i = 0; i < current->blocks.size(); ++i) {
      if (current->blocks[i].second == 0) {
        outside = true;
        break;
      }
    }
    for (auto& block : current->blocks) {
      block.second -= 1;
    }
    if (outside || Collision()) {
      for (auto &block : current->blocks) {
        block.second += 1;
      }
    }
  }
}

void Game::MoveRight() {
  if (!gameOver && !paused) {
    bool outside = false;
    for (size_t i = 0; i < current->blocks.size(); ++i) {
      if (current->blocks[i].second >= board.wight_ - 1) {
        outside = true;
        break;
      }
    }

    for (auto& block : current->blocks) {
      block.second += 1;
    }
    if (outside || Collision()) {
      for (auto &block : current->blocks) {
        block.second -= 1;
      }
    }
  }
}

void Game::MoveUp() {
  if (!gameOver && !paused) {
    bool outside = false;
    for (size_t i = 0; i < current->blocks.size(); ++i) {
      if (current->blocks[i].first == 0) {
        outside = true;
        break;
      }
    }

    for (auto& block : current->blocks) {
      block.first -= 1;
    }
    if (outside || Collision()) {
      for (auto &block : current->blocks) {
        block.first += 1;
      }
    }
  }
}

bool Game::MoveDown() {
  bool outside = false;
  if (!gameOver && !paused && !outside) {
    for (size_t i = 0; i < current->blocks.size(); ++i) {
      if (current->blocks[i].first >= board.height_ - 1) {
        outside = true;
        break;
      }
    }

    for (auto& block : current->blocks) {
      block.first += 1;
    }
    if (outside || Collision()) {
      for (auto& block : current->blocks) {
        block.first -= 1;
      }
      Lock();
    }
  }

  return !outside;
}

void Game::RotateBlock() {
  if (!gameOver && !paused) {
    current->Rotate();
    if (current->GetColor() != 2) {
      bool outside_l = false;
      for (size_t i = 0; i < current->blocks.size(); ++i) {
        if (current->blocks[i].second == 0) {
          outside_l = true;
          break;
        }
      }

      bool outside_r = false;
      for (size_t i = 0; i < current->blocks.size(); ++i) {
        if (current->blocks[i].second >= board.wight_ - 1) {
          outside_r = true;
          break;
        }
      }

      bool outside_up = false;
      for (size_t i = 0; i < current->blocks.size(); ++i) {
        if (current->blocks[i].first == 0) {
          outside_up = true;
          break;
        }
      }

      bool outside_down = false;
      for (auto& block : current->blocks) {
        if (block.first >= board.height_ - 1) {
          outside_down = true;
          break;
        }
      }

      if (outside_l) {
        MoveRight();
        if (current->GetColor() == 5) {
          MoveRight();
        }
      }
      if (outside_r) {
        MoveLeft();
        if (current->GetColor() == 5) {
          MoveLeft();
        }
      }
      if (outside_up) {
        MoveDown();
        if (current->GetColor() == 5) {
          MoveDown();
        }
      }
      if (outside_down) {
        MoveUp();
        if (current->GetColor() == 5) {
          MoveUp();
        }
      }
    }
  }
}

void Game::Restart() {
  gameOver = false;
  score = 0;
  board.Clear();
  current = RandomBlock();
  next = RandomBlock();
}

void Game::Pause() {
  paused = !paused;
  if (!paused_music) {
    if (paused) {
      music.pause();
    } else {
      music.play();
    }
  }
}

void Game::PauseMusic() {
  paused_music = !paused_music;
  if (paused_music) {
    music.pause();
  } else {
    music.play();
  }
}

void Game::GameKeys(sf::RenderWindow& window) {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    } else if (event.type == sf::Event::KeyPressed) {
      if (gameOver) {
        Restart();
      }
      switch (event.key.code) {
        case sf::Keyboard::Left:
        case sf::Keyboard::A:
          if (!paused) MoveLeft();
          break;
        case sf::Keyboard::Right:
        case sf::Keyboard::D:
          if (!paused) MoveRight();
          break;
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
          if (!paused) MoveDown();
          break;
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
          if (!paused) RotateBlock();
          break;
        case sf::Keyboard::LShift:
        case sf::Keyboard::RShift:
          if (!paused) Restart();
          break;
        case sf::Keyboard::M:
          if (!paused) PauseMusic();
          break;
        case sf::Keyboard::Space:
          Pause();
          break;
        case sf::Keyboard::Enter:
          window.close();
          break;
        default:
          break;
      }
    }
  }
}

int Game::Score() {
  return score;
}