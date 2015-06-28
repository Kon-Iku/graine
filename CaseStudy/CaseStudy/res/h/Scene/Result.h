//========================================================================================
//		File        : Result.cpp
//		Program     : ���U���g�N���X
//
//		Description : ���U���g�N���X�̒�`
//
//		History     : 2015/01/09	�쐬�J�n
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
#include "../Object/Object2D.h"
#include "../Object/Camera.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CResult : public CScene
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
		TL_BG = 0,		// �w�i�e�N�X�`��

		MAX_TEXLIST
	};

	// ----- �t�F�[�Y�t���O
	static enum _ePhase
	{
		PHASE_FADEIN = 0,		// �t�F�[�h�C��
		PHASE_FADEOUT,			// ���̃V�[���փt�F�[�h�A�E�g
		PHASE_MAIN,				// ���U���g�{��
	
		MAX_PHASE
	};

// ===== �����o�ϐ�
private:
	// ----- �I�u�W�F�N�g
	CCamera*		m_pCamera;		// �J����
	CObject2D*		m_pBG;			// �w�i
	
	DWORD		m_phase;		// �t�F�[�Y�t���O
	
// ===== �����o�֐�
public:
	CResult();
	virtual ~CResult();

	void	Init(void);			// ������
	void	Uninit(void);		// ��n��
	void	Update(void);		// �X�V
	void	Draw(void);			// �`��
	static CResult* Create();		// ����

private:
	bool	Initialize();		// ������
	void	Finalize(void);		// ��n��
	
	void	Main();				// ���C��
};


//========================================================================================
//	End of File
//========================================================================================