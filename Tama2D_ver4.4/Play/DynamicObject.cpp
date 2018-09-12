#include "Play/DynamicObject.h"
#include"Constants.h"
#include"Image.h"

DynamicObject::DynamicObject():
	StaticObject(),
	m_modeX(MODEX_LEFT),
	m_modeY(MODEY_ON_LAND){
}


DynamicObject::~DynamicObject()
{
}




void DynamicObject::getMove(Vector2* moveOut) {
	//”ÍˆÍŠO‚È‚ç“®‚©‚È‚¢
	Vector2 move(0.f, 0.f);
	if (m_position.x<(-WINDOW_WIDTH/16) || m_position.x>WINDOW_WIDTH) {
		*moveOut = move;
		return;
	}
	*moveOut = move;
}

void DynamicObject::movePosition(const Vector2& moveVector) {
	m_position += moveVector;
	m_rect.setPosition(m_position);
	m_prevMove = moveVector;
}
void DynamicObject::movePosition(float x, float y) {
	Vector2 t(x, y);
	movePosition(t);
}


void DynamicObject::flipDirection() {
	if (m_modeX == MODEX_LEFT) {
		m_modeX = MODEX_RIGHT;
	}
	else if (m_modeX == MODEX_RIGHT) {
		m_modeX = MODEX_LEFT;
	}
}