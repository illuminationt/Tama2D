#include "Hatena.h"
#include"Image.h"


Hatena::Hatena():StaticObject(),m_hatenaCount(0){
	m_colNumber = 31;
	m_rowNumber = 31;
	m_startFrame = 9;
	m_endFrame = 9+2;
	m_currentFrame = 9;
	m_frameDelay = 10;

	m_rect.setOffset(0.f, 0.f);
	m_rect.setSizeRate(1.f, 1.f);
	
	m_rect.setPosition(m_position);
	m_rect.setSize(m_size);

	m_tag = TAG_HATENA;
}


Hatena::~Hatena()
{
}


void Hatena::update(const Vector2& playerMove, const Vector2& playerPos) {
	StaticObject::update(playerMove, playerPos);

	if (!m_isActive) {
		return;
	}

	if (m_isKilled) {
		m_position.set(-1.f, -1.f);
		m_rect.setSize(0.f, 0.f);
		m_isActive = false;
	}

	if (m_hatenaCount == 0) {
		m_image->setCurrentFrame(9);
	}
	else if (m_hatenaCount == 40) {
		m_image->setCurrentFrame(9+ 1);
	}
	else if (m_hatenaCount == 50) {
		m_image->setCurrentFrame(9 + 2);
	}
	else if (m_hatenaCount == 60) {
		m_image->setCurrentFrame(9+ 1);
	}
	else if (m_hatenaCount == 70) {
		m_hatenaCount = 0;
		return;
	}
	m_hatenaCount++;
}
