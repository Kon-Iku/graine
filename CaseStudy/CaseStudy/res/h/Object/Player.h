//========================================================================================
//		File        : Player.h
//		Program     : �v���C���[
//
//		Description : �v���C���[�ʂ̓���
//
//		History     : 2015/05/6	�쐬�J�n
//						   
//
//																Author : ���񂽂܃Y
//========================================================================================

#pragma once

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../System/PreInclude.h"
#
#include <d3d9.h>
#include <d3dx9.h>
#include "../System/Input.h"
#include "../System/System.h"
#include "../Object/Object2Dsub.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#define PLAYER_SIZE_X (200)
#define PLAYER_SIZE_Y (250)

#define PLAYER_ANIME_SIZE_X	(10)	// �e�N�X�`���̕�����
#define PLAYER_ANIME_SIZE_Y	(2)

#define PLAYER_ANIME_STOP	(1)
#define PLAYER_ANIME_MOVE	(6)
#define PLAYER_ANIME_JUMP	(2)

#define PLAYER_MOVE_SPD		(10)

enum PLAYER_PHASE
{


};
enum PLAYER_STATE
{
	P_STOP = 0,
	P_MOVE,
	P_JUMP,
};

enum PLAYER_TYPE
{
	P_TYPE_PLAYER = 0,
	P_TYPE_OTHER,
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CPlayer : public CObject2Dsub
{
private:
	bool	m_bStop;	// �����Ă邩�ǂ���
	int		m_nState;	// �v���C���[�̃X�e�[�g�i�����ɂ��āj
	int		m_nType;	// �v���C���[�̎�ށi���삷�������̑����j
public:
	CPlayer();
	void Update();
	void moveControllerPlayer();					// �����i�v���C���[�j����N���X�ɂ������������̂���
	void Animation();								// �A�j��            ����N���X�ɂ������������̂���
	static CPlayer* Create(const LPCTSTR pszFName);	// ����
	virtual void Release();							// �j��
};
//========================================================================================
//	End of File
//========================================================================================