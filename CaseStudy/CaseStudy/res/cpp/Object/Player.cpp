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


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/Input.h"
#include "../../h/Object/Player.h"

//========================================================================================
// public:
//========================================================================================
// �\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// using�錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
using namespace Input;
//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CPlayer::CPlayer()
{
	m_nNo = 0;				// �ŏ��͑S��0�@�����ς��
	m_nType = P_TYPE_OTHER; // ����͂��Ƃŕς��Ȃ��Ƃ������

	// �X�s�[�h����
	m_fSpeed = PLAYER_MOVE_SPD + (0.1f *(rand() % 10)) + rand()%3;
}
//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : ������
//	Arguments   : 
//	Returns     : 
//����������������������������������������������������������������������������������������
void CPlayer::Init()
{
	// �L�����N�^�[�̏�����
	CCharacter::Init(D3DXVECTOR2(PLAYER_SIZE_X,PLAYER_SIZE_Y),
		D3DXVECTOR3(PLAYER_POS_DEFAULT_X,PLAYER_POS_DEFAULT_Y,0));

	// �A�j���[�V����������
	StartAnimation();

	UVDivision(0, PLAYER_ANIME_SIZE_X, PLAYER_ANIME_SIZE_Y);

	// ��Ԃ�ҋ@��
	m_status = ST_WAIT;
	AddStatus(ST_FLYING);

	m_pPlayer	= NULL;
	m_pField	= NULL;
}

//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : �I�u�W�F�N�g�𐶐�����
//	Arguments   : pszFName / �ǂݍ��݃t�@�C����
//	Returns     : �I�u�W�F�N�g�f�[�^
//����������������������������������������������������������������������������������������
CPlayer* CPlayer::Create(const LPCTSTR pszFName)
{
	// ----- �ϐ��錾
	CPlayer* pObj;

	// ----- ����������
	pObj = new CPlayer();
	if (pObj)
	{
		if (!pObj->Initialize(pszFName))
		{
			SAFE_DELETE(pObj);
		}
	}

	return pObj;
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �����ȍX�V
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CPlayer::Update()
{
	
	D3DXVECTOR3 prevPos = m_pos; 
	D3DXVECTOR2 prevTopPos		= D3DXVECTOR2(m_pos.x,GetTopPos());
	D3DXVECTOR3 prevButtomPos	= D3DXVECTOR2(m_pos.x,GetBottomPos());

	switch (m_nType){
	case P_TYPE_PLAYER:
			moveControllerPlayer();
		break;
	case P_TYPE_OTHER:
			moveControllerOther();
		break;
	}

	CCharacter::Update();
	
	// ----- �����蔻��

	// ������
	m_colStartLine	= D3DXVECTOR2(prevPos.x,prevPos.y);

	D3DXVECTOR3 move = {0,0,0};		// �i�s����
	// �܂��i�s�����𐳋K��
	D3DXVec3Normalize(&move,&(D3DXVECTOR3(prevPos.x,m_pos.y,0) - prevPos));
	// �����ɋ�����������
	move = m_pos + move * m_colRadius;

	m_colEndLine	= D3DXVECTOR2(move.x,move.y);

	if(CollisionEnter(COL2D_LINESQUARE,m_pField)){
		printf("true\n");
		SubStatus(ST_FLYING);
		
		m_pos = prevPos;
	}
	else{
		AddStatus(ST_FLYING);
	}

	printf("%f\n",move.y);
	printf("%f\n",GetBottomPos());
	printf("%f\n",m_pField->GetTopPos());

	Animation();

}
//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : ���삷��v���C���[�̓���
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CPlayer::moveControllerPlayer()
{
	 if(GetPrsKey(DIK_RIGHT)){
		TranslationX(m_fSpeed);
	 }
	 if(GetPrsKey(DIK_LEFT)){
		TranslationX(-m_fSpeed);
	 }
}

//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : ���Ă���v���C���[�̓���
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CPlayer::moveControllerOther()
{
	// �������߂�������t���Ă��Ȃ�
	D3DXVECTOR3 pos = m_pPlayer->GetPosition();
	if(D3DXVec3LengthSq(&(pos - m_pos)) < PLAYER_LENGTH * PLAYER_LENGTH)
		return;

	D3DXVECTOR3 move;
	D3DXVec3Normalize(&move,&(pos - m_pos));
	m_pos += move * m_fSpeed;
	
}
//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : ���Ă���v���C���[�̓���
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CPlayer::moveControllerOther2()
{
	// �������߂�������t���Ă��Ȃ�
	D3DXVECTOR3 pos = m_pPlayer->GetPosition();
	if(D3DXVec3LengthSq(&(pos - m_pos)) < PLAYER_LENGTH * PLAYER_LENGTH)
		return;

	D3DXVECTOR3 move;
	D3DXVec3Normalize(&move,&(pos - m_pos));
	m_pos += move * m_fSpeed;
	
}
//����������������������������������������������������������������������������������������
//	Name        : �A�j��
//	Description : �A�j���[�����
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CPlayer::Animation()
{
	// ��Ԃɂ���ăA�j���[�V�����ω�
	switch (m_status)
	{
	case ST_WAIT:
		FrameAnimation(0, 0, 1, 1, 0.5f);
		break;
	case ST_MOVE:
		FrameAnimation(0, 0, 1, 1, 0.1f);
		break;
	}
	
	
}
//========================================================================================
//	End of File
//========================================================================================