#include "GameWindow.h"
#include "Tile.h"
#include <SDL.h>
#include <iostream>
#include <mimalloc.h>
#include <spdlog/spdlog.h>

int main() {
  GameWindow::GameWindow gameWindow(
      "Game Engine", 640, 480, SDL_WINDOW_RESIZABLE, SDL_RENDERER_PRESENTVSYNC);

  Tile::Tile tile(100, 100, 100, 100);
  tile.setColorChoice(255, 0, 0, 255);
  // SDL_FRect rectangle;
  // rectangle.x = 100;
  // rectangle.y = 100;
  // rectangle.w = 100;
  // rectangle.h = 100;

  // Uint8 r = 255;
  // Uint8 g = 0;
  // Uint8 b = 0;
  // Uint8 a = 255;

  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }
    gameWindow.setRenderDrawColor(255, 255, 255, 255);
    gameWindow.clearScreen();

    gameWindow.setRenderDrawColor(tile.getColor()->r, tile.getColor()->g,
                                  tile.getColor()->b, tile.getColor()->a);

    gameWindow.drawRect(tile);
    // gameWindow.setRenderDrawColor(r,g,b,a);
    // gameWindow.drawRect(rectangle);

    gameWindow.present();
  }
  return 0;
}
