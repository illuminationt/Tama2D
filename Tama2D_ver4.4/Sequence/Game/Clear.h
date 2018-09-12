#ifndef SEQUENCE_GAME_CLEAR_H
#define SEQUENCE_GAME_CLEAR_H
#include"Sequence/Game/Child.h"

class Image;

namespace Sequence {
	namespace Game {

		class Parent;

		class Clear :public Child {
		public:
			Clear();
			virtual ~Clear();

			Child* update(Parent* parent);

		private:
			Image* m_image;
			int m_count;
		};

	}
}
#endif