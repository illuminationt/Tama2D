#ifndef GRAPHICS_H
#define GRAPHICS_H
#define WIN32_LEAN_AND_MEAN
/*
おおよそ描画を扱うクラス
GraphicsクラスにはGameクラスのメンバ、m_graphics*ポインタでしか参照できない。
そしてGameクラスでは、renderGameメソッドでgraphicsオブジェクトを扱う。
renderGameメソッド内でrenderメソッドを呼び出す。
renderメソッドはGameを継承クラスでオーバーロードされ、ゲームに応じて実装される

描画の最も根本的な関数はこのGraphicsクラスのdrawSprite()です。
m_spriteDataの情報を元に行列作ったりして描画します
ただ、実際に各コードでdrawするのはImageクラスになるでしょう
（今後Graphicsクラスを直に扱うことはないだろう（たぶん）

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
//スプライト全体の情報をを表す構造体
struct SpriteData {
	int width;
	int height;
	float x; // x.y : 左上の座標
	float y;//
	float scale;
	float angle;
	RECT rect; //テクスチャの一部を使うときに必要
	LPDIRECT3DTEXTURE9 texture;//テクスチャへのポインタ
	bool flipHorizontal;
	bool flipVertical;
};

class Graphics {
public:
	Graphics(HWND hWnd);
	virtual ~Graphics();
	void releaseAll();

	/*
	描画手順
	Imageクラスでテクスチャ準備
	Graphics::loadTextureでファイル名からテクスチャ読み込み
	setTextureをdrawの直前に呼び出し、drawで場所を指定し描画！
	*/


	//テクスチャをロード
	HRESULT loadTexture(
		const char* filename,
		LPDIRECT3DTEXTURE9& texOut);
	//描画関数
	void draw(float*, float*, float*, float* = 0, float* = 0, float* = 0);
	//テクスチャをデバイスにセット。(分離した）
	void setTexture(LPDIRECT3DTEXTURE9)const;
	
	
	//ゲット関数
	const LPDIRECT3DDEVICE9 D3DDev()const;
	const LPD3DXSPRITE sprite()const;


	//バックバッファをメインバッファに
	HRESULT showBackBuffer();
	//TODO:なにこれ？？？
	bool isAdapterCompatible();
	//
	void drawSprite(
		const SpriteData& spriteData,
		DWORD filterColor = graphicsNS::WHITE);
	//グラフィックスデバイスのリセット
	HRESULT reset();
	//
	void changeDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);



	//デバイスが消失してないかチェック
	HRESULT getDeviceState();
	//カラーセット
	void setBackColor(DWORD c) { m_backColor = c; };
	//バックバッファをクリア、次にBeginScene()
	HRESULT beginScene();
	//EndScene()の肩代わり
	HRESULT endScene();
	//スプライトにもbeginとend
	//こいつらはGame::render()で呼び出される
	void spriteBegin();
	void spriteEnd();

private:
	//D3DPRESENTATION_PARAMETERSを初期化！
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
