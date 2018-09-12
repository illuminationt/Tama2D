#ifndef IMAGE_H
#define IMAGE_H

#include"Root.h"

class Image
{
public:
	Image(
		const char* filename,
		int colNumber,
		int rowNumber,
		int startFrame,
		int endFrame,
		int frameDelay);

	virtual ~Image();

	//p : 左上の座標
	void draw(float* p,int width,int height);
	void draw(float x, float y, int width, int height);
	void setTexture()const;

	void reInitialize(
		int colNumber,
		int rowNumber,
		int startFrame,
		int endFrame,
		int frameDelay);
	void setFrameDelay(int frameDelay);
	void setCurrentFrame(int currentFrame);
	void setFlipX(bool flipX);
private:
	Graphics* m_graphics;
	LPDIRECT3DTEXTURE9 m_texture;

	int m_colNumber;//テクスチャ内の列の数
	int m_rowNumber;
	int m_startFrame;
	int m_endFrame;
	int m_currentFrame;
	int m_frameDelay;
	int m_animTimer;


	bool m_loop;
	bool m_animComplete;
	bool m_flipX;
};



#endif