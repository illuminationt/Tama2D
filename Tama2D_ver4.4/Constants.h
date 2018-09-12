#ifndef CONSTANTS_H
#define CONSTANTS_H
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>

#define DELETE(ptr) {if(ptr){delete(ptr);(ptr)=0;}}
#define DELETE_ARRAY(ptr) {if(ptr){delete[](ptr);(ptr)=0;}}
#define SAFE_RELEASE(ptr) {if(ptr){(ptr)->Release();(ptr)=0;}}
static const char* CLASS_NAME = "game";
static const char* GAME_TITLE = "tama2D";

static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;
static const int WINDOW_COL_NUMBER = 16;//��ʓ��̃I�u�W�F�N�g�̍ŏ��P�ʂ̗�̐��i�u���b�N�����ɕ��Ԑ��j
static const int WINDOW_ROW_NUMBER = 15;//��ʓ��̍s�̐�
static const float HOR_MIN_UNIT = WINDOW_WIDTH / WINDOW_COL_NUMBER;//�������́A�`�悷��I�u�W�F�N�g�̍ŏ��P��
static const float VER_MIN_UNIT = WINDOW_HEIGHT / WINDOW_ROW_NUMBER;//�c�����́A�`�悷��I�u�W�F�N�g�̍ŏ��P��
static bool FULLSCREEN = false;

const double PI = 3.1415926535;
const float FRAME_RATE = 60.0f;
const float MIN_FRAME_RATE = 10.f;
const float MIN_FRAME_TIME = 1.f / FRAME_RATE;
const float MAX_FRAME_TIME = 1.f / MIN_FRAME_RATE;

//�I�[�f�B�I��
static const char* WAVE_BANK = "resource/audio/Wave Bank.xwb";
static const char* SOUND_BANK = "resource/audio/Sound Bank.xsb";

#define TRANSCOLOR 0x00ff00ff

static void WARN(const char* errMsg, const char* errTitle = "Error!") {
	MessageBoxA(NULL, errMsg, errTitle, MB_ICONSTOP);
}



static const int SCORE_GOOMBA = 100;
static const int SCORE_NOKO = 100;
static const int SCORE_COIN = 200;








#endif