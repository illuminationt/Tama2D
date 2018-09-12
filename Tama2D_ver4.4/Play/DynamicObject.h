#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include"Space/Vector2.h"
#include"Play/StaticObject.h"
class Rect;

class DynamicObject:public StaticObject{
public:
	DynamicObject();
	virtual ~DynamicObject();

	

	//�����\����Q�b�g�B����moveOut��Rectangle::restrictMove�ɓ����
	virtual void getMove(Vector2* moveOut);
	virtual void movePosition(const Vector2&);
	virtual void movePosition(float, float);
	virtual void flipDirection();
	enum ModeX {
		MODEX_LEFT,
		MODEX_RIGHT,
		MODEX_STOP_FROM_LEFT,
		MODEX_STOP_FROM_RIGHT,
		MODEX_OTHERS,//���̑����X
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