#ifndef GAME_H
#define GAME_H
#define WIN32_LEAN_AND_MEAN

/*

Graphics,Inputクラスへのポインタを持つクラス
これから作るゲームの本体となるクラスはこれを継承。
ゲームに必要な毎フレーム呼ばれる関数（update,AI,collision,renderは
ここで定義してあって、ゲームのメインループはもう既に（純粋仮想関数の形でだが
完成している。あとは継承先のクラスでこれら4つをオーバーライドすればOK

render()はrenderGame()の中に入っていて、renderGameの方で
BeginSceneとかはやっている。よってrender内は描画に専念すればいい

*/



#include<Windows.h>
#include<Mmsystem.h>
#include"Graphics.h"
#include"Input.h"
#include"TextDX.h"
#include"Audio.h"
#include"Constants.h"

class Game {
private:
	

	static  Graphics* m_graphics;
	static  Input* m_input;
	static TextDX* m_text;
	static Audio* m_audio;
	const int m_textNumber;

	HWND m_hWnd;//ウインドウハンドル
	HRESULT m_hr;//なんかの戻り値
	LARGE_INTEGER m_timeStart;//パフォーマンスカウンタの開始値
	LARGE_INTEGER m_timeEnd;//パフォーマンスカウンタの終了値
	LARGE_INTEGER m_timerFreq;//パフォーマンスカウンタの周波数
	float m_frameTime;//最後のフレームに要した時間
	float m_fps;//フレームレート
	DWORD m_sleepTime;//フレーム間でスリープする時間(mSec)
	bool m_initialized;//初期化済みならtrue
public:
	Game();
	virtual ~Game();
	//ウインドウズメッセージハンドラー
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//Graphics,Inputなど初期化
	virtual void initialize(HWND hwnd);
	//毎フレーム呼んでゲームを走らせる
	virtual void run(HWND hwnd);
	//グラフィックデバイス消失時に呼ぶ
	//
	virtual void releaseAll();
	//
	virtual void resetAll();
	//全ての予約済みメモリを解放
	virtual void deleteAll();
	//消失デバイスの処理？
	virtual void handleLostGraphicsDevice();

	virtual void setDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);

	//ゲット関数
	static Graphics* graphics() ;
	static Input* input();
	static TextDX* text(int index = 0);
	static Audio* audio();
	static LPD3DXSPRITE sprite();
	//ゲームから出る
	void exitGame();


	//純粋仮想関数
	//軽装クラスで実装必要あり
	virtual void update() = 0;
};













#endif

