#ifndef SEQUENCE_PARENT_H
#define SEQUENCE_PARENT_H

#include"Sequence/Child.h"

namespace Sequence {

	class Child;

	//�V���O���g��
	class Parent {

	public:
		static void create();
		static void destroy();
		static Parent* instance();

		//���C���֐����Ăяo���������Ƃ̊֐�
		void update();

	private:
		Parent();
		virtual ~Parent();

		Child* m_child;

		//�B��̃C���X�^���X
		static Parent* m_instance;
	};



}
#endif