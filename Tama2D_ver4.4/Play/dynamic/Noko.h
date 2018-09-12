#ifndef NOKO_H
#define NOKO_H
#include"Play/DynamicObject.h"
class Noko:public DynamicObject{
public:
	Noko();
	virtual ~Noko();

	enum ModeX {
		MODEX_WALK_LEFT,
		MODEX_WALK_RIGHT,
		MODEX_WALK_STOP_FROM_LEFT,
		MODEX_WALK_STOP_FROM_RIGHT,
		MODEX_SHELL_STOP,
		MODEX_SHELL_LEFT,
		MODEX_SHELL_RIGHT,
	};


	virtual void getMove(Vector2* mevoOut);

private:
	ModeX m_modeX;
	//”ÏŽG‚È‚Ì‚Å•ª‚¯‚é
	void intoShell();
	void outofShell();
	int m_shellCount;
	static const float m_gravity;
	static const float m_speedX;
	static const float m_shellSpeedX;
	static const float m_maxShellSpeedX;
	static const int m_inStaticShellTime;
	static const int m_inDynamicShellTime;
};


#endif