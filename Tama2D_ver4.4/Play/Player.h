#ifndef PLAYER_H
#define PLAYER_H



class Image;

#include"Rect.h"
#include"Space/Vector2.h"
#include"Play/StaticObject.h"
#include"Play/DynamicObject.h"
class Player:public DynamicObject{
public:
	//はじめの位置
	Player();
	virtual ~Player();

	//動く予定をゲット。このmoveOutをRectangle::restrictMoveに入れてからupdateに渡す
	void getMove(Vector2* moveOut);
	
	void processCollision(Vector2* moveOut,StaticObject& s);
	void update(const Vector2& move);



	enum Condition {
		COND_ALIVE,
		COND_IS_DYING,//死んでからシーケンス遷移が始まるまで
		COND_DEAD,
		COND_GOAL,
		COND_EASY_GOAL,
		COND_CLEAR,
	};

	enum ModeX {
		MODEX_LEFT,
		MODEX_RIGHT,
		MODEX_TURN_TO_LEFT,
		MODEX_TURN_TO_RIGHT,
		MODEX_STOP,
	};


	enum ModeY {
		MODEY_JUMP_UP,
		MODEY_JUMP_UP_ACCEL,
		MODEY_JUMP_STAY,
		MODEY_JUMP_DOWN,
		MODEY_ON_LAND,
	};
	
	const Condition cond()const;

private:
	void addScore(int score);
	ModeX m_modeX;
	ModeY m_modeY;
	void isDying(Vector2* moveOut);
	void goal(Vector2* moveOut);
	void easyGoal(Vector2* moveOut);
	int m_dyingCount;
	int m_goalCount;
	int m_easyGoalCount;
	int m_accelTimeCount;
	int m_scoreRate;
	Condition m_cond;

	static const float m_gravity;
	static const float m_maxSpeedX;
	static const float m_accelX;//x方向加速度
	static const float m_resistRate;//X速度減衰率
	static const float m_turnAccelXRate;//X向き換え時の強さ補正率
	static const float m_jumpForce;//ジャンプの強さ
	static const float m_jumpForceStumpEnemy;//敵踏んだ時のジャンプの強さ
	static const float m_jumpForceStumpEnemyWithButtonRate;//ボタン押しながら敵踏んだ時のジャンプの強さの比率
	static const float m_jumpAccelForce;//ジャンプ長押しで加わる力の強さ
	static const int m_jumpAccelTime;//ジャンプ長押しに必要な時間
	static const int m_minFrameDelay;//FrameDelayの最小値
};



#endif