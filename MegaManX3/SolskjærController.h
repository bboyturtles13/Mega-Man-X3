#pragma once
#include<vector>

#include "BarrierSystem.h"
#include "Solskj�r.h"
#include "CarryArm.h"

class Solskj�rController
{
public:
	Solskj�rController();
	~Solskj�rController();
	void update(DWORD dt);
	void render(DWORD dt);
	void generateCarryArm(DWORD dt);
	void generateSolskj�r(DWORD dt);

private:
	BarrierSystem* barrier;
	Solskj�r* solskj�r;
	CarryArm* carryArmFirst;
	CarryArm* carryArmSecond;

	bool isOnlyOne_1;
	bool isOnlyOne_2;
	
	int counter;
};

