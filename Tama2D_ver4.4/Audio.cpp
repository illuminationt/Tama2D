#include"Audio.h"

Audio::Audio():
	m_xactEngine(NULL),
	m_waveBank(NULL),
	m_soundBank(NULL),
	m_mapWaveBank(NULL),
	m_soundBankData(NULL),
	m_cueI(0){
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (SUCCEEDED(hr)) {
		m_coInitialized = true;
	}
	else {
		m_coInitialized = false;
	}
}

Audio::~Audio() {
	if (m_xactEngine) {
		m_xactEngine->ShutDown();
		m_xactEngine->Release();
	}

	if (m_soundBankData) {
		DELETE_ARRAY(m_soundBankData);
	}

	if (m_mapWaveBank) {
		UnmapViewOfFile(m_mapWaveBank);
	}
	m_mapWaveBank == NULL;

	if (m_coInitialized) {
		CoUninitialize();
	}
}




HRESULT Audio::initialize() {

	if (!m_coInitialized) {
		return E_FAIL;
	}
	//まずXACTオブジェクトへのポインタゲット
	HRESULT result;
	result = XACT3CreateEngine(0, &m_xactEngine);
	if (FAILED(result) || !m_xactEngine) {
		return E_FAIL;
	}
	//XACTエンジンの初期化に必要な初期化パラメータを含む構造体
	XACT_RUNTIME_PARAMETERS xactParams = {};
	xactParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
	result = m_xactEngine->Initialize(&xactParams);
	if (FAILED(result)) {
		return E_FAIL;
	}

	DWORD fileSize;
	DWORD bytesRead;
	HANDLE hMapFile;
	//ここまででm_xactEngineの初期化終了
	//次にインメモリのwave bankを作る
	HANDLE hFile = CreateFile(WAVE_BANK, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE) {
		fileSize = GetFileSize(hFile, NULL);
		if (fileSize != -1) {
			hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY,0,fileSize,NULL);
			if (hMapFile) {
				m_mapWaveBank = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
				if (m_mapWaveBank) {
					result = m_xactEngine->CreateInMemoryWaveBank(m_mapWaveBank, fileSize, 0, 0, &m_waveBank);
				
					CloseHandle(hMapFile);
				}
			}
		}
		CloseHandle(hFile);
	}
	if (FAILED(result)) {
		return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}
	//
	result = E_FAIL;
	hFile = CreateFile(SOUND_BANK, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE) {
		fileSize = GetFileSize(hFile, NULL);
		if (fileSize != -1) {
			m_soundBankData = new BYTE[fileSize];
			if (m_soundBankData) {
				if (ReadFile(hFile, m_soundBankData, fileSize, &bytesRead, NULL)) {
					result = m_xactEngine->CreateSoundBank(m_soundBankData, fileSize, 0, 0, &m_soundBank);
				}
			}
		}
		CloseHandle(hFile);
	}
	if (FAILED(result)) {
		return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}

	return S_OK;
}

void Audio::run() {
	if (m_xactEngine==NULL) {
		return;
	}
	m_xactEngine->DoWork();
}

void Audio::playCue(const char* cueName) {
	if (m_soundBank == NULL) {
		return;
	}
	m_cueI = m_soundBank->GetCueIndex(cueName);
	m_soundBank->Play(m_cueI, 0, 0, NULL);
}
void Audio::stopCue(const char* cueName) {
	if (m_soundBank == NULL) {
		return;
	}
	m_cueI = m_soundBank->GetCueIndex(cueName);
	m_soundBank->Stop(m_cueI, XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE);
}