#ifndef SEQUENCE_CHILD_H
#define SEQUENCE_CHILD_H


namespace Sequence {

	class Parent;

	class Child
	{
	public:
		virtual Child* update(Parent* parent) = 0;
		virtual ~Child() {};
	};

}

#endif