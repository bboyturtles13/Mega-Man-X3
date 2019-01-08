#pragma once
#include<vector>

#include "DynamicObject.h";
#include "ConstGlobals.h"
#include "Camera.h"
#include "CollisionEvent.h"
#include "Brick.h"

#include "BulletCollision.h"
#include "Solskj�rBullet.h"

#define SOLSKJ�R_STATE_INIT 0
#define SOLSKJ�R_STATE_READY_SHOT 100
#define SOLSKJ�R_STATE_SHOT 200
#define SOLSKJ�R_STATE_EXIT 300
#define SOLSKJ�R_STATE_DIE 400

#define SOLSKJ�R_ID_TEXTURE 791

class Solskj�r :
	public DynamicObject
{
public:
	bool isRepeat;
	bool* isDie = &_death;

	Solskj�r();
	~Solskj�r();
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void renderDie(DWORD dt, D3DCOLOR colorBrush = WHITE(255));// **
	void generatePosition();// **
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void reset();

private:
	PointF die[3];// **
	BulletCollision* collisionEffect = BulletCollision::getInstance();

	void setState(int state);
	void loadResources();

	void createBullet();
	void createCloneBullet();
};

