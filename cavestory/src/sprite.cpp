#include "sprite.h"
#include "graphics.h"

Sprite::Sprite() { }

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX,
    int sourceY, int width, int height, float posX, float posY) :
      _x(posX), _y(posY)
{
  _sourceRect.x = sourceX;
  _sourceRect.y = sourceY;
  _sourceRect.w = width;
  _sourceRect.h = height;

  _spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));

  if (_spriteSheet == NULL) {
    printf("\n Error unable to load image \n");
  }
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics &graphics, int x, int y) {
  SDL_Rect destRect = { x, y, _sourceRect.w, _sourceRect.h };

  graphics.blitSurface(_spriteSheet, &_sourceRect, &destRect);
}

void Sprite::update() {}
