#include "Play/Player.h"
#include"Image.h"
#include"Constants.h"
#include"Space/Vector2.h"
#include"Play/StaticObject.h"
#include"Sequence/Game/Parent.h"
#include<sstream>
const float Player::m_gravity = 0.5f;
const float Player::m_maxSpeedX = 7.f;
const float Player::m_accelX = 0.4f;
const float Player::m_resistRate = 0.8f;
const float Player::m_turnAccelXRate = 5.4f;
const float Player::m_jumpForce = 10.f;
const float Player::m_jumpForceStumpEnemy = 4.f;
const float Player::m_jumpForceStumpEnemyWithButtonRate = 3.5f;
const float Player::m_jumpAccelForce = 1.f;
const int Player::m_jumpAccelTime = 10;
const int Player::m_minFrameDelay = 5;


Player::Player() :
	DynamicObject(),
	m_dyingCount(0),
	m_accelTimeCount(0),
	m_goalCount(0),
	m_easyGoalCount(0),
	m_modeX(MODEX_STOP),
	m_modeY(MODEY_JUMP_STAY),
	m_cond(COND_ALIVE),
	m_scoreRate(1){
	m_position = Vector2(200, 180);
	m_size = Vector2(HOR_MIN_UNIT*0.8f, VER_MIN_UNIT*0.8f);
	m_image = new Image(
		"resource/picture/mario.png",
		21,3,42,42,0);
	//setの順番大切！
	m_rect.setSizeRate(1.f, 1.f);
	m_rect.setOffset(0.f, 0.f);
	m_rect.setPosition(m_position);
	m_rect.setSize(m_size);
	
}


Player::~Player(){
	DELETE(m_image);
}



void Player::getMove(Vector2* moveOut) {
	Input* i = Root::input();
	if (m_cond == COND_IS_DYING) {
		
		isDying(moveOut);
		return;
	}
	else if (m_cond == COND_GOAL) {
		goal(moveOut);
		return;
	}
	else if (m_cond == COND_EASY_GOAL) {
		easyGoal(moveOut);
		return;
	}
	/*
	if (i->isKeyDown('Z')) {
		move.y += m_speedX;
	}
	if (i->isKeyDown('A')) {
		move.y -= m_speedX;
	}
	*/
	//=====================X方向==========================//
	switch (m_modeX) {
	case MODEX_LEFT:
		
		if (i->isKeyDown('L')) {
			m_velocity.x += m_accelX*m_turnAccelXRate;
		}else if (i->isKeyDown('J')) {
			m_velocity.x -= m_accelX;
			if (m_velocity.x < -m_maxSpeedX) {
				m_velocity.x = -m_maxSpeedX;
			}
		}
		else {
			m_velocity.x *= m_resistRate;
		}

		if (m_prevMove.x >= 0.f) {
			m_modeX = MODEX_STOP;
		}

		
		break;
	case MODEX_RIGHT:

		if (i->isKeyDown('L')) {
			m_velocity.x += m_accelX;
			if (m_velocity.x > m_maxSpeedX) {
				m_velocity.x = m_maxSpeedX;
			}
		}
		else if (i->isKeyDown('J')) {
			m_velocity.x -= m_accelX*m_turnAccelXRate;
		}
		else {
			m_velocity.x *= m_resistRate;
		}

		if (m_prevMove.x <= 0.f) {
			m_modeX = MODEX_STOP;
		}

		
		break;

	case MODEX_STOP:
		m_velocity.x = 0.f;
		if (i->isKeyDown('L')) {
			m_velocity.x += m_accelX;
			m_image->setFlipX(false);
			m_modeX = MODEX_RIGHT;
			break;
		}
		else if (i->isKeyDown('J')) {
			m_velocity.x -= m_accelX;
			m_image->setFlipX(true);
			m_modeX = MODEX_LEFT;
			break;
		}
		break;
	}
	if (abs(m_velocity.x)>m_accelX) {
		m_image->setFrameDelay(m_minFrameDelay * m_maxSpeedX*m_maxSpeedX / (m_velocity.x*m_velocity.x));
	}
	else {
		if (m_modeY == MODEY_ON_LAND) {
			m_image->setCurrentFrame(42);
		}
		m_image->setFrameDelay(INT_MAX);
	}
	//==================X方向終了=======================//
	
	

	switch (m_modeY) {
	case MODEY_JUMP_UP:
		m_velocity.y += m_gravity;
		if (m_prevMove.y == 0.f) {
			m_modeY = MODEY_JUMP_STAY;
		}
		else if (m_prevMove.y > 0.f) {
			m_modeY = MODEY_JUMP_DOWN;
		}

		break;
	case MODEY_JUMP_UP_ACCEL:
		if (i->isKeyDown('Z')&&(m_accelTimeCount<m_jumpAccelTime)) {
			m_accelTimeCount++;
			break;
		}
		if (m_accelTimeCount >= m_jumpAccelTime) {
			m_velocity.y -= m_jumpAccelForce;
		}
		m_modeY = MODEY_JUMP_UP;
		break;
	case MODEY_JUMP_STAY:
		m_velocity.y += m_gravity;
		if (m_prevMove.y > 0.f) {
			m_modeY = MODEY_JUMP_DOWN;
		}
		break;
	case MODEY_JUMP_DOWN:
		m_velocity.y += m_gravity;
		if (m_prevMove.y == 0.f) {
			m_velocity.y = 0.f;
			m_image->reInitialize(21, 3,42,45, 10);
			m_modeY = MODEY_ON_LAND;
		}
		if (m_prevMove.y < 0.f) {
			m_modeY = MODEY_JUMP_UP;
		}
		break;
	case MODEY_ON_LAND:
		m_velocity.y = m_gravity;
		m_scoreRate = 1;
		//ジャンプ
		if (i->wasKeyPressed('Z')) {
			m_velocity.y = -m_jumpForce;
			m_accelTimeCount = 0;
			m_image->reInitialize(21, 3, 47, 47, 0);
			Root::audio()->playCue("Jump");
			m_modeY = MODEY_JUMP_UP_ACCEL;
		}
		if (m_prevMove.y > 0.f) {
			m_modeY = MODEY_JUMP_DOWN;
		}
		break;
	}

	TextDX* t = Root::text();
	std::ostringstream oss;
	/*
	oss << "m_modeX = " << m_modeX;
	t->print(oss.str().c_str(), 0, 200);
	oss.str("");
	oss << "m_modeY = " << m_modeY;
	t->print(oss.str().c_str(), 0, 260);
	*/

	if (i->wasKeyPressed('1')) {
		m_cond = COND_ALIVE;
	}
	else if (i->wasKeyPressed('2')) {
		m_cond = COND_DEAD;
	}
	else if (i->wasKeyPressed('3')) {
		m_cond = COND_CLEAR;
	}


	*moveOut = m_velocity;
	
}

void Player::isDying(Vector2* moveOut) {
	if (m_dyingCount == 0) {
		Root::audio()->stopCue("Above Ground");
		Root::audio()->playCue("Die");
	}
	if (1 <= m_dyingCount&&m_dyingCount <= 30) {
		m_velocity.set(0.f, 0.f);
	}
	else if (m_dyingCount == 31) {
		m_image->reInitialize(21, 3, 48, 48, 0);
		m_velocity.y = -14.f;
	}
	else if(m_position.y<WINDOW_HEIGHT*5.f) {
		m_velocity.y += m_gravity;
	}
	else {
		m_cond = COND_DEAD;
	}
	*moveOut = m_velocity;
	m_dyingCount++;
}

void Player::goal(Vector2* moveOut) {
	if (m_goalCount == 0) {
		Root::audio()->stopCue("AboveGround");
		
		m_velocity.set(0.f, 0.f);
		m_image->reInitialize(21, 3, 50, 50, 0);
	}
	if (m_goalCount <= 30) {
		m_goalCount++;
		return;
	}
	if (m_position.y > VER_MIN_UNIT * 11) {
		Root::audio()->stopCue("Flagpole");
		m_goalCount++;
		if (m_goalCount == 60) {
			Root::audio()->playCue("LevelComplete");
			m_image->setFlipX(true);
			m_position.x += m_size.x/2;
			m_velocity.y = 0.f;
		}
		else if (m_goalCount == 120) {
			m_image->reInitialize(21, 3, 42, 45, 5);
			m_image->setFlipX(false);
		}
		else if (120<m_goalCount&&m_goalCount<210) {
			m_velocity.x = 3.f;
			m_velocity.y = 2.f;
			*moveOut = m_velocity;
		}
		else if (210<=m_goalCount&&m_goalCount<420) {
			this->m_isActive = false;
		}
		else if (m_goalCount == 420) {
			Root::audio()->stopCue("LevelComplete");
			m_cond = Player::COND_CLEAR;
		}


		return;
	}
	if (m_goalCount == 31) {
		Root::audio()->playCue("Flagpole");
		m_goalCount++;
	}
	if (m_goalCount >= 31) {//旗につかまり下がる
		
		m_velocity.y = 5.f;
		*moveOut = m_velocity;
	}
	

}

void Player::easyGoal(Vector2* moveOut) {
	if (m_easyGoalCount == 0) {
		Root::audio()->stopCue("AboveGround");
		Root::audio()->playCue("LevelComplete");
		moveOut->set(0.f, 0.f);
	}
	if (m_easyGoalCount > 300) {
		m_cond = COND_CLEAR;
	}

	m_easyGoalCount++;
}
void Player::processCollision(Vector2* moveOut, StaticObject& s) {
	switch (s.tag()) {
	case StaticObject::TAG_BRICK:
		break;

	case StaticObject::TAG_OTHER_BLOCKS:
	case StaticObject::TAG_HATENA:
		m_rect.restrictMove(moveOut, *s.rect(), m_prevMove);
		break;

	case StaticObject::TAG_COIN:
		if (m_rect.isIntersect(*s.rect())) {
			Root::audio()->playCue("Coin");
			addScore(200);
			s.kill();
		}
		break;
	case StaticObject::TAG_GOALPOLE:
		if (m_rect.isIntersect(*s.rect())) {
			m_cond = COND_GOAL;
		}
		break;
	case StaticObject::TAG_BACKGROUND:
		break;
	case StaticObject::TAG_CLEAR_FLAG:
		if(m_rect.isIntersect(*s.rect())) {
			m_cond = COND_EASY_GOAL;
		}
		break;
	case StaticObject::TAG_OTHER_ENEMY:
		if (m_rect.isIntersect(*s.rect())) {
			if (m_prevMove.y>0.f) {
				addScore(100);
				Root::audio()->playCue("Squish");
				s.kill();
				m_position.y -= m_size.y;//マジックナンバーごめんなさい
				m_velocity.y = -m_jumpForceStumpEnemy;
				if (Root::input()->isKeyDown('Z')) {
					m_velocity.y *= m_jumpForceStumpEnemyWithButtonRate;
				}
				break;
			}
			else {
				m_cond = COND_IS_DYING;
			}
		}
		break;
	case StaticObject::TAG_NOKO:
		if (m_rect.isIntersect(*s.rect())) {
			if (m_position.y<s.position()->y || m_prevMove.y>0.f) {
				addScore(100);
				Root::audio()->playCue("Squish");
				s.kill();
				m_position.y -= (s.position()->y - m_position.y);
				m_velocity.y = -m_jumpForceStumpEnemy;
				if (Root::input()->isKeyDown('Z')) {
					m_velocity.y *= m_jumpForceStumpEnemyWithButtonRate;
				}
				break;
			}else if (s.velocity()->x==0.f) {//inTheShellの状態
				Root::audio()->playCue("Squish");
				s.kill();
				//===========当たる方向チェック==========
				Vector2 dir;
				dir.setSub(*s.position(), m_position);
				s.setHittedDir(dir);
				//=====================================
	
				//m_position.x -= dir.x;
				break;
			}
			else if (6.f<abs(s.velocity()->x)&&abs(s.velocity()->x) < 9.8f){
				break;
			}
			else {
				m_cond = COND_IS_DYING;
			}
		}
		break;


	}
}
void Player::update(const Vector2& move) {
	m_position.y += move.y;
	m_rect.setPosition(m_position);

	m_prevMove = move;
}



const Player::Condition Player::cond()const {
	return m_cond;
}

void Player::addScore(int score) {
	Sequence::Game::Parent::addScore(score*m_scoreRate);
	m_scoreRate *= 2;
}

