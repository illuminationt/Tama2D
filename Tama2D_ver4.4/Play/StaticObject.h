#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include"Rect.h"
#include"Space/Vector2.h"
class Image;
//テクスチャ、テクスチャの中の書く場所、画面内の描く場所、大きさをもらって
//それを描画するだけの関数がいいかな～～

class StaticObject
{
public:
	StaticObject();
	virtual ~StaticObject();

	enum Tag {
		TAG_BRICK,
		TAG_HATENA,
		TAG_COIN,
		TAG_GOALPOLE,
		TAG_CLEAR_FLAG,//ゴールの旗ではない
		TAG_OTHER_BLOCKS,
		TAG_BACKGROUND,

		TAG_NOKO,

		TAG_OTHER_ENEMY,
	};
	
	virtual void initialize(
		const char* filename,
		int colNumber,//テクスチャの列
		int rowNumber,//テクスチャの行
		int startFrame,//その絵が始まるフレーム（場所）
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
		Tag tag);

	//drawごとにsetTextureしてもいいがさすがに重そう
	virtual void setTexture()const;
	virtual void draw();
	//updateは毎フレーム呼ばれる（プレイヤーが死なない限り）
	virtual void update(const Vector2& playerMove,const Vector2& playerPos);
	//そのオブジェクトを殺す
	virtual void kill();

	virtual void setCheckCollision();
	virtual bool needCheckCollision();
	virtual bool isActive()const;
	virtual bool isKilled()const;
	const Rect* rect()const;
	void setRectOffset(float, float);
	void setRectSizeRate(float, float);

	const Vector2* position()const;
	const Vector2* size()const;
	const Vector2* velocity()const;
	const Vector2* prevMove()const;

	
	const Tag tag()const;
	void setTag(Tag type);

	int colNumber()const;//テクスチャ内の行の数
	int rowNumber()const;//テクスチャ内の列の数
	int startFrame()const;//テクスチャ内でアニメの開始フレーム
	int endFrame()const;//テクスチャ内でアニメの終了点
	int currentFrame()const;//テクスチャ内で今描いてるフレーム
	int frameDelay()const;//アニメのコマ送りの間隔

	void setHittedDir(const Vector2&);
	int index()const;
	void setIndex(int j);
protected:
	Rect m_rect;
	Image* m_image;
	Vector2 m_position;
	Vector2 m_size;
	Vector2 m_velocity;
	Vector2 m_prevMove;

	//あたり判定しなくていい位置にあるときはfalse
	bool m_needCheckCollision;
	//殺されたらtrue
	bool m_isKilled;
	//画面表示の必要がなくなったらfalse
	bool m_isActive;
	//そのオブジェクトの実体はなにか？
	Tag m_tag;

	//テクスチャのどこを描くか判定するための変数
	//テクスチャ内の行、列の数
	//具体的な敵クラスでは敵クラスのコンストラクタで初期化
	//コンストラクタは基底→派生の順で呼ばれる
	int m_colNumber;
	int m_rowNumber;
	int m_startFrame;
	int m_endFrame;
	int m_currentFrame;
	int m_frameDelay;

	Vector2 m_hittedDir;
	int m_index;//マップ上の何番目に配置されたか？
	
};


#endif