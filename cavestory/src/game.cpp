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

  _player = Sprite(graphics, "assets/sprites/MyChar.png", 0, 0, 16, 16, 100, 100);

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

  _player.draw(graphics, 100, 100);

  graphics.flip();
}

void Game::update(float elapsedTime) {

}

