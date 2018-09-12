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

	//�ǂ̏����N���A���܂����H �t���O�ł�
	const UCHAR KEYS_DOWN = 1;
	const UCHAR KEYS_PRESSED = 2;
	const UCHAR MOUSE = 4;
	const UCHAR TEXT_IN = 8;
	const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN | KEYS_PRESSED | MOUSE | TEXT_IN;
}
const DWORD MAX_CONTROLLERS = 4;
const DWORD GAMEPAD_THUMBSTICK_DEADZONE = (DWORD)(0.2f * 0X7FFF);
const DWORD GAMEPAD_TRIGGER_DEADZONE = 30;

//�Q�[���p�b�h�̃{�^���BDPAD=DirectionPad
//����XINPUT_GAMEPAD_A�Ƃ�������̂ɒ�`�������H
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
	float vibrateTimeLeft; //�~���b
	float vibrateTimeRight;//�~���b
	bool connected;
};

class Input {
private:
	bool m_keysDown[inputNS::KEYS_ARRAY_LEN]; //������Ă���true
	bool m_keysPressed[inputNS::KEYS_ARRAY_LEN];//���߂̃t���[���ŉ�����Ă���true
	
	std::string m_textIn;     //���͂��ꂽ�e�L�X�g
	char m_charIn;            //�Ō�ɓ��͂��ꂽ����
	bool m_newLine; //������
	
	int m_mouseX, m_mouseY;//�}�E�X�̍��W
	int m_mouseRawX, m_mouseRawY;//�}�E�X�̈ړ��ʁB���𑜓x�}�E�X�Ή�
	RAWINPUTDEVICE Rid[1];//���𑜓x�}�E�X�̂��߂̂�B�悭�킩���
	bool m_mouseCaptured;//�}�E�X�A�L���v�`������Ă�H
	bool m_mouseLButton;//���N���b�N����Ă�H
	bool m_mouseRButton;//�E�N���b�N����Ă�H
	bool m_mouseMButton;//Middle�N���b�N����Ă�H
	bool m_mouseX1Button;//X1�{�^��������Ă�H
	bool m_mouseX2Button;//X2�{�^��������Ă�H
	 
	ControllerState m_controllers[MAX_CONTROLLERS];

public:
	Input();
	virtual ~Input();
	//�}�E�X�A�R���g���[���[�̏�����
	void initialize(HWND hWnd, bool capture);
	//�����ꂽ�L�[��down,pressed��true��
	void keyDown(WPARAM);
	//������ĂȂ��L�[��down��false��
	void keyUp(WPARAM);
	//�����ꂽ�L�[�̕�����charIn,textIn�ɕۑ�
	void keyIn(WPARAM);
	//���̃L�[��down�ł����H
	bool isKeyDown(UCHAR vkey)const;
	//���̃L�[��pressed�ł����H
	bool wasKeyPressed(UCHAR vkey)const;
	//�ǂꂩ��pressed�ł����H
	bool anyKeyPressd()const;
	//���̃L�[��pressed�Ƃ��������N���A�[
	void clearKeyPress(UCHAR vkey);
	//����f�o�C�X����̓��͂�false��
	void clear(UCHAR what);

	//�S�Ẵf�o�C�X�̓��͂�false��
	void clearAll() { clear(inputNS::KEYS_MOUSE_TEXT); };

	//�e�L�X�g�����
	void clearTextIn() { m_textIn.clear(); };

	//�e�L�X�g��Ԃ�
	const std::string* textIn()const  { return &m_textIn; };

	//�Ō�ɉ����ꂽ����m_charIn��Ԃ�
	char charIn() { return m_charIn; };

	//�}�E�X�̍��W��m_mouseX,m_mouseY�ɓǂݍ���
	void mouseIn(LPARAM);

	//�}�E�X�̈ړ��ʂ�m_mouseRawX�Ƃ��ɓǂݍ���
	//���𑜓x�}�E�X�Ή�
	void mouseRawIn(LPARAM);

	//���N���b�N�̏�Ԃ�m_mouseLButton�ɓǂݍ���
	void setMouseLButton(bool b) { m_mouseLButton = b; };
	//�E�N���b�N�̏�Ԃ�m_mouseRButton�ɓǂݍ���
	void setMouseRButton(bool b) { m_mouseRButton = b; };
	//�~�h���N���b�N�̏�Ԃ�m_mouseMButton�ɓǂݍ���
	void setMouseMButton(bool b) { m_mouseMButton = b; };
	//X�{�^���̏�Ԃ�m_mouseX1Button�Ƃ��ɓǂݍ���
	void setMouseXButton(WPARAM wParam) {m_mouseX1Button = (wParam&MK_XBUTTON1) ? true : false;
										 m_mouseX2Button = (wParam&MK_XBUTTON2) ? true : false;};
	//�}�E�X�̍��W��Ԃ�
	int mouseX()const { return m_mouseX; };
	int mouseY()const { return m_mouseY; };
	//�}�E�X�̈ړ��ʂ�Ԃ�
	int mouseRawX()const { return m_mouseRawX; };
	int mouseRawY()const { return m_mouseRawY; };
	//�}�E�X�̊e�X�̃{�^���̃N���b�N��Ԃ�Ԃ�
	bool mouseLButton()const { return m_mouseLButton; };
	bool mouseRButton()const { return m_mouseRButton; };
	bool mouseMButton()const { return m_mouseMButton; };
	bool mouseX1Button()const { return m_mouseX1Button; };
	bool mouseX2Button()const { return m_mouseX2Button; };

	//XINPUT�\���̂�state�ɃR���g���[���[�����i�[
	void checkControllers();
	//�R���g���[���[�̏���XINPUT�\���̂�state�ɓǂݍ���
	//��̂�Ƃ̈Ⴂ�̓R�[�h����
	void readControllers();

	//ControllerState�\���̂̃|�C���^��Ԃ�
	const ControllerState* controllerState(UINT index);
	//n�{�^���̏��(WORD(=unsigned short)�̃r�b�g�t���O)��Ԃ�
	const WORD gamepadButtons(UINT n);

	//�e�X�̃{�^���̏�Ԃ�Ԃ�
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
	
	//���E�g���K�[��BYTE�ŕԂ�
	BYTE gamepadLeftTrigger(UINT index);
	BYTE gamepadRightTrigger(UINT index);
	//���E�T���X�e�B�b�N�̒l��SHORT��Ԃ�
	SHORT gamepadThumbLX(UINT index);
	SHORT gamepadThumbLY(UINT index);
	SHORT gamepadThumbRX(UINT index);
	SHORT gamepadThumbRY(UINT index);

	//�R���g���[���[�̃��[�^�[��U��
	//���͒���g�Bspeed: �U���̋���.sec:�U������(�b�j
	void gamepadVibrateLeft(UINT index, WORD speed, float sec);
	void gamepadVibrateRight(UINT index, WORD speed, float sec);

	void vibrateControllers(float frameTime);

	bool isControllerConnected(UINT index)const;
};








#endif