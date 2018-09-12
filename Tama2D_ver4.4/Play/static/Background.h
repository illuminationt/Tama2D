#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Play/StaticObject.h"

class Background :public StaticObject
{
public:
	Background(int CSVNumber);
	virtual ~Background();
};


#endif