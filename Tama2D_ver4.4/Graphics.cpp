#include "Graphics.h"
#include"Constants.h"


Graphics::Graphics(HWND hWnd) :
	m_D3D(NULL),
	m_D3DDev(NULL),
	m_texture(0),
	m_vertex(0),
	m_hWnd(hWnd),
	m_fullscreen(false),
	m_width(WINDOW_WIDTH),
	m_height(WINDOW_HEIGHT),
	m_backColor(0xff1e90ff){

	//Direct3D��������
	m_D3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_D3D) {
		WARN("m_pD3d���������ł��Ȃ�����www");
	}
	//D3DPRESENTATION_PARAMETERS��������
	initD3Dpp();

	if (FAILED(m_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3dpp, &m_D3DDev)))
		if (FAILED(m_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3dpp, &m_D3DDev)))
			if (FAILED(m_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3dpp, &m_D3DDev)))
				if (FAILED(m_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3dpp, &m_D3DDev)))
				{
					SAFE_RELEASE(m_D3D);
					WARN("createDevice�ŃG���[");
				}

	m_result = D3DXCreateSprite(m_D3DDev, &m_sprite);
	if (FAILED(m_result)) {
		WARN("rroororERROR");
	}

	//���_����
	if (FAILED(m_D3DDev->CreateVertexBuffer(sizeof(CUSTOMVERTEX) * 3, 0, D3DFVF_XYZRHW | D3DFVF_TEX1|D3DFVF_DIFFUSE, D3DPOOL_MANAGED, &m_vertex, NULL))) {
		m_D3DDev->Release();
		m_D3D->Release();
		WARN("vertexError", "�N�\�����^");
	}

}

Graphics::~Graphics(){
	releaseAll();
}

void Graphics::releaseAll() {
	SAFE_RELEASE(m_sprite);
	SAFE_RELEASE(m_D3DDev);
	SAFE_RELEASE(m_D3D);
}


HRESULT Graphics::loadTexture(
	const char* filename,
	LPDIRECT3DTEXTURE9& textureOut){
	//�t�@�C���̏����i�[����\����info
	D3DXIMAGE_INFO info;
	m_result = E_FAIL;

	try {
		if (filename == NULL) {
			m_texture = NULL;
			return D3DERR_INVALIDCALL;//TODO:�Ȃɂ���
		}
		//�t�@�C������info�Ƀe�N�X�`���̏��i�����A�~�b�v���x���̐��Ȃǁj���i�[
		m_result = D3DXGetImageInfoFromFile(filename, &info);
		if (FAILED(m_result)) {
			return m_result;
		}

		//��������info�Ƃ����g���āA
		//�t�@�C������e�N�X�`����ǂݍ���
		m_result = D3DXCreateTextureFromFileEx(
			m_D3DDev,
			filename,
			info.Width,
			info.Height,
			1, 0, D3DFMT_A8R8G8B8,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,//�����Ƃ��Ĉ����F���w��
			&info,
			NULL,
			&textureOut);
	}
	catch (...) {
		WARN("�e�N�X�`���ǂ߂Ȃ�");
	}
	return m_result;
}

void Graphics::draw(float* p1, float* p2, float* p3, float* t1, float* t2,float* t3) {
	if (t1 == NULL) {
		m_v[0] = { p1[0],p1[1],0.f,1.f,0x80ffffff,0.f,0.f };
		m_v[1] = { p2[0],p2[1],0.f,1.f,0x80ffffff,0.f,0.f };
		m_v[2] = { p3[0],p3[1],0.f,1.f,0x80ffffff,0.f,0.f};
	}
	else {
		m_v[0] = { p1[0],p1[1],0.f,1.f,0xffffffff,t1[0],t1[1] };
		m_v[1] = { p2[0],p2[1],0.f,1.f,0xffffffff,t2[0],t2[1] };
		m_v[2] = { p3[0],p3[1],0.f,1.f,0xffffffff,t3[0],t3[1] };
	}
	void* data;
	if (SUCCEEDED(m_vertex->Lock(0, sizeof(CUSTOMVERTEX) * 3, &data, 0))) {
		memcpy(data, m_v, sizeof(CUSTOMVERTEX) * 3);
		m_vertex->Unlock();

		//=============���炢���̃R�[�h======================//
		//����ӂ��Ԃꂎ
		m_D3DDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);// �����̐�������Z����
		m_D3DDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_D3DDev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

		m_D3DDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_D3DDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_D3DDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		//=====================================================//

		m_D3DDev->SetStreamSource(0, m_vertex, 0, sizeof(CUSTOMVERTEX));
		m_D3DDev->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1|D3DFVF_DIFFUSE);
		m_D3DDev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);
		
	}
}

void Graphics::setTexture(LPDIRECT3DTEXTURE9 tex)const {
	m_D3DDev->SetTexture(0, tex);
}


const LPDIRECT3DDEVICE9 Graphics::D3DDev()const {
	return m_D3DDev;
}
const LPD3DXSPRITE Graphics::sprite()const {
	return m_sprite;
}

void Graphics::initD3Dpp() {
	//D3DPRESENT_PARAMETERS�ɂ��낢��o�^
	try {
		ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
		m_d3dpp.BackBufferWidth = m_width;
		m_d3dpp.BackBufferHeight = m_height;
		if (m_fullscreen) {                              // if fullscreen
			m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;  // 24 bit color
		}
		else {
			m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;   // use desktop setting
		}
		m_d3dpp.BackBufferCount = 1;
		m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_d3dpp.hDeviceWindow = m_hWnd;
		m_d3dpp.Windowed = (!m_fullscreen);
		m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	catch (...) {
		WARN("wwww");
	}
	//m_d3dpp����I��
}

HRESULT Graphics::showBackBuffer() {
	m_result= m_D3DDev->Present(NULL, NULL, NULL,NULL);
	return m_result;
}

bool Graphics::isAdapterCompatible() {
	UINT modes = m_D3D->GetAdapterModeCount(D3DADAPTER_DEFAULT, m_d3dpp.BackBufferFormat);

	if (m_mode.Height == m_d3dpp.BackBufferHeight&&
		m_mode.Width == m_d3dpp.BackBufferWidth&&
		m_mode.RefreshRate >= m_d3dpp.FullScreen_RefreshRateInHz) {
		return true;
	}
	return false;
}

void Graphics::drawSprite(
	const SpriteData& spriteData,
	DWORD color) {

	if (!spriteData.texture) {
		return;
	}

	//�X�v���C�g�̒��S�����(��]�ɕK�v�j
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2(
		((float)spriteData.width / 2)*spriteData.scale,
		((float)spriteData.height / 2)*spriteData.scale);

	//���[���h�ϊ��s��ɕK�v��
	//���s�ړ����]��g��k���x�N�g�������
	//�܂����s�ړ��x�N�g��
	D3DXVECTOR2 translate(spriteData.x, spriteData.y);

	//�g��k��
	D3DXVECTOR2 scale(spriteData.scale, spriteData.scale);
	if (spriteData.flipHorizontal) {
		scale.x *= -1;

		spriteCenter.x -= (float)(spriteData.width*spriteData.scale);
		translate.x += (float)(spriteData.width*spriteData.scale);
	}//TODO:����2��flip��if���̗������܂���
	if (spriteData.flipVertical) {
		scale.y *= -1;

		spriteCenter.y -= (float)(spriteData.width*spriteData.scale);
		translate.y += (float)(spriteData.width*spriteData.scale);
	}

	//���[���h�s�񐶐�
	D3DXMATRIX wm;
	D3DXMatrixTransformation2D(
		&wm,
		NULL,
		0.f,
		&scale,
		&spriteCenter,
		spriteData.angle,
		&translate);

	m_sprite->SetTransform(&wm);

	m_sprite->Draw(
		spriteData.texture,
		&spriteData.rect,
		NULL,
		NULL,
		color);

	
}


void Graphics::changeDisplayMode(graphicsNS::DISPLAY_MODE mode) {
	try {
		switch (mode) {
		case graphicsNS::FULLSCREEN:
			if (m_fullscreen) {//���Ƀt���X�N���[��
				return;
			}
			m_fullscreen = true;
			break;
		case graphicsNS::WINDOW:
			if (!m_fullscreen) {//���ɃE�C���h�E
				return;
			}
			m_fullscreen = false;
			break;
		case graphicsNS::TOGGLE://����ւ��\��
			m_fullscreen = !m_fullscreen;
			reset();

			if (m_fullscreen) {//�t���X�N���[��
				SetWindowLong(m_hWnd, GWL_STYLE, WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP);
			}
			else {//�E�C���h�E
				SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
				SetWindowPos(m_hWnd, HWND_TOP, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
					SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

				RECT clientRect;
				GetClientRect(m_hWnd, &clientRect);
				MoveWindow(m_hWnd,
					0, 0,
					WINDOW_WIDTH + (WINDOW_WIDTH - clientRect.right),
					WINDOW_HEIGHT + (WINDOW_HEIGHT - clientRect.bottom),
					TRUE);
			}
			break;
		}
	}
	catch (...) {
		SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(m_hWnd, HWND_TOP, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

		RECT clientRect;
		GetClientRect(m_hWnd, &clientRect);
		MoveWindow(m_hWnd,
			0, 0,
			WINDOW_WIDTH + (WINDOW_WIDTH - clientRect.right),
			WINDOW_HEIGHT + (WINDOW_HEIGHT - clientRect.bottom),
			TRUE);
	}
}

HRESULT Graphics::getDeviceState() {
	m_result = E_FAIL;
	if (m_D3DDev == NULL) {
		return m_result;
	}
	m_result = m_D3DDev->TestCooperativeLevel();
	return m_result;
}

HRESULT Graphics::reset() {
	m_result = E_FAIL;
	initD3Dpp();
	m_result = m_D3DDev->Reset(&m_d3dpp);
	return m_result;
}

HRESULT Graphics::beginScene() {
	m_result = E_FAIL;
	if (m_D3DDev == NULL) {
		return m_result;
	}
	//�o�b�N�o�b�t�@��m_backColor�ŃN���A
	m_D3DDev->Clear(0, NULL, D3DCLEAR_TARGET, m_backColor, 1.f, 0);
	//���ꂪ�^��BeginScene().�@���b�v���̈��
	m_result = m_D3DDev->BeginScene();
	return m_result;
}
HRESULT Graphics::endScene() {
	m_result = E_FAIL;
	if (m_D3DDev) {
		m_result = m_D3DDev->EndScene();
	}
	return m_result;
}

void Graphics::spriteBegin(){
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
};
void Graphics::spriteEnd() {
	m_sprite->End();
};
