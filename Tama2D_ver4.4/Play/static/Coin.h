#ifndef COIN_H
#define COIN_H

#include"Play/StaticObject.h"

class Coin :public StaticObject {
public:
	Coin();
	virtual ~Coin();

	virtual void update(const Vector2& playerMove, const Vector2& playerPos);

private:
	int m_coinCount;
};

#endif

