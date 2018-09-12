#include"Sequence/Game/Parent.h"
#include"Sequence/Game/Play.h"
#include"Sequence/Game/Pause.h"
#include"Sequence/Game/Clear.h"
#include"Sequence/Game/Dead.h"

#include"Graphics.h"
#include"Input.h"
#include"Root.h"
#include"Constants.h"
#include"Image.h"
#include"Play/State.h"

#include<sstream>


namespace Sequence {
	namespace Game {
		Play::Play() {
			m_image = new Image("resource/boy.jpg", 1, 1, 0, 0, 0);
			Root::audio()->playCue("AboveGround");
		}
		Play::~Play() {
			DELETE(m_image);
			Root::audio()->stopCue("AboveGround");
		};

		Child* Play::update(Parent* parent) {
			Child* next = this;
			TextDX* t0 = Root::text();
			Input* i = Root::input();
			m_image->setTexture();
			//m_image->draw(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT);
			parent->state()->update();


			if (i->wasKeyPressed('P')) {
				next = new Pause();
			}


			std::ostringstream oss;
			oss << " MARIO\r\n " << parent->score();
			t0->print(oss.str().c_str(), WINDOW_WIDTH*0.05f, WINDOW_HEIGHT*0.02f);
			oss.str("");
			oss << "WORLD\n" << parent->stageID() / 5 + 1 << "-" << parent->stageID() % 5;
			t0->print(oss.str().c_str(), WINDOW_WIDTH*0.6f, WINDOW_HEIGHT*0.02f);

			switch (parent->state()->cond()) {
			case Player::COND_ALIVE:
				break;
			case Player::COND_DEAD:
				parent->addLives(-1);
				if (parent->lives() <= 0) {
					parent->moveTo(Parent::NEXT_GAMEOVER);
					break;
				}
				next = new Dead();
				break;
			case Player::COND_CLEAR:
				parent->addStageID(1);
				next = new Clear();
				break;
			}



			if (i->wasKeyPressed(VK_SPACE)) {
				//t->print("hello,world", 100, 100, 30,true, true);
				
				parent->moveTo(Parent::NEXT_TITLE);
			}

			return next;
		}

		
	}
}