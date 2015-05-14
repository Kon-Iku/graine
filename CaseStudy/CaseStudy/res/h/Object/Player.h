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
#include "../Object/FieldObject.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\

#define PLAYER_ANIME_SIZE_X	(10)	// �e�N�X�`���̕�����
#define PLAYER_ANIME_SIZE_Y	(2)

const float PLAYER_POS_DEFAULT_X = 100;
const float PLAYER_POS_DEFAULT_Y = 100;

const float PLAYER_SIZE_X = 200;
const float PLAYER_SIZE_Y = 250;

#define PLAYER_ANIME_STOP	(1)
#define PLAYER_ANIME_MOVE	(6)
#define PLAYER_ANIME_JUMP	(2)

static const float PLAYER_MOVE_SPD = 5;	// �X�s�[�h�Œ�l

const float PLAYER_LENGTH	= 100;	// ���삷���Ƃ��Ă���z�̋���		

enum PLAYER_TYPE
{
	P_TYPE_PLAYER = 0,
	P_TYPE_OTHER,

	MAX_PLAYER_TYPE
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CPlayer : public CCharacter
{
private:
	
	int		m_nNo;		// ���ʔԍ�
	int		m_nType;	// �v���C���[�̎�ށi���삷�������̑����j

	float	m_fSpeed;	// �ړ����x(�����_��)

	CFieldObject*	m_pField;	// �����蔻����s���t�B�[���h

	CPlayer*	m_pPlayer;	// ����ݒ��Player(����ݒ�̏ꍇ��NULL)

public:
	CPlayer();
	void Init();									// ������
	void Update();
	void moveControllerPlayer();					// �����i�v���C���[	����N���X�ɂ������������̂���
	void moveControllerOther();						// �����i�W�c�j		����N���X�ɂ������������̂���
	void moveControllerOther2();
	void Animation();								// �A�j��			����N���X�ɂ������������̂���
	static CPlayer* Create(const LPCTSTR pszFName);	// ����

	// ----- �Z�b�^�[
	void SetNo(int no){m_nNo = no;}					// �v���C���[�̎��ʔԍ�
	void SetPlayerType(int type){m_nType = type;}	// �v���C���[�̑���ݒ�
	void SetPlayer(CPlayer* p){m_pPlayer = p;}		// ���삷��Player���ݒ�
	void SetField(CFieldObject* f){m_pField = f;}	// �t�B�[���h���ݒ�

	// ----- �Q�b�^�[
	int GetNo(){return m_nNo;}						// �v���C���[�̎��ʔԍ�
	int GetType(){return m_nType;}					// ��ގ擾
};
//========================================================================================
//	End of File
//========================================================================================