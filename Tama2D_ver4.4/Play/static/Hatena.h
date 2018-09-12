#ifndef HATENA_H
#define HATENA_H
#include"Play/StaticObject.h"


class Hatena:public StaticObject{
public:
	Hatena();
	virtual ~Hatena();

	virtual void update(const Vector2& playerMove, const Vector2& playerPos);

private:
	int m_hatenaCount;
};


#endif