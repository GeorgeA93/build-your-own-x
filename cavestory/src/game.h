#ifndef _GAME_
#define _GAME_

#include "player.h"

class Graphics;

class Game {
  public:
    Game();
    ~Game();
  private:
    void gameLoop();
    void draw(Graphics &graphics);
    void update(float elapsedTime);

    Player _player;
};
#endif
