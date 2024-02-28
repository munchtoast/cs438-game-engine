#include "GameWindow.h"
#include "Animation.h"
#include "GameObject.h"
#include "Map.h"
#include "MemoryManagement.h"
#include <SDL.h>
#include <chrono>
#include <spdlog/spdlog.h>
#include <thread>

namespace GameWindow {
/**
 * @brief Constructs a GameWindow instance.
 *
 * @param title - Title of the game window.
 * @param w - Width of the game window.
 * @param h - Height of the game window.
 * @param Uint32 windowFlags - Window args to pass to SDL
 * @param Uint32 rendererFlags - Renderer args to pass to SDL
 */
GameWindow::GameWindow(const char *title, const int w, const int h,
                       const Uint32 windowFlags, const Uint32 rendererFlags) {

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    return;

  window = SDL_CreateWindow(title, w, h, windowFlags);

  if (!window) {
    spdlog::error("Cannot create window! Exiting...");
    cleanup();
  }

  // NULL uses any video driver available to the system
  renderer = SDL_CreateRenderer(window, NULL, rendererFlags);

  if (!renderer) {
    spdlog::error("Cannot establish renderer! Exiting...");
    cleanup();
  }
}

GameWindow::~GameWindow() { GameWindow::cleanup(); }

SDL_Window *GameWindow::getWindow() { return window; }

SDL_Renderer *GameWindow::getRenderer() { return renderer; }

void GameWindow::clearScreen() {
  setRenderDrawColor(255, 255, 255, 255);
  SDL_RenderClear(renderer);
}

void GameWindow::setRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void GameWindow::draw(int x, int y, RectStruct::Color *c) {
  setRenderDrawColor(c->r, c->g, c->b, c->a);
  SDL_RenderPoint(getRenderer(), x, y);
}

void GameWindow::drawRect(int x, int y, int width, int height,
                          RectStruct::Color *c) {
  for (int i = x; i < x + width; i++)
    for (int j = y; j < y + height; j++)
      draw(i, j, c);
}

void GameWindow::present() { SDL_RenderPresent(renderer); }

void GameWindow::render(Map::Map<GameObject::GameObject> *gameObjects,
                        GameObject::GameObject *camera) {
  Map::Map<Animation::Cel> *cels = nullptr;
  Animation::Animation *animation = nullptr;
  GameObject::GameObject **mem = gameObjects->getMap();

  if (Util::Util::checkIfNullPtr(mem))
    return;

  GameWindow::clearScreen();

  /**
   * @brief Gets all GameObjects, and then the Animation Engine determines which
   * Cels to render. Smooths out the CPU cycles by introducing a thread-safe
   * sleep.
   *
   */
  for (size_t i = 0; i < gameObjects->getSize(); i++) {
    if (isRenderable(mem[i], camera)) {
      animation = mem[i]->getAnimation();

      if (Util::Util::checkIfNullPtr(mem[i]))
        continue;

      cels = animation->getCelsToRender();

      if (!Util::Util::checkIfNullPtr(cels)) {
        renderCel(cels, camera, mem[i]);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
      }
    }
  }

  GameWindow::present();
}

/**
 * @brief Draws all animation cels obtained by getting their individual pixel
 * mappings. Then, draws all animation cels pixel by pixel
 *
 * @param cels - Map of all cels to animate
 * @param gameObject - GameObject to be rendered onto the screen
 * @param camera - GameObject as the "Ground Truth" to render relative to the
 * screen
 */
void GameWindow::renderCel(Map::Map<Animation::Cel> *cels,
                           GameObject::GameObject *camera,
                           GameObject::GameObject *gameObject) {
  Animation::Cel **memCel = nullptr;
  RectStruct::Rect **memPixel = nullptr;

  memCel = cels->getMap();
  if (Util::Util::checkIfNullPtr(memCel))
    return;

  for (size_t i = 0; i < cels->getSize(); i++) {
    if (Util::Util::checkIfNullPtr(memCel[i]))
      continue;

    memPixel = memCel[i]->getPixels()->getMap();

    if (Util::Util::checkIfNullPtr(memPixel))
      continue;

    for (size_t j = 0; j < memCel[i]->getPixels()->getSize(); j++) {
      if (Util::Util::checkIfNullPtr(memPixel[j]))
        break;

      GameWindow::drawRect(
          (gameObject->getX() - memPixel[j]->position.x) - camera->getX(),
          (gameObject->getY() - memPixel[j]->position.y) - camera->getY(),
          gameObject->getW() - memPixel[j]->size.width,
          gameObject->getH() - memPixel[j]->size.height,
          static_cast<RectStruct::Color *>(&memPixel[j]->color));
    }
  }
}

/**
 * @brief Given the Camera GameObject, this function determines if the
 * GameObject is on the screen with respect to the Camera GameObject
 *
 * @param gameObject - GameObject to determine if rendering is possible
 * @param camera - GameObject that is defined as the "Ground Truth" of possible
 * rendering onto the screen
 *
 */
bool GameWindow::isRenderable(GameObject::GameObject *gameObject,
                              GameObject::GameObject *camera) {
  return (std::abs(gameObject->getX()) <= std::abs(camera->getW()) &&
          std::abs(gameObject->getY()) <= std::abs(camera->getH()));
}

void GameWindow::cleanup() {
  if (!Util::Util::checkIfNullPtr(window))
    SDL_DestroyWindow(window);

  if (!Util::Util::checkIfNullPtr(renderer))
    SDL_DestroyRenderer(renderer);
}
} // namespace GameWindow
