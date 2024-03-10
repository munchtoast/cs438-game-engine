#include "BoxRigidBody.h"
#include "GameObject.h"
#include "Map.h"
#include "spdlog/spdlog.h"
#include <algorithm>

namespace BoxRigidBody {
BoxRigidBody::BoxRigidBody(float x, float y, float width, float height,
                           float angle)
    : GameObject(x, y, width, height, angle) {
  BoxRigidBody::setRectProperties(static_cast<RectStruct::Rect *>(
      MemoryManagement::MemoryManagement::allocate<RectStruct::Rect>(
          sizeof(RectStruct::Rect))));

  Util::Util::checkIfMemAllocSuccess(getRectProperties());

  BoxRigidBody::setX(x);
  BoxRigidBody::setY(y);
  BoxRigidBody::setW(width);
  BoxRigidBody::setH(height);
  BoxRigidBody::setA(angle);
}
BoxRigidBody::~BoxRigidBody() { BoxRigidBody::cleanup(); }
void BoxRigidBody::setVX(float velx) {
  BoxRigidBody::getRectProperties()->velocity.vx = velx;
}
void BoxRigidBody::setVY(float vely) {
  BoxRigidBody::getRectProperties()->velocity.vy = vely;
}
void BoxRigidBody::update() {
  BoxRigidBody::setX(BoxRigidBody::getX() + BoxRigidBody::getVX());
  BoxRigidBody::setY(BoxRigidBody::getY() + BoxRigidBody::getVY());
}
float BoxRigidBody::getVX() {
  return BoxRigidBody::getRectProperties()->velocity.vx;
}
float BoxRigidBody::getVY() {
  return BoxRigidBody::getRectProperties()->velocity.vy;
}
void BoxRigidBody::cleanup() {
  if (!Util::Util::checkIfNullPtr(getRectProperties()))
    BoxRigidBody::setRectProperties(static_cast<RectStruct::Rect *>(
        MemoryManagement::MemoryManagement::deallocate<RectStruct::Rect>(
            BoxRigidBody::getRectProperties())));
  Util::Util::checkIfMemFreeSuccess(BoxRigidBody::getRectProperties());
}
} // namespace BoxRigidBody
