/**
 * @file Animation.h
 * @brief Defines the Animation and Cel class which is responsible for handling
 * the visual representation of objects.
 *
 * The Animation object, and Cel object represent the core building blocks for
 * the animation engine. More specifically, the Animation object is the
 * Animation engine itself, and the Cel object are the bound group of pixels.
 * Then, the Animation engine handles the sequence of Cel objects to send to the
 * rendering engine.
 *
 * @note The Animation engine's dependencies should be fulfilled. (i.e. Map
 * requirements and RectStruct)
 *
 * @remark This class serves to interact with the rendering engine by supplying
 * the sequence of pixels to project.
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-26)
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Map.h"
#include "RectStruct.h"

namespace Animation {
class Cel {
public:
  Cel();
  virtual ~Cel();
  void setRenderable(bool r);
  bool getRenderable();

  Map::Map<RectStruct::Rect> *getPixels();
  void setSprite();
  void setPixels(Map::Map<RectStruct::Rect> *npixel);

private:
  Map::Map<RectStruct::Rect> *pixels;
  bool renderable;

  void cleanup();
};

class Animation {
public:
  Animation();
  virtual ~Animation();

  void addCels(Map::Map<Cel> *cels);

  void setAnimationState(int nstate);
  int getAnimationState();

  Map::Map<Cel> *getCelsToRender();

  void handleEvent();

private:
  Map::Map<Map::Map<Cel>> *animationList;
  int state;

  void cleanup();
};
} // namespace Animation

#endif