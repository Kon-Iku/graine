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
#include "../../h/Scene/GameMain.h"
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
	_T("res/img/GameScene/Popup/WindowS.png"),		// �E�B���h�E�e�N�X�`���t�@�C����
	_T("res/img/GameScene/Popup/Next.png"),			// �{�^���e�N�X�`���t�@�C����
	_T("res/img/GameScene/Popup/Select.png"),		// �{�^���e�N�X�`���t�@�C����
	_T("res/img/Fade.jpg"),
	_T("res/img/GameScene/Popup/GameClear.png"),
};

const D3DXVECTOR2 CGameClear::FILTER_SIZE((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
const D3DXVECTOR3 CGameClear::FILTER_POS((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);

const D3DXVECTOR2 CGameClear::W_0_DEFAULET_SIZE		= D3DXVECTOR2(330,351);
const D3DXVECTOR3 CGameClear::W_0_DEFAULET_POS		= D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);

const D3DXVECTOR2 CGameClear::TEXT_SIZE(399.0f * 0.6f - 5.0f, 109.0f * 0.6f);
const D3DXVECTOR3 CGameClear::TEXT_POS((float)SCREEN_WIDTH * 0.5f, 240.0f, 0.0f);

const float CGameClear::B_0_POS_INTERVAL_Y = 40;

const D3DXVECTOR2 CGameClear::B_0_DEFAULET_SIZE		= D3DXVECTOR2(200,73);
const D3DXVECTOR3 CGameClear::B_0_DEFAULET_POS		=  D3DXVECTOR3(SCREEN_WIDTH / 2 - 5.0f,
														SCREEN_HEIGHT / 2 - B_0_POS_INTERVAL_Y + 40.0f,0);

const D3DXVECTOR2 CGameClear::B_1_DEFAULET_SIZE		= D3DXVECTOR2(200,73);
const D3DXVECTOR3 CGameClear::B_1_DEFAULET_POS		=  D3DXVECTOR3(SCREEN_WIDTH / 2 - 5.0f,
														SCREEN_HEIGHT / 2 + B_0_POS_INTERVAL_Y + 40.0f,0);

const D3DXVECTOR3 CGameClear::DIRECTION_CAMERA_SPD	= D3DXVECTOR3(0.0f, 0.0f, 8.0f);	// ���o���̃J�����ړ����x
const float CGameClear::DIRECTION_ADJUST_DIST		= 600.0f;							// ���o���̃J�������Ջ����̒����l

const int CGameClear::FADEIN_TIME = 5;		// �t�F�[�h�C���Ԋu(�A���t�@�l:0�`255)
const int CGameClear::FADEOUT_TIME = 10;		// �t�F�[�h�A�E�g�Ԋu(�A���t�@�l:0�`255)

const int CGameClear::DRAWTEX_FADEIN_TIME = 5;


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

	m_pFilter			= NULL;
	m_pWnd				= NULL;
	m_pText				= NULL;

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
	m_pFilter = CObject2D::Create(TEX_FILENAME[TEX_FILTER]);

	// �E�B���h�E�쐬
	m_pWnd	= CObject2D::Create(TEX_FILENAME[TEX_WND_0]);
	m_pWnd->Init(W_0_DEFAULET_SIZE,W_0_DEFAULET_POS);
	
	m_pText = CObject2D::Create(TEX_FILENAME[TEX_TEXT]);
	
	// �{�^���쐬
	m_pButtonNext		= CButton::Create(TEX_FILENAME[TEX_NEXT]);
	m_pButtonGoSelect	= CButton::Create(TEX_FILENAME[TEX_SELECT]);

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
	if(m_pFilter){
		m_pFilter->Uninit();
		SAFE_RELEASE(m_pFilter)
	}

	if(m_pWnd){
		m_pWnd->Uninit();
		SAFE_RELEASE(m_pWnd)
	}

	if(m_pText){
		m_pText->Uninit();
		SAFE_RELEASE(m_pText)
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
	
	m_pFilter->Init(FILTER_SIZE, FILTER_POS);

	m_pText->Init(TEXT_SIZE, TEXT_POS);

	// �ŏ��̑I���́u�Q�[���ɖ߂�v
	m_vecButton[NEXT_BUTTON]->SetPhase(B_PHASE_CHOICE);
	
	m_pCamera			= NULL;
	m_cameraStartPos	= D3DXVECTOR2(0.0f, 0.0f);
	m_dirDist			= 0.0f;

	m_pWnd->SetAlpha(0);
	m_pText->SetAlpha(0);
	for (unsigned int i = 0;i < m_vecButton.size(); ++i)
		m_vecButton[i]->SetAlpha(0);

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
//	CGraphics::SetDraw2D();
	m_pFilter->Uninit();
	m_pText->Uninit();
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �����ȍX�V
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameClear::Update(CObject2D* pDark, CObject2D* pLight, D3DXVECTOR2* pClipSize)
{
	switch(m_nPhase)
	{
	case PHASE_INIT:
		break;
	case PHASE_FADEIN_DIRECTION:
		FadeinDirection();
		break;
	case PHASE_INIT_DIRECTION:
		InitDirection();
		pDark->TranslateX(m_cameraStartPos.x);
		pDark->TranslateY(m_cameraStartPos.y);
		pLight->TranslateX(m_cameraStartPos.x);
		pLight->TranslateY(m_cameraStartPos.y);
		break;
	case PHASE_DIRECTION:
		Direction(pDark, pLight, pClipSize);
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
	case PHASE_DIRECTION:
		break;

	case PHASE_INIT:
	case PHASE_INIT_DIRECTION:
	case PHASE_FADEIN_DIRECTION:
	case PHASE_UNINIT_DIRECTION:
		m_pFilter->DrawScreenAlpha();
		break;

	case PHASE_WAIT:
	case PHASE_ENTER:
		m_pWnd->DrawScreenAlpha();
		m_pText->DrawScreenAlpha();

		for(unsigned int i = 0;i < m_vecButton.size();i++){
			m_vecButton[i]->DrawScreenAlpha();
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
//	CGraphics::SetDraw3D();
	m_pCamera->SetEyeX(m_cameraStartPos.x);
	m_pCamera->SetEyeY(m_cameraStartPos.y);

	// ----- �t�F�[�h�C������
	//D3DXVECTOR3 fadePos(m_cameraStartPos.x, m_cameraStartPos.y, 0.0f);
	//CChangeScene::SetNormalFadePos(fadePos);
	//CChangeScene::SetNormalFadeAlpha(255);

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
	if(m_pFilter->FadeOutAlpha(FADEIN_TIME)) {
		m_nPhase = PHASE_DIRECTION;
	}
}

//����������������������������������������������������������������������������������������
//	Name        : ���o����
//	Description : �J��������ʂ��������蓙�A���o���s��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameClear::Direction(CObject2D* pDark, CObject2D* pLight, D3DXVECTOR2* pClipSize)
{
	// ----- �X�e�[�W����Ղ���
	float z = m_pCamera->GetEye().z;
	z -= DIRECTION_CAMERA_SPD.z;
	m_pCamera->SetEyeZ(z);

	// ----- �w�i�T�C�Y�̒���
	const float SCALE = 0.004f;
	pDark->ScalingX(SCALE);
	pDark->ScalingY(SCALE);
	pLight->ScalingX(SCALE);
	pLight->ScalingY(SCALE);
	
	// ----- �N���b�v�T�C�Y�̒���
	const float CLIP_SCALE = 20.0f;
	pClipSize->x += CLIP_SCALE;
	pClipSize->y += CLIP_SCALE;

	// ----- ���Պ���(���o�I��)
	if(m_dirDist <= tanf(D3DXToRadian(FOVY)) * -z + DIRECTION_ADJUST_DIST)
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
	// �I���@�㉺�L�[
	if(GetTrgKey(DIK_DOWN)){
		CGameMain::PlaySE(SE_CHOICE);
		if(m_nCurButton < MAX_BUTTON - 1)
			m_nCurButton++;
	}
	if(GetTrgKey(DIK_UP)){
		CGameMain::PlaySE(SE_CHOICE);
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
		CGameMain::PlaySE(SE_ENTER);
		m_vecButton[m_nCurButton]->SetPhase(B_PHASE_ENTER);
		m_nPhase = PHASE_ENTER;
	}

	// ----- �e�N�X�`������
	m_pWnd->FadeInAlpha(DRAWTEX_FADEIN_TIME);
	m_pText->FadeInAlpha(DRAWTEX_FADEIN_TIME);
	for(unsigned int i = 0; i < m_vecButton.size(); ++i)
		m_vecButton[i]->FadeInAlpha(DRAWTEX_FADEIN_TIME);
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