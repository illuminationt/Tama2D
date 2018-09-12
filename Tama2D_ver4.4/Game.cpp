#include"Game.h"
#include"Constants.h"

#include"Root.h"
#include<sstream>

Graphics* Game::m_graphics = 0;
Input* Game::m_input = 0;
TextDX* Game::m_text = 0;
Audio* Game::m_audio = 0;

Game::Game() :
	m_textNumber(2),//使うフォントの種類の数
	m_hWnd(0),
	m_hr(0),
	m_frameTime(-1),//ありえない値入れときます
	m_fps(-1),
	m_sleepTime(-1),
	m_initialized(false) {
	//とにもかくにもキーボード入力を即時に初期化
	//その他の処理はm_input->initialize()でどうぞ
	m_input = new Input();
	m_text=new TextDX();
	m_audio = new Audio();
	

	
}
Game::~Game() {
	releaseAll();
	DELETE(m_graphics);
	DELETE(m_input);
	DELETE(m_text);
	DELETE(m_audio);
	m_initialized = false;//予約されていたメモリを全て解放
	ShowCursor(true);//TODO:なにこれ。カーソルを表示
}

LRESULT Game::messageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	//初期化されてなかったらmsgを処理しない
	if (m_initialized) {
		switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN://キーが押された
			m_input->keyDown(wParam);
			return 0;
		case WM_KEYUP:
		case WM_SYSKEYUP://キーが離された
			m_input->keyUp(wParam);
			return 0;
		case WM_CHAR://文字が入力された
			m_input->keyIn(wParam);
			return 0;
		case WM_MOUSEMOVE://これは高解像度マウスに対応しない
			m_input->mouseIn(lParam);
			return 0;
		case WM_INPUT://高解像度マウス対応
			m_input->mouseRawIn(lParam);
			return 0;
		case WM_LBUTTONDOWN:
			m_input->setMouseLButton(true);
			m_input->mouseIn(lParam);
			return 0;
		case WM_LBUTTONUP:
			m_input->setMouseLButton(false);
			m_input->mouseIn(lParam);
			return 0;
		case WM_RBUTTONDOWN:
			m_input->setMouseRButton(true);
			m_input->mouseIn(lParam);
			return 0;
		case WM_RBUTTONUP:
			m_input->setMouseRButton(false);
			m_input->mouseIn(lParam);
			return 0;
		case WM_MBUTTONDOWN:
			m_input->setMouseMButton(true);
			m_input->mouseIn(lParam);
			return 0;
		case WM_MBUTTONUP:
			m_input->setMouseMButton(false);
			m_input->mouseIn(lParam);
			return 0;
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
			m_input->setMouseXButton(wParam);
			m_input->mouseIn(lParam);
			return 0;
		case WM_DEVICECHANGE://TODO　なにこれ
							 //コントローラをチェック
			m_input->checkControllers();
			return 0;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//ゲームを初期化
//このhWndはm_graphics、m_inputの初期化に必要
void Game::initialize(HWND hWnd) {
	m_hWnd = hWnd;
	//グラフィックスを初期化
	m_graphics = new Graphics(hWnd);
	//マウス入力を準備
	m_input->initialize(m_hWnd, false);
	//テキストを全て初期化
	if (!m_text->initialize(m_graphics, 0xffffffff,WINDOW_HEIGHT/18, true, false, "Courier")) {
		WARN("couldn't initialize m_text0");
	}
	//オーディオシステム初期化
	HRESULT hr = m_audio->initialize();
	if (FAILED(hr)) {
		if (m_hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) {
			WARN("failed to initialize sound system because media file not found");
		}
		else {
			WARN("failed to initialize sonud system wwww lol lol");
		}
	}
	

	//パフォーマンスカウンタの周波数を取得！
	if (QueryPerformanceFrequency(&m_timerFreq) == false) {

	}
	//パフォーマンスカウンタの開始時刻を取得
	QueryPerformanceCounter(&m_timeStart);

	m_initialized = true;
}




//begin
//消失デバイスの処理
void Game::handleLostGraphicsDevice() {
	m_hr = m_graphics->getDeviceState();
	if (FAILED(m_hr)) {//m_hrがD3D_OKじゃない
					   //デバイスが消失 かつリセットできない状態
		if (m_hr == D3DERR_DEVICELOST) {
			Sleep(100);//デバイスがリセットできる状態に復帰するまで待機
			return;
		}//デバイス消失、しかしリセットできる状態
		else if (m_hr == D3DERR_DEVICENOTRESET) {
			releaseAll();
			m_hr = m_graphics->reset();//グラフィックスデバイスをリセット
			if (FAILED(m_hr)) {
				return;
			}
			//ゲームのエンティティとかリセット
			resetAll();
		}
		else {
			return;//他のデバイスエラー
		}
	}
}

void Game::setDisplayMode(graphicsNS::DISPLAY_MODE mode) {
	releaseAll();
	m_graphics->changeDisplayMode(mode);
	resetAll();
}


//ゲット関数
Graphics* Game::graphics(){ return m_graphics; };
Input* Game::input(){ return m_input; };
TextDX* Game::text(int index){ return m_text; };
Audio* Game::audio() { return m_audio; };
LPD3DXSPRITE Game::sprite() { return m_graphics->sprite(); };

//ゲームから出る
void Game::exitGame() { PostMessage(m_hWnd, WM_DESTROY, 0, 0); };




//WinMainから毎フレーム呼ぶ
void Game::run(HWND hWnd) {
	if (m_graphics == NULL) {
		return;
	}
	//最後のフレームにかかった時間を計算し、m_frameTimeに格納
	QueryPerformanceCounter(&m_timeEnd);
	m_frameTime = (float)(m_timeEnd.QuadPart - m_timeStart.QuadPart) /
		(float)m_timerFreq.QuadPart;
	//省電力のためのコード。winmm.libを入力しろ
	
	if (m_frameTime < MIN_FRAME_TIME) {
		m_sleepTime = (DWORD)((MIN_FRAME_TIME - m_frameTime) * 1000);
		timeBeginPeriod(1);//1mSecの分解能をWIndowsタイマーに要求するだけの関数
		Sleep(m_sleepTime);//おやすみ
		timeEndPeriod(1);//1mSec分解能終了
		return;
	}
	
	if (m_frameTime > 0.0) {//TODO:なにこれ
		m_fps = (m_fps*0.99f) + (0.01f / m_frameTime);
	}
	//フレームレートが超遅い場合
	if (m_frameTime > MAX_FRAME_TIME) {
		m_frameTime = MAX_FRAME_TIME;
	}
	//今フレームの終了時刻を次フレームの開始時刻とする
	m_timeStart = m_timeEnd;


	//===============主要部===================//


	//ここから下がrunのメイン
	m_audio->run();//オーディオ再生に必要
	//シーン開始
	if (SUCCEEDED(m_graphics->beginScene())) {
		//純粋仮想関数. 継承クラスでupdate
		update();


		//FPS表示
		std::ostringstream oss;
		oss << "FPS : " << m_fps;
		text()->print(oss.str().c_str(), WINDOW_WIDTH-200, WINDOW_HEIGHT-40);
		
		//シーン終了
		m_graphics->endScene();
	}
	handleLostGraphicsDevice();

	//バックバッファをメインスクリーンへ
	m_graphics->showBackBuffer();
	m_input->readControllers();

	//ウインドウ切り替え処理
	if (m_input->isKeyDown(VK_MENU) && m_input->isKeyDown(VK_RETURN)) {
		setDisplayMode(graphicsNS::TOGGLE);
	}

	//ESCキーを押したらウインドウモード
	if (m_input->isKeyDown(VK_ESCAPE)) {
		setDisplayMode(graphicsNS::WINDOW);
	}

	//全てのキーチェックが行われた後これを呼び出す
	m_input->clear(inputNS::KEYS_PRESSED);
}

void Game::releaseAll() {

}
void Game::resetAll() {

}
void Game::deleteAll() {
	releaseAll();
	DELETE(m_graphics);
	DELETE(m_input);
	m_initialized = false;
}
