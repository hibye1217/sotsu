#include "stdafx.h"
#include "Player.h"

Player::Player() {
	isJump = false;
	doubleJump = false;
	gravity = 9.8;

	playerAnimation = new Animation(6);
	playerAnimation->AddFrame("Resources/Image/Player-run.png");
	playerAnimation->AddFrame("Resources/Image/Player-stop.png");
	AddChild(playerAnimation);
	
	rect = playerAnimation->getRect();
}

Player::~Player() {

}

void Player::Render() {
	Object::Render();
	playerAnimation->Render();
}

void Player::Update(float dTime) {
	gravity += 9.8f;

	setPos(getPosX(),
		getPosY() + gravity * dTime);

	if (isJump) {
		setPos(getPosX(),
			getPosY() - 450 * dTime);
		if (doubleJump) {
			setPos(getPosX(),
				getPosY() - 50 * dTime);
		}
		if (inputManager->GetKeyState(VK_UP) == KEY_DOWN) {
			if (!doubleJump) gravity = 0;
			doubleJump = true;
		}
	}
	if (getPosY() > 350) {
		setPos(getPosX(), 350);
		doubleJump = false;
		isJump = false;
	}

	if (inputManager->GetKeyState(VK_UP) == KEY_DOWN) {
		if (getPosY() == 350) {
			isJump = true;
			gravity = 0;
		}
	}

	playerAnimation->Update(dTime);
}