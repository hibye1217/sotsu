#pragma once

#include "Object.h"
#include "Sprite.h"

class Background : public Object {
private:
	Sprite* background;
public:
	Background();
	~Background();

	void Render();
	void Update(float dTime);
};