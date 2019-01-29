#include "player.h"
#include "graphics.h"

Player::Player() { }

Player::Player(Graphics &graphics, float x, float y) :
  AnimatedSprite(graphics, "assets/sprites/MyChar.png", 0, 0, 16, 16, x, y, 100) {
    graphics.loadImage("assets/sprites/MyChar.png");
    
    setupAnimations();
    playAnimation("run_right");
  }

void Player::setupAnimations() {
  addAnimation(3, 0, 0, "run_left", 16, 16, Vector2(0, 0));
  addAnimation(3, 0, 16, "run_right", 16, 16, Vector2(0, 0));
}

void Player::animationDone(std::string currentAnimation) { }

void Player::draw(Graphics &graphics) {
  AnimatedSprite::draw(graphics, _x, _y);
}

void Player::update(float elapsedTime) {
  AnimatedSprite::update(elapsedTime);
}
