#include "Background.h"



Background::Background(int csvNumber):StaticObject(){
	m_colNumber = 31;
	m_rowNumber = 31;
	m_startFrame = csvNumber;
	m_endFrame = csvNumber;
	m_currentFrame = csvNumber;
	m_frameDelay = 0;

	
	m_rect.setPosition(0.f, 0.f);
	m_rect.setSize(0.f, 0.f);

	m_tag = TAG_BACKGROUND;
}


Background::~Background()
{
}
