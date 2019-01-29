#include "animated_sprite.h"
#include "graphics.h"
#include "sprite.h"

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, 
    float posX, float posY, float timeToUpdate) :
  Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
  _timeToUpdate(timeToUpdate),
  _currentAnimationOnce(false),
  _currentAnimation(""),
  _frameIndex(0),
  _visible(true)
{}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset) {
  std::vector<SDL_Rect> rects;

  for (int i = 0; i < frames; i ++) {
    SDL_Rect newRect = { (i + x) * width, y, width, height };
    rects.push_back(newRect);
  }

  _animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rects));
  _offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::resetAnimations() {
  _animations.clear();
  _offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once) {
  _currentAnimationOnce = once;
  if (_currentAnimation != animation) {
    _currentAnimation = animation;
    _frameIndex = 0;
  }
}

void AnimatedSprite::setVisible(bool visible) {
  _visible = visible;
}

void AnimatedSprite::stopAnimation() {
  _frameIndex = 0;
  animationDone(_currentAnimation);
}

void AnimatedSprite::update(int elapsedTime) {
  Sprite::update();

  _timeElapsed += elapsedTime;
  if (_timeElapsed > _timeToUpdate) {
    _timeElapsed -= _timeToUpdate;
    if (_frameIndex < _animations[_currentAnimation].size() - 1) {
      _frameIndex ++;
    } else {
      if (_currentAnimationOnce == true) {
        setVisible(false);
      }
      _frameIndex = 0;
      animationDone(_currentAnimation);
    }
  }
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y) {
  if (!_visible) {
    return;
  }

  SDL_Rect destRect;
  destRect.x = x + _offsets[_currentAnimation].x;
  destRect.y = y + _offsets[_currentAnimation].y;
  destRect.w = _sourceRect.w * globals::SPRITE_SCALE;
  destRect.h = _sourceRect.h * globals::SPRITE_SCALE;

  SDL_Rect sourceRect = _animations[_currentAnimation][_frameIndex];
  graphics.blitSurface(_spriteSheet, &sourceRect, &destRect);
}
