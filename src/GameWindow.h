#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <SDL.h>

class GameWindow {
public:
  GameWindow();
  ~GameWindow();

  SDL_Window *getWindow();
  SDL_Renderer *getRenderer();

  void clearScreen();
  void present();

private:
  SDL_Renderer *renderer;
  SDL_Window *window;
  void cleanup();
};

#endif
