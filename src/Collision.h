/*
 * @file Collision.h
 * @brief Defines the GameObject class, a fundamental component of the game
 * engine.
 *
 * The GameObject class represents a basic object within the game engine. It is
 * equipped with rectProperties, essential for rendering the object.
 * Additionally, it maintains the internal location of the object before
 * projection through the renderer.
 *
 * @note Ensure that rectProperties are properly configured for rendering.
 *
 * @remark This class serves as a foundational element for constructing
 * interactive elements in the game.
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-01)
 */

#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
#include <GameObject.h>

namespace Collision {
	class Collision {
	public:
		Collision();
		virtual ~Collision();


		static bool detectCollision(GameObject *obj1, GameObject *obj2);

		static void handleCollision(GameObject *obj1, GameObject *obj2);

	private:
		void cleanup();

} // namespace Collision
#endif