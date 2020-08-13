#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene() {
	gravity = 0;
	isJump = false;
	doubleJump = false;

	backgroundList.push_back(new Sprite("Resources/Image/Background.png"));

	Sprite* tmpBackground = new Sprite("Resources/Image/Background.png");
	tmpBackground->setPos(SCREEN_WIDTH, 0);
	backgroundList.push_back(tmpBackground);

	Sprite* tmpBridge = new Sprite("Resources/Image/LoopMap.png");
	tmpBridge->setPos(0, 500);
	bridgeList.push_back(tmpBridge);

	Sprite* tempBridge = new Sprite("Resources/Image/LoopMap.png");
	tempBridge->setPos(SCREEN_WIDTH, 500);
	bridgeList.push_back(tempBridge);

	player = new Animation(6);
	player->AddFrame("Resources/Image/Player-run.png");
	player->AddFrame("Resources/Image/Player-stop.png");
	player->setPos(50, 100);
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

	player->Render();
}

void GameScene::Update(float dTime) {
	Scene::Update(dTime);
	gravity += 9.8f;

	player->setPos(player->getPosX(),
		player->getPosY() + gravity * dTime);

	if (isJump) {
		player->setPos(player->getPosX(),
			player->getPosY() - 400 * dTime);
		if (doubleJump) {
			player->setPos(player->getPosX(),
				player->getPosY() - 50 * dTime);
		}
		if (inputManager->GetKeyState(VK_UP) == KEY_DOWN) {
			if (!doubleJump) gravity = 0;
			doubleJump = true;
		}
	}
	if (player->getPosY() > 350) {
		player->setPos(player->getPosX(), 350);
		doubleJump = false;
		isJump = false;
	}

	if (inputManager->GetKeyState(VK_UP) == KEY_DOWN) {
		if (player->getPosY() == 350) {
			isJump = true;
			gravity = 0;
		}
	}

	player->Update(dTime);

	int backgroundDiff = 250 * dTime;
	for (auto iter = backgroundList.begin();
		iter != backgroundList.end(); iter++) {

		(*iter)->setPos((*iter)->getPosX() - backgroundDiff,
			(*iter)->getPosY());

		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			SAFE_DELETE(*iter);
			iter = backgroundList.erase(iter);

			Sprite* tmpBackground = new Sprite("Resources/Image/Background.png");
			tmpBackground->setPos(SCREEN_WIDTH - 20, 0);
			backgroundList.push_back(tmpBackground);

			if (iter == backgroundList.end()) {
				break;
			}
		}
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
}