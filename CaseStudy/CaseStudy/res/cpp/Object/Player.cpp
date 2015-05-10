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
	m_bStop = true;			// �~�܂��Ă�
	m_nNo = 0;				// �ŏ��͑S��0�@�����ς��
	m_nPhase = P_STOP;
	m_nType = P_TYPE_OTHER; // ����͂��Ƃŕς��Ȃ��Ƃ������

	// �X�s�[�h����
	
	m_fSpeed = PLAYER_MOVE_SPD + (0.1f *(rand() % 10)) + rand()%3;

	m_fGravity = GRAVITY_CASE_2;
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
	switch (m_nType){
	case P_TYPE_PLAYER:
			moveControllerPlayer();
		break;
	case P_TYPE_OTHER:
			moveControllerOther();
		break;
	}

	Animation();

	// ����͐�΂ɍŌ�ɗ���悤�ɂˁ�
	CObject2Dsub::Update();
}
//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : ���삷��v���C���[�̓���
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CPlayer::moveControllerPlayer()
{
	m_bStop = true;
	// �L�[����
	if (GetPrsKey(DIK_RIGHT)){		// �E
		m_pos.x += m_fSpeed;

		if (m_nState != P_MOVE){
			m_nState = P_MOVE;	// �����Ă�
		}
		// �����Ă������ς���
		if (m_scale.x < 0)
			m_scale.x = -m_scale.x;
		m_bStop = false;
	}	
	if (GetPrsKey(DIK_LEFT)){		// ��

		m_pos.x -= m_fSpeed;

		if (m_nState != P_MOVE){
			m_nState = P_MOVE;	// �����Ă�
		}
		// �����Ă������ς���
		if (m_scale.x > 0)
			m_scale.x = -m_scale.x;
		m_bStop = false;
	}
	if (m_bStop == true)
		m_nState = P_STOP;
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
//	Name        : �A�j��
//	Description : �A�j���[�����
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CPlayer::Animation()
{
	// m_nState�ɂ���ăA�j���[�V�����ω�
	switch (m_nState)
	{
	case P_STOP:
		FrameAnimation(1, 7, 10, 2, 0.5f);
//		TimeAnimation(0, 0, 10, 2, 0.05f);
		break;
	case P_MOVE:
		FrameAnimation(1, 7, 10, 2, 0.1f);
//		TimeAnimation(1, 6, 10, 2, 0.05f);
		break;
	}
	
	
}
//========================================================================================
//	End of File
//========================================================================================