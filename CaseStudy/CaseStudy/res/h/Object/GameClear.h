//========================================================================================
//		File        : GameClear.h
//		Program     : �Q�[���N���A�E�B���h�E
//
//		Description : �Q�[���N���A�E�B���h�E�̒�`
//
//		History     : 2015/06/22	�쐬�J�n
//						   
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
#include "../Object/Object2D.h"
#include "../Object/Character.h"
#include "../Object/Camera.h"
#include "../Object/Button.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CGameClear
{
// ===== �����o�萔
public:
	enum
	{
		PHASE_INIT = 0,
		PHASE_INIT_DIRECTION,
		PHASE_FADEIN_DIRECTION,
		PHASE_DIRECTION,
		PHASE_UNINIT_DIRECTION,
		PHASE_WAIT,
		PHASE_ENTER,
		PHASE_UNINIT,
		PHASE_END,

		PHASE_MAX
	};

private:
	enum
	{
		GO_NEXT = 0,
		GO_SELECT
	};

	enum{
		NEXT_BUTTON = 0,
		GOSELECT_BUTTON,

		MAX_BUTTON
	};

	enum{
		TEX_WND_0	= 0,
		TEX_NEXT,
		TEX_SELECT,
		TEX_FILTER,
		TEX_TEXT,

		MAX_TEX
	};
	
	static const D3DXVECTOR2 FILTER_SIZE;
	static const D3DXVECTOR3 FILTER_POS;

	static const D3DXVECTOR2 W_0_DEFAULET_SIZE;
	static const D3DXVECTOR3 W_0_DEFAULET_POS;
	
	static const D3DXVECTOR2 TEXT_SIZE;
	static const D3DXVECTOR3 TEXT_POS;

	static const float B_0_POS_INTERVAL_Y;

	static const D3DXVECTOR2 B_0_DEFAULET_SIZE;
	static const D3DXVECTOR3 B_0_DEFAULET_POS;

	static const D3DXVECTOR2 B_1_DEFAULET_SIZE;
	static const D3DXVECTOR3 B_1_DEFAULET_POS;
	
	static const LPCTSTR TEX_FILENAME[];			// �e�N�X�`���̃t�@�C����

	static const D3DXVECTOR3 DIRECTION_CAMERA_SPD;		// ���o���̃J�����ړ����x
	static const float DIRECTION_ADJUST_DIST;			// ���o���̃J�������Ջ����̒����l
	
	static const int FADEIN_TIME;			// �t�F�[�h�C���Ԋu(�A���t�@�l:0�`255)
	static const int FADEOUT_TIME;			// �t�F�[�h�A�E�g�Ԋu(�A���t�@�l:0�`255)
	
	static const int DRAWTEX_FADEIN_TIME;

// ===== �����o�ϐ�
private:
	int				m_nPhase;
	int				m_nCurButton;

	int				m_nGo;			// �s��

	CObject2D*		m_pFilter;
	CObject2D*		m_pWnd;
	CObject2D*		m_pText;

	CButton*		m_pButtonNext;
	CButton*		m_pButtonGoSelect;

	vector<CButton*> m_vecButton;

	CCamera*		m_pCamera;
	D3DXVECTOR2		m_cameraStartPos;
	float			m_dirDist;

public:
	virtual void Initialize();
	virtual void Init();
	virtual void Uninit();
	virtual void Update(CObject2D* pDark, CObject2D* pLight, D3DXVECTOR2* pClipSize);
	virtual void Draw();

	// ----- �Q�b�^�[
	int GetPhase(){return m_nPhase;}
	int GetGo(){return m_nGo;}

	// ----- �Z�b�^�[
	void SetPhase(int no){m_nPhase = no;}
	void SetCamera(CCamera* pCamera) {m_pCamera = pCamera;}
	void SetCameraStartPos(const D3DXVECTOR2& pos) {m_cameraStartPos = pos;}
	void SetDirectionDistance(float distance) {m_dirDist = distance;}

	CGameClear();
	static CGameClear* Create();	// ����
	void Release();

private:
	bool InitDirection();
	void FadeinDirection();
	void Direction(CObject2D* pDark, CObject2D* pLight, D3DXVECTOR2* pClipSize);
	void UninitDirection();
	void Wait();
	void Enter();
};

//========================================================================================
//	End of File
//========================================================================================