#ifndef _StaticObject_H
#define _StaticObject_H

#include "GameObject.h"
#include "ConstGlobals.h"

class StaticObject 
	: public GameObject
{
protected:
	bool _canBreak = false;

public:
	int width;
	int height;
	StaticObject() {}
	~StaticObject() {}


	StaticObject(UINT id, float x, float y, int width, int height);
	
	virtual void render(DWORD dt, D3DCOLOR colorBrush) {}
	bool canBreak();
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
};

#endif // !_StaticObject_H
