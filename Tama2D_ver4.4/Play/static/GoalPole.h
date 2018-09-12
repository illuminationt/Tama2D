#ifndef GOALPOLE_H
#define GOALPOLE_H

#include"Play/StaticObject.h"

class GoalPole:public StaticObject{
public:
	GoalPole(int csvNumber);
	virtual ~GoalPole();

	//virtual void update(const Vector2& playerMove, const Vector2& playerPos);


};

#endif
