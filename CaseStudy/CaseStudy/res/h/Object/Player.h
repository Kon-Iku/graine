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
#include "../Object/Character.h"
#include "../Object/Stage.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\

#define PLAYER_ANIME_SIZE_X	(4)	// �e�N�X�`���̕�����
#define PLAYER_ANIME_SIZE_Y	(7)

const float PLAYER_POS_DEFAULT_X = -200;
const float PLAYER_POS_DEFAULT_Y = 100;

const float PLAYER_SIZE_X = 128;
const float PLAYER_SIZE_Y = 128;

#define PLAYER_ANIME_STOP	(1)
#define PLAYER_ANIME_MOVE	(6)
#define PLAYER_ANIME_JUMP	(2)

static const float PLAYER_MOVE_SPD = 10;	// �X�s�[�h�Œ�l

const float PLAYER_LENGTH	= 80;	// ���삷���Ƃ��Ă���z�̋���		

enum PLAYER_TYPE
{
	P_TYPE_PLAYER = 0,
	P_TYPE_OTHER,
	P_TYPE_THROW_READY_READY,
	P_TYPE_THROW_READY,
	P_TYPE_THROW,

	P_TYPE_FLOWER,

	P_TYPE_DELETE,

	MAX_PLAYER_TYPE
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CPlayer : public CCharacter
{
private:
	const float JUMP_DEFAULT	= 10.f;	// �W�����v���x�̏����x
	const float JUMP_GRAVITY	= 0.1f;		// �W�����v���x�̌���
protected:
	
	int		m_nNo;		// ���ʔԍ�
	int		m_nType;	// �v���C���[�̎�ށi���삷�������̑����j

	int		m_nPrevRL;
	int		m_nRL;		// �����Ă����

	float	m_fSpeed;		// �ړ����x(�����_��)
	float	m_fJumpSpeed;	// �W�����v�̑��x

	bool	m_bDelete;
	bool	m_bCol;			//�������Ă邩�ǂ���

	CStage*	m_pStage;	// �����蔻����s���t�B�[���h

	CPlayer*	m_pPlayer;	// ����ݒ��Player(����ݒ�̏ꍇ��NULL)

	// �����p
	int		m_nThrowNo;

public:
	CPlayer();
	virtual void Init();									// ������
	virtual void Uninit();
	virtual void Update();
	virtual void moveControllerPlayer();					// �����i�v���C���[	����N���X�ɂ������������̂���
	virtual void moveControllerOther();						// �����i�W�c�j		����N���X�ɂ������������̂���
	virtual void moveControllerThrowReady();
	virtual void moveControllerThrowReadyReady();
	virtual void moveControllerThrow();
	virtual void Animation();								// �A�j��			����N���X�ɂ������������̂���
	static CPlayer* Create(const LPCTSTR pszFName);	// ����

	// ----- �Z�b�^�[
	void SetNo(int no){m_nNo = no;}					// �v���C���[�̎��ʔԍ�
	void SetPlayerType(int type){m_nType = type;}	// �v���C���[�̑���ݒ�
	void SetThrowNo(int no){m_nThrowNo = no;}
	void SetPlayer(CPlayer* p){m_pPlayer = p;}		// ���삷��Player���ݒ�
	void SetStage(CStage* f){m_pStage = f;}			// �t�B�[���h���ݒ�

	void EnableDelete(){m_bDelete = true;}
	void DisableDelete(){m_bDelete = false;}

	void EnableCol(){m_bCol = true;}
	void DisableCol(){m_bCol = false;}

	// ----- �Q�b�^�[
	int GetStatus(){return m_status;}
	int GetNo(){return m_nNo;}						// �v���C���[�̎��ʔԍ�
	int GetType(){return m_nType;}					// ��ގ擾
	int GetRL(){return m_nRL;}
	bool GetDelete(){return m_bDelete;}
	bool GetCol(){return m_bCol;}
};
//========================================================================================
//	End of File
//========================================================================================