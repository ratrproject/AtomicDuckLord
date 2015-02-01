#pragma once
#include "Entity.h"
#include "../Collision/AABBCollider.h"
#include "../System/Time.h"
#include "../Graphics/Image.h"

namespace Entity
{
	class Duck : public Entity
	{
		Vector2f unscaledVelocity;
		Graphics::Image image;
		float jumpPower;
		float timeOfDeath;
		float rotation;
	
	public:
		Duck(float posX,float posY,float width,float height);

		void update();
	
		void draw(System::Window&);

		void onCollideLeft(Entity* other = NULL);
		void onCollideRight(Entity* other = NULL);
		void onCollideUp(Entity* other = NULL);
		void onCollideDown(Entity* other = NULL);
	};
}