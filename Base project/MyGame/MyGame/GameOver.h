#pragma once
#include "Engine/GameEngine.h"
class GameOver : public GameObject
{
public:
	GameOver(int score);
	void draw();
	void update(sf::Time& elapsed);
private:
	sf::Text text_;
};
typedef std::shared_ptr<GameOver> GameOverPtr;