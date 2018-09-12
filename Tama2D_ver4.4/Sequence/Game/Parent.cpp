#include"Sequence/Child.h"
#include"Sequence/Parent.h"
#include"Sequence/Game/Parent.h"
#include"Sequence/Title.h"
#include"Sequence/GameOver.h"

#include"Sequence/Game/Play.h"
#include"Constants.h"
#include"Sequence/Game/Load.h"
#include"Play/State.h"


namespace Sequence {
	namespace Game {
		int Parent::m_score = 0;
		Parent::Parent():
			m_child(0),
			m_state(0),
			m_next(NEXT_NONE),
			m_stageID(1),
			m_lives(3){
			m_child = new Load();
		}
		Parent::~Parent() {
			DELETE(m_state);
			DELETE(m_child)
		};



		//このSequence::updateの中で、Sequence::Game::update()を呼び出す。
		//返り値はSequence::Child.

		Sequence::Child* Parent::update(Sequence::Parent* grandparent) {
			Sequence::Child* next = this;
			Game::Child* nextChild = m_child->update(this);

			if (nextChild != m_child) {
				DELETE(m_child);
				m_child = nextChild;
			}

			switch (m_next) {
			case NEXT_TITLE:
				next = new Title();
				break;
			case NEXT_GAMEOVER:
				next = new GameOver();
			case NEXT_NONE:
				break;
			}

			return next;
		}

		State* Parent::state() const {
			return m_state;
		}

		void Parent::loadState(int stageID) {
			DELETE(m_state);
			m_state = new State(stageID);
		}

		void Parent::moveTo(NextSequence ns) {
			m_next = ns;
		}

		int Parent::stageID()const {
			return m_stageID;
		}
		void Parent::addStageID(int j) {
			m_stageID += j;
		}

		int Parent::lives()const {
			return m_lives;
		}
		void Parent::addLives(int j) {
			m_lives += j;
		}

		int Parent::score()const {
			return m_score;
		}
		void Parent::addScore(int score) {
			m_score += score;
		}

	}
}