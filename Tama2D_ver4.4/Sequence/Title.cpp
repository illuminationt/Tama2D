#include "Sequence/Title.h"
#include"Sequence/Game/Child.h"
#include"Sequence/Parent.h"
#include"Sequence/Game/Parent.h"
#include"Root.h"
#include"Image.h"
namespace Sequence {



	Title::Title(){
		m_image = new Image("resource/boy2.jpg", 1, 1, 0, 0, 0);
	}


	Title::~Title()
	{
		DELETE(m_image);
	}

	Child* Title::update(Parent* parent) {
		Child* next = this;

		TextDX* t = Root::text();
		//TextDX* t1 = Root::text(1);
		Input* i = Root::input();

		m_image->setTexture();
		m_image->draw(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT);

		t->print("Title:Tama2D", 100, 100);


		if (i->wasKeyPressed('0')) {
			next = new Game::Parent();
		}

		return next;
	}



}