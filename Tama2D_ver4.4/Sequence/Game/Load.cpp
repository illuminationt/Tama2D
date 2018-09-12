#include "Load.h"
#include"Image.h"
#include"Sequence/Game/Play.h"
#include"Sequence/Game/Parent.h"
#include"Root.h"

#include<sstream>
namespace Sequence {
	namespace Game {


		Load::Load():
			m_image(0),
			m_count(0){
			m_image = new Image("resource/boy.jpg", 1, 1, 0, 0, 0);
			
		}


		Load::~Load(){
			DELETE(m_image);
		}

		Child* Load::update(Parent* parent) {
			Child* next = this;

			

			m_image->setTexture();
			m_image->draw(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT);
			
			TextDX* t = Root::text();
			std::ostringstream oss;
			oss << "WORLD " << parent->stageID()/5+1<<"-"<<parent->stageID()%5;

			t->print(oss.str().c_str(), WINDOW_WIDTH*0.38f, WINDOW_HEIGHT*0.45);

			m_count++;
			if (m_count >10) {
				parent->loadState(parent->stageID());
				next = new Play();
			}
			return next;
		}


	}
}