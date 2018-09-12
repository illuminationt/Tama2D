#ifndef SEQUENCE_PARENT_H
#define SEQUENCE_PARENT_H

#include"Sequence/Child.h"

namespace Sequence {

	class Child;

	//シングルトン
	class Parent {

	public:
		static void create();
		static void destroy();
		static Parent* instance();

		//メイン関数が呼び出すおおもとの関数
		void update();

	private:
		Parent();
		virtual ~Parent();

		Child* m_child;

		//唯一のインスタンス
		static Parent* m_instance;
	};



}
#endif