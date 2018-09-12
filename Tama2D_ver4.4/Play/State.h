#ifndef STATE_H
#define STATE_H

#include"Play/Player.h"
#include"Play/Stage.h"

//名前空間：Gameの階層で扱うオブジェクトをまとめて管理。
//プレイ→ポーズとかの遷移でステージの状態を保存しておく意味もある
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