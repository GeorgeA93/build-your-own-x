#ifndef _PLAYER_
#define _PLAYER_

#include <string>

#include "animated_sprite.h"

class Graphics;

class Player : public AnimatedSprite {
  public:
    Player();
    Player(Graphics &graphics, float x, float y);

    void draw(Graphics &graphics);
    void update(float elapsedTime);

    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimations();
  private:
};

#endif
