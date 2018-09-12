#ifndef SEQUENCE_GAME_PARENT_H
#define SEQUENCE_GAME_PARENT_H

#include"Sequence/Child.h"
#include"Sequence/Game/Child.h"
//このParentはSequenceの子でありGameの親。
//
class State;
namespace Sequence {
	namespace Game {

		class Parent :public Sequence::Child{
		public:
			enum NextSequence {
				NEXT_TITLE,
				NEXT_GAMEOVER,
				NEXT_NONE,
			};
			Parent();
			virtual ~Parent();

			Child* update(Sequence::Parent* parent);
			
			State* state()const;

			void loadState(int stageID);
			void moveTo(NextSequence);

			int stageID()const;
			//stageIDをjだけ増減させる
			void addStageID(int j);

			int lives()const;
			//残機数(m_lives)をj増減させる
			void addLives(int j);

			int score()const;
			//scoreだけm_scoreを増減させる
			static void addScore(int score);
		private:
			Game::Child* m_child;
			State* m_state;
			NextSequence m_next;

			int m_stageID;
			int m_lives;
			static int m_score;
		};



	}
}






#endif