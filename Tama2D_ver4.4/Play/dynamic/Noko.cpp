#include "Play/dynamic/Noko.h"
#include"Constants.h"
#include"Image.h"

#include<sstream>

const float Noko::m_gravity = 0.1f;
const float Noko::m_speedX = 2.f;
const float Noko::m_shellSpeedX = 9.f;
const float Noko::m_maxShellSpeedX = 10.f;
const int Noko::m_inStaticShellTime = 300;
const int Noko::m_inDynamicShellTime = 500;
Noko::Noko():
	DynamicObject(),
	m_modeX(MODEX_WALK_STOP_FROM_RIGHT),
	m_shellCount(0){
	m_colNumber = 18;
	m_rowNumber = 10;
	m_startFrame = 6;
	m_endFrame = 7;
	m_currentFrame = 6;
	m_frameDelay = 10;

	m_rect.setSizeRate(1.f, 1.f);
	m_rect.setOffset(0.f, 0.f);
	m_rect.setPosition(m_position);
	m_rect.setSize(m_size);


	m_tag = TAG_NOKO;
}


Noko::~Noko()
{
}

void Noko::getMove(Vector2* moveOut) {
	if (!m_isActive) {
		return;
	}

	if (m_position.x<(-WINDOW_WIDTH / 16) || m_position.x>WINDOW_WIDTH) {
		*moveOut = Vector2(0.f, 0.f);
		return;
	}
	
	switch (m_modeX) {
	case MODEX_WALK_LEFT:
		m_velocity.x = -m_speedX;
		if (m_prevMove.x == 0.f) {
			m_modeX = MODEX_WALK_STOP_FROM_LEFT;
		}
		if (m_isKilled) {
			m_isKilled = false;
			intoShell();			
			m_modeX = MODEX_SHELL_STOP;
		}
		break;
	case MODEX_WALK_RIGHT:
		m_velocity.x = m_speedX;
		if (m_prevMove.x == 0.f) {
			m_modeX = MODEX_WALK_STOP_FROM_RIGHT;
		}
		if (m_isKilled) {
			intoShell();
			m_modeX = MODEX_SHELL_STOP;
			m_isKilled = false;
		}
		break;
	case MODEX_WALK_STOP_FROM_LEFT:
		m_velocity.x = m_speedX;
		m_modeX = MODEX_WALK_RIGHT;
		m_image->setFlipX(true);
		break;
	case MODEX_WALK_STOP_FROM_RIGHT:
		m_velocity.x = -m_speedX;
		m_modeX = MODEX_WALK_LEFT;
		m_image->setFlipX(false);
		break;
	case MODEX_SHELL_STOP:
		m_velocity.x = 0.f;
		if (m_isKilled) {
			m_shellCount = 0;
			m_isKilled = false;
			if (m_hittedDir.x >= 0.f) {
				m_velocity.x = m_shellSpeedX;
				m_modeX = MODEX_SHELL_RIGHT;
				break;
			}
			else {
				m_velocity.x = -m_shellSpeedX;
				m_modeX = MODEX_SHELL_LEFT;
				break;
			}
		}
		m_shellCount++;
		if (m_shellCount==m_inStaticShellTime) {
			m_image->reInitialize(18, 15, 144, 145, 40);
		}
		else if (m_shellCount > m_inDynamicShellTime) {
			outofShell();
			m_modeX = MODEX_WALK_LEFT;
			m_shellCount = 0;
		}
		break;
	case MODEX_SHELL_LEFT:
		if (m_prevMove.x == 0.f) {
			m_velocity.x = -m_maxShellSpeedX;
			m_modeX = MODEX_SHELL_RIGHT;
		}
		if (m_isKilled) {
			m_isKilled = false;
			m_modeX = MODEX_SHELL_STOP;
		}
		break;
	case MODEX_SHELL_RIGHT:
		if (m_prevMove.x == 0.f) {
			m_velocity.x = m_maxShellSpeedX;
			m_modeX = MODEX_SHELL_LEFT;
		}
		if (m_isKilled) {
			m_isKilled = false;
			m_modeX = MODEX_SHELL_STOP;
		}
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
	TextDX* t = Root::text();
	/*
	std::ostringstream oss;
	oss << "Noko::m_modeX = " << m_modeX;
	t->print(oss.str().c_str(), 100, 400);
	*/
	*moveOut = m_velocity;
}

void Noko::intoShell() {
	m_image->reInitialize(18, 15, 144, 144, 0);
	m_position.set(m_position.x, m_position.y+m_size.y*0.3f);//è≠ÇµçÇÇﬂ
	m_size.set(HOR_MIN_UNIT, VER_MIN_UNIT);

	m_rect.setSizeRate(0.9f, 0.9f);
	m_rect.setOffset(m_size*0.05f);
	m_rect.setPosition(m_position);
	m_rect.setSize(m_size);
	
	
}
void Noko::outofShell() {
	m_image->reInitialize(18, 10, 6, 7, 10);
	m_position.set(m_position.x, m_position.y-VER_MIN_UNIT*0.6f);//è≠ÇµçÇÇﬂ
	m_size.set(HOR_MIN_UNIT, VER_MIN_UNIT*1.5f);
	m_rect.setPosition(m_position);
	m_rect.setSize(m_size);
}