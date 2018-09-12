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

	D3DXMATRIX m_matrix;//��]�̂���
	float m_angle;//��]�p

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

	//(x,y)��str��`��B�Ԃ�l...���s:0 ����:�e�L�X�g�̍���
	virtual int print(const std::string& str, int x, int y);
	//rect���Ɏw���format�ŕ`��
	virtual int print(const std::string& str, RECT& rect, UINT format);
	

	virtual void onLostDevice();
	virtual void onResetDevice();

	//�Q�b�g�֐��Q
	virtual float degrees();
	virtual float radians();
	virtual DWORD fontColor();

	//�Z�b�g�֐��Q
	virtual void setDegrees(float deg);
	virtual void setRadians(float rad);
	virtual void setFontColor(DWORD c);









};

















#endif