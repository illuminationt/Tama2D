#ifndef SEQUENCE_GAME_PARENT_H
#define SEQUENCE_GAME_PARENT_H

#include"Sequence/Child.h"
#include"Sequence/Game/Child.h"
//����Parent��Sequence�̎q�ł���Game�̐e�B
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
			//stageID��j��������������
			void addStageID(int j);

			int lives()const;
			//�c�@��(m_lives)��j����������
			void addLives(int j);

			int score()const;
			//score����m_score�𑝌�������
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