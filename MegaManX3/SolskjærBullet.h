#pragma once
#include<vector>
#include <stdlib.h>

#include "Weapon.h"
#include "Camera.h"
#include "ConstGlobals.h"
#include "CollisionEvent.h"
#include "Brick.h"


#define SOLSKJ�R_BULLET_SPEED_X -0.055f;
#define SOLSKJ�R_BULLET_SPEED_Y 0.05f

#define SOLSKJ�R_BULLET_STATE_ONLY 0

#define SOLSKJ�R_BULLET_ID_TEXTURE 337

class Solskj�rBullet : public Weapon
{
public:
	Solskj�rBullet(float x, float y);
	~Solskj�rBullet();
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void setPosition(float x, float y);
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;

private:
	Solskj�rBullet* clone;
	bool isClone;
	int counter;
	bool isOnly;

	void setState(int state);
	void loadResources();
	void collisionStatic(unordered_map<int, GameObject*>* staticObjects);
};

