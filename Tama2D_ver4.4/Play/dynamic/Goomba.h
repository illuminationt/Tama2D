#ifndef GOOMBA_H
#define GOOMBA_H
#include"Play/DynamicObject.h"

class Goomba:public DynamicObject
{
public:
	Goomba();
	virtual ~Goomba();



	virtual void getMove(Vector2* moveOut);
	void die();
private:
	int m_deathCount;
	static const float m_gravity;
	static const float m_speedX;
	static const int m_remainTimeAfterDeath;
};



#endif