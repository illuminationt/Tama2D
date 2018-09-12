#include "Image.h"
#include"Root.h"

namespace {
	const float corr = 1.f / 496.f;
}

Image::Image(
	const char* filename,
	int colNum,
	int rowNum,
	int startFrame,
	int endFrame,
	int frameDelay) :
	m_graphics(0),
	m_texture(0),
	m_colNumber(colNum),
	m_rowNumber(rowNum),
	m_startFrame(startFrame),
	m_endFrame(endFrame),
	m_currentFrame(startFrame),
	m_frameDelay(frameDelay),
	m_animTimer(0),
	m_loop(true),
	m_animComplete(false),
	m_flipX(false) {

	m_graphics = Root::graphics();
	m_graphics->loadTexture(filename, m_texture);

}


Image::~Image(){
	SAFE_RELEASE(m_texture);
}

void Image::draw(float* p,int width,int height) {
	
	if (m_endFrame - m_startFrame > 0) {//アニメがあるなら
		m_animTimer++;
		if (m_animTimer > m_frameDelay) {
			m_animTimer = 0;
			m_currentFrame++;
			if (m_currentFrame<m_startFrame || m_currentFrame>m_endFrame) {
				if (m_loop) {
					m_currentFrame = m_startFrame;
				}
				else {
					m_currentFrame = m_endFrame;
					m_animComplete = true;
				}
			}
		}
	}
	double rcpColNum = 1.0 / (double)m_colNumber;
	double rcpRowNum = 1.0 / (double)m_rowNumber;
	double u = m_currentFrame % m_colNumber;
	double v = m_currentFrame / m_colNumber;

	float p2[2] = { p[0] + width,p[1] };
	float p3[2] = { p[0],p[1] + height };
	float p4[2] = { p[0] + width,p[1] + height };
	
	//X反転するかチェック
	if (!m_flipX) {
		float uv[4][2] = {
			{u*rcpColNum+corr,v*rcpRowNum+corr},
			{(u + 1.f)*rcpColNum-corr,v *rcpRowNum +corr},
			{u *rcpColNum+corr,(v + 1.f)*rcpRowNum-corr},
			{(u + 1.f) *rcpColNum-corr,(v + 1.f) *rcpRowNum-corr },
		};
		m_graphics->draw(p, p2, p3, uv[0], uv[1], uv[2]);
		m_graphics->draw(p2, p4, p3, uv[1], uv[3], uv[2]);
		return;
	}
	else {
		float uv[4][2] = {
			{ (u+1.f) *rcpColNum,v *rcpRowNum },
			{ u *rcpColNum,v *rcpRowNum },
			{ (u+1.f) *rcpColNum,(v + 1.f) *rcpRowNum },
			{ u *rcpColNum,(v + 1.f) *rcpRowNum },
		};
		m_graphics->draw(p, p2, p3, uv[0], uv[1], uv[2]);
		m_graphics->draw(p2, p4, p3, uv[1], uv[3], uv[2]);
	}
}

void Image::draw(float x, float y, int width, int height) {
	float p[2] = { x,y };
	draw(p, width, height);
}


void Image::setTexture() const{
	m_graphics->setTexture(m_texture);
}

void Image::reInitialize(
	int colNumber,
	int rowNumber,
	int startFrame,
	int endFrame,
	int frameDelay) {
	m_colNumber = colNumber;
	m_rowNumber = rowNumber;
	m_startFrame = startFrame;
	m_endFrame = endFrame;
	m_currentFrame = startFrame;
	m_frameDelay = frameDelay;
}
void Image::setFrameDelay(int frameDelay) {
	m_frameDelay = frameDelay;
}
void Image::setCurrentFrame(int currentFrame) {
	if (m_startFrame <= currentFrame&&currentFrame <= m_endFrame) {
		m_currentFrame = currentFrame;
	}
	else {
		WARN("Range error in Image::setCurrentFrame()");
	}
}

void Image::setFlipX(bool flipX) {
	m_flipX = flipX;
}