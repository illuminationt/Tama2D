#include "Play/static/GoalPole.h"
#include"Constants.h"


GoalPole::GoalPole(int csvNumber):StaticObject(){
	m_colNumber = 31;
	m_rowNumber = 31;
	m_startFrame = csvNumber;
	m_endFrame = csvNumber;
	m_currentFrame = csvNumber;
	m_frameDelay = 0;

	m_rect.setOffset(HOR_MIN_UNIT*0.4f, 0.f);
	m_rect.setSizeRate(0.2f, 1.f);

	m_rect.setPosition(m_position);
	m_rect.setSize(m_size);

	m_tag = TAG_GOALPOLE;
}


GoalPole::~GoalPole()
{
}
