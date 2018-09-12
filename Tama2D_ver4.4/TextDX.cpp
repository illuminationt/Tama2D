#include "TextDX.h"
#include"Graphics.h"


TextDX::TextDX():
	m_graphics(0),
	m_color(0xff00ff00),
	m_dxFont(0),
	m_angle(0){
	//fontRect������
	m_fontRect.top = 0;
	m_fontRect.left = 0;
	m_fontRect.right = WINDOW_WIDTH;
	m_fontRect.bottom = WINDOW_HEIGHT;
}


TextDX::~TextDX(){
	SAFE_RELEASE(m_dxFont);
}

bool TextDX::initialize(
	Graphics* g,
	DWORD color,
	int height,
	bool bold,
	bool italic,
	const std::string& fontName) {
	m_graphics = g;
	UINT weight = FW_NORMAL;
	if (bold) {
		weight = FW_BOLD;
	}

	m_color = color;

	//DirectX�t�H���g�쐬
	HRESULT r;
	r = D3DXCreateFont(
		m_graphics->D3DDev(),
		height,
		0,
		weight,
		1,
		italic,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		fontName.c_str(),
		&m_dxFont);
	if (FAILED(r)) {
		WARN("failed to createFont");
		return false;
	}

	//�ϊ��s���������
	D3DXMatrixTransformation2D(&m_matrix, NULL, 0.f, NULL, NULL, 0.f,NULL);

	return true;
}

int TextDX::print(const std::string& str, int x, int y) {
	if (m_dxFont == NULL) {
		WARN("m_dxFont ==NULL");
	}
	m_fontRect.top = y;
	m_fontRect.left = x;

	//��]���S
	D3DXVECTOR2 center((float)x, (float)y);
	//��]�s�񐶐�
	D3DXMatrixTransformation2D(&m_matrix, NULL, 0.f, NULL, &center,m_angle,NULL);
	m_graphics->sprite()->SetTransform(&m_matrix);


	m_graphics->spriteBegin();

	int ret = 0;
	ret= m_dxFont->DrawTextA(m_graphics->sprite(), str.c_str(), -1, &m_fontRect, DT_LEFT, m_color);
	
	m_graphics->spriteEnd();
	
	return ret;
}

int TextDX::print(const std::string& str, RECT& rect, UINT format) {
	if (m_dxFont == NULL) {
		return 0;
	}
	//�e�L�X�g���͉̂�]�����Ȃ��irect����]����)
	//��]�����Ȃ����߂ɍs���ϊ����Ƃ�
	D3DXMatrixTransformation2D(&m_matrix, NULL, 0.f, NULL, NULL, 0.f, NULL);
	m_graphics->sprite()->SetTransform(&m_matrix);
	
	//�X�v���C�g�`�揀��
	m_graphics->spriteBegin();
	int ret = 0;
	ret= m_dxFont->DrawTextA(m_graphics->sprite(), str.c_str(), -1, &m_fontRect, format, m_color);
	m_graphics->spriteEnd();
	return ret;
}



void TextDX::onLostDevice() {
	if (m_dxFont == NULL) {
		return;
		m_dxFont->OnLostDevice();
	}
}

void TextDX::onResetDevice() {
	if (m_dxFont == NULL) {
		return;
	}
	m_dxFont->OnResetDevice();
}


//�Q�b�g�֐��Q
float TextDX::degrees() {
	return m_angle*(180.f / PI);
}
float TextDX::radians() {
	return m_angle;
}
DWORD TextDX::fontColor() {
	return m_color;
}

//�Z�b�g�֐��Q
void TextDX::setDegrees(float deg) {
	m_angle = deg*((float)PI / 180.f);
}
void TextDX::setRadians(float rad) {
	m_angle = rad;
}
void TextDX::setFontColor(DWORD c) {
	m_color = c;
}