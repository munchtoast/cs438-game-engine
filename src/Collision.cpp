#include "Collision.h"
#include "GameObject.h"

namespace Collision {
    /**
    * @brief Handles collisions between game objects
    *
    */

    Collision::Collision() {
    }

    Collision::~Collision() { Collision::cleanup(); }

    bool Collision::detectCollision(GameObject *obj1, GameObject *obj2) {
        // Check for collision along x-axis
        bool xCollision = obj1.x < obj2.x + obj2.width && obj1.x + obj1.width > obj2.x;

        // Check for collision along y-axis
        bool yCollision = obj1.y < obj2.y + obj2.height && obj1.y + obj1.height > obj2.y;

        return xCollision && yCollision;
    }
    void Collision::handleCollision(GameObject *obj1, GameObject *obj2) {
        // assuming that obj1 is the object that is moving into obj2
        while !(detectCollision(obj1, obj2) {
            if (obj1.x < obj2.x + obj2.width) {
                obj1.setX(obj1.x + 1);
            }
            else if (obj1.x + obj1.width > obj2.x) {
                obj1.setX(obj1.x - 1);
            }
            if (obj1.y < obj2.y + obj2.height) {
                obj1.setY(obj1.y + 1);
            }
            else if (obj1.y + obj1.height > obj2.y) {
                obj1.setY(obj1.x - 1);
            }
        }

    }

    void Collision::cleanup() { return; }


}