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
#include "../Object/Jack.h"
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
// ===== �����o�\����
private:
	// �N���b�s���O���
	struct TCLIPINFO {
		D3DXVECTOR3	pos;	// �ʒu
		D3DXVECTOR2 size;	// �T�C�Y
	};

// ===== ���[�U�^��`
private:
	typedef std::vector<TCLIPINFO>		CLIPINFO_ARRAY;
	typedef CLIPINFO_ARRAY::iterator	CLIPINFO_ARRAY_IT;

// ===== �����o�萔
private:
	static const LPCTSTR TEX_FILENAME[];			// �e�N�X�`���̃t�@�C����
	static const D3DXVECTOR3 INIT_TEXTURE_POS[];	// �e�N�X�`���̏����ʒu

	static const float FADE_POSZ;			// �t�F�[�h�p�e�N�X�`����Z���W
	static const int FADEIN_TIME;			// �t�F�[�h�C���Ԋu(�A���t�@�l:0�`255)
	static const int FADEOUT_TIME;			// �t�F�[�h�A�E�g�Ԋu(�A���t�@�l:0�`255)

	static D3DXVECTOR2	CLIP_SIZE;			// �N���b�s���O�T�C�Y
	static D3DXVECTOR3	CLIP_INITPOS;		// �N���b�s���O�����ʒu
	static float		CLIP_SCALING_SPD;	// �N���b�s���O�g�呬�x

	// ----- �e�N�X�`�����X�g
	static enum _eTexList
	{
		TL_BG_DARK = 0,		// �w�i�e�N�X�`��
		TL_BG_LIGHT,		// �w�i�e�N�X�`��
		TL_PLAYER_0,		// �v���C���[�e�N�X�`���i�{�́j
		TL_BLOCK_0,			// �u���b�N�e�N�X�`��
		TL_FLOWER_0,
		TL_FLOWER_1,
		TL_JACK_0,
		TL_CLIP,

		MAX_TEXLIST
	};

// ===== �����o�ϐ�
private:
	// ----- �I�u�W�F�N�g
	CGameCamera*	m_pCamera;		// �J����
	CObject2D*		m_pDarkBG;		// �w�i
	CObject2D*		m_pLightBG;		// �w�i

	// ----- �v���C���[�@----- //
	CPlayersGroup*		m_pPlayersGroup;

	std::vector<CFlower*> m_listFlower;

	CStage*				m_pStage;
	static int			m_stageID;		// �I�������X�e�[�W��ID

	CGameStop*			m_pGameStop;
	CGameOver*			m_pGameOver;
	CGameClear*			m_pGameClear;

	CCharacter*			m_pClipCircle;
	CLIPINFO_ARRAY		m_clipInfoList;
	std::vector<float>	m_clipEasingList;

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

	void CreateFlower(D3DXVECTOR3 pos, D3DXVECTOR3 dir);
	void CreateJack(D3DXVECTOR3 pos, D3DXVECTOR3 dir);

	static void SetStageID(int id) {	// �X�e�[�WID�ݒ�
		id >= 0 && id < CMapData::MAX_STAGEID ?
			m_stageID = id : m_stageID = 0;
	}

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