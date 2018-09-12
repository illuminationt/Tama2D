#include"Input.h"

Input::Input() :
	m_newLine(true),//テキスト、新しい行から始める？
	m_textIn(""),
	m_charIn(0),
	m_mouseX(0),
	m_mouseY(0),
	m_mouseRawX(0),
	m_mouseRawY(0),
	m_mouseLButton(false),
	m_mouseRButton(false),
	m_mouseMButton(false),
	m_mouseX1Button(false),
	m_mouseX2Button(false){

	for (int j = 0; j < inputNS::KEYS_ARRAY_LEN; j++) {
		m_keysDown[j] = false;
		m_keysPressed[j] = false;
	}
	for (int j = 0; j < MAX_CONTROLLERS; j++) {
		//これから振動する時間
		m_controllers[j].vibrateTimeLeft = 0;
		m_controllers[j].vibrateTimeRight = 0;
	}
}

Input::~Input() {
	if (m_mouseCaptured) {
		//TODO:なんかこういう関数？
		ReleaseCapture();
	}
}

//captureは高精度マウスをキャプチャするかどうか。
void Input::initialize(HWND hWnd, bool capture) {
	try {
//なんかこのtryブロックの中身、考えるの大変だから
//また後で考えるわ～とりあえずコピペよ～ん
		m_mouseCaptured = capture;
		
		//高精度マウスの登録
		Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
		Rid[0].dwFlags = RIDEV_INPUTSINK;
		Rid[0].hwndTarget = hWnd;
		RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

		if (m_mouseCaptured) {
			SetCapture(hWnd);
		}
		ZeroMemory(m_controllers, sizeof(ControllerState)*MAX_CONTROLLERS);
		//自作関数.
		checkControllers();

	}
	catch (...) {
		WARN("Error initializing input system");
	}
}

//
void Input::keyDown(WPARAM wParam) {
	if (wParam < inputNS::KEYS_ARRAY_LEN) {
		m_keysDown[wParam] = true;
		m_keysPressed[wParam] = true;
	}
}
//そのキーがUp(押されてない）かどうかチェック。
//押されてたらfalse
void Input::keyUp(WPARAM wParam) {
	//wParamが常識範囲内なら
	if (wParam < inputNS::KEYS_ARRAY_LEN) {
		m_keysDown[wParam] = false;
	}
}

//m_textInに入力された文字列を保存
void Input::keyIn(WPARAM wParam) {
	if (m_newLine) {
		m_textIn.clear();
		m_newLine = false;
	}
	if (wParam == '\b') {//バックスペースキー
		if (m_textIn.length() > 0) {
			m_textIn.erase(m_textIn.size() - 1);
		}
	}
	else {
		m_textIn += wParam;
		m_charIn = wParam;
	}

	if ((char)wParam == '\r') {//エンターキー
		m_newLine = true;
	}
}

//そのキーが押されてたらtrue,押されてないならfalse
bool Input::isKeyDown(UCHAR vkey)const {
	if (vkey < inputNS::KEYS_ARRAY_LEN) {
		return m_keysDown[vkey];
	}
	else {
		return false;
	}
}
//そのキーが前のフレームに初めて押されたならtrue
//[キーが押された]という記録は毎フレーム最後に消される(具体的にはGame::run関数で)
bool Input::wasKeyPressed(UCHAR vkey)const {
	if (vkey < inputNS::KEYS_ARRAY_LEN) {
		return m_keysPressed[vkey];
	}
	else {
		return false;
	}
}
//何でもいいから前フレームに新しく押されたらtrue
bool Input::anyKeyPressd()const {
	for (int j = 0; j < inputNS::KEYS_ARRAY_LEN; j++) {
		if (m_keysPressed[j]) {
			return true;
		}
	}
	return false;
}
//「前フレームにそのキーが押された」という情報を消す
void Input::clearKeyPress(UCHAR vkey) {
	if (vkey < inputNS::KEYS_ARRAY_LEN) {
		m_keysPressed[vkey] = false;
	}
}

//あるインプットデバイスの「押された情報」を消す
//what : どのデバイスの情報を消す？
//input.hに値が定義してあります
void Input::clear(UCHAR what) {
	if (what&inputNS::KEYS_DOWN) {
		for (int j = 0; j < inputNS::KEYS_ARRAY_LEN; j++) {
			m_keysDown[j] = false;
		}
	}
	if (what&inputNS::KEYS_PRESSED) {
		for (int j = 0; j < inputNS::KEYS_ARRAY_LEN; j++) {
			m_keysPressed[j] = false;
		}
	}
	if (what&inputNS::MOUSE) {
		m_mouseX = m_mouseY = 0;
		m_mouseRawX = m_mouseRawY = 0;
	}
	if (what&inputNS::TEXT_IN) {
		clearTextIn();
	}
}

//スクリーン上のマウスの位置をm_mouseX,m_mouseYに格納
void Input::mouseIn(LPARAM lParam) {
	m_mouseX = GET_X_LPARAM(lParam);
	m_mouseY = GET_Y_LPARAM(lParam);
}
//TODO: なにこれ～～～
void Input::mouseRawIn(LPARAM lParam) {
	UINT dwSize = 40;
	static BYTE lpb[40];

	GetRawInputData((HRAWINPUT)lParam, RID_INPUT,
		lpb, &dwSize, sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)lpb;

	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		m_mouseRawX = raw->data.mouse.lLastX;
		m_mouseRawY = raw->data.mouse.lLastY;
	}
}

//コントローラーの状態（どのボタンが押されてるかとか）をチェック
//つながってたらtrue
void Input::checkControllers() {
	DWORD result;
	for (DWORD j = 0; j < MAX_CONTROLLERS; j++) {
		result = XInputGetState(j, &m_controllers[j].state);
		if (result==ERROR_SUCCESS) {
			//TODO: SUCCEEDED(result)ではダメ？
			m_controllers[j].connected = true;
		}
		else {
			m_controllers[j].connected = false;
		}

	}
}
//繋がってなかったらfalse
//コントローラーの状態をm_controllersに読み込む
void Input::readControllers() {
	DWORD result;
	for (DWORD j = 0; j < MAX_CONTROLLERS; j++) {
		if (m_controllers[j].connected) {
			result = XInputGetState(j, &m_controllers[j].state);
			if (result == ERROR_DEVICE_NOT_CONNECTED) {
				m_controllers[j].connected = false;
			}
		}
	}
}

const ControllerState* Input::controllerState(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return &m_controllers[index];
}
const WORD Input::gamepadButtons(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index=MAX_CONTROLLERS - 1;
	}
	return m_controllers[index].state.Gamepad.wButtons;
}
bool Input::gamepadDPadUp(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return (gamepadButtons(index)&GAMEPAD_DPAD_UP) != 0;
}
bool Input::gamepadDPadDown(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return (gamepadButtons(index)&GAMEPAD_DPAD_DOWN) != 0;
}
bool Input::gamepadDPadLeft(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return (gamepadButtons(index)&GAMEPAD_DPAD_LEFT) != 0;
}
bool Input::gamepadDPadRight(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return (gamepadButtons(index)&GAMEPAD_DPAD_RIGHT) != 0;
}
bool Input::gamepadStart(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return (gamepadButtons(index)&GAMEPAD_START) != 0;
}
bool Input::gamepadBack(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return (gamepadButtons(index)&GAMEPAD_BACK) != 0;
}
bool Input::gamepadLeftThumb(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
index = MAX_CONTROLLERS - 1;
	}
	return (gamepadButtons(index)&GAMEPAD_LEFT_THUMB) != 0;
}
bool Input::gamepadRightThumb(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return (gamepadButtons(index)&GAMEPAD_RIGHT_THUMB) != 0;
}
bool Input::gamepadLeftShoulder(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return (gamepadButtons(index)&GAMEPAD_LEFT_SHOULDER) != 0;
}
bool Input::gamepadRightShoulder(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return (gamepadButtons(index)&GAMEPAD_RIGHT_SHOULDER) != 0;
}
bool Input::gamepadA(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return (gamepadButtons(index)&GAMEPAD_A) != 0;
}
bool Input::gamepadB(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return (gamepadButtons(index)&GAMEPAD_B) != 0;
}
bool Input::gamepadX(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return (gamepadButtons(index)&GAMEPAD_X) != 0;
}
bool Input::gamepadY(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return (gamepadButtons(index)&GAMEPAD_Y) != 0;
}

BYTE Input::gamepadLeftTrigger(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return m_controllers[index].state.Gamepad.bLeftTrigger;
}
BYTE Input::gamepadRightTrigger(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return m_controllers[index].state.Gamepad.bRightTrigger;
}
SHORT Input::gamepadThumbLX(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return m_controllers[index].state.Gamepad.sThumbLX;
}
SHORT Input::gamepadThumbLY(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return m_controllers[index].state.Gamepad.sThumbLY;
}
SHORT Input::gamepadThumbRX(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return m_controllers[index].state.Gamepad.sThumbRX;
}
SHORT Input::gamepadThumbRY(UINT index) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	return m_controllers[index].state.Gamepad.sThumbRY;
}

void Input::gamepadVibrateLeft(UINT index, WORD speed, float sec) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	m_controllers[index].vibration.wLeftMotorSpeed = speed;
	m_controllers[index].vibrateTimeLeft = sec;
}
void Input::gamepadVibrateRight(UINT index, WORD speed, float sec) {
	if (index > MAX_CONTROLLERS - 1) {
		index = MAX_CONTROLLERS - 1;
	}
	m_controllers[index].vibration.wLeftMotorSpeed = speed;
	m_controllers[index].vibrateTimeLeft = sec;
}

void Input::vibrateControllers(float frameTime) {
	for (int j = 0; j < MAX_CONTROLLERS; j++) {
		if (m_controllers[j].connected) {

			m_controllers[j].vibrateTimeLeft -= frameTime;
			if (m_controllers[j].vibrateTimeLeft < 0) {
				m_controllers[j].vibrateTimeLeft = 0;
				m_controllers[j].vibration.wLeftMotorSpeed = 0;
			}

			m_controllers[j].vibrateTimeRight -= frameTime;
			if (m_controllers[j].vibrateTimeRight < 0) {
				m_controllers[j].vibrateTimeRight = 0;
				m_controllers[j].vibration.wRightMotorSpeed = 0;
			}

			XInputSetState(j, &m_controllers[j].vibration);
		}
	}
}

bool Input::isControllerConnected(UINT index)const {
	return m_controllers[0].connected;
}