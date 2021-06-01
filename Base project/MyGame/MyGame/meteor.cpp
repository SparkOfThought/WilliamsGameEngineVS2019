#include "meteor.h"
#include "explosion.h"
#include "Laser.h"
#include "GameScene.h"
const float SPEED = 0.50f;
Meteor::Meteor(sf::Vector2f pos)
{
	sprite_.setTexture(GAME.getTexture("Resources/meteor.png"));
	sprite_.setPosition(pos);
	assignTag("meteor");
	setCollisionCheckEnabled(true);
}
void Meteor::draw() {
	GAME.getRenderWindow().draw(sprite_);
}
void Meteor::update(sf::Time& elapsed) {
	int msElapsed = elapsed.asMilliseconds();
	sf::Vector2f pos = sprite_.getPosition();

	if (pos.x < sprite_.getGlobalBounds().width*-1)
	{

		makeDead();
	}
	else
	{
		sprite_.setPosition(sf::Vector2f(pos.x - SPEED * msElapsed, pos.y));
	}
}
sf::FloatRect Meteor::getCollisionRect() 
{
	return sprite_.getGlobalBounds();
}

void Meteor::handleCollision(GameObject& otherGameObject) {
	if (otherGameObject.hasTag("laser"))
	{
		Laser& laser = (Laser&)otherGameObject;
			laser.increaseCounter();
		makeDead();
		sf::Vector2f pos = sprite_.getPosition();
		float x = pos.x;
		float y = pos.y;
		sf::FloatRect bounds = sprite_.getGlobalBounds();
		float explosionX = x + (bounds.width / 2.00f);
		float explosionY = y + (bounds.height / 2.00);
		ExplosionPtr explosion = std::make_shared<Explosion>(sf::Vector2f(explosionX, explosionY));
		GAME.getCurrentScene().addGameObject(explosion);
		GameScene& scene = (GameScene&)GAME.getCurrentScene();
		scene.IncreasesScore();
	};
	if (otherGameObject.hasTag("ship"))
	{
		GameScene& scene = (GameScene&)GAME.getCurrentScene();
		scene.decreaseLives();
		makeDead();
		sf::Vector2f pos = sprite_.getPosition();
		float x = pos.x;
		float y = pos.y;
		sf::FloatRect bounds = sprite_.getGlobalBounds();
		float explosionX = x + (bounds.width / 2.00f);
		float explosionY = y + (bounds.height / 2.00);
		ExplosionPtr explosion = std::make_shared<Explosion>(sf::Vector2f(explosionX, explosionY));
		GAME.getCurrentScene().addGameObject(explosion);
	}
}