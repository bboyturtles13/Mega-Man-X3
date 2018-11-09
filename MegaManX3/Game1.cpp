#include "Game1.h"


void Game1::initGolbals()
{
	texturesGlobal = CTextures::getInstance();
	spritesGlobal = CSprites::getInstance();
	animationsGlobal = CAnimations::getInstance();
	cameraGlobal = new Camera(0, 700, 1024, 2048);
	viewPortGlobal = &cameraGlobal->viewport;
	
}

void Game1::loadResource()
{

}

void Game1::initOption()
{
	
}

void Game1::update(DWORD dt)
{
	//keyGlobal->processKeyboard();


}	

void Game1::render(DWORD dt)
{

}


Game1::~Game1()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
	spriteHandler = 0;
	backBuffer = 0;
	d3ddv = 0;
	d3d = 0;
}
