#ifndef TEXTDX_H
#define TEXTDX_H

#include<Windows.h>
#include"Graphics.h"
#include<string>
#include"Constants.h"

class TextDX {
private:
	Graphics* m_graphics;
	DWORD m_color;
	LPD3DXFONT m_dxFont;
	RECT m_fontRect;

	D3DXMATRIX m_matrix;//‰ñ“]‚Ì‚½‚ß
	float m_angle;//‰ñ“]Šp

public:
	TextDX();
	virtual ~TextDX();

	virtual bool initialize(
		Graphics* g,
		DWORD color=0xffffffff,
		int height=30,
		bool bold=false,
		bool italic=false,
		const std::string& fontName="Arial");

	//(x,y)‚Éstr‚ğ•`‰æB•Ô‚è’l...¸”s:0 ¬Œ÷:ƒeƒLƒXƒg‚Ì‚‚³
	virtual int print(const std::string& str, int x, int y);
	//rect“à‚Éw’è‚Ìformat‚Å•`‰æ
	virtual int print(const std::string& str, RECT& rect, UINT format);
	

	virtual void onLostDevice();
	virtual void onResetDevice();

	//ƒQƒbƒgŠÖ”ŒQ
	virtual float degrees();
	virtual float radians();
	virtual DWORD fontColor();

	//ƒZƒbƒgŠÖ”ŒQ
	virtual void setDegrees(float deg);
	virtual void setRadians(float rad);
	virtual void setFontColor(DWORD c);









};

















#endif