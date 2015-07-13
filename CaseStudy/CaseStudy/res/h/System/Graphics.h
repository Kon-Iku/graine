//========================================================================================
//		File        : Graphics.h
//		Program     : �`��N���X
//
//		Description : �`��N���X�̒�`
//
//		History     : 2014/04/17	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================

#pragma once

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../System/PreInclude.h"
#
#include <d3d9.h>
#include <d3dx9.h>

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔�E�}�N����`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
const float FOVY		= 30.0f;		// ����p
const float NEAR_CLIP	= 1.0f;			// �j�A�N���b�v���s������
const float FAR_CLIP	= 10000.0f;		// �t�@�[�N���b�v���s������

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CGraphics
{
// ===== �����o�ϐ�
private:
	static LPDIRECT3D9				m_pD3D;				// Direct3D9 �I�u�W�F�N�g
	static LPDIRECT3DDEVICE9		m_pDevice;			// Direct3DDevice9 �I�u�W�F�N�g
	static D3DPRESENT_PARAMETERS	m_D3DPP;			// PRESENT PARAMETERS
	static LPD3DXFONT				m_pFont;			// D3DXFont �I�u�W�F�N�g

	static D3DXMATRIX				m_MatView;			// �r���[ �}�g���b�N�X
	static D3DXMATRIX				m_MatProj;			// �ˉe�}�g���b�N�X

	static HWND						m_hWnd;				// �E�B���h�E �n���h��
	static int						m_nWidth;			// �\���̈敝
	static int						m_nHeight;			// �\���̈捂��

	static DWORD					m_curZTest;			// ������Z�e�X�g�̗L��
	static DWORD					m_curZFunc;			// ������Z�e�X�g��r�֐�
	
// ===== �����o�֐�
public:
	CGraphics();
	virtual ~CGraphics();

	static LPDIRECT3DDEVICE9 GetDevice() {return m_pDevice;}

	static CGraphics* Create(HWND hWnd, int nWidth, int nHeight, bool bWindow);
	void Release();
	bool Begin();
	void End();
	void SwapBuffer();
	void DrawText(int nX, int nY, LPCTSTR pszText);

	static bool StencilRegionBegin();	// �X�e���V���N���b�s���O�̈�쐬�J�n
	static bool StencilRegionEnd();		// �X�e���V���N���b�s���O�̈�쐬�I��
	static bool StencilDrawBegin();		// �X�e���V���N���b�s���O�`��J�n
	static bool StencilDrawEnd();		// �X�e���V���N���b�s���O�`��I��
	
	static void SetDraw2D();		// 2D�`�揀��
	static void SetDraw3D();		// 3D�`�揀��

private:
	bool Initialize(HWND hWnd, int nWidth, int nHeight, bool bWindow);
	void Finalize();
};


//========================================================================================
//	End of File
//========================================================================================