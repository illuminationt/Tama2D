#ifndef SEQUENCE_TITLE_H
#define SEQUENCE_TITLE_H

#include"Sequence/Child.h"
class Image;
namespace Sequence {
	class Child;
	class Parent;
	namespace Game {
		class Parent;
	}

	class Title:public Child{
	public:
		Title();
		virtual ~Title();

		Child* update(Parent* parent);

	private:
		Image* m_image;
	};

}
#endif