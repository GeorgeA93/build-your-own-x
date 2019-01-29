#ifndef _PLAYER_
#define _PLAYER_

#include "globals.h"
#include "animated_sprite.h"

class Graphics;

class Player : public AnimatedSprite {
  public:
    Player();
    Player(Graphics &graphics, float x, float y);

    void draw(Graphics &graphics);
    void update(float elapsedTime);

    void moveLeft();
    void moveRight();
    void stopMoving();

    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimations();
  private:
    float _deltaX, _deltaY;

    Direction _facing;
};

#endif
