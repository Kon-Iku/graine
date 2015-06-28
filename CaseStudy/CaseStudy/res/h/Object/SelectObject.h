//========================================================================================
//		File        : SelectObject.h
//		Program     : �V�[���J�ڃV�X�e��
//
//		Description : �V�[���J�ڃV�X�e���̒�`
//
//		History     : 2015/02/20	�쐬�J�n
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
#include <vector>
#include "../Object/Character.h"

enum SelectObject_Status
{
	S_STATUS_WAIT = 0,
	S_STATUS_LEFT,
	S_STATUS_RIGHT,
};

enum Select_Stage
{
	S_STAGE_1 = 0,
	S_STAGE_2,

	S_STAGE_MAX,
};

#define SELECT_ANIME_SIZE_X		(10)	// �e�N�X�`���̕�����
#define SELECT_ANIME_SIZE_Y		(11)
#define PLAYER_INIT_POS_X		(SCREEN_WIDTH / 2)
#define PLAYER_INIT_POS_Y		((SCREEN_HEIGHT / 2) - 10)
#define LEFT_ARROW_INIT_POS_X	(SCREEN_RIGHT - 384)
#define LEFT_ARROW_INIT_POS_Y	100
#define RIGHT_ARROW_INIT_POS_X	(SCREEN_RIGHT + 384)
#define RIGHT_ARROW_INIT_POS_Y	100
#define ROGO_INIT_POS_X			(SCREEN_WIDTH / 2)
#define ROGO_INIT_POS_Y			100
#define ROGO_SCREEN_OUT_POS_X	(SCREEN_LEFT - 192)
#define ROGO_SCREEN_OUT_POS_Y	(SCREEN_TOP + 192)
#define STAGE_INIT_POS_X		(SCREEN_WIDTH / 2)
#define STAGE_INIT_POS_Y		(SCREEN_HEIGHT + SCREEN_TOP - 10)
#define MOVE_COUNT				40

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CSelectObject : public CCharacter
{
	// ===== �����o�萔
private:
	// ===== �����o�ϐ�
private:
	int		m_nStatus;
	bool	m_bAnime;
	// ===== �����o�֐�
public:
	CSelectObject();
	virtual ~CSelectObject();

	static CSelectObject* Create(const LPCTSTR pszFName);	// ����
	void PlayerUpdate(bool bAnime,int StageNo);		// �V�[���J�� ��2 (��ʂɏo��)
	int ArrowUpdate(int nNo,int nStatus);
	void RogoUpdate(int nNo,int nStatus,int nStage);
	bool StageUpdate(int nStatus,int nStage);
};

//========================================================================================
//	End of File
//========================================================================================