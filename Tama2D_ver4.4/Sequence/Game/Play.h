#ifndef SEQUENCE_GAME_PLAY_H
#define SEQUENCE_GAME_PLAY_H

#include"Sequence/Game/Child.h"
#include"Play/Player.h"
class Stage;

namespace Sequence {
	namespace Game {

		class Play :public Child {
		public:
			Play();
			virtual ~Play();

			Child* update(Parent* parnt);

		private:
			Image* m_image;
			

		};
	}
}




#endif