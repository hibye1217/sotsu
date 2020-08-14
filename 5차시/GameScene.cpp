#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene() {
	score = 0;
	backgroundInstantiate = false;

	Background* background = new Background();
	background->setPos(0, 0);
	backgroundList.push_back(background);
	AddObject(background);

	Sprite* tmpBridge = new Sprite("Resources/Image/LoopMap.png");
	tmpBridge->setPos(0, 500);
	bridgeList.push_back(tmpBridge);

	Sprite* tempBridge = new Sprite("Resources/Image/LoopMap.png");
	tempBridge->setPos(SCREEN_WIDTH, 500);
	bridgeList.push_back(tempBridge);

	Sprite* tmpCoin = new Sprite("Resources/Image/coin-yellow.png");
	tmpCoin->setPos(SCREEN_WIDTH + 70, 400);
	coinList.push_back(tmpCoin);

	Sprite* tmpObstacle = new Sprite("Resources/Image/Drop.png");
	tmpObstacle->setPos(SCREEN_WIDTH, 400);
	obstacleList.push_back(tmpObstacle);

	for (int i = 0; i < 4; i++) {
		numArray[i].setPos(0 + 60 * i, 10);
	}

	player = new Player();
}

GameScene::~GameScene() {

}

void GameScene::Render() {
	for (auto& background : backgroundList) {
		background->Render();
	}

	for (auto& bridge : bridgeList) {
		bridge->Render();
	}

	for (auto& obstacle : obstacleList) {
		obstacle->Render();
	}

	for (auto& coin : coinList) {
		coin->Render();
	}

	for (int i = 0; i < 4; i++) {
		numArray[i].Render();
	}

	player->Render();
}

void GameScene::Update(float dTime) {
	Scene::Update(dTime);

	int randNum = rand() % 1 + 1;
	if (randNum == 1) {
		Sprite* tempCoin = new Sprite("Resources/Image/coin-yellow.png");
		tempCoin->setPos(SCREEN_WIDTH + 100, 400);
		coinList.push_back(tempCoin);
	}

	numArray[0].setNum(score / 1000 % 10);
	numArray[1].setNum(score / 100 % 10);
	numArray[2].setNum(score / 10 % 10);
	numArray[3].setNum(score % 10);

	player->Update(dTime);

	for (auto iter = backgroundList.begin();
		iter != backgroundList.end(); iter++) {

		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			RemoveObject(*iter);
			SAFE_DELETE(*iter);
			iter = backgroundList.erase(iter);
			backgroundInstantiate = false;

			if (iter == backgroundList.end()) {
				break;
			}
		}
	}

	if (!backgroundInstantiate) {
		Background* background = new Background();
		background->setPos(SCREEN_WIDTH - 10, 0);
		backgroundList.push_back(background);
		AddObject(background);
		backgroundInstantiate = true;
	}

	int bridgeDiff = 500 * dTime;
	for (auto iter = bridgeList.begin();
		iter != bridgeList.end(); iter++) {

		(*iter)->setPos((*iter)->getPosX() - bridgeDiff,
			(*iter)->getPosY());

		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			SAFE_DELETE(*iter);
			iter = bridgeList.erase(iter);

			Sprite* tempBridge = new Sprite("Resources/Image/LoopMap.png");
			tempBridge->setPos(SCREEN_WIDTH - 20, 500);
			bridgeList.push_back(tempBridge);

			if (iter == bridgeList.end()) {
				break;
			}
		}
	}

	int obstacleDiff = 500 * dTime;
	for (auto iter = obstacleList.begin();
		iter != obstacleList.end(); iter++) {

		(*iter)->setPos((*iter)->getPosX() - obstacleDiff,
			(*iter)->getPosY());

		if (player->IsCollisionRect(*iter)) {
			sceneManager->ChangeScene(new MainScene());
			return;
		}

		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			SAFE_DELETE(*iter);
			iter = obstacleList.erase(iter);

			Sprite* tempObstacle = new Sprite("Resources/Image/Drop.png");
			tempObstacle->setPos(SCREEN_WIDTH - 20, 400);
			obstacleList.push_back(tempObstacle);

			if (iter == obstacleList.end()) {
				break;
			}
		}
	}

	int coinDiff = 500 * dTime;
	for (auto iter = coinList.begin();
		iter != coinList.end(); iter++) {

		(*iter)->setPos((*iter)->getPosX() - coinDiff,
			(*iter)->getPosY());

		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			SAFE_DELETE(*iter);
			iter = coinList.erase(iter);

			if (iter == coinList.end()) {
				break;
			}
		}
	}

	for(auto iter = coinList.begin();
	iter != coinList.end(); iter++) {
		if (player->IsCollisionRect(*iter)
			&& (inputManager->GetKeyState('M') == KEY_DOWN
				|| inputManager->GetKeyState('N') == KEY_DOWN)) {
			score += 1;

			SAFE_DELETE(*iter);
			iter = coinList.erase(iter);

			if (iter == coinList.end()) {
				break;
			}
		}
	}
}