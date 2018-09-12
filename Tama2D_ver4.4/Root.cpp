#include "Root.h"


Root::Root() :Game() {
	
}


Root::~Root()
{
}



void Root::initialize(HWND hWnd) {
	Game::initialize(hWnd);

	if (!Sequence::Parent::instance()) {
		Sequence::Parent::create();
	}
}
Graphics* Root::graphics() {
	return Game::graphics();
}
Input* Root::input() {
	return Game::input();
}
TextDX* Root::text(int index) {
	return Game::text(index);
}
Audio* Root::audio() {
	return Game::audio();
}
LPD3DXSPRITE Root::sprite() {
	return Game::sprite();
}

void Root::update() {
	Sequence::Parent::instance()->update();

}
