#include "Play/StaticObject.h"
#include"Space/Vector2.h"
#include"Image.h"
#include"Rect.h"



StaticObject::StaticObject() :
	m_image(0),
	m_position(0.f, 0.f),
	m_size(0.f, 0.f),
	m_velocity(0.f,0.f),
	m_colNumber(0),
	m_rowNumber(0),
	m_startFrame(0),
	m_endFrame(0),
	m_currentFrame(0),
	m_frameDelay(0),
	m_needCheckCollision(true),
	m_isKilled(false),
	m_isActive(true) ,
	m_hittedDir(0.f,0.f),
	m_index(-1){

	m_rect.setSizeRate(1.f, 1.f);
	m_rect.setOffset(0.f, 0.f);
	m_rect.setPosition(m_position);
	m_rect.setSize(m_size);
	
}

StaticObject::~StaticObject(){
	DELETE(m_image);
}

void StaticObject::initialize(
	const char* filename,
	int colNumber,
	int rowNumber,
	int startFrame,
	int endFrame,
	int currentFrame,
	int frameDelay,
	float drawPosX,
	float drawPosY,
	float width,
	float height,
	float offsetX,
	float offsetY,
	float sizeRateX,
	float sizeRateY,
	Tag tag) {
	m_image = new Image(filename, colNumber, rowNumber, startFrame,endFrame, frameDelay);
	m_position.set(drawPosX, drawPosY);
	m_size.set(width, height);

	m_tag = tag;

	m_rect.setSizeRate(sizeRateX, sizeRateY);
	m_rect.setOffset(offsetX, offsetY);
	m_rect.setPosition(m_position);
	m_rect.setSize(m_size);
}

void StaticObject::setTexture()const {
	m_image->setTexture();
}

void StaticObject::draw() {
	if (this->m_isActive) {
		m_image->draw(&m_position.x, m_size.x, m_size.y);
	}
}

void StaticObject::update(const Vector2& playerMove,const Vector2& playerPos) {
	m_position.x -= playerMove.x;
	m_rect.setPosition(m_position);

	setCheckCollision();
}

void StaticObject::kill() {
	m_isKilled = true;
}

//TODO: ‰ü‘P‚Ì—]’n—L‚è
void StaticObject::setCheckCollision() {
	if (0< m_position.x&&m_position.x < WINDOW_WIDTH/2) {
		m_needCheckCollision = true;
	}
	else {
		m_needCheckCollision = false;
	}
}

bool StaticObject::needCheckCollision() {
	return m_needCheckCollision;
}
bool StaticObject::isActive()const {
	return m_isActive;
}
bool StaticObject::isKilled()const {
	return m_isKilled;
}

const Rect* StaticObject::rect()const {
	return &m_rect;
}
void StaticObject::setRectOffset(float x, float y) {
	m_rect.setOffset(x, y);
}
void StaticObject::setRectSizeRate(float x, float y) {
	m_rect.setSizeRate(x, y);
}


const Vector2* StaticObject::position()const {
	return &m_position;
}
const Vector2* StaticObject::size()const {
	return &m_size;
}
const Vector2* StaticObject::velocity()const {
	return &m_velocity;
}
const Vector2* StaticObject::prevMove()const {
	return &m_prevMove;
}


const StaticObject::Tag StaticObject::tag()const {
	return m_tag;
}
void StaticObject::setTag(Tag tag) {
	m_tag = tag;
}


int StaticObject::colNumber()const { return m_colNumber; };
int StaticObject::rowNumber()const { return m_rowNumber; };
int StaticObject::startFrame()const { return m_startFrame; };
int StaticObject::endFrame()const { return m_endFrame; };
int StaticObject::currentFrame()const { return m_currentFrame; };
int StaticObject::frameDelay()const { return m_frameDelay; };

void StaticObject::setHittedDir(const Vector2& dir) {
	m_hittedDir = dir;
}
int StaticObject::index()const {
	return m_index;
}
void StaticObject::setIndex(int j) {
	m_index = j;
}