#include "Play/State.h"
#include"Constants.h"
#include"Play/Player.h"
#include"Play/Stage.h"
#include"Play/DynamicObject.h"
#include"Rect.h"
#include<sstream>

State::State(int stageID):
	m_player(0),
	m_stage(0){
	m_player = new Player();
	
	std::ostringstream oss;
	oss << "resource/csv/stage" << stageID << "_map.csv";
	std::ostringstream oss2;
	oss2 << "resource/csv/stage" << stageID << "_enemy.csv";
	m_stage = new Stage(oss.str().c_str(),oss2.str().c_str());
}


State::~State(){
	DELETE(m_stage);
	DELETE(m_player);
}

void State::update() {
	
	Vector2 playerMove(0.f, 0.f);
	Vector2* enemyMove = new Vector2[m_stage->dObjectNumber()];

	//入力処理
	getMove(&playerMove, enemyMove);

	if (m_player->cond() == Player::COND_ALIVE||m_player->cond()==Player::COND_GOAL) {
		//あたり判定処理(プレイヤーと地形）
		for (int j = 0; j < m_stage->sObjectNumber(); j++) {
			if (m_stage->needCheckColWithPlayer(j)) {
				if (m_stage->sObject(j)->isActive()) {
					m_player->processCollision(&playerMove, *m_stage->sObject(j));
				}
			}
		}
	
		
		//あたり判定処理（敵と地形）
		for (int j = 0; j < m_stage->dObjectNumber(); j++) {
			if (m_stage->dObject(j)->isActive()) {
				const Rect* d = m_stage->dObject(j)->rect();
				for (int k = 0; k < m_stage->sObjectNumber(); k++) {
					if (m_stage->sObject(k)->tag() != StaticObject::TAG_BACKGROUND&&
						m_stage->sObject(k)->tag()!=StaticObject::TAG_COIN) {
						const Rect* s = m_stage->rect(k);
						d->restrictMove(&enemyMove[j], *s, *m_stage->dObject(j)->prevMove());
					}
				}
			}
		}
		
		//あたり判定処理（プレイヤーと敵）
		for (int j = 0; j < m_stage->dObjectNumber(); j++) {
			if (!m_stage->dObject(j)->isKilled()) {
				m_player->processCollision(&playerMove, *m_stage->dObject(j));
			}
		}
		
		//あたり判定（敵と敵）
		for (int j = 0; j < m_stage->dObjectNumber() - 1; j++) {
			if (m_stage->dObject(j)->isActive()) {
				const Rect* d1 = m_stage->dObject(j)->rect();
				for (int k = j + 1; k < m_stage->dObjectNumber(); k++) {
					if (m_stage->dObject(j)->isActive()) {
						const Rect* d2 = m_stage->dObject(k)->rect();
						d1->restrictMove(&enemyMove[j], *d2);
						//m_stage->dObject(j)->flipDirection();
						//m_stage->dObject(k)->flipDirection();

					}
				}
			}
		}
		

		//更新
		m_stage->update(playerMove, *m_player->position(), enemyMove);
	}//if(m_player->cond()==COND_ALIVE)
	//ALIVE以外はステージの更新とか衝突処理とかしない（プレイヤーの更新はする）。描画のみする
	m_player->update(playerMove);


	//各々描画
	m_stage->setStaticTexture();
	m_stage->drawStatic();
	m_stage->setDynamicTexture();
	m_stage->drawDynamic();

	m_player->setTexture();
	m_player->draw();

	DELETE_ARRAY(enemyMove);
}

void State::getMove(Vector2* playerMoveOut, Vector2* enemyMoveOut)const {
	m_player->getMove(playerMoveOut);

	for (int j = 0; j < m_stage->dObjectNumber(); j++) {
		m_stage->dObject(j)->getMove(&enemyMoveOut[j]);
	}
}

const Player::Condition State::cond()const {
	return m_player->cond();
}