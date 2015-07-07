//========================================================================================
//		File        : Graphics.cpp
//		Program     : �`��N���X
//
//		Description : �`��N���X�̎���
//
//		History     : 2014/04/17	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/PreInclude.h"
#
#include <windows.h>
#include <tchar.h>
#include "../../h/System/Graphics.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �}�N����`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)			if(x){ x->Release(); x=NULL; }
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)			if(x){ delete x; x=NULL; }
#endif

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �����o���̐錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
LPDIRECT3D9				CGraphics::m_pD3D		= NULL;		// Direct3D9 �I�u�W�F�N�g
LPDIRECT3DDEVICE9		CGraphics::m_pDevice	= NULL;		// Direct3DDevice9 �I�u�W�F�N�g
D3DPRESENT_PARAMETERS	CGraphics::m_D3DPP;					// PRESENT PARAMETERS
LPD3DXFONT				CGraphics::m_pFont		= NULL;		// D3DXFont �I�u�W�F�N�g

D3DXMATRIX	CGraphics::m_MatView;	// �r���[ �}�g���b�N�X
D3DXMATRIX	CGraphics::m_MatProj;	// �ˉe�}�g���b�N�X

HWND	CGraphics::m_hWnd;		// �E�B���h�E �n���h��
int		CGraphics::m_nWidth;	// �\���̈敝
int		CGraphics::m_nHeight;	// �\���̈捂��


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : ��������
//	Description : �`��N���X�𐶐�����
//	Arguments   : hWnd    / �E�B���h�E�n���h��
//				  nWidth  / �Q�[����ʂ̕�
//				  nHeight / �Q�[����ʂ̍���
//				  bWindow / �E�B���h�E���[�h
//	Returns     : �`��N���X
//����������������������������������������������������������������������������������������
CGraphics* CGraphics::Create(HWND hWnd, int nWidth, int nHeight, bool bWindow)
{
	CGraphics* pGraph = new CGraphics();
	if (pGraph) {
		if (!pGraph->Initialize(hWnd, nWidth, nHeight, bWindow)) {
			SAFE_DELETE(pGraph);
		}
	}
	return pGraph;
}

//����������������������������������������������������������������������������������������
//	Name        : �������
//	Description : �`��N���X���������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGraphics::Release()
{
	Finalize();
	delete this;
}

//����������������������������������������������������������������������������������������
//	Name        : �����_�����O�J�n
//	Description : �����_�����O���J�n����
//	Arguments   : None.
//	Returns     : ����
//����������������������������������������������������������������������������������������
bool CGraphics::Begin()
{
	// �r���[�|�[�g���N���A
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
					 D3DCOLOR_XRGB(128, 128, 255), 1.0f, 0);

	return SUCCEEDED(m_pDevice->BeginScene());	// �V�[���J�n
}

//����������������������������������������������������������������������������������������
//	Name        : �����_�����O�I��
//	Description : �����_�����O���I������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGraphics::End()
{
	m_pDevice->EndScene();						// �V�[���I��
}

//����������������������������������������������������������������������������������������
//	Name        : �o�b�N�o�b�t�@����ւ�
//	Description : �o�b�N�o�b�t�@�ɕ`�悵�����e��\������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGraphics::SwapBuffer()
{
	// �o�b�N�o�b�t�@�ɕ`�悵�����e��\��
	if (FAILED(m_pDevice->Present(NULL, NULL, NULL, NULL))) {
		m_pDevice->Reset(&m_D3DPP);
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �f�o�b�O������`��
//	Description : �f�o�b�O�������`�悷��
//	Arguments   : nX      / X���W
//				  nY      / Y���W
//				  pszText / �f�o�b�O������
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGraphics::DrawText(int nX, int nY, LPCTSTR pszText)
{
	RECT rcStr = {nX, nY, m_nWidth, m_nHeight};
	m_pFont->DrawText(NULL, pszText, -1, &rcStr, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
}

//����������������������������������������������������������������������������������������
//	Name        : 2D�`�揀��
//	Description : ������W�n���ˉe�s����쐬����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGraphics::SetDraw2D(void)
{
	D3DXMatrixOrthoLH(&m_MatProj, (float)m_nWidth,
		(float)m_nHeight, NEAR_CLIP, FAR_CLIP);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &m_MatProj);
}

//����������������������������������������������������������������������������������������
//	Name        : 3D�`�揀��
//	Description : ������W�n�p�[�X�y�N�e�B�u�ˉe�s����쐬����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGraphics::SetDraw3D(void)
{
	D3DXMatrixPerspectiveFovLH(&m_MatProj, D3DXToRadian(FOVY),
		(float)m_nWidth / m_nHeight, NEAR_CLIP, FAR_CLIP);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &m_MatProj);
}


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �O���t�B�b�N��������������
//	Arguments   : hWnd    / �E�B���h�E�n���h��
//				  nWidth  / �Q�[����ʂ̕�
//				  nHeight / �Q�[����ʂ̍���
//				  bWindow / �E�B���h�E���[�h
//	Returns     : ����(true:����)
//����������������������������������������������������������������������������������������
bool CGraphics::Initialize(HWND hWnd, int nWidth, int nHeight, bool bWindow)
{
	// �f�o�C�X���e�[�u��
	struct TCreateDevice {
		D3DDEVTYPE	type;			// �f�o�C�X�̎��
		DWORD		behavior;		// �f�o�C�X�̓���
	};
	const int c_nMaxDevice = 3;
	const TCreateDevice device[c_nMaxDevice] = {
		{ D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING },	// �n�[�h�E�F�A�V�F�[�_���g��
		{ D3DDEVTYPE_HAL, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// HAL
		{ D3DDEVTYPE_REF, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// REF
	};
	int		nDev;			// �f�o�C�X��ʃJ�E���^

	// Direct3D�I�u�W�F�N�g�𐶐�
	if ((m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		MessageBox(hWnd, _T("Direct3D�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
#endif
		return false;
	}
	// Direct3D �������p�����[�^�̐ݒ�
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	ZeroMemory(&m_D3DPP, sizeof(D3DPRESENT_PARAMETERS));
	m_D3DPP.BackBufferWidth        = (UINT)nWidth;				// �Q�[����ʃT�C�Y
	m_D3DPP.BackBufferHeight       = (UINT)nHeight;
	m_D3DPP.Windowed               = bWindow;					// �E�B���h�E���[�h��?
	m_D3DPP.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	m_D3DPP.EnableAutoDepthStencil = true;						// �y�o�b�t�@�L��
	m_D3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;				// �y�o�b�t�@�t�H�[�}�b�g
	if (bWindow) {
		// �E�B���h�E���[�h
		m_D3DPP.BackBufferFormat           = D3DFMT_UNKNOWN;				// �o�b�N�o�b�t�@
		m_D3DPP.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		m_D3DPP.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	} else {
		// �t���X�N���[�����[�h
		m_D3DPP.BackBufferFormat           = D3DFMT_X8R8G8B8;				// �o�b�N�o�b�t�@
		m_D3DPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
		m_D3DPP.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��
	}

	// �f�o�C�X�I�u�W�F�N�g���쐬
	for (nDev = 0; nDev < c_nMaxDevice; nDev++) {
		HRESULT hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, device[nDev].type, hWnd,	// �f�o�C�X���쐬
					  device[nDev].behavior, &m_D3DPP, &m_pDevice);
		if(SUCCEEDED(hr))
			break;
		
		switch(hr)
		{
			case D3DERR_DEVICELOST:
#ifdef _DEBUG_MESSAGEBOX
				MessageBox(hWnd, _T("D3DERR_DEVICELOST"), _T("error"), MB_OK | MB_ICONERROR);
#endif
				break;
			case D3DERR_INVALIDCALL:
#ifdef _DEBUG_MESSAGEBOX
				MessageBox(hWnd, _T("D3DERR_INVALIDCALL"), _T("error"), MB_OK | MB_ICONERROR);
#endif
				break;
			case D3DERR_NOTAVAILABLE:
#ifdef _DEBUG_MESSAGEBOX
				MessageBox(hWnd, _T("D3DERR_NOTAVAILABLE"), _T("error"), MB_OK | MB_ICONERROR);
#endif
				break;
			case D3DERR_OUTOFVIDEOMEMORY:
#ifdef _DEBUG_MESSAGEBOX
				MessageBox(hWnd, _T("D3DERR_OUTOFVIDEOMEMORY"), _T("error"), MB_OK | MB_ICONERROR);
#endif
				break;
			default:
				break;
		}
	}
	if (nDev >= c_nMaxDevice) {
#ifdef _DEBUG_MESSAGEBOX
		MessageBox(hWnd, _T("�f�o�C�X�̍쐬�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
#endif
		return false;
	}
	
	m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);								// Z�o�b�t�@���g�p
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);					// ���u�����h���s��
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);				// ���\�[�X�J���[�̎w��
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);			// ���f�X�e�B�l�[�V�����J���[�̎w��
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		// �A���t�@�`�����l���L����

	// ���\���p�t�H���g��ݒ�
	D3DXCreateFont(m_pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);

	//-------- ��������R�c�֘A
	// 3D�`��ݒ�
	SetDraw3D();

	// �}�e���A���̐ݒ�
	D3DMATERIAL9	mtrl;				// �}�e���A���I�u�W�F�N�g
	ZeroMemory(&mtrl, sizeof(mtrl));	// ��������[���ŃN���A
	mtrl.Diffuse.r = mtrl.Diffuse.g = mtrl.Diffuse.b = mtrl.Diffuse.a = 1.0f;
	mtrl.Ambient = mtrl.Diffuse;
	m_pDevice->SetMaterial(&mtrl);

	// ���C�g�̐ݒ�
	D3DXVECTOR3	vecDir;					// �������w�肷��x�N�g��
	D3DLIGHT9	light;					// ���C�g�I�u�W�F�N�g
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;	// ���s����
	light.Diffuse.r = light.Diffuse.g = light.Diffuse.b = light.Diffuse.a = 1.0f;
	light.Ambient.r = light.Ambient.g = light.Ambient.b = light.Ambient.a = 0.2f;
	light.Specular = light.Diffuse;
	vecDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f);					// ���̌��������߂�
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);	// ���K�������x�N�g����Ԃ�
	m_pDevice->SetLight(0, &light);
	m_pDevice->LightEnable(0, TRUE);	// ���C�g0��L��

	m_pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pDevice->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
	
	//m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	// �w�ʃJ�����O��ݒ�
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// �w�ʃJ�����O�𖳌�

	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �O���t�B�b�N�����N���[���A�b�v����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGraphics::Finalize()
{
	SAFE_RELEASE(m_pFont);		// D3DXFont �I�u�W�F�N�g�����
	SAFE_RELEASE(m_pDevice);	// Direct3DDevice �I�u�W�F�N�g�����
	SAFE_RELEASE(m_pD3D);		// Direct3D �I�u�W�F�N�g�����
}


//========================================================================================
//	End of File
//========================================================================================