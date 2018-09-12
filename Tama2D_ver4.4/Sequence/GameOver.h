#ifndef SEQUENCE_GAMEOVER_H
#define SEQUENCE_GAMEOVER_H

#include"Sequence/Child.h"
class Image;
namespace Sequence {
	class Child;
	class Parent;
	class GameOver :public Child {
	public:
		GameOver();
		virtual ~GameOver();

		Child* update(Parent* parent);

	private:
		Image* m_image;
		int m_count;
	};


}
#endif