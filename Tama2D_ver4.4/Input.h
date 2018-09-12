#ifndef INPUT_H
#define INPUT_H
#define WIN32_LEAN_AND_MEAN

#include<Windows.h>
#include<windowsx.h>
#include<XInput.h>
#include<string>
#include"Constants.h"


// for high-definition mouse
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC      ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE     ((USHORT) 0x02)
#endif
//--------------------------



namespace inputNS {
	const int KEYS_ARRAY_LEN = 256;

	//どの情報をクリアしますか？ フラグです
	const UCHAR KEYS_DOWN = 1;
	const UCHAR KEYS_PRESSED = 2;
	const UCHAR MOUSE = 4;
	const UCHAR TEXT_IN = 8;
	const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN | KEYS_PRESSED | MOUSE | TEXT_IN;
}
const DWORD MAX_CONTROLLERS = 4;
const DWORD GAMEPAD_THUMBSTICK_DEADZONE = (DWORD)(0.2f * 0X7FFF);
const DWORD GAMEPAD_TRIGGER_DEADZONE = 30;

//ゲームパッドのボタン。DPAD=DirectionPad
//既にXINPUT_GAMEPAD_Aとかがあるのに定義し直す？
const DWORD GAMEPAD_DPAD_UP        = 0x0001;
const DWORD GAMEPAD_DPAD_DOWN      = 0x0002;
const DWORD GAMEPAD_DPAD_LEFT      = 0x0004;
const DWORD GAMEPAD_DPAD_RIGHT     = 0x0008;
const DWORD GAMEPAD_START          = 0x0010;
const DWORD GAMEPAD_BACK           = 0x0020;
const DWORD GAMEPAD_LEFT_THUMB     = 0x0040;
const DWORD GAMEPAD_RIGHT_THUMB    = 0x0080;
const DWORD GAMEPAD_LEFT_SHOULDER  = 0x0100;
const DWORD GAMEPAD_RIGHT_SHOULDER = 0x0200;
const DWORD GAMEPAD_A              = 0x1000;
const DWORD GAMEPAD_B              = 0x2000;
const DWORD GAMEPAD_X              = 0x4000;
const DWORD GAMEPAD_Y              = 0x8000;

struct ControllerState {
	XINPUT_STATE state;
	XINPUT_VIBRATION vibration;
	float vibrateTimeLeft; //ミリ秒
	float vibrateTimeRight;//ミリ秒
	bool connected;
};

class Input {
private:
	bool m_keysDown[inputNS::KEYS_ARRAY_LEN]; //押されてたらtrue
	bool m_keysPressed[inputNS::KEYS_ARRAY_LEN];//直近のフレームで押されてたらtrue
	
	std::string m_textIn;     //入力されたテキスト
	char m_charIn;            //最後に入力された文字
	bool m_newLine; //何これ
	
	int m_mouseX, m_mouseY;//マウスの座標
	int m_mouseRawX, m_mouseRawY;//マウスの移動量。高解像度マウス対応
	RAWINPUTDEVICE Rid[1];//高解像度マウスのためのやつ。よくわからん
	bool m_mouseCaptured;//マウス、キャプチャされてる？
	bool m_mouseLButton;//左クリックされてる？
	bool m_mouseRButton;//右クリックされてる？
	bool m_mouseMButton;//Middleクリックされてる？
	bool m_mouseX1Button;//X1ボタン押されてる？
	bool m_mouseX2Button;//X2ボタン押されてる？
	 
	ControllerState m_controllers[MAX_CONTROLLERS];

public:
	Input();
	virtual ~Input();
	//マウス、コントローラーの初期化
	void initialize(HWND hWnd, bool capture);
	//押されたキーのdown,pressedをtrueに
	void keyDown(WPARAM);
	//押されてないキーのdownをfalseに
	void keyUp(WPARAM);
	//押されたキーの文字をcharIn,textInに保存
	void keyIn(WPARAM);
	//そのキーはdownですか？
	bool isKeyDown(UCHAR vkey)const;
	//そのキーはpressedですか？
	bool wasKeyPressed(UCHAR vkey)const;
	//どれかはpressedですか？
	bool anyKeyPressd()const;
	//そのキーがpressedという情報をクリアー
	void clearKeyPress(UCHAR vkey);
	//特定デバイスからの入力をfalseに
	void clear(UCHAR what);

	//全てのデバイスの入力をfalseに
	void clearAll() { clear(inputNS::KEYS_MOUSE_TEXT); };

	//テキストを空に
	void clearTextIn() { m_textIn.clear(); };

	//テキストを返す
	const std::string* textIn()const  { return &m_textIn; };

	//最後に押された文字m_charInを返す
	char charIn() { return m_charIn; };

	//マウスの座標をm_mouseX,m_mouseYに読み込む
	void mouseIn(LPARAM);

	//マウスの移動量をm_mouseRawXとかに読み込む
	//高解像度マウス対応
	void mouseRawIn(LPARAM);

	//左クリックの状態をm_mouseLButtonに読み込む
	void setMouseLButton(bool b) { m_mouseLButton = b; };
	//右クリックの状態をm_mouseRButtonに読み込む
	void setMouseRButton(bool b) { m_mouseRButton = b; };
	//ミドルクリックの状態をm_mouseMButtonに読み込む
	void setMouseMButton(bool b) { m_mouseMButton = b; };
	//Xボタンの状態をm_mouseX1Buttonとかに読み込む
	void setMouseXButton(WPARAM wParam) {m_mouseX1Button = (wParam&MK_XBUTTON1) ? true : false;
										 m_mouseX2Button = (wParam&MK_XBUTTON2) ? true : false;};
	//マウスの座標を返す
	int mouseX()const { return m_mouseX; };
	int mouseY()const { return m_mouseY; };
	//マウスの移動量を返す
	int mouseRawX()const { return m_mouseRawX; };
	int mouseRawY()const { return m_mouseRawY; };
	//マウスの各々のボタンのクリック状態を返す
	bool mouseLButton()const { return m_mouseLButton; };
	bool mouseRButton()const { return m_mouseRButton; };
	bool mouseMButton()const { return m_mouseMButton; };
	bool mouseX1Button()const { return m_mouseX1Button; };
	bool mouseX2Button()const { return m_mouseX2Button; };

	//XINPUT構造体のstateにコントローラー情報を格納
	void checkControllers();
	//コントローラーの情報をXINPUT構造体のstateに読み込み
	//上のやつとの違いはコード見ろ
	void readControllers();

	//ControllerState構造体のポインタを返す
	const ControllerState* controllerState(UINT index);
	//nボタンの情報(WORD(=unsigned short)のビットフラグ)を返す
	const WORD gamepadButtons(UINT n);

	//各々のボタンの状態を返す
	bool gamepadDPadUp(UINT index);
	bool gamepadDPadDown(UINT index);
	bool gamepadDPadLeft(UINT index);
	bool gamepadDPadRight(UINT index);
	bool gamepadStart(UINT index);
	bool gamepadBack(UINT index);
	bool gamepadLeftThumb(UINT index);
	bool gamepadRightThumb(UINT index);
	bool gamepadLeftShoulder(UINT index);
	bool gamepadRightShoulder(UINT index);
	bool gamepadA(UINT index);
	bool gamepadB(UINT index);
	bool gamepadX(UINT index);
	bool gamepadY(UINT index);
	
	//左右トリガーをBYTEで返す
	BYTE gamepadLeftTrigger(UINT index);
	BYTE gamepadRightTrigger(UINT index);
	//左右サムスティックの値をSHORTを返す
	SHORT gamepadThumbLX(UINT index);
	SHORT gamepadThumbLY(UINT index);
	SHORT gamepadThumbRX(UINT index);
	SHORT gamepadThumbRY(UINT index);

	//コントローラーのモーターを振動
	//左は低周波。speed: 振動の強さ.sec:振動時間(秒）
	void gamepadVibrateLeft(UINT index, WORD speed, float sec);
	void gamepadVibrateRight(UINT index, WORD speed, float sec);

	void vibrateControllers(float frameTime);

	bool isControllerConnected(UINT index)const;
};








#endif