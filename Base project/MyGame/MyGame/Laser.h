#pragma once
#include "Engine/GameEngine.h"

class Laser : public GameObject
{
public:
	Laser(sf::Vector2f pos);
	void increaseCounter();
	void draw();
	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
private:
	sf::Sprite sprite_;
	int counter;
};

typedef std::shared_ptr<Laser> LaserPtr;
