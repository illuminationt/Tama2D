#ifndef SEQUENCE_GAME_DEAD_H
#define SEQUENCE_GAME_DEAD_H
#include"Sequence/Game/Child.h"

class Image;

namespace Sequence {
	namespace Game {

		class Parent;

		class Dead:public Child {
		public:
			Dead();
			virtual ~Dead();

			Child* update(Parent* parent);

		private:
			Image* m_image;
			int m_count;
		};

	}
}
#endif