#include"Sequence/Game/Pause.h"
#include"Root.h"
#include"Sequence/Game/Play.h"
namespace Sequence {
	namespace Game {
		class Parent;

		Pause::Pause() {

		}
		Pause::~Pause() {

		}

		Child* Pause::update(Parent* parent) {
			Child* next = this;

			TextDX* t = Root::text();
			Input* i = Root::input();

			t->print("Pause", 10, 10);
			
			if (i->wasKeyPressed('P')) {
				next = new Play();
			}

			return next;
		}
	}
}