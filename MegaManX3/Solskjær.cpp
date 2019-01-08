#include "Solskj�r.h"


Solskj�r::Solskj�r()
{
	this->x = 4970;
	this->y = 849;
	this->isRepeat = true;
	this->visible = false;
	*isDie = false;

	this->setState(SOLSKJ�R_STATE_INIT);
	this->loadResources();
}


Solskj�r::~Solskj�r()
{
}

void Solskj�r::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	createCloneBullet();

	for (auto bullet = _weapons.begin(); bullet != _weapons.end();)
	{
		bullet[0]->update(dt, staticObjects);
		if (bullet[0]->getIsDelete())
		{
			delete bullet[0];
			bullet = _weapons.erase(bullet);
		}
		else ++bullet;
	}


	this->dt = dt;
	if (*isDie) {
		generatePosition();
		return;
	}

	visible = isRepeat;

	if (_animations[state]->isLastFrame()) {
		if (state == SOLSKJ�R_STATE_SHOT) {
			createBullet();
		}

		if (isRepeat) {
			state += 100;
		}

		if (state > 300) {
			state = 0;
			isRepeat = false;
		}

		setState(state);
	}
}

void Solskj�r::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (*isDie) {
		renderDie(dt);
		return;
	}

	if (visible) {
		auto center = cameraGlobal->transform(x, y);
		_animations[state]->render(center.x, center.y);
	}

	int size = _weapons.size();
	for (int i = 0; i < size; ++i)
	{
		_weapons[i]->render(dt);
	}

}

void Solskj�r::renderDie(DWORD dt, D3DCOLOR colorBrush)
{
	for (int i = 0; i < 3; i++) {
		auto center = cameraGlobal->transform(die[i].x, die[i].y);
		_animations[SOLSKJ�R_STATE_DIE + i]->render(center.x, center.y);
	}
}

void Solskj�r::generatePosition()
{
	// init position
	die[0] = { x, y }; //* important
	die[1] = { x + 24, y };
	die[2] = { x, y + 24 };

	speed.vy += 0.01f * dt;
	speed.vx += 0.008f * dt;

	dx = speed.vx * dt;
	dy = speed.vy * dt;

	die[0].x -= dx * 1.25;
	die[1].x += dx * 1.5;
	die[2].x -= dx;

	die[0].y += dy * 2;
	die[1].y += dy;
	die[2].y += dy * 2;
}

void Solskj�r::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 32;
	bottom = y + 23;
}

void Solskj�r::reset()
{
	this->x = 4970;
	this->y = 849;
	this->isRepeat = true;
	this->visible = true;
	*isDie = false;

	this->setState(SOLSKJ�R_STATE_EXIT);
}

void Solskj�r::setState(int state)
{
	this->state = state;
}

void Solskj�r::loadResources()
{
	CTextures * textures = CTextures::getInstance();
	if (!textures->getTexture(SOLSKJ�R_ID_TEXTURE))
		textures->add(SOLSKJ�R_ID_TEXTURE, L"Resource\\Textures\\subboss.png", 0, 0, D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::getInstance();
	CAnimations * animations = CAnimations::getInstance();

	LPANIMATION ani;
	// init
	sprites->addSprite(20001, SOLSKJ�R_ID_TEXTURE, 11, 189, 32, 23);
	sprites->addSprite(20002, SOLSKJ�R_ID_TEXTURE, 46, 189, 32, 23);
	sprites->addSprite(20003, SOLSKJ�R_ID_TEXTURE, 81, 189, 32, 23);
	sprites->addSprite(20004, SOLSKJ�R_ID_TEXTURE, 116, 189, 32, 23);
	sprites->addSprite(20005, SOLSKJ�R_ID_TEXTURE, 151, 189, 32, 23);
	sprites->addSprite(20006, SOLSKJ�R_ID_TEXTURE, 186, 189, 32, 23);
	sprites->addSprite(20007, SOLSKJ�R_ID_TEXTURE, 221, 189, 32, 23);
	sprites->addSprite(20008, SOLSKJ�R_ID_TEXTURE, 255, 189, 32, 23);
	sprites->addSprite(20009, SOLSKJ�R_ID_TEXTURE, 289, 189, 32, 23);
	sprites->addSprite(20010, SOLSKJ�R_ID_TEXTURE, 323, 189, 32, 23);

	ani = new CAnimation(100);
	ani->add(20001);
	ani->add(20002);
	ani->add(20003);
	ani->add(20004);
	ani->add(20005);
	ani->add(20006);
	ani->add(20007);
	ani->add(20008);
	ani->add(20009);
	ani->add(20010);
	animations->add(SOLSKJ�R_STATE_INIT, ani);

	// ready shot
	sprites->addSprite(20011, SOLSKJ�R_ID_TEXTURE, 21, 221, 32, 25);
	sprites->addSprite(20012, SOLSKJ�R_ID_TEXTURE, 55, 221, 32, 25);
	sprites->addSprite(20013, SOLSKJ�R_ID_TEXTURE, 89, 221, 32, 25);
	sprites->addSprite(20014, SOLSKJ�R_ID_TEXTURE, 123, 221, 32, 25);

	ani = new CAnimation(200);
	ani->add(20011);
	ani->add(20012);
	ani->add(20013);
	ani->add(20014);
	animations->add(SOLSKJ�R_STATE_READY_SHOT, ani);

	// shot
	sprites->addSprite(20021, SOLSKJ�R_ID_TEXTURE, 157, 221, 32, 30);
	sprites->addSprite(20022, SOLSKJ�R_ID_TEXTURE, 191, 221, 32, 30);
	sprites->addSprite(20023, SOLSKJ�R_ID_TEXTURE, 225, 221, 32, 30);
	sprites->addSprite(20024, SOLSKJ�R_ID_TEXTURE, 259, 221, 32, 30);
	sprites->addSprite(20025, SOLSKJ�R_ID_TEXTURE, 293, 221, 32, 30);

	ani = new CAnimation(200);
	ani->add(20021);
	ani->add(20022);
	ani->add(20023);
	ani->add(20024);
	ani->add(20025);
	animations->add(SOLSKJ�R_STATE_SHOT, ani);

	// exit
	sprites->addSprite(20031, SOLSKJ�R_ID_TEXTURE, 123, 221, 32, 25);
	sprites->addSprite(20032, SOLSKJ�R_ID_TEXTURE, 89, 221, 32, 25);
	sprites->addSprite(20033, SOLSKJ�R_ID_TEXTURE, 55, 221, 32, 25);
	sprites->addSprite(20034, SOLSKJ�R_ID_TEXTURE, 21, 221, 32, 25);
	sprites->addSprite(20035, SOLSKJ�R_ID_TEXTURE, 323, 189, 32, 25);
	sprites->addSprite(20036, SOLSKJ�R_ID_TEXTURE, 289, 189, 32, 25);
	sprites->addSprite(20037, SOLSKJ�R_ID_TEXTURE, 255, 189, 32, 25);
	sprites->addSprite(20038, SOLSKJ�R_ID_TEXTURE, 221, 189, 32, 25);
	sprites->addSprite(20039, SOLSKJ�R_ID_TEXTURE, 186, 189, 32, 25);
	sprites->addSprite(20040, SOLSKJ�R_ID_TEXTURE, 151, 189, 32, 25);

	ani = new CAnimation(100);
	ani->add(20031);
	ani->add(20032);
	ani->add(20033);
	ani->add(20034);
	ani->add(20035);
	ani->add(20036);
	ani->add(20037);
	ani->add(20038);
	ani->add(20039);
	ani->add(20040);
	animations->add(SOLSKJ�R_STATE_EXIT, ani);

	// die
	sprites->addSprite(20041, SOLSKJ�R_ID_TEXTURE, 11, 189, 32, 6);
	sprites->addSprite(20042, SOLSKJ�R_ID_TEXTURE, 13, 168, 8, 10);
	sprites->addSprite(20043, SOLSKJ�R_ID_TEXTURE, 35, 166, 26, 10);

	for (int i = 0; i < 3; i++)
	{
		ani = new CAnimation(100);
		ani->add(20041 + i);
		animations->add(SOLSKJ�R_STATE_DIE + i, ani);
		this->addAnimation(SOLSKJ�R_STATE_DIE + i);
	}

	this->addAnimation(SOLSKJ�R_STATE_INIT);
	this->addAnimation(SOLSKJ�R_STATE_READY_SHOT);
	this->addAnimation(SOLSKJ�R_STATE_SHOT);
	this->addAnimation(SOLSKJ�R_STATE_EXIT);
}

void Solskj�r::createBullet()
{
	Solskj�rBullet* bullet = new Solskj�rBullet(x + 7, y + 18);
	_weapons.emplace_back(bullet);
}

void Solskj�r::createCloneBullet()
{
	int size = _weapons.size();
	for (int i = 0; i < size; ++i) {
		auto bullet = dynamic_cast<Solskj�rBullet*>(_weapons[i]);
		if (bullet && !bullet->getIsClone() && bullet->getIsCreateClone()) {
			bullet->setIsClone(true);

			Solskj�rBullet* cloneBullet = new Solskj�rBullet(bullet->x, bullet->y);
			cloneBullet->setIsClone(true);
			_weapons.emplace_back(cloneBullet);
		}
	}
}
