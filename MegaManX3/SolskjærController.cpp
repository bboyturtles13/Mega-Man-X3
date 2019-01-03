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

void Solskj�rController::update(DWORD dt, unordered_map<int, GameObject*>* staticObject, MegamanX* main)
{
	this->staticObject = staticObject;
	objects.clear();
	barrier->update(dt);
	
	if (!barrier->isHidden) {
		if (barrier->y >= 855) {
			generateCarryArm(dt);
			generateSolskj�r(dt);
		}
	}
	if (solskj�r->isDie) barrier->isHidden = true;

	if (carryArmFirst)
		objects[4] = carryArmFirst->getBox();

	if (carryArmSecond)
		objects[5] = carryArmSecond->getBox();

	collisionMain(main);
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

void Solskj�rController::collisionMain(MegamanX* main)
{
	bulletCollisionDynamic(main);//like main bullet collision dynamic
	if (main->protect()) return;
	dynamicCollisionMain(main); //like dynamic obejct bullet collision this
}

void Solskj�rController::bulletCollisionDynamic(MegamanX* main)
{
	auto dynamicObjects = &objects;
	for (auto it = dynamicObjects->begin(); it != dynamicObjects->end(); )
	{
		if (!(*it).second) return; //null

		DynamicObject* obj = dynamic_cast<DynamicObject*>((*it).second);
		
		// bullet main collision enemies or boss (use single & swept aabb)
		auto objBox = obj->getBoundBox();
		auto weapons = main->getWeapons();
		for (auto bullet = weapons->begin(); bullet != weapons->end();)
		{
			if (obj->isDeath()) break;
			if (bullet[0]->getBoundBox().intersectsWith(objBox) //single aabb collision
				||
				main->collisionGameObject(*bullet, obj)) //colision bullet with dynamic with swept aabb
			{
				obj->receiveDamage(bullet[0]->getDamage());
				if (obj->isDeath())
				{
					if (dynamic_cast<BusterShot*>(*bullet)) // don't cross delete bullet
					{
						delete *bullet;
						bullet = weapons->erase(bullet);
					}
				}
				else
				{
					delete *bullet;
					bullet = weapons->erase(bullet);
				}
				break;// out for bullet
			}
			else // bullet main collision bullet enemies or boss (use swept aabb)
			{
				++bullet;
			}
		}
		++it;
	}
}

void Solskj�rController::dynamicCollisionMain(MegamanX* main)
{
	auto megamanBox = main->getBoundBox();
	auto dynamicObjects = &objects;//dynamic object

	for (auto kv : *dynamicObjects)
	{
		// object collision main (include bullet) (use single & swept aabb)
		DynamicObject* obj = dynamic_cast<DynamicObject*>(kv.second);
		if (!obj || obj->isDeath()) continue;

		if (kv.second->getBoundBox().intersectsWith(megamanBox) //single
			||
			main->collisionGameObject(obj, main)) // swpet
		{
			main->setHurt();
			return;
		}

		auto bullets = obj->getWeapons();
		for (auto bullet = bullets->begin(); bullet != bullets->end(); )
		{
			if (bullet[0]->getBoundBox().intersectsWith(megamanBox) //single
				||
				main->collisionBullet(*bullet, main)) //swept
			{
				if (bullet[0]->toLeft)
					obj->createExplosion(bullet[0]->x + 10, bullet[0]->y);
				else
					obj->createExplosion(bullet[0]->x - 10, bullet[0]->y);
				delete *bullet;
				bullet = bullets->erase(bullet);
				main->setHurt();
				return;
			}
			else ++bullet;
		}
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
		objects[2] = carryArmFirst;
		return;
	}
	
	if (!carryArmFirst->isDie && carryArmFirst->isComplete) {
		if (isOnlyOne_2) {
			carryArmSecond = new CarryArm(barrier->initX + 36, barrier->initY - 20, true);
			isOnlyOne_2 = false;
		}
		carryArmSecond->update(dt);
		objects[3] = carryArmSecond;
		
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
		solskj�r->update(dt, staticObject);
		objects[1] = solskj�r;
		return;
	}
}
