#include "GameOver.h"
#include "GameOverScene.h"

GameOverScene::GameOverScene(int score)
{
	GameOverPtr gameOver = std::make_shared<GameOver>(score);
	addGameObject(gameOver); 
}
