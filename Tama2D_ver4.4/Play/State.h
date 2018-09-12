#ifndef STATE_H
#define STATE_H

#include"Play/Player.h"
#include"Play/Stage.h"

//���O��ԁFGame�̊K�w�ň����I�u�W�F�N�g���܂Ƃ߂ĊǗ��B
//�v���C���|�[�Y�Ƃ��̑J�ڂŃX�e�[�W�̏�Ԃ�ۑ����Ă����Ӗ�������
class DynamicObject;
class State{
public:
	State(int stageID);
	virtual ~State();

	
	void update();
	void getMove(Vector2* playerMoveOut, Vector2* enemyMove)const;
	const Player::Condition cond()const;
private:
	Player* m_player;
	Stage* m_stage;



};


#endif