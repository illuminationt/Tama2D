#include "GameOver.h"
#include"Image.h"
#include"Sequence/Child.h"
#include"Sequence/Title.h"

namespace Sequence {

	GameOver::GameOver():m_image(0),m_count(0){
		m_image = new Image("resource/boy4.jpg", 1, 1, 0, 0, 0);
	}


	GameOver::~GameOver(){
		DELETE(m_image);
	}

	Child* GameOver::update(Parent* parent) {
		Child* next = this;

		m_image->setTexture();
		m_image->draw(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT);

		TextDX* t = Root::text();
		t->print("GameOver", 100, 200);

		if (m_count == 0) {
			Root::audio()->playCue("Game Over");
		}
		if (m_count > 200) {
			next = new Title();
		}
		m_count++;
		return next;
	}

}