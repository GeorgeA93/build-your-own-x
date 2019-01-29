#include <SDL2/SDL.h>

#include "game.h"
#include "graphics.h"
#include "input.h"

namespace {
  const int FPS = 60;
  const int MAX_FRAME_TIME = 6 * 1000 / FPS;
}

Game::Game() {
  SDL_Init(SDL_INIT_EVERYTHING);

  gameLoop();
}

Game::~Game() {
}

void Game::gameLoop() {
  Graphics graphics;
  Input input;
  SDL_Event event;

  _player = Player(graphics, 100, 100);
  _level = Level("map foo", Vector2(100, 100) , graphics);

  int lastUpdateTime = SDL_GetTicks();

  while (true) {
    input.beginNewFrame();

    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        if (event.key.repeat == 0) {
          input.keyDownEvent(event);
        }
      } else if (event.type == SDL_KEYUP) {
        input.keyUpEvent(event);
      } else if (event.type == SDL_QUIT) {
        return;
      }
    }

    if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
      return;
    } else if (input.isKeyHeld(SDL_SCANCODE_A) == true) {
      _player.moveLeft();
    } else if (input.isKeyHeld(SDL_SCANCODE_D) == true) {
      _player.moveRight();
    }

    if (!input.isKeyHeld(SDL_SCANCODE_A) && !input.isKeyHeld(SDL_SCANCODE_D)) {
      _player.stopMoving();
    }

    const int currentTimeMs = SDL_GetTicks();
    int elapsedTimeMs = currentTimeMs - lastUpdateTime;
    update(std::min(elapsedTimeMs, MAX_FRAME_TIME));
    lastUpdateTime = currentTimeMs;

    draw(graphics);
  }
}

void Game::draw(Graphics &graphics) {
  graphics.clear();

  _level.draw(graphics);
  _player.draw(graphics);

  graphics.flip();
}

void Game::update(float elapsedTime) {
  _player.update(elapsedTime);
  _level.update(elapsedTime);
}

