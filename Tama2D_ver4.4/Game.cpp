#include"Game.h"
#include"Constants.h"

#include"Root.h"
#include<sstream>

Graphics* Game::m_graphics = 0;
Input* Game::m_input = 0;
TextDX* Game::m_text = 0;
Audio* Game::m_audio = 0;

Game::Game() :
	m_textNumber(2),//�g���t�H���g�̎�ނ̐�
	m_hWnd(0),
	m_hr(0),
	m_frameTime(-1),//���肦�Ȃ��l����Ƃ��܂�
	m_fps(-1),
	m_sleepTime(-1),
	m_initialized(false) {
	//�Ƃɂ������ɂ��L�[�{�[�h���͂𑦎��ɏ�����
	//���̑��̏�����m_input->initialize()�łǂ���
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
	m_initialized = false;//�\�񂳂�Ă�����������S�ĉ��
	ShowCursor(true);//TODO:�Ȃɂ���B�J�[�\����\��
}

LRESULT Game::messageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	//����������ĂȂ�������msg���������Ȃ�
	if (m_initialized) {
		switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN://�L�[�������ꂽ
			m_input->keyDown(wParam);
			return 0;
		case WM_KEYUP:
		case WM_SYSKEYUP://�L�[�������ꂽ
			m_input->keyUp(wParam);
			return 0;
		case WM_CHAR://���������͂��ꂽ
			m_input->keyIn(wParam);
			return 0;
		case WM_MOUSEMOVE://����͍��𑜓x�}�E�X�ɑΉ����Ȃ�
			m_input->mouseIn(lParam);
			return 0;
		case WM_INPUT://���𑜓x�}�E�X�Ή�
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
		case WM_DEVICECHANGE://TODO�@�Ȃɂ���
							 //�R���g���[�����`�F�b�N
			m_input->checkControllers();
			return 0;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//�Q�[����������
//����hWnd��m_graphics�Am_input�̏������ɕK�v
void Game::initialize(HWND hWnd) {
	m_hWnd = hWnd;
	//�O���t�B�b�N�X��������
	m_graphics = new Graphics(hWnd);
	//�}�E�X���͂�����
	m_input->initialize(m_hWnd, false);
	//�e�L�X�g��S�ď�����
	if (!m_text->initialize(m_graphics, 0xffffffff,WINDOW_HEIGHT/18, true, false, "Courier")) {
		WARN("couldn't initialize m_text0");
	}
	//�I�[�f�B�I�V�X�e��������
	HRESULT hr = m_audio->initialize();
	if (FAILED(hr)) {
		if (m_hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) {
			WARN("failed to initialize sound system because media file not found");
		}
		else {
			WARN("failed to initialize sonud system wwww lol lol");
		}
	}
	

	//�p�t�H�[�}���X�J�E���^�̎��g�����擾�I
	if (QueryPerformanceFrequency(&m_timerFreq) == false) {

	}
	//�p�t�H�[�}���X�J�E���^�̊J�n�������擾
	QueryPerformanceCounter(&m_timeStart);

	m_initialized = true;
}




//begin
//�����f�o�C�X�̏���
void Game::handleLostGraphicsDevice() {
	m_hr = m_graphics->getDeviceState();
	if (FAILED(m_hr)) {//m_hr��D3D_OK����Ȃ�
					   //�f�o�C�X������ �����Z�b�g�ł��Ȃ����
		if (m_hr == D3DERR_DEVICELOST) {
			Sleep(100);//�f�o�C�X�����Z�b�g�ł����Ԃɕ��A����܂őҋ@
			return;
		}//�f�o�C�X�����A���������Z�b�g�ł�����
		else if (m_hr == D3DERR_DEVICENOTRESET) {
			releaseAll();
			m_hr = m_graphics->reset();//�O���t�B�b�N�X�f�o�C�X�����Z�b�g
			if (FAILED(m_hr)) {
				return;
			}
			//�Q�[���̃G���e�B�e�B�Ƃ����Z�b�g
			resetAll();
		}
		else {
			return;//���̃f�o�C�X�G���[
		}
	}
}

void Game::setDisplayMode(graphicsNS::DISPLAY_MODE mode) {
	releaseAll();
	m_graphics->changeDisplayMode(mode);
	resetAll();
}


//�Q�b�g�֐�
Graphics* Game::graphics(){ return m_graphics; };
Input* Game::input(){ return m_input; };
TextDX* Game::text(int index){ return m_text; };
Audio* Game::audio() { return m_audio; };
LPD3DXSPRITE Game::sprite() { return m_graphics->sprite(); };

//�Q�[������o��
void Game::exitGame() { PostMessage(m_hWnd, WM_DESTROY, 0, 0); };




//WinMain���疈�t���[���Ă�
void Game::run(HWND hWnd) {
	if (m_graphics == NULL) {
		return;
	}
	//�Ō�̃t���[���ɂ����������Ԃ��v�Z���Am_frameTime�Ɋi�[
	QueryPerformanceCounter(&m_timeEnd);
	m_frameTime = (float)(m_timeEnd.QuadPart - m_timeStart.QuadPart) /
		(float)m_timerFreq.QuadPart;
	//�ȓd�͂̂��߂̃R�[�h�Bwinmm.lib����͂���
	
	if (m_frameTime < MIN_FRAME_TIME) {
		m_sleepTime = (DWORD)((MIN_FRAME_TIME - m_frameTime) * 1000);
		timeBeginPeriod(1);//1mSec�̕���\��WIndows�^�C�}�[�ɗv�����邾���̊֐�
		Sleep(m_sleepTime);//���₷��
		timeEndPeriod(1);//1mSec����\�I��
		return;
	}
	
	if (m_frameTime > 0.0) {//TODO:�Ȃɂ���
		m_fps = (m_fps*0.99f) + (0.01f / m_frameTime);
	}
	//�t���[�����[�g�����x���ꍇ
	if (m_frameTime > MAX_FRAME_TIME) {
		m_frameTime = MAX_FRAME_TIME;
	}
	//���t���[���̏I�����������t���[���̊J�n�����Ƃ���
	m_timeStart = m_timeEnd;


	//===============��v��===================//


	//�������牺��run�̃��C��
	m_audio->run();//�I�[�f�B�I�Đ��ɕK�v
	//�V�[���J�n
	if (SUCCEEDED(m_graphics->beginScene())) {
		//�������z�֐�. �p���N���X��update
		update();


		//FPS�\��
		std::ostringstream oss;
		oss << "FPS : " << m_fps;
		text()->print(oss.str().c_str(), WINDOW_WIDTH-200, WINDOW_HEIGHT-40);
		
		//�V�[���I��
		m_graphics->endScene();
	}
	handleLostGraphicsDevice();

	//�o�b�N�o�b�t�@�����C���X�N���[����
	m_graphics->showBackBuffer();
	m_input->readControllers();

	//�E�C���h�E�؂�ւ�����
	if (m_input->isKeyDown(VK_MENU) && m_input->isKeyDown(VK_RETURN)) {
		setDisplayMode(graphicsNS::TOGGLE);
	}

	//ESC�L�[����������E�C���h�E���[�h
	if (m_input->isKeyDown(VK_ESCAPE)) {
		setDisplayMode(graphicsNS::WINDOW);
	}

	//�S�ẴL�[�`�F�b�N���s��ꂽ�ケ����Ăяo��
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
