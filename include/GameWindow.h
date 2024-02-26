/**
 * @file GameWindow.h
 * @brief Defines the GameWindow class, responsible for creating the game window
 * and renderer engine.
 *
 * The GameWindow class manages the creation of the game window and renderer
 * engine, providing a centralized interface for window-related operations. It
 * initializes and manages the rendering environment for the game.
 *
 * @note Ensure proper configuration and initialization of the game window and
 * renderer.
 *
 * @remark This class serves as a crucial component for setting up the visual
 * aspect of the game environment.
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-01)
 * - 1.1: Add bit by bit rendering (dexter@nekocake.cafe) (2024-02-26)
 * - 1.2: Add animation support for rendering (dexter@nekocake.cafe)
 * (2024-02-26)
 */

#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

namespace GameObject {
class GameObject;
}

#include "GameObject.h"
#include "Map.h"
#include "RectStruct.h"
#include <SDL.h>

namespace GameWindow {
class GameWindow {
public:
  GameWindow(const char *title, const int w, const int h,
             const Uint32 windowFlags, const Uint32 rendererFlags);
  ~GameWindow();

  SDL_Window *getWindow();
  SDL_Renderer *getRenderer();

  void clearScreen();
  void setRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  void draw(int x, int y, RectStruct::Color *c);
  void drawRect(int x, int y, int width, int height, RectStruct::Color *c);
  void present();
  void render(Map::Map<GameObject::GameObject> *gameObjects,
              GameObject::GameObject *camera);

private:
  SDL_Renderer *renderer;
  SDL_Window *window;
  bool isRenderable(GameObject::GameObject *gameObject,
                    GameObject::GameObject *camera);
  void renderCel(Map::Map<Animation::Cel> *cels, GameObject::GameObject *camera,
                 GameObject::GameObject *gameObject);
  void cleanup();
};
} // namespace GameWindow

#endif
