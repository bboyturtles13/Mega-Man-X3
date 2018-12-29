#include "Solskj�rBullet.h"


Solskj�rBullet::Solskj�rBullet(float x, float y)
{
	this->x = x;
	this->y = y;
	isDelete = false;
	isClone = false;
	counter = 0;
	isOnly = true;

	this->setState(SOLSKJ�R_BULLET_STATE_ONLY);
	this->loadResources();
}

Solskj�rBullet::~Solskj�rBullet()
{
}

void Solskj�rBullet::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	counter++;
	if (counter >= 60) {
		counter = 60;

		x += speed.vx * dt;
		y += speed.vy * dt;

		if (y >= 930) {
			speed.vy = 0;
			if (!isClone) {
				if (isOnly) {
					clone = new Solskj�rBullet(x, y);
					clone->isClone = true;
					clone->setState(SOLSKJ�R_BULLET_STATE_ONLY);
					isOnly = false;
				}
				clone->update(dt);
			}
		}
	}
}

void Solskj�rBullet::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (isClone) debugOut(L"clone x = %i \n", x);
	else debugOut(L"not clone x = %i \n", x);
	auto center = cameraGlobal->transform(x, y);
	_animations[state]->render(center.x, center.y);
	if (!isClone && clone != NULL) 
		clone->render(dt);
}

void Solskj�rBullet::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Solskj�rBullet::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	// correct?????
	left = x;
	top = y;
	right = x + 14;
	bottom = y + 16;
}

void Solskj�rBullet::setState(int state)
{
	if (!isClone) {
		speed.vx = SOLSKJ�R_BULLET_SPEED_X;
	}
	else
	{
		speed.vx = -SOLSKJ�R_BULLET_SPEED_X;
	}
	speed.vy = SOLSKJ�R_BULLET_SPEED_Y;

	this->state = state;
}

void Solskj�rBullet::loadResources()
{
	CTextures * textures = CTextures::getInstance();
	if (!textures->getTexture(SOLSKJ�R_BULLET_ID_TEXTURE))
		textures->add(SOLSKJ�R_BULLET_ID_TEXTURE, L"Resource\\Textures\\subboss.png", 0, 0, D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::getInstance();
	CAnimations * animations = CAnimations::getInstance();

	LPANIMATION ani;

	sprites->addSprite(20001, SOLSKJ�R_BULLET_ID_TEXTURE, 57, 256, 14, 16);
	sprites->addSprite(20002, SOLSKJ�R_BULLET_ID_TEXTURE, 193, 256, 14, 16);

	ani = new CAnimation(50);
	ani->add(20001);
	ani->add(20002);
	animations->add(SOLSKJ�R_BULLET_STATE_ONLY, ani);

	this->addAnimation(SOLSKJ�R_BULLET_STATE_ONLY);
}

void Solskj�rBullet::collisionStatic(unordered_map<int, GameObject*>* staticObjects)
{
	vector<CollisionEvent*> coEvents;
	vector<CollisionEvent*> coEventsResult;

	collision->findCollisions(dt, this, *staticObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += speed.vx * dt;
		y += speed.vy * dt;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		collision->filterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 1.f;
		y += min_ty * dy + ny * 1.f;

		isDelete = true;
	}
	UINT size = coEvents.size();
	for (UINT i = 0; i < size; ++i) delete coEvents[i];
}
