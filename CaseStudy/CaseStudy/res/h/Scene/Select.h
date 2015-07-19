//========================================================================================
//		File        : Select.h
//		Program     : �y�ȑI���N���X
//
//		Description : �y�ȑI���N���X�̒�`
//
//		History     : 2014/07/30	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================

#pragma once

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../System/PreInclude.h"
#
#include "../System/Graphics.h"
#include "../Scene/Scene.h"
#include "../Object/Texture.h"
#include "../Object/Camera.h"
#include "../Object/SelectObject.h"
#include "../Scene/GameMain.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CSelect : public CScene
{
	// ===== �����o�萔
private:

	static const LPCTSTR TEX_FILENAME[];			// �e�N�X�`���̃t�@�C����
	static const D3DXVECTOR3 INIT_CAMERA_EYE;		// �J�����̏������_
	static const D3DXVECTOR3 INIT_CAMERA_LOOK;		// �J�����̏��������_
	static const D3DXVECTOR3 INIT_TEXTURE_POS[];	// �e�N�X�`���̏����ʒu

	static const float FADE_POSZ;		// �t�F�[�h�p�e�N�X�`����Z���W
	static const int FADEIN_TIME;		// �t�F�[�h�C���Ԋu(�A���t�@�l:0�`255)
	static const int FADEOUT_TIME;		// �t�F�[�h�A�E�g�Ԋu(�A���t�@�l:0�`255)

	// ----- �e�N�X�`�����X�g
	static enum _eTexList
	{
		TL_BG_1 = 0,		// �w�i�e�N�X�`��
		TL_BG_2,		// �w�i�e�N�X�`��
		TL_RING_TRUE,
		TL_RING_FALSE,
		TL_TACTILE,
		TL_PLAYER,
		TL_ARROW,
		TL_ROGO_1,
		TL_ROGO_2,
		TL_ROGO_3,
		TL_ROGO_4,
		TL_ROGO_5,
		TL_STAGE_1,
		TL_STAGE_2,
		TL_STAGE_3,

		MAX_TEXLIST
	};

	// ----- �I�u�W�F�N�g���X�g
	static enum _eObjectList
	{
		OL_BG_1 = 0,
		OL_BG_2,
		OL_RING_TRUE,
		OL_RING_FALSE,
		OL_STAGE_1,
		OL_STAGE_2,
		OL_STAGE_3,
		OL_ARROW_LEFT,
		OL_ARROW_RIGHT,
		OL_ROGO_1,
		OL_ROGO_2,
		OL_ROGO_3,
		OL_ROGO_4,
		OL_ROGO_5,
		OL_TACTILE,
		OL_PLAYER,

		MAX_OBJECTLIST
	};

	// ----- �t�F�[�Y�t���O
	static enum _ePhase
	{
		PHASE_FADEIN = 0,		// �t�F�[�h�C��
		PHASE_FADEOUT,			// ���̃V�[���փt�F�[�h�A�E�g
		PHASE_MAIN,				// �y�ȑI��{��

		MAX_PHASE
	};

	// ===== �����o�ϐ�
private:
	// ----- �I�u�W�F�N�g
	CCamera*		m_pCamera;		// �J����
	CObject2D*		m_pBG;			// �w�i

	DWORD			m_phase;			// �t�F�[�Y�t���O

	CSelectObject*	m_pSelectPlayer[MAX_OBJECTLIST];
	int				m_nStatus;
	int				m_nStage;
	bool			m_bAnime;
	bool			m_bBG1Anime;
	bool			m_bBG2Anime;

	int*			m_pClearFlg;
	int				m_nClearFlg[5];
	int				m_nClear;
	bool			m_bEffect;

	float			m_fRotationZ;
	int				m_nCount;

	// ===== �����o�֐�
public:
	CSelect();
	virtual ~CSelect();

	void	Init();			// ������
	void	Uninit();		// ��n��
	void	Update();		// �X�V
	void	Draw();			// �`��
	static CSelect* Create();	// ����

private:
	bool	Initialize();	// ������
	void	Finalize();		// ��n��

	void	Main();			// ���C��
};


//========================================================================================
//	End of File
//========================================================================================