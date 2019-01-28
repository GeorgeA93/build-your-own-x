#ifndef _GRAPHICS_
#define _GRAPHICS_

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
  public:
    Graphics();
    ~Graphics();
  private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
};

#endif
