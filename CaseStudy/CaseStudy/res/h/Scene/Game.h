//========================================================================================
//		File        : Game.h
//		Program     : �Q�[���{�҃N���X
//
//		Description : �Q�[���{�҃N���X�̒�`
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
#include "../Object/Object2D.h"
#include "../Object/GameCamera.h"

#include "../Object/Stage.h"
#include "../Object/Player.h"
#include "../Object/Flower.h"
#include "../Object/PlayersGroup.h"
#include "../Object/GameStop.h"
#include "../Object/GameOver.h"
#include "../Object/GameClear.h"


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
const int MAX_OBJECT = 50;		//�I�u�W�F�N�g��(��)

// ----- �t�F�[�Y�t���O
	static enum _ePhase
	{
		PHASE_FADEIN = 0,		// �t�F�[�h�C��
		PHASE_FADEOUT,			// ���̃V�[���փt�F�[�h�A�E�g
		PHASE_MAIN,				// �Q�[���{��
		PHASE_STOP,				// �ꎞ��~
		PHASE_OVER,				// �I�[�o
		PHASE_CLEAR,			// �N���A
	
		MAX_PHASE
	};
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CGame : public CScene
{
// ===== �����o�萔
private:
	static const LPCTSTR TEX_FILENAME[];			// �e�N�X�`���̃t�@�C����
	static const D3DXVECTOR3 INIT_TEXTURE_POS[];	// �e�N�X�`���̏����ʒu
	
	static const float FADE_POSZ;			// �t�F�[�h�p�e�N�X�`����Z���W
	static const int FADEIN_TIME;			// �t�F�[�h�C���Ԋu(�A���t�@�l:0�`255)
	static const int FADEOUT_TIME;			// �t�F�[�h�A�E�g�Ԋu(�A���t�@�l:0�`255)

	// ----- �e�N�X�`�����X�g
	static enum _eTexList
	{
		TL_BG = 0,		// �w�i�e�N�X�`��
		TL_PLAYER_0,	// �v���C���[�e�N�X�`���i�{�́j
		TL_BLOCK_0,		// �u���b�N�e�N�X�`��
		TL_FLOWER_0,

		MAX_TEXLIST
	};

// ===== �����o�ϐ�
private:
	// ----- �I�u�W�F�N�g
	CGameCamera*	m_pCamera;	// �J����
	CObject2D*	m_pBG;			// �w�i
	
	// ----- �v���C���[�@----- //
	CPlayersGroup*		m_pPlayersGroup;

	std::vector<CFlower*> m_listFlower;

	CStage*				m_pStage;

	CGameStop*			m_pGameStop;
	CGameOver*			m_pGameOver;
	CGameClear*			m_pGameClear;
	

	// ----- �Q�[���V�X�e��
	DWORD		m_phase;		// �t�F�[�Y�t���O
	DWORD		m_pNextScene;

// ===== �����o�֐�
public:
	CGame();
	virtual ~CGame();

	void	Init(void);			// ������
	void	Uninit(void);		// ��n��
	void	Update(void);		// �X�V
	void	Draw(void);			// �`��
	static CGame* Create();		// ����

	void CreateFlower(D3DXVECTOR3 pos,D3DXVECTOR3 dir);

private:
	bool	Initialize();		// ������
	void	Finalize(void);		// ��n��

	void	Main();		// ���C��
	void	DrawMain();

	void	Stop();		// �ꎞ��~
	void	DrawStop();

	void	Over();		// �I�[�o
	void	DrawOver();

	void	Clear();		// �N���A
	void	DrawClear();
};


//========================================================================================
//	End of File
//========================================================================================