#include "Sequence/Parent.h"
#include"Sequence/Child.h"
#include"Sequence/Game/Parent.h"
#include"Sequence/Title.h"

#include"Constants.h"

#include"Root.h"

namespace Sequence {
	Parent* Parent::m_instance = 0;

	void Parent::create() {
		if (m_instance) {
			WARN("already Parend::instance is created!");
		}
		m_instance = new Parent();
	}

	void Parent::destroy() {
		if (!m_instance) {
			WARN("instance haven't been created yet");
		}
		DELETE(m_instance);
	}

	Parent* Parent::instance() {
		return m_instance;
	}
	void Parent::update() {
		//update‚µ‚Â‚Ânext‚ð’²’B
		Child* next = m_child->update(this);


		if (next != m_child) {
			DELETE(m_child);
			m_child = next;
		}
		next = 0;
	}


	Parent::Parent() {
		m_child = new Title();
	}


	Parent::~Parent(){
		DELETE(m_child);
	}

	

}//namespace Sequence