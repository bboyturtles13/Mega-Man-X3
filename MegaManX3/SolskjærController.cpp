#include "Solskj�rController.h"



Solskj�rController::Solskj�rController()
{
	barrier = new BarrierSystem();
	solskj�r = new Solskj�r();
	carryArmFirst = new CarryArm(barrier->initX + 36, barrier->initY - 20, false);

	isOnlyOne_1 = isOnlyOne_2 = true;
	counter = 0;
}


Solskj�rController::~Solskj�rController()
{
}

void Solskj�rController::update(DWORD dt)
{
	barrier->update(dt);
	
	if (!barrier->isHidden) {
		if (barrier->y >= 855) {
			generateCarryArm(dt);
			generateSolskj�r(dt);
		}
	}
	if (solskj�r->isDie) barrier->isHidden = true;
}

void Solskj�rController::render(DWORD dt)
{
	if (!barrier->isHidden) {
		solskj�r->render(dt);
		barrier->render(dt);
		carryArmFirst->render(dt);
		if (carryArmSecond != NULL) carryArmSecond->render(dt);
	}
	else
	{
		barrier->render(dt);
	}
}

void Solskj�rController::generateCarryArm(DWORD dt)
{
	if (carryArmFirst->isDie) {
		if (isOnlyOne_1) {
			carryArmFirst = new CarryArm(barrier->initX + 36, barrier->initY - 20, false);
			isOnlyOne_1 = false;
		}
		carryArmFirst->update(dt);

		return;
	}
	
	if (!carryArmFirst->isDie && carryArmFirst->isComplete) {
		if (isOnlyOne_2) {
			carryArmSecond = new CarryArm(barrier->initX + 36, barrier->initY - 20, true);
			isOnlyOne_2 = false;
		}
		carryArmSecond->update(dt);

		return;
	}

	carryArmFirst->update(dt);
	if (carryArmSecond != NULL) carryArmSecond->update(dt);
}

void Solskj�rController::generateSolskj�r(DWORD dt)
{
	if (carryArmSecond != NULL && carryArmSecond->isComplete) {
		counter++;
		if (counter >= 800) {
			solskj�r = new Solskj�r();
			counter = 0;
		}
		solskj�r->update(dt);

		return;
	}
}
