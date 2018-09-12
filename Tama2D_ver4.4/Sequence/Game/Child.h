#ifndef SEQUENCE_GAME_CHILD_H
#define SEQUENCE_GAME_CHILD_H



namespace Sequence {
	namespace Game {
		class Parent;

		class Child {
		public:
			virtual Child* update(Parent* parent) = 0;
			virtual ~Child() {};
		};
	}
}





#endif