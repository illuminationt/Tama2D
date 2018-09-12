#ifndef STAGE_H
#define STAGE_H

#include"Space/Vector2.h"
#include<vector>
class StaticObject;
class DynamicObject;
class Rect;

class Stage
{
public:
	Stage(const char* CSVfilename,
		const char* CSVEnemyFilename);
	virtual ~Stage();

	const Rect* rect(int index)const;
	//j番目のスタティックオブジェクトは衝突処理必要な位置にあるか？
	bool needCheckColWithPlayer(int j)const;

	void setStaticTexture();
	void setDynamicTexture();
	void drawStatic();
	void drawDynamic();

	//プレイヤーのX移動はステージの相対移動で実現。
	//プレイヤーの動きを受け取り相対移動
	void update(const Vector2& playerMove, const Vector2& playerPos,const Vector2* enemyMove);

	StaticObject* sObject(int j)const;
	DynamicObject* dObject(int j)const;

	int indexStatic(int j)const;
	int indexDynamic(int j)const;
	int gridNumber()const;
	int sObjectNumber()const;
	int dObjectNumber()const;
private:
	StaticObject** m_sObjects;
	DynamicObject** m_dObjects;

	//CSVの中の数字を記録した配列
	std::vector<int> m_indexStatic;
	int* m_indexDynamic;

	int m_colNumber;
	int m_rowNumber;
	int m_gridNumber;
	int m_sObjectNumber;//実際のstatic objectの数
	int m_dObjectNumber;//実際のdynamic objectの数

	static const int m_maxColNumberStatic;//テクスチャ内の最大の列の数(スタティックオブジェクトの）
	static const int m_maxRowNumberStatic;//テクスチャ内の最大の行の数(スタティックオブジェクトの）
	static const int m_maxColNumberDynamic;;//テクスチャ内の最大の列の数(ダイナミックオブジェクトの）
	static const int m_maxRowNumberDynamic;;//テクスチャ内の最大の行の数(ダイナミックオブジェクトの）
};



#endif