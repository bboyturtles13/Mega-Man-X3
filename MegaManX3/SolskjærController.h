#pragma once
#include<vector>

#include "BarrierSystem.h"
#include "Solskj�r.h"
#include "CarryArm.h"
#include "MegamanX.h"
#include <unordered_map>
class Solskj�rController
{
public:
	Solskj�rController();
	~Solskj�rController();
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObject, MegamanX* main);
	void render(DWORD dt);
	
	void generateCarryArm(DWORD dt);
	void generateSolskj�r(DWORD dt);

	bool getIsFinish() { return barrier->isFinish; }

private:
	BarrierSystem* barrier;
	Solskj�r* solskj�r;
	CarryArm* carryArmFirst;
	CarryArm* carryArmSecond;
	unordered_map<int, GameObject*> objects;
	unordered_map<int, GameObject*>* staticObject;
	
	bool isOnlyOne;
	bool isDisplayBoss;
	int clock;
	int clockForCarryArm;
	int clockForSolskj�r;
	int limitTime;

	void collisionMain(MegamanX* main);
	void bulletCollisionDynamic(MegamanX* main);
	void dynamicCollisionMain(MegamanX* main);
};

