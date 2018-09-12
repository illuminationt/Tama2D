#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include"Space/Vector2.h"
#include"Play/StaticObject.h"
class Rect;

class DynamicObject:public StaticObject{
public:
	DynamicObject();
	virtual ~DynamicObject();

	

	//動く予定をゲット。このmoveOutをRectangle::restrictMoveに入れる
	virtual void getMove(Vector2* moveOut);
	virtual void movePosition(const Vector2&);
	virtual void movePosition(float, float);
	virtual void flipDirection();
	enum ModeX {
		MODEX_LEFT,
		MODEX_RIGHT,
		MODEX_STOP_FROM_LEFT,
		MODEX_STOP_FROM_RIGHT,
		MODEX_OTHERS,//その他諸々
	};
	enum ModeY {
		MODEY_FALL,
		MODEY_ON_LAND,
	};
	
	
protected:
	
	
	ModeX m_modeX;
	ModeY m_modeY;

	
};


#endif