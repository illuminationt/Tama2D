#include "Goomba.h"
#include"Space/Vector2.h"
#include"Constants.h"
#include"Image.h"
const float Goomba::m_gravity = 0.4f;
const float Goomba::m_speedX = 1.f;
const int Goomba::m_remainTimeAfterDeath = 30;
Goomba::Goomba() :
	DynamicObject(),
	m_deathCount(0){
	m_colNumber = 18;
	m_rowNumber = 15;
	m_startFrame = 0;
	m_endFrame = 1;
	m_currentFrame = 0;
	m_frameDelay = 10;
	
	m_rect.setSizeRate(0.4f, 0.8f);
	m_rect.setOffset(HOR_MIN_UNIT*0.3f, VER_MIN_UNIT*0.1f);
	m_rect.setPosition(m_position);
	m_rect.setSize(m_size);
	m_modeX = MODEX_RIGHT;

	m_tag = TAG_OTHER_ENEMY;
}


Goomba::~Goomba(){
}

//getMoveÇÕñàÉtÉåÅ[ÉÄÅAkillledÇ≈Ç†ÇÎÇ§Ç™!isActiveÇ≈Ç†ÇÎÇ§Ç™ÇÊÇŒÇÍÇÈ

void Goomba::getMove(Vector2* moveOut) {
	if (!m_isActive) {
		return;
	}
	if (m_isKilled) {
		die();
	}
	if (m_position.x<(-WINDOW_WIDTH / 16) || m_position.x>WINDOW_WIDTH) {
		*moveOut = Vector2(0.f, 0.f);
		return;
	}
	switch (m_modeX) {
	case MODEX_LEFT:
		m_velocity.x = -m_speedX;
		if (m_prevMove.x == 0.f) {
			m_modeX = MODEX_STOP_FROM_LEFT;
		}
		break;
	case MODEX_RIGHT:
		m_velocity.x = m_speedX;
		if (m_prevMove.x == 0.f) {
			m_modeX = MODEX_STOP_FROM_RIGHT;
		}
		break;
	case MODEX_STOP_FROM_LEFT:
		m_velocity.x = m_speedX;
		m_modeX = MODEX_RIGHT;
		break;
	case MODEX_STOP_FROM_RIGHT:
		m_velocity.x = -m_speedX;
		m_modeX = MODEX_LEFT;
		break;
	}
	
	switch (m_modeY) {
	case MODEY_FALL:
		m_velocity.y += m_gravity;
		if (m_prevMove.y == 0.f) {
			m_velocity.y = 0.f;
			m_modeY = MODEY_ON_LAND;
		}
		break;
	case MODEY_ON_LAND:
		m_velocity.y = m_gravity;
		if (m_prevMove.y != 0.f) {
			m_modeY = MODEY_FALL;
		}
		break;
	}
	
	*moveOut = m_velocity;
}


void Goomba::die() {
	if (m_deathCount == 0) {
		m_image->reInitialize(18, 30, 20, 20, 0);
		m_position.set(m_position.x, m_position.y + m_size.y / 2);
		m_size.set(m_size.x, m_size.y / 2);
	}
	else if (m_deathCount > m_remainTimeAfterDeath) {
		m_position.set(-1.f, -1.f);
		m_rect.setSize(0.f, 0.f);
		m_isActive = false;
	}
	m_deathCount++;
}