#ifndef ROOT_H
#define ROOT_H

#include"Game.h"
#include"Sequence/Parent.h"

class Root :public Game {
public:
	Root();
	virtual ~Root();

	static  Graphics* graphics();
	static  Input* input() ;
	static TextDX* text(int index = 0);
	static Audio* audio();
	static LPD3DXSPRITE sprite();

	void initialize(HWND hWNd);

	void update();
private:
	
};






#endif