#include "Play/Stage.h"
#include"Play/StaticObject.h"
#include"Play/DynamicObject.h"
#include"Constants.h"
#include"Space/Vector2.h"
#include"Play/dynamic/Goomba.h"
#include"Play/dynamic/Noko.h"
#include"Play/dynamic/Goomba.h"
#include"Play/dynamic/Noko.h"
#include"Play/static/Hatena.h"
#include"Play/static/Coin.h"
#include"Play/static/GoalPole.h"
#include"Play/static/ClearFlag.h"
#include"Play/static/OtherBlocks.h"
#include"Play/static/Background.h"

#include<sstream>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;

const int Stage::m_maxColNumberStatic = 31;//テクスチャ内の最大の列の数(スタティックオブジェクトの）
const int Stage::m_maxRowNumberStatic = 31;//テクスチャ内の最大の行の数(スタティックオブジェクトの）
const int Stage::m_maxColNumberDynamic = 18;//テクスチャ内の最大の列の数(ダイナミックオブジェクトの）
const int Stage::m_maxRowNumberDynamic = 15;//テクスチャ内の最大の行の数(ダイナミックオブジェクトの）

namespace {
	vector<string> split(string& input, char delimiter)
	{
		istringstream stream(input);
		string field;
		vector<string> result;
		while (getline(stream, field, delimiter)) {
			result.push_back(field);
		}
		return result;
	}
}


Stage::Stage(const char* CSVfilename,
	const char* CSVEnemyFilename) :
	m_sObjects(0),
	m_dObjects(0),
	m_indexStatic(0),
	m_indexDynamic(0),
	m_colNumber(0),
	m_rowNumber(0),
	m_gridNumber(0),
	m_sObjectNumber(0),
	m_dObjectNumber(0) {

	//まずfにCSVデータ格納。扱いやすくするためstringにコピー。
	ifstream ifs(CSVfilename);
	string str;
	int t = 0;
	int tRowNum = 0;
	//「j番目に何を描画するか」を司るm_indexに代入してく。
	while (getline(ifs, str)) {
		vector<string> strvec = split(str, ',');

		for (int i = 0; i < strvec.size(); i++) {
			m_indexStatic.push_back(stoi(strvec.at(i)));
		}
		tRowNum++;
	}
	//CSV読み取り完了。行、列の数を代入
	m_rowNumber = tRowNum;
	m_gridNumber = m_indexStatic.size();
	m_colNumber = m_gridNumber / m_rowNumber;
	//オブジェクトの描画には何番目のjが必要。
	//まず、sObjectが何個あるのか調べる。
	for (int j = 0; j < m_gridNumber; j++) {
		if (m_indexStatic[j] != -1) {
			m_sObjectNumber++;
		}
	}
	//続いてsObjectの数だけsObjectをnew
	m_sObjects = new StaticObject*[m_sObjectNumber];
	t = 0;
	for (int j = 0; j < m_gridNumber; j++) {
		if (m_indexStatic[j] != -1) {
			m_sObjects[t] = new StaticObject();
			m_sObjects[t]->setIndex(j);
			t++;
		}
	}
	//そして各々をinitialize
	for (int j = 0; j < m_sObjectNumber; j++) {
		int t = m_sObjects[j]->index();
		int s = m_indexStatic[m_sObjects[j]->index()];
		switch (m_indexStatic[m_sObjects[j]->index()]) {
			case 9:
				m_sObjects[j] = new Hatena();
				break;
			case 40:
				m_sObjects[j] = new Coin();
				break;
			case 201://ポールの頭
			case 232://ポール本体
				m_sObjects[j] = new GoalPole(s);
				break;
			default:
				
				if (310<=s&&s<=1000) {
					m_sObjects[j] = new Background(s);
				}
				else if (s >= 1000) {
					m_sObjects[j] = new ClearFlag(s);
				}
				else {
					m_sObjects[j] = new OtherBlocks(s);
				}
				break;
		}
		m_sObjects[j]->setIndex(t);

		m_sObjects[j]->initialize(
			"resource/picture/map.png",
			m_sObjects[j]->colNumber(),
			m_sObjects[j]->rowNumber(),
			m_sObjects[j]->startFrame(),
			m_sObjects[j]->endFrame(),
			m_sObjects[j]->currentFrame(),
			m_sObjects[j]->frameDelay(),
			(m_sObjects[j]->index() % m_colNumber)*(HOR_MIN_UNIT),
			(m_sObjects[j]->index() / m_colNumber)*(VER_MIN_UNIT),
			HOR_MIN_UNIT,
			VER_MIN_UNIT,
			m_sObjects[j]->rect()->offsetX(),
			m_sObjects[j]->rect()->offsetY(),
			m_sObjects[j]->rect()->sizeRateX(),
			m_sObjects[j]->rect()->sizeRateY(),
			m_sObjects[j]->tag());
	}

	//続いてDynamicObject
	//もうこの時点で列とかの数が分かってる。それ前提で進める

	//CSV解析
	ifstream ifstr(CSVEnemyFilename);
	m_indexDynamic = new int[m_gridNumber];
	for (int j = 0; j < m_gridNumber; j++) {
		ifstr >> m_indexDynamic[j];
		if ((j + 1) % m_colNumber != 0) {
			ifstr.ignore(3, ',');
		}
	}

	//dObjectが何個あるか調べる
	for (int j = 0; j < m_gridNumber; j++) {
		if (m_indexDynamic[j] != -1) {
			m_dObjectNumber++;
		}
	}
	//dObjectの数だけnew
	m_dObjects = new DynamicObject*[m_dObjectNumber];
	t = 0;
	for (int j = 0; j < m_gridNumber; j++) {
		if (m_indexDynamic[j] != -1) {
			m_dObjects[t] = new DynamicObject();
			m_dObjects[t]->setIndex(j);
			t++;
		}
	}


	for (int j = 0; j < m_dObjectNumber; j++) {
		//ダイナミックオブジェクトに敵を振り分け
		int t = m_dObjects[j]->index();//m_indexも初期化されてしまうのでコピーしとく
		switch (m_indexDynamic[m_dObjects[j]->index()]) {
		case 0:
			m_dObjects[j] = new Goomba();//ここでm_colNumberとか決定
			break;
		case 1:
			m_dObjects[j] = new Noko();
			break;
		}
		m_dObjects[j]->setIndex(t);
		
		m_dObjects[j]->initialize(
			"resource/picture/enemies.png",
			m_dObjects[j]->colNumber(),
			m_dObjects[j]->rowNumber(),
			m_dObjects[j]->startFrame(),
			m_dObjects[j]->endFrame(),
			m_dObjects[j]->currentFrame(),
			m_dObjects[j]->frameDelay(),
			(m_dObjects[j]->index() % m_colNumber)*HOR_MIN_UNIT,
			(m_dObjects[j]->index() / m_colNumber)*VER_MIN_UNIT,
			static_cast<float>((WINDOW_WIDTH*m_maxColNumberDynamic) / (WINDOW_COL_NUMBER*m_dObjects[j]->colNumber())),
			static_cast<float>((WINDOW_HEIGHT*m_maxRowNumberDynamic) / (WINDOW_ROW_NUMBER*m_dObjects[j]->rowNumber())),
			m_dObjects[j]->rect()->offsetX(),
			m_dObjects[j]->rect()->offsetY(),
			m_dObjects[j]->rect()->sizeRateX(),
			m_dObjects[j]->rect()->sizeRateY(),
			m_dObjects[j]->tag());
	}
}



Stage::~Stage() {
	for (int j = 0; j < m_dObjectNumber; j++) {
		DELETE(m_dObjects[j]);
	}
	for (int j = 0; j < m_sObjectNumber; j++) {
		DELETE(m_sObjects[j]);
	}
	DELETE_ARRAY(m_sObjects);
	DELETE_ARRAY(m_dObjects);
	DELETE_ARRAY(m_indexDynamic);
}

const Rect* Stage::rect(int index)const {
	return m_sObjects[index]->rect();
}
bool Stage::needCheckColWithPlayer(int index)const {
	return m_sObjects[index]->needCheckCollision();
}


void Stage::setStaticTexture() {
	m_sObjects[0]->setTexture();
}
void Stage::setDynamicTexture() {
	m_dObjects[0]->setTexture();
}

void Stage::drawStatic() {
	for (int j = 0; j < m_sObjectNumber; j++) {
		if ((-WINDOW_WIDTH / 16)<m_sObjects[j]->position()->x&&
			m_sObjects[j]->position()->x < (WINDOW_WIDTH)) {
			if (m_sObjects[j]->isActive()) {
				m_sObjects[j]->draw();
			}
		}
	}
}
void Stage::drawDynamic() {
	for (int j = 0; j < m_dObjectNumber; j++) {
		if (m_dObjects[j]->isActive()) {
			if ((-WINDOW_WIDTH / 16) < m_dObjects[j]->position()->x&&
				m_dObjects[j]->position()->x < WINDOW_WIDTH) {
				m_dObjects[j]->draw();
			}
		}
	}
}
void Stage::update(const Vector2& playerMove, const Vector2& playerPos,const Vector2* enemyMove) {
	for (int j = 0; j < m_sObjectNumber; j++) {
		m_sObjects[j]->update(playerMove, playerPos);
	}
	for(int j=0;j<m_dObjectNumber;j++){
		m_dObjects[j]->update(playerMove, playerPos);
		if (!m_dObjects[j]->isKilled()) {
			m_dObjects[j]->movePosition(enemyMove[j]);
		}
		
	}
}
StaticObject* Stage::sObject(int j)const {
	return m_sObjects[j];
}
DynamicObject* Stage::dObject(int j)const {
	return m_dObjects[j];
}

int Stage::indexStatic(int j)const {
	return m_indexStatic[j];
}
int Stage::indexDynamic(int j)const {
	return m_indexDynamic[j];
}
int Stage::gridNumber()const {
	return m_gridNumber;
}
int Stage::sObjectNumber()const {
	return m_sObjectNumber;
}
int Stage::dObjectNumber()const {
	return m_dObjectNumber;
}