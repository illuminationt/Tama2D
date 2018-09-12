#ifndef GAME_H
#define GAME_H
#define WIN32_LEAN_AND_MEAN

/*

Graphics,Input�N���X�ւ̃|�C���^�����N���X
���ꂩ����Q�[���̖{�̂ƂȂ�N���X�͂�����p���B
�Q�[���ɕK�v�Ȗ��t���[���Ă΂��֐��iupdate,AI,collision,render��
�����Œ�`���Ă����āA�Q�[���̃��C�����[�v�͂������Ɂi�������z�֐��̌`�ł���
�������Ă���B���Ƃ͌p����̃N���X�ł����4���I�[�o�[���C�h�����OK

render()��renderGame()�̒��ɓ����Ă��āArenderGame�̕���
BeginScene�Ƃ��͂���Ă���B�����render���͕`��ɐ�O����΂���

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

	HWND m_hWnd;//�E�C���h�E�n���h��
	HRESULT m_hr;//�Ȃ񂩂̖߂�l
	LARGE_INTEGER m_timeStart;//�p�t�H�[�}���X�J�E���^�̊J�n�l
	LARGE_INTEGER m_timeEnd;//�p�t�H�[�}���X�J�E���^�̏I���l
	LARGE_INTEGER m_timerFreq;//�p�t�H�[�}���X�J�E���^�̎��g��
	float m_frameTime;//�Ō�̃t���[���ɗv��������
	float m_fps;//�t���[�����[�g
	DWORD m_sleepTime;//�t���[���ԂŃX���[�v���鎞��(mSec)
	bool m_initialized;//�������ς݂Ȃ�true
public:
	Game();
	virtual ~Game();
	//�E�C���h�E�Y���b�Z�[�W�n���h���[
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//Graphics,Input�ȂǏ�����
	virtual void initialize(HWND hwnd);
	//���t���[���Ă�ŃQ�[���𑖂点��
	virtual void run(HWND hwnd);
	//�O���t�B�b�N�f�o�C�X�������ɌĂ�
	//
	virtual void releaseAll();
	//
	virtual void resetAll();
	//�S�Ă̗\��ς݃����������
	virtual void deleteAll();
	//�����f�o�C�X�̏����H
	virtual void handleLostGraphicsDevice();

	virtual void setDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);

	//�Q�b�g�֐�
	static Graphics* graphics() ;
	static Input* input();
	static TextDX* text(int index = 0);
	static Audio* audio();
	static LPD3DXSPRITE sprite();
	//�Q�[������o��
	void exitGame();


	//�������z�֐�
	//�y���N���X�Ŏ����K�v����
	virtual void update() = 0;
};













#endif

