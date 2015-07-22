//========================================================================================
//		File        : Camera.cpp
//		Program     : �J�����N���X
//
//		Description : �J�����N���X�̎���
//
//		History     : 2013/11/26	�쐬�J�n
//					  2014/05/23	�t�@�C�����ύX
//
//																Author : Kei Hashimoto
//========================================================================================


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/PreInclude.h"
#
#include <tchar.h>
#include <math.h>
#include "../../h/System/System.h"
#include "../../h/System/Graphics.h"
#include "../../h/Scene/Game.h"
#include "../../h/Object/GameCamera.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �����o���̐錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
const float CGameCamera::DEFAULT_CAMERA_POS_Z = -2000.0f;
const D3DXVECTOR3 CGameCamera::CAMERA_DEFAULT_POS = D3DXVECTOR3(0.0f,0.0f,DEFAULT_CAMERA_POS_Z);
const float CGameCamera::C_LENGTH_0 = 100;
const float CGameCamera::C_LENGTH_1 = 50;
const float CGameCamera::C_LENGTH_2 = 250;
const float CGameCamera::C_MOVE_SPD = 5;


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CGameCamera::CGameCamera()
{
	m_nPhase = 0;
	m_bMove = false;
	m_eye	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vNextEye	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_look	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_up	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//����������������������������������������������������������������������������������������
//	Name        : �f�X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CGameCamera::~CGameCamera()
{
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �J�����f�[�^������������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameCamera::Init(void)
{
	m_nPhase = PHASE_MAIN;
	m_eye = CAMERA_DEFAULT_POS;
	m_vNextEye = m_eye;
	SyncEyeLook();
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �J�����f�[�^���������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameCamera::Uninit(void)
{
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �J�����f�[�^���X�V����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameCamera::Update()
{
	switch (m_nPhase)
	{
	case PHASE_FADEIN:
	case PHASE_MAIN:
		cameraControllMain();
		break;
	}
	SyncEyeLook();
}
//����������������������������������������������������������������������������������������
//	Name        : �ړ�����
//	Description : �J�����f�[�^���X�V����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameCamera::cameraControllMain()
{
	float move;
	move = m_vNextEye.x - m_eye.x;

	if(abs(move) > C_LENGTH_0){
		m_bMove = true;
	}
	if(abs(move) < C_LENGTH_1){
		m_bMove = false;
	}
	if(abs(move) > C_LENGTH_2){
		m_bMove = false;
		if(move > 0 && m_eye.x < CMapData::GetRightWallX() - SCREEN_WIDTH / 1.25)
			m_eye.x = m_vNextEye.x - C_LENGTH_2;
	//	else if(move > 0)
	//		m_eye.x = CMapData::GetRightWallX() - SCREEN_WIDTH / 1.25;
		if(move < 0 && m_eye.x > CMapData::GetLeftWallX() + SCREEN_WIDTH / 1.25)
			m_eye.x = m_vNextEye.x + C_LENGTH_2;
		else if(move < 0)
			m_eye.x = CMapData::GetLeftWallX() + SCREEN_WIDTH / 1.25f;
	}

	if(m_bMove){
		if(move > 0 && m_eye.x < CMapData::GetRightWallX() - SCREEN_WIDTH / 1.25)
			m_eye.x += C_MOVE_SPD;
		if(move < 0 && m_eye.x > CMapData::GetLeftWallX() + SCREEN_WIDTH / 1.25)
			m_eye.x -= C_MOVE_SPD;
	}

	if(m_vNextEye.y < CMapData::GetTopWallY() - SCREEN_HEIGHT * 0.5f && m_vNextEye.y > CMapData::GetBottomWallY() + SCREEN_HEIGHT * 0.5f)
		m_eye.y = m_vNextEye.y;
	else if(m_vNextEye.y > CMapData::GetTopWallY() - SCREEN_HEIGHT * 0.5f)
		m_eye.y = CMapData::GetTopWallY() - SCREEN_HEIGHT * 0.5f;
	else if(m_vNextEye.y < CMapData::GetBottomWallY() + SCREEN_HEIGHT * 0.5f)
		m_eye.y = CMapData::GetBottomWallY() + SCREEN_HEIGHT * 0.5f;
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �J������`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameCamera::Draw(void)
{	
	// ----- ���݂��Ă��Ȃ���Ζ�����
	if(!m_bExist)
		return;

	// ----- �ϐ��錾
	D3DXMATRIX	matView;		// �r���[ �}�g���b�N�X

	// ----- �J�����ʒu�X�V
	D3DXMatrixLookAtLH(&matView,
						&m_eye,		// ���_���W
						&m_look,	// �����_���W
						&m_up);		// �A�b�v�x�N�g��
	CGraphics::GetDevice()->SetTransform(D3DTS_VIEW, &matView);
}

//����������������������������������������������������������������������������������������
//	Name        : ���
//	Description : �J�����f�[�^���������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameCamera::Release(void)
{
	Finalize();
	delete this;
}

//����������������������������������������������������������������������������������������
//	Name        : ��������
//	Description : �J�����f�[�^�𐶐�����
//	Arguments   : None.
//	Returns     : �J�����f�[�^
//����������������������������������������������������������������������������������������
CGameCamera* CGameCamera::Create(void)
{
	// ----- �ϐ��錾
	CGameCamera* pCamera;

	// ----- ����������
	pCamera = new CGameCamera();
	if(pCamera)
	{
		if(!pCamera->Initialize())
		{
			SAFE_DELETE(pCamera);
		}
	}

	return pCamera;
}


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �ʒu�ƒ����_�̓���
//	Description : �����_���ʒu�Ɠ������W�ɂ���
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameCamera::SyncEyeLook(void)
{
	SetLook(m_eye);
	SetLookZ(0);
	SetUp(D3DXVECTOR3(0,1,0));
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �u���b�N��������������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
bool CGameCamera::Initialize(void)
{
	m_bExist = true;

	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �u���b�N���̎��㏈��������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameCamera::Finalize(void)
{
}

//========================================================================================
//	End of File
//========================================================================================