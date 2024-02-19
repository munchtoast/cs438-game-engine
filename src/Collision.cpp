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

    static bool Collision::detectCollision(GameObject *obj1, GameObject *obj2) {
        // Check for collision along x-axis
        bool xCollision = obj1.x < obj2.x + obj2.width && obj1.x + obj1.width > obj2.x;

        // Check for collision along y-axis
        bool yCollision = obj1.y < obj2.y + obj2.height && obj1.y + obj1.height > obj2.y;

        return xCollision && yCollision;
    }
    static void handleCollision(GameObject *obj1, GameObject *obj2) {
        // will handle collisions
    }

    void Collision::cleanup() { return; }


}