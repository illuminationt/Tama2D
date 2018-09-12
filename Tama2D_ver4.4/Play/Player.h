#ifndef PLAYER_H
#define PLAYER_H



class Image;

#include"Rect.h"
#include"Space/Vector2.h"
#include"Play/StaticObject.h"
#include"Play/DynamicObject.h"
class Player:public DynamicObject{
public:
	//�͂��߂̈ʒu
	Player();
	virtual ~Player();

	//�����\����Q�b�g�B����moveOut��Rectangle::restrictMove�ɓ���Ă���update�ɓn��
	void getMove(Vector2* moveOut);
	
	void processCollision(Vector2* moveOut,StaticObject& s);
	void update(const Vector2& move);



	enum Condition {
		COND_ALIVE,
		COND_IS_DYING,//����ł���V�[�P���X�J�ڂ��n�܂�܂�
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
	static const float m_accelX;//x���������x
	static const float m_resistRate;//X���x������
	static const float m_turnAccelXRate;//X�����������̋����␳��
	static const float m_jumpForce;//�W�����v�̋���
	static const float m_jumpForceStumpEnemy;//�G���񂾎��̃W�����v�̋���
	static const float m_jumpForceStumpEnemyWithButtonRate;//�{�^�������Ȃ���G���񂾎��̃W�����v�̋����̔䗦
	static const float m_jumpAccelForce;//�W�����v�������ŉ����͂̋���
	static const int m_jumpAccelTime;//�W�����v�������ɕK�v�Ȏ���
	static const int m_minFrameDelay;//FrameDelay�̍ŏ��l
};



#endif