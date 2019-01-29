#include "level.h"
#include "graphics.h"

#include <SDL2/SDL.h>

Level::Level() {  }

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) :
  _mapName(mapName),
  _spawnPoint(spawnPoint),
  _size(Vector2::zero())
{
  loadMap(mapName, graphics);
}

Level::~Level() {  }

void Level::loadMap(std::string mapName, Graphics &graphics) {
  _backgroundTexture = SDL_CreateTextureFromSurface(
      graphics.getRenderer(), graphics.loadImage("assets/backgrounds/bkBlue.png"));
  _size = Vector2(1280, 960);
}

void Level::update(float elapsedTime) {

}

void Level::draw(Graphics &graphics) {
  SDL_Rect sourceRect = { 0, 0, 64, 64 };
  SDL_Rect destRect;

  for (int x = 0; x < _size.x / 64; x ++) {
    for (int y = 0; y < _size.y / 64; y ++) {
      destRect.x = x * 64;
      destRect.y = y * 64;
      destRect.w = 64;
      destRect.h = 64;

      graphics.blitSurface(_backgroundTexture, &sourceRect, &destRect);
    }
  }
}
