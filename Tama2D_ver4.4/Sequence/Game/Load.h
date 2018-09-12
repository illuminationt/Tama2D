#ifndef SEQUENCE_GAME_LOAD_H
#define SEQUENCE_GAME_LOAD_H
#include"Sequence/Game/Child.h"
class Image;
namespace Sequence {
	namespace Game {

		class Parent;

		class Load :public Child {
		public:
			Load();
			virtual ~Load();

			Child* update(Parent* parent);

		private:
			Image* m_image;
			int m_count;
		};





	}
}


#endif