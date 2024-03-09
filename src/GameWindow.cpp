#include "GameWindow.h"
#include "Animation.h"
#include "GameObject.h"
#include "Map.h"
#include "MemoryManagement.h"
#include <SDL.h>
#include <chrono>
#include <cmath>
#include <limits>
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

void GameWindow::drawTriangle(int v1x, int v1y, int v2x, int v2y, int v3x,
                              int v3y, RectStruct::Color *c) {
  GameWindow::drawLine(v1x, v1y, v2x, v2y, c);
  GameWindow::drawLine(v1x, v1y, v3x, v3y, c);
  GameWindow::drawLine(v2x, v2y, v3x, v3y, c);

  GameWindow::fillTriangle(v1x, v1y, v2x, v2y, v3x, v3y, c);
}

/**
 * @brief Performs the scanline algorithm to fill in a triangle
 *
 * @note The order of vertices do not matter, as the algorithm will draw and
 * fill up accordingly.
 *
 * @param v1x - Vertex1 x position
 * @param v1y - Vertex1 y position
 * @param v2x - Vertex2 x position
 * @param v2y - Vertex2 y position
 * @param v3x - Vertex3 x position
 * @param v3y - Vertex3 y position
 * @param c - Color to draw to screen
 *
 */
void GameWindow::fillTriangle(int v1x, int v1y, int v2x, int v2y, int v3x,
                              int v3y, RectStruct::Color *c) {
  // Sort vertices by y-coordinate
  if (v1y > v2y) {
    std::swap(v1x, v2x);
    std::swap(v1y, v2y);
  }
  if (v1y > v3y) {
    std::swap(v1x, v3x);
    std::swap(v1y, v3y);
  }
  if (v2y > v3y) {
    std::swap(v2x, v3x);
    std::swap(v2y, v3y);
  }

  // Calculate slopes
  float invSlope1 = static_cast<float>(v2x - v1x) / (v2y - v1y);
  float invSlope2 = static_cast<float>(v3x - v1x) / (v3y - v1y);

  // Initialize edge values
  float currentX1 = v1x;
  float currentX2 = v1x;

  // Fill the top part of the triangle
  for (int y = v1y; y <= v2y; y++) {
    drawLine(static_cast<int>(currentX1), y, static_cast<int>(currentX2), y, c);
    currentX1 += invSlope1;
    currentX2 += invSlope2;
  }

  // Adjust for the bottom flat side of the triangle
  invSlope1 = static_cast<float>(v3x - v2x) / (v3y - v2y);
  currentX1 = v2x;

  // Fill the bottom part of the triangle
  for (int y = v2y + 1; y <= v3y; y++) {
    drawLine(static_cast<int>(currentX1), y, static_cast<int>(currentX2), y, c);
    currentX1 += invSlope1;
    currentX2 += invSlope2;
  }
}

/**
 * @brief Draws a line given two points
 *
 * @param x1 - x position of object 1
 * @param y1 - y position of object 1
 * @param x2 - x position of object 2
 * @param y2 - y position of object 2
 * @param c - Color to draw to screen
 */
void GameWindow::drawLine(int x1, int y1, int x2, int y2,
                          RectStruct::Color *c) {
  // Can't draw on top of itself
  if (x1 == x2 && y1 == y2)
    return;
  if (x1 > x2) {
    std::swap(x1, x2);
    std::swap(y1, y2);
  }

  // Vertical line has no valid slope
  if (x1 == x2) {
    for (int y = y1; y == y2; y++)
      draw(x1, y, c);

    return;
  }

  float slope = static_cast<float>(y2 - y1) / (x2 - x1);

  for (int x = x1; x <= x2; x++) {
    int y = y1 + static_cast<int>(slope * (x - x1));
    draw(x, y, c);
  }
}

void GameWindow::present() { SDL_RenderPresent(renderer); }

void GameWindow::render(Map::Map<GameObject::GameObject> *gameObjects,
                        GameObject::GameObject *camera,
                        GameObject::GameObject *light) {
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
        renderCel(cels, camera, mem[i], light);
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
                           GameObject::GameObject *gameObject,
                           GameObject::GameObject *light) {
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

      GameWindow::castShadow(gameObject, memPixel[j], camera, light);

      // Meant to draw on top of casted shadows
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
 * @brief Casts a shadow given a pixel with respect to the GameObject and
 * weights observed from the light source.
 *
 * @param gameObject - GameObject to cast shadows
 * @param pixel - Relative pixel to cast shadows
 * @param camera - GameObject to draw pixels with respect to the screen
 * @param light - GameObject that represents the source to procure shadows from.
 * The width and height represent intensity vectors
 */
void GameWindow::castShadow(GameObject::GameObject *gameObject,
                            RectStruct::Rect *pixel,
                            GameObject::GameObject *camera,
                            GameObject::GameObject *light) {
  RectStruct::Color *c =
      new (MemoryManagement::MemoryManagement::allocate<RectStruct::Color>(
          sizeof(RectStruct::Color))) RectStruct::Color;

  std::vector<int> lightDir;
  int relObjX = gameObject->getX() - pixel->position.x - camera->getX();
  int relObjY = gameObject->getY() - pixel->position.y - camera->getY();
  int relLightX = light->getX() - camera->getX();
  int relLightY = light->getY() - camera->getY();

  int dirX = relLightX - relObjX;
  int dirY = relLightY - relObjY;

  float shadowOffsetFactor = 0.1;

  int shadowOffsetX = static_cast<int>(dirX * shadowOffsetFactor);
  int shadowOffsetY = static_cast<int>(dirY * shadowOffsetFactor);

  drawRect(relObjX - shadowOffsetX, relObjY - shadowOffsetY, gameObject->getW(),
           gameObject->getH(), c);

  c = static_cast<RectStruct::Color *>(
      MemoryManagement::MemoryManagement::deallocate<RectStruct::Color>(c));
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
