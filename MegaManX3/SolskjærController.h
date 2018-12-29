#pragma once
#include<vector>

#include "BarrierSystem.h"
#include "Solskj�r.h"
#include "CarryArm.h"
#include "Box.h"

class Solskj�rController
{
public:
	Solskj�rController();
	~Solskj�rController();
	void update(DWORD dt);
	void render(DWORD dt);
	void generateCarryArm(DWORD dt);

private:
	BarrierSystem* barrier;
	Solskj�r* solskj�r;
	CarryArm* carryArm;
	Box* tempBoxLeft;
	Box* tempBoxRight;

	int counterCarryArm;
};

