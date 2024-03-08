#include "BoxRigidBody.h"
#include "BoxBody.h"
#include "GameObject.h"
#include "Map.h"
#include "spdlog/spdlog.h"
#include <algorithm>

namespace BoxRigidBody {
BoxRigidBody::BoxRigidBody(float x, float y, float width, float height,
                           float angle) {
  BoxRigidBody::setBoxProperties(static_cast<BoxBody::Box*>(
      MemoryManagement::MemoryManagement::allocate<BoxBody::Box>(
          sizeof(BoxBody::Box))));

  Util::Util::checkIfMemAllocSuccess(getBoxProperties());
  BoxRigidBody::setX(x);
  BoxRigidBody::setY(y);
  BoxRigidBody::setW(width);
  BoxRigidBody::setH(height);
  BoxRigidBody::setA(angle);
}

BoxRigidBody::~BoxRigidBody() { BoxRigidBody::cleanup(); }

void BoxRigidBody::setX(float x) {
    BoxRigidBody::getBoxProperties()->position.x = x;
}
void BoxRigidBody::setY(float y) {
    BoxRigidBody::getBoxProperties()->position.y = y;
}
void BoxRigidBody::setW(float width) {
    BoxRigidBody::getBoxProperties()->size.width = width;
}
void BoxRigidBody::setH(float height) {
    BoxRigidBody::getBoxProperties()->size.height = height;
}
void BoxRigidBody::setA(float angle) { BoxRigidBody::getBoxProperties()->position.angle = angle; }

void BoxRigidBody::setVX(float velx) {
    BoxRigidBody::getBoxProperties()->velocity.vx = velx;
}
void BoxRigidBody::setVY(float vely) { BoxRigidBody::getBoxProperties()->velocity.vy = vely; }


float BoxRigidBody::getX() { return BoxRigidBody::getBoxProperties()->position.x; }
float BoxRigidBody::getY() { return BoxRigidBody::getBoxProperties()->position.y; }
float BoxRigidBody::getW() { return BoxRigidBody::getBoxProperties()->size.width; }
float BoxRigidBody::getH() { return BoxRigidBody::getBoxProperties()->size.height; }
float BoxRigidBody::getA() { return BoxRigidBody::getBoxProperties()->position.angle; }
float BoxRigidBody::getVX() { return BoxRigidBody::getBoxProperties()->velocity.vx; }
float BoxRigidBody::getVY() { return BoxRigidBody::getBoxProperties()->velocity.vy; }

BoxBody::Box* BoxRigidBody::getBoxProperties() {
    return BoxRigidBody::boxProperties;
}

void BoxRigidBody::setBoxProperties(BoxBody::Box* ptr) {
    boxProperties = ptr;
}


void BoxRigidBody::cleanup() {
    if (!Util::Util::checkIfNullPtr(getBoxProperties()))
        BoxRigidBody::setBoxProperties(static_cast<BoxBody::Box *>(
            MemoryManagement::MemoryManagement::deallocate<BoxBody::Box>(
                BoxRigidBody::getBoxProperties())));
    Util::Util::checkIfMemFreeSuccess(BoxRigidBody::getBoxProperties());
}
} // namespace BoxRigidBody
