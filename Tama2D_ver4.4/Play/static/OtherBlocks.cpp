#include "OtherBlocks.h"



OtherBlocks::OtherBlocks(int csvNumber):StaticObject(){
	m_colNumber = 31;
	m_rowNumber = 31;
	m_startFrame = csvNumber;
	m_endFrame = csvNumber;
	m_currentFrame = csvNumber;
	m_frameDelay = 0;

	m_rect.setOffset(0.f, 0.f);
	m_rect.setSizeRate(1.f, 1.f);

	m_rect.setPosition(m_position);
	m_rect.setSize(m_size);

	m_tag = TAG_OTHER_BLOCKS;
}


OtherBlocks::~OtherBlocks()
{
}
