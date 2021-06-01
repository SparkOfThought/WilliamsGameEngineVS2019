#include "Ship.h"
#include <memory>
#include "Laser.h"


const float SPEED = 0.3f;
const int FIRE_DELAY = 750;
void Ship::update(sf::Time& elapsed) {
	sf::Vector2f pos = sprite_.getPosition();
	float x = pos.x;
	float y = pos.y;

	int msElapsed = elapsed.asMilliseconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) y -= SPEED * msElapsed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) y += SPEED * msElapsed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) x -= SPEED * msElapsed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) x += SPEED * msElapsed;
	sprite_.setPosition(sf::Vector2f(x, y));
	if (fireTimer_ > 0) 
	{
		fireTimer_ -= msElapsed;
	}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fireTimer_ <= 0)
		{
			fireTimer_ = FIRE_DELAY;
			sf::FloatRect bounds = sprite_.getGlobalBounds();
			float laserx = x + (bounds.width / 1.25f);
			float laserY = y + (bounds.height / 2.00);
			LaserPtr laser = std::make_shared<Laser>(sf::Vector2f(laserx, laserY));
			GAME.getCurrentScene().addGameObject(laser);

			if (pos.x < sprite_.getGlobalBounds().width * -1)
			{
				makeDead();
				
			}
		}
	}

Ship::Ship()
{
	sprite_.setTexture(GAME.getTexture("resources/Ship.png"));
	sprite_.setPosition(sf::Vector2f(25, 25));
	assignTag("ship");
}

void Ship::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}
sf::FloatRect Ship::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}