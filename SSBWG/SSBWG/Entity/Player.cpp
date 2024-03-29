#include "Player.h"
#include "EntityManager.h"
#include "../Map/Map.h"
#include "../Utility/randf.h"

Entity::Player::Player(float posX,float posY,float width,float height, Group::Group team)
	:Entity(posX, posY, width, height),
	jumpSound((team == Group::red)? "red_jump.wav" : "blue_jump.wav"),
	collideSound((team == Group::red)? "red_collide.wav" : "blue_collide.wav")
{
	col = new Collision::AABBCollider(body, this);
	maxSpeed = 450;
	group = team;
	if(group == Group::red)
		img.loadFromFile("red.png");
	else
		img.loadFromFile("blue.png");

	if(group == Group::red)
		heading.x = Direction::right;
	else
		heading.x = Direction::left;
}

void Entity::Player::update()
{	
	setPosition(getPosition() + velocity);
	unscaledVelocity.x = 0;

	System::Keyboard keyboard = System::Window::getInstance().getKeyboard();
	
	if(group == Group::red)
	{
		if(keyboard.keyHeld(System::Key::A))
		{
			unscaledVelocity.x -= maxSpeed;
			heading.x = Direction::left;
		}
		if(keyboard.keyHeld(System::Key::D))
		{
			unscaledVelocity.x += maxSpeed;
			heading.x = Direction::right;
		}
		if(static_cast<Collision::AABBCollider*>(col)->getCollideDown())
		{
			if(keyboard.keyHeld(System::Key::W))
			{
				unscaledVelocity.y -= 600;
				
				jumpSound.setPitch(randf(.7, 1.3));
				jumpSound.setVolume(17);
				jumpSound.Play();
			}
		}
		else	
			unscaledVelocity.y += 550 * System::Time::getInstance().unscaledDeltaTime();
	}
	else if(group == Group::blue)
	{
		if(keyboard.keyHeld(System::Key::L))
		{
			unscaledVelocity.x += maxSpeed;
			heading.x = Direction::right;
		}
		if(keyboard.keyHeld(System::Key::J))
		{
			unscaledVelocity.x -= maxSpeed;
			heading.x = Direction::left;
		}
		if(static_cast<Collision::AABBCollider*>(col)->getCollideDown())
		{
			if(keyboard.keyHeld(System::Key::I))
			{
				unscaledVelocity.y -= 600;
				jumpSound.setPitch(randf(.7, 1.3));
				jumpSound.setVolume(37);
				jumpSound.Play();
			}
		}
		else	
			unscaledVelocity.y += 550 * System::Time::getInstance().unscaledDeltaTime();
	}

	velocity = unscaledVelocity * System::Time::getInstance().unscaledDeltaTime();

	boundsCheck();
}

void Entity::Player::draw(System::Window& window)
{
	//window.drawRect(body);
	window.drawImage(img, getPosition(), heading.x, 1.0);
}

void Entity::Player::onCollideLeft(Entity* other) 
{
	if(velocity.x < 0) 
	{
		velocity.x = 0;
		unscaledVelocity.x = 0;
	}
}
void Entity::Player::onCollideRight(Entity* other) 
{
	if(velocity.x > 0) 
	{
		velocity.x = 0;
		unscaledVelocity.x = 0;
	}
}
void Entity::Player::onCollideUp(Entity* other) 
{
	if(velocity.y < 0) 
	{
		velocity.y = 0;
		unscaledVelocity.y = 0;

		if(other == NULL)
		{
			collideSound.setPitch(randf(.7, 1.3));
			collideSound.Play();
		}
	}
}
void Entity::Player::onCollideDown(Entity* other) 
{
	if(velocity.y > 0)
	{ 
		velocity.y = 0;
		unscaledVelocity.y = 0;

		if(other == NULL)
		{
			collideSound.setPitch(randf(.7, 1.3));
			collideSound.Play();
		}
	}
}

void Entity::Player::boundsCheck()
{
	if(group == Group::red)
	{
		if(getBody().getRight() + velocity.x >=  Map::getMap().getPixelWidth()/2)
		{
			velocity.x = 0;
			Vector2f v = getPosition();
			v.x = Map::getMap().getPixelWidth()/2 - getWidth();
			setPosition(v);
		}
	}
	else if(group == Group::blue)
	{
		if(getBody().getLeft() + velocity.x <  Map::getMap().getPixelWidth()/2)
		{
			velocity.x = 0;
			Vector2f v = getPosition();
			v.x = Map::getMap().getPixelWidth()/2;
			setPosition(v);
		}
	}
}