#include <SDL2/SDL.h>
#include "graphics.h"

Graphics::Graphics() {
  SDL_CreateWindowAndRenderer(640, 480, 0, &_window, &_renderer);
  SDL_SetWindowTitle(_window, "Cavestory");
}

Graphics::~Graphics() {
  SDL_DestroyWindow(_window);
}
