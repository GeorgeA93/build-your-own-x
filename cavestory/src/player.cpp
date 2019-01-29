#include "player.h"
#include "graphics.h"

namespace player_constants {
  const float WALK_SPEED = 0.2f;
}

Player::Player() { }

Player::Player(Graphics &graphics, float x, float y) :
  AnimatedSprite(graphics, "assets/sprites/MyChar.png", 0, 0, 16, 16, x, y, 100) {
    setupAnimations();
    playAnimation("idle_left");
  }

void Player::setupAnimations() {
  addAnimation(1, 0, 0, "idle_left", 16, 16, Vector2(0, 0));
  addAnimation(1, 0, 16, "idle_right", 16, 16, Vector2(0, 0));
  addAnimation(3, 0, 0, "run_left", 16, 16, Vector2(0, 0));
  addAnimation(3, 0, 16, "run_right", 16, 16, Vector2(0, 0));
}

void Player::animationDone(std::string currentAnimation) { }

void Player::draw(Graphics &graphics) {
  AnimatedSprite::draw(graphics, _x, _y);
}

void Player::update(float elapsedTime) {
  _x += _deltaX * elapsedTime;
  _y += _deltaY * elapsedTime;

  AnimatedSprite::update(elapsedTime);
}

void Player::moveLeft() {
  _deltaX = -player_constants::WALK_SPEED;
  playAnimation("run_left");
  _facing = LEFT;
}

void Player::moveRight() {
  _deltaX = +player_constants::WALK_SPEED;
  playAnimation("run_right");
  _facing = RIGHT;
}

void Player::stopMoving() {
  _deltaX = 0.0f;
  _deltaY = 0.0f;

  if (_facing == RIGHT) {
    playAnimation("idle_right"); 
  } else {
    playAnimation("idle_left");
  }
}
