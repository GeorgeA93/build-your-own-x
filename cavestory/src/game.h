#ifndef _GAME_
#define _GAME_

struct Graphics;

class Game {
  public:
    Game();
    ~Game();
  private:
    void gameLoop();
    void draw(Graphics *graphics);
    void update(float elapsedTime);
};
#endif
