//========================================================================================
//		File        : Title.h
//		Program     : �^�C�g���N���X
//
//		Description : �^�C�g���N���X�̒�`
//
//		History     : 2013/12/18	�쐬�J�n
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



#include "../Object/Character.h"
#include "../System/MapData.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CTitle : public CScene
{
// ===== �����o�萔
private:
	static const LPCTSTR TEX_FILENAME[];			// �e�N�X�`���̃t�@�C����
	static const D3DXVECTOR3 INIT_CAMERA_EYE;		// �J�����̏������_
	static const D3DXVECTOR3 INIT_CAMERA_LOOK;		// �J�����̏��������_
	static const D3DXVECTOR3 INIT_TEXTURE_POS[];	// �e�N�X�`���̏����ʒu

	static const int FADEIN_TIME;	// �t�F�[�h�C���Ԋu(�A���t�@�l:0�`255)
	static const int FADEOUT_TIME;	// �t�F�[�h�A�E�g�Ԋu(�A���t�@�l:0�`255)

	// ----- �e�N�X�`�����X�g
	static enum _eTexList
	{
		TL_BG = 0,		// �w�i�e�N�X�`��
		TL_FADE,		// �t�F�[�h�p�e�N�X�`��

		MAX_TEXLIST
	};

	// ----- �t�F�[�Y�t���O
	static enum _ePhase
	{
		PHASE_FADEIN = 0,		// �t�F�[�h�C��
		PHASE_FADEOUT,			// ���̃V�[���փt�F�[�h�A�E�g
		PHASE_MAIN,				// �^�C�g���{��
	
		MAX_PHASE
	};
	
// ===== �����o�ϐ�
private:
	// ----- �I�u�W�F�N�g
	CCamera*		m_pCamera;		// �J����
	CTexture*		m_pBG;			// �w�i
	CTexture*		m_pFilter;		// �t�F�[�h�p�t�B���^�[

	DWORD			m_phase;		// �t�F�[�Y�t���O



	CCharacter*		m_pPlayer;
	CCharacter*		m_pEnemy;

	LPFIELDOBJECT_ARRAY	m_pFieldObj;	// �t�B�[���h�I�u�W�F�N�g���X�g

// ===== �����o�֐�
public:
	CTitle();
	virtual ~CTitle();

	void	Init();			// ������
	void	Uninit();		// ��n��
	void	Update();		// �X�V
	void	Draw();			// �`��
	static CTitle* Create();	// ����

private:
	bool	Initialize();	// ������
	void	Finalize();		// ��n��

	void	Main();			// ���C��
};


//========================================================================================
//	End of File
//========================================================================================