#ifndef SEQUENCE_GAME_PAUSE_H
#define SEQUENCE_GAME_PAUSE_H

#include"Sequence/Game/Child.h"

namespace Sequence {
	namespace Game {


		class Pause :public Child {
		public:
			Pause();
			virtual ~Pause();

			Child* update(Parent* parent);
		};
	}
}



#endif