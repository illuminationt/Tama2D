#include "Play/static/Coin.h"
#include"Image.h"


Coin::Coin() :StaticObject(), m_coinCount(0) {
	m_colNumber = 31;
	m_rowNumber = 31;
	m_startFrame = 40;
	m_endFrame = 40 + 2;
	m_currentFrame = 40;
	m_frameDelay = INT_MAX;

	m_rect.setOffset(0.f, 0.f);
	m_rect.setSizeRate(1.f, 1.f);

	m_rect.setPosition(m_position);
	m_rect.setSize(m_size);

	m_tag = TAG_COIN;
}


Coin::~Coin()
{
}

void Coin::update(const Vector2& playerMove, const Vector2& playerPos) {
	StaticObject::update(playerMove, playerPos);
	if (!m_isActive) {
		return;
	}

	if (m_isKilled) {
		m_position.set(-1.f, -1.f);
		m_rect.setSize(0.f, 0.f);
		m_isActive = false;
	}

	if (m_coinCount == 0) {
		m_image->setCurrentFrame(40);
	}
	else if (m_coinCount == 40) {
		m_image->setCurrentFrame(40 + 1);
	}
	else if (m_coinCount == 45) {
		m_image->setCurrentFrame(40 + 2);
	}
	else if (m_coinCount == 50) {
		m_image->setCurrentFrame(40 + 1);
	}
	else if (m_coinCount == 55) {
		m_coinCount = 0;
		return;
	}
	m_coinCount++;
}