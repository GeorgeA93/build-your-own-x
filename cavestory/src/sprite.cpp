#include "sprite.h"
#include "graphics.h"

Sprite::Sprite() { }

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY) : _x(posX), _y(posY) {

}

