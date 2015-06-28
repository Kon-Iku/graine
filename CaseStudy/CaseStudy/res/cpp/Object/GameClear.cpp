//========================================================================================
//		File        : �Q�[���N���A�E�B���h�E
//		Program     : �Q�[���N���A�E�B���h�E
//
//		Description : �Q�[���N���A�E�B���h�E��`
//
//		History     : 2015/06/22	�쐬�J�n
//						   
//
//																Author : Kei Hashimoto
//========================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/PreInclude.h"
#
#include <math.h>
#include "../../h/System/Graphics.h"
#include "../../h/System/Input.h"
#include "../../h/System/ChangeScene.h"
#include "../../h/Object/GameClear.h"
#include <tchar.h>

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// using�錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
using namespace System;
using namespace Input;

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �����o���̐錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ----- �����o�萔
// private:
const LPCTSTR CGameClear::TEX_FILENAME[MAX_TEX] = {
	_T("res/img/GameScene/Object/block.png"),		// �E�B���h�E�e�N�X�`���t�@�C����
	_T("res/img/GameScene/Object/block.png"),		// �{�^���e�N�X�`���t�@�C����
};

const D3DXVECTOR2 CGameClear::W_0_DEFAULET_SIZE		= D3DXVECTOR2(512,256);
const D3DXVECTOR3 CGameClear::W_0_DEFAULET_POS		= D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);

const float CGameClear::B_0_POS_INTERVAL_X = 150;

const D3DXVECTOR2 CGameClear::B_0_DEFAULET_SIZE		= D3DXVECTOR2(128,64);
const D3DXVECTOR3 CGameClear::B_0_DEFAULET_POS		=  D3DXVECTOR3(SCREEN_WIDTH / 2 - B_0_POS_INTERVAL_X,
														SCREEN_HEIGHT / 2 + 60,0);

const D3DXVECTOR2 CGameClear::B_1_DEFAULET_SIZE		= D3DXVECTOR2(128,64);
const D3DXVECTOR3 CGameClear::B_1_DEFAULET_POS		=  D3DXVECTOR3(SCREEN_WIDTH / 2 + B_0_POS_INTERVAL_X,
														SCREEN_HEIGHT / 2 + 60,0);

const D3DXVECTOR3 CGameClear::DIRECTION_CAMERA_SPD	= D3DXVECTOR3(0.0f, 0.0f, 10.0f);	// ���o���̃J�����ړ����x

//========================================================================================
// public:
//========================================================================================
//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Description : �R���X�g���N�^
//	Arguments   : 
//	Returns     : 
//����������������������������������������������������������������������������������������
CGameClear::CGameClear()
{
	m_nPhase		= 0;
	m_nCurButton	= 0;
	m_nGo			= 0;

	m_pWnd				= NULL;

	m_pButtonNext		= NULL;
	m_pButtonGoSelect	= NULL;

	m_pCamera			= NULL;
	m_cameraStartPos	= D3DXVECTOR2(0.0f, 0.0f);
	m_dirDist			= 0.0f;
}

//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : �I�u�W�F�N�g�𐶐�����
//	Arguments   : pszFName / �ǂݍ��݃t�@�C����
//	Returns     : �I�u�W�F�N�g�f�[�^
//����������������������������������������������������������������������������������������
CGameClear* CGameClear::Create()
{
	// ----- �ϐ��錾
	CGameClear* pObj;

	// ----- ����������
	pObj = new CGameClear();
	
	return pObj;
}

//����������������������������������������������������������������������������������������
//	Name        : ��ԍŏ�������
//	Description : 
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameClear::Initialize()
{
		// �E�B���h�E�쐬
	m_pWnd				= CObject2D::Create(TEX_FILENAME[TEX_WND_0]);
	m_pWnd->Init(W_0_DEFAULET_SIZE,W_0_DEFAULET_POS);
	
	// �{�^���쐬
	m_pButtonNext		= CButton::Create(TEX_FILENAME[TEX_BUTTON_0]);
	m_pButtonGoSelect	= CButton::Create(TEX_FILENAME[TEX_BUTTON_0]);

	m_pButtonNext->Init(B_0_DEFAULET_SIZE,B_0_DEFAULET_POS);
	m_pButtonGoSelect->Init(B_0_DEFAULET_SIZE,B_1_DEFAULET_POS);
	
	m_pButtonNext->SetName("Next");
	m_pButtonGoSelect->SetName("Select");
		
	m_vecButton.push_back(m_pButtonNext);
	m_vecButton.push_back(m_pButtonGoSelect);
}

//����������������������������������������������������������������������������������������
//	Name        : �������
//	Description : 
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameClear::Release()
{
	if(m_pWnd){
		m_pWnd->Uninit();
		SAFE_RELEASE(m_pWnd)
	}

	// ���X�g���S����n��
	for (unsigned int i = 0;i < m_vecButton.size(); ++i){
		m_vecButton[i]->Uninit();
		SAFE_RELEASE(m_vecButton[i])
	}

	m_vecButton.clear();		// �I�u�W�F�N�g���X�g
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �����ȏ�����
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameClear::Init()
{
	m_nPhase = PHASE_INIT;
	m_nCurButton = NEXT_BUTTON;
	m_nGo		= GO_NEXT;

	// �ŏ��̑I���́u�Q�[���ɖ߂�v
	m_vecButton[NEXT_BUTTON]->SetPhase(B_PHASE_CHOICE);

	// �f�o�b�O�p
	m_pWnd->SetColor(D3DXVECTOR3(128,128,128));
	m_pWnd->SetAlpha(190);

	for(unsigned int i = 0;i < m_vecButton.size();i++)
		m_vecButton[i]->SetAlpha(190);
	
	m_pCamera			= NULL;
	m_cameraStartPos	= D3DXVECTOR2(0.0f, 0.0f);
	m_dirDist			= 0.0f;

	m_nPhase = PHASE_INIT_DIRECTION;
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : 
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameClear::Uninit()
{
	// ----- �O���t�B�b�N�X�ݒ��������
	CGraphics::SetDraw2D();
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �����ȍX�V
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameClear::Update()
{
	switch(m_nPhase)
	{
	case PHASE_INIT:
	case PHASE_FADEIN_DIRECTION:
		break;
	case PHASE_INIT_DIRECTION:
		InitDirection();
		break;
	case PHASE_DIRECTION:
		Direction();
		break;
	case PHASE_UNINIT_DIRECTION:
		UninitDirection();
		break;
	case PHASE_WAIT:
		Wait();
		break;
	case PHASE_ENTER:
		Enter();
		break;
	case PHASE_UNINIT:
		m_nPhase = PHASE_END;
		break;
	case PHASE_END:
		break;
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �����ȕ`��
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameClear::Draw()
{
	switch(m_nPhase)
	{
	case PHASE_INIT:
	case PHASE_INIT_DIRECTION:
	case PHASE_DIRECTION:
	case PHASE_UNINIT_DIRECTION:
		break;

	case PHASE_FADEIN_DIRECTION:
		FadeinDirection();
		break;

	case PHASE_WAIT:
	case PHASE_ENTER:
		m_pWnd->DrawScreenAlpha();

		for(unsigned int i = 0;i < m_vecButton.size();i++){
			m_vecButton[i]->DrawScreen();
		}
		break;

	case PHASE_UNINIT:
		m_nPhase = PHASE_END;
		break;

	case PHASE_END:
		break;
	}
}

//����������������������������������������������������������������������������������������
//	Name        : ���o����
//	Description : �Q�[���N���A���o�̏���������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
bool CGameClear::InitDirection()
{
	if(!m_pCamera)
		return false;

	// ----- �J�����̈ړ���������
	CGraphics::SetDraw3D();
	m_pCamera->SetEyeX(m_cameraStartPos.x);
	m_pCamera->SetEyeY(m_cameraStartPos.y);

	// ----- �t�F�[�h�C������
	D3DXVECTOR3 fadePos(m_cameraStartPos.x, m_cameraStartPos.y, 0.0f);
	CChangeScene::SetNormalFadePos(fadePos);
	CChangeScene::SetNormalFadeAlpha(255);

	m_nPhase = PHASE_FADEIN_DIRECTION;
	
	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : ���o�����t�F�[�h�C��
//	Description : ���o�����ɓ��邽�߂̃t�F�[�h�C������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameClear::FadeinDirection()
{
	if(CChangeScene::NormalFadeOut(0.0f, 1))
		m_nPhase = PHASE_DIRECTION;
}

//����������������������������������������������������������������������������������������
//	Name        : ���o����
//	Description : �J��������ʂ��������蓙�A���o���s��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameClear::Direction()
{
	// ----- �X�e�[�W����Ղ���
	float z = m_pCamera->GetEye().z;
	z -= DIRECTION_CAMERA_SPD.z;
	m_pCamera->SetEyeZ(z);

	// ----- ���Պ���(���o�I��)
	if(m_dirDist <= tanf(D3DXToRadian(FOVY)) * -z)
		m_nPhase = PHASE_UNINIT_DIRECTION;
}

//����������������������������������������������������������������������������������������
//	Name        : ���o���㏈��
//	Description : �Q�[���N���A���o�̎��㏈��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameClear::UninitDirection()
{
	m_nPhase = PHASE_WAIT;
}

//����������������������������������������������������������������������������������������
//	Name        : ����҂�
//	Description : 
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameClear::Wait()
{
	// �I���@���E�L�[
	if(GetTrgKey(DIK_RIGHT)){
		if(m_nCurButton < MAX_BUTTON - 1)
			m_nCurButton++;
	}
	if(GetTrgKey(DIK_LEFT)){
		if(m_nCurButton > 0)
			m_nCurButton--;
	}

	// ���ݑI������Ă�{�^��
	for(unsigned int i = 0;i < m_vecButton.size();i++){

		if(i == m_nCurButton)
			m_vecButton[i]->SetPhase(B_PHASE_CHOICE);
		else
			m_vecButton[i]->SetPhase(B_PHASE_WAIT);

		if(m_vecButton[i]->GetPhase() == B_PHASE_CHOICE){
			m_vecButton[i]->SetColor(D3DXVECTOR3(255,255,0));
		}else{
			m_vecButton[i]->SetColor(D3DXVECTOR3(255,255,255));
		}
	}

	// ����
	if(GetTrgKey(DIK_RETURN)){
		m_vecButton[m_nCurButton]->SetPhase(B_PHASE_ENTER);
		m_nPhase = PHASE_ENTER;
	}
}

//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : 
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameClear::Enter()
{
	for(unsigned int i = 0;i < m_vecButton.size();i++){
		if(m_vecButton[i]->GetPhase() == B_PHASE_ENTER){
			switch(i)
			{
			case NEXT_BUTTON:
				m_nGo = GO_NEXT;
				break;
			case GOSELECT_BUTTON:
				m_nGo = GO_SELECT;
				break;
			}
		}
	}
	
	m_nPhase = PHASE_UNINIT;
}

//========================================================================================
//	End of File
//========================================================================================