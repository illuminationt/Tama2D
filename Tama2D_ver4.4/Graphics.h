#ifndef GRAPHICS_H
#define GRAPHICS_H
#define WIN32_LEAN_AND_MEAN
/*
�����悻�`��������N���X
Graphics�N���X�ɂ�Game�N���X�̃����o�Am_graphics*�|�C���^�ł����Q�Ƃł��Ȃ��B
������Game�N���X�ł́ArenderGame���\�b�h��graphics�I�u�W�F�N�g�������B
renderGame���\�b�h����render���\�b�h���Ăяo���B
render���\�b�h��Game���p���N���X�ŃI�[�o�[���[�h����A�Q�[���ɉ����Ď��������

�`��̍ł����{�I�Ȋ֐��͂���Graphics�N���X��drawSprite()�ł��B
m_spriteData�̏������ɍs�������肵�ĕ`�悵�܂�
�����A���ۂɊe�R�[�h��draw����̂�Image�N���X�ɂȂ�ł��傤
�i����Graphics�N���X�𒼂Ɉ������Ƃ͂Ȃ����낤�i���Ԃ�j

*/


#include<Windows.h>
#include<d3d9.h>
#include<d3dx9.h>

namespace graphicsNS {
	const DWORD ORANGE = D3DCOLOR_ARGB(255, 255, 165, 0);
	const DWORD BROWN = D3DCOLOR_ARGB(255, 139, 69, 19);
	const DWORD LTGRAY = D3DCOLOR_ARGB(255, 192, 192, 192);
	const DWORD GRAY = D3DCOLOR_ARGB(255, 128, 128, 128);
	const DWORD OLIVE = D3DCOLOR_ARGB(255, 128, 128, 0);
	const DWORD PURPLE = D3DCOLOR_ARGB(255, 128, 0, 128);
	const DWORD MAROON = D3DCOLOR_ARGB(255, 128, 0, 0);
	const DWORD TEAL = D3DCOLOR_ARGB(255, 0, 128, 128);
	const DWORD GREEN = D3DCOLOR_ARGB(255, 0, 128, 0);
	const DWORD NAVY = D3DCOLOR_ARGB(255, 0, 0, 128);
	const DWORD WHITE = D3DCOLOR_ARGB(255, 255, 255, 255);
	const DWORD YELLOW = D3DCOLOR_ARGB(255, 255, 255, 0);
	const DWORD MAGENTA = D3DCOLOR_ARGB(255, 255, 0, 255);
	const DWORD RED = D3DCOLOR_ARGB(255, 255, 0, 0);
	const DWORD CYAN = D3DCOLOR_ARGB(255, 0, 255, 255);
	const DWORD LIME = D3DCOLOR_ARGB(255, 0, 255, 0);
	const DWORD BLUE = D3DCOLOR_ARGB(255, 0, 0, 255);
	const DWORD BLACK = D3DCOLOR_ARGB(255, 0, 0, 0);
	const DWORD FILTER = D3DCOLOR_ARGB(0, 0, 0, 0);  // use to specify drawing with colorFilter
	const DWORD ALPHA25 = D3DCOLOR_ARGB(64, 255, 255, 255);  // AND with color to get 25% alpha
	const DWORD ALPHA50 = D3DCOLOR_ARGB(128, 255, 255, 255);  // AND with color to get 50% alpha
	const DWORD BACK_COLOR = NAVY;

	enum DISPLAY_MODE {
		TOGGLE,
		FULLSCREEN,
		WINDOW,
	};

}
//�X�v���C�g�S�̂̏�����\���\����
struct SpriteData {
	int width;
	int height;
	float x; // x.y : ����̍��W
	float y;//
	float scale;
	float angle;
	RECT rect; //�e�N�X�`���̈ꕔ���g���Ƃ��ɕK�v
	LPDIRECT3DTEXTURE9 texture;//�e�N�X�`���ւ̃|�C���^
	bool flipHorizontal;
	bool flipVertical;
};

class Graphics {
public:
	Graphics(HWND hWnd);
	virtual ~Graphics();
	void releaseAll();

	/*
	�`��菇
	Image�N���X�Ńe�N�X�`������
	Graphics::loadTexture�Ńt�@�C��������e�N�X�`���ǂݍ���
	setTexture��draw�̒��O�ɌĂяo���Adraw�ŏꏊ���w�肵�`��I
	*/


	//�e�N�X�`�������[�h
	HRESULT loadTexture(
		const char* filename,
		LPDIRECT3DTEXTURE9& texOut);
	//�`��֐�
	void draw(float*, float*, float*, float* = 0, float* = 0, float* = 0);
	//�e�N�X�`�����f�o�C�X�ɃZ�b�g�B(���������j
	void setTexture(LPDIRECT3DTEXTURE9)const;
	
	
	//�Q�b�g�֐�
	const LPDIRECT3DDEVICE9 D3DDev()const;
	const LPD3DXSPRITE sprite()const;


	//�o�b�N�o�b�t�@�����C���o�b�t�@��
	HRESULT showBackBuffer();
	//TODO:�Ȃɂ���H�H�H
	bool isAdapterCompatible();
	//
	void drawSprite(
		const SpriteData& spriteData,
		DWORD filterColor = graphicsNS::WHITE);
	//�O���t�B�b�N�X�f�o�C�X�̃��Z�b�g
	HRESULT reset();
	//
	void changeDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);



	//�f�o�C�X���������ĂȂ����`�F�b�N
	HRESULT getDeviceState();
	//�J���[�Z�b�g
	void setBackColor(DWORD c) { m_backColor = c; };
	//�o�b�N�o�b�t�@���N���A�A����BeginScene()
	HRESULT beginScene();
	//EndScene()�̌�����
	HRESULT endScene();
	//�X�v���C�g�ɂ�begin��end
	//�������Game::render()�ŌĂяo�����
	void spriteBegin();
	void spriteEnd();

private:
	//D3DPRESENTATION_PARAMETERS���������I
	void initD3Dpp();

	LPDIRECT3D9 m_D3D;
	LPDIRECT3DDEVICE9 m_D3DDev;
	LPD3DXSPRITE m_sprite;
	IDirect3DTexture9* m_texture;
	IDirect3DVertexBuffer9* m_vertex;
	D3DPRESENT_PARAMETERS m_d3dpp;
	D3DDISPLAYMODE m_mode;



	//other variables
	HRESULT m_result;
	HWND m_hWnd;
	bool m_fullscreen;
	int m_width;
	int m_height;
	DWORD m_backColor;

	struct CUSTOMVERTEX {
		float x, y, z;
		float rhw;
		DWORD color;
		float u, v;
	};
	CUSTOMVERTEX m_v[3];

};



#endif
