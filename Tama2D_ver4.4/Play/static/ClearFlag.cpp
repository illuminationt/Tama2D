#include "ClearFlag.h"



ClearFlag::ClearFlag(int csvNumber):StaticObject(){
	m_colNumber = 31;
	m_rowNumber = 31;
	m_startFrame = csvNumber-1000;
	m_endFrame = csvNumber-1000;
	m_currentFrame = csvNumber-1000;

	m_rect.setOffset(0.f, 0.f);
	m_rect.setSizeRate(1.f, 1.f);

	m_rect.setPosition(m_position);
	m_rect.setSize(m_size);

	m_tag = TAG_CLEAR_FLAG;
}


ClearFlag::~ClearFlag()
{
}
