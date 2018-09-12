#ifndef AUDIO_H
#define AUDIO_H
#define WIN32_LEAN_AND_MEAN

#include<xact3.h>
#include"Constants.h"

class Audio {
private:
	IXACT3Engine* m_xactEngine;
	IXACT3WaveBank* m_waveBank;
	IXACT3SoundBank* m_soundBank;
	XACTINDEX m_cueI;

	void* m_mapWaveBank;
	void* m_soundBankData;
	bool m_coInitialized;

public:
	Audio();
	virtual ~Audio();
	//オーディオを初期化
	HRESULT initialize();
	//毎フレーム呼び出す
	void run();

	void playCue(const char* cueName);
	void stopCue(const char* cueName);
};













#endif