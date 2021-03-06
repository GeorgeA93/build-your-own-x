#ifndef _LEVEL_
#define _LEVEL_

#include <string>
#include "globals.h"

class Graphics;
struct SDL_Texture;

class Level {
  public:
    Level();
    Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);

    ~Level();

    void update(float elapsedTime);
    void draw(Graphics &graphics);
  private:
    std::string _mapName;
    Vector2 _spawnPoint;
    Vector2 _size;
    SDL_Texture* _backgroundTexture;

    void loadMap(std::string mapName, Graphics &graphics);
};

#endif
