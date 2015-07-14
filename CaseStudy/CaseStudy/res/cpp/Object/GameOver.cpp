//========================================================================================
//		File        : �Q�[���I�[�o�E�B���h�E
//		Program     : �Q�[���I�[�o�E�B���h�E
//
//		Description : �Q�[���I�[�o�E�B���h�E��`
//
//		History     : 2015/05/31	�쐬�J�n
//						   
//
//																Author : ���񂽂܃Y
//========================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/PreInclude.h"
#
#include <math.h>
#include "../../h/Scene/GameMain.h"
#include "../../h/Object/GameOver.h"
#include "../../h/System/Input.h"
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
const LPCTSTR CGameOver::TEX_FILENAME[MAX_TEX] = {
	_T("res/img/GameScene/Object/block.png"),		// �E�B���h�E�e�N�X�`���t�@�C����
	_T("res/img/GameScene/Object/block.png"),		// �{�^���e�N�X�`���t�@�C����
};

const D3DXVECTOR2 CGameOver::W_0_DEFAULET_SIZE		= D3DXVECTOR2(512,256);
const D3DXVECTOR3 CGameOver::W_0_DEFAULET_POS		= D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0);

const float CGameOver::B_0_POS_INTERVAL_X = 150;

const D3DXVECTOR2 CGameOver::B_0_DEFAULET_SIZE		= D3DXVECTOR2(128,64);
const D3DXVECTOR3 CGameOver::B_0_DEFAULET_POS		=  D3DXVECTOR3(SCREEN_WIDTH / 2 - B_0_POS_INTERVAL_X,
														SCREEN_HEIGHT / 2 + 60,0);

const D3DXVECTOR2 CGameOver::B_1_DEFAULET_SIZE		= D3DXVECTOR2(128,64);
const D3DXVECTOR3 CGameOver::B_1_DEFAULET_POS		=  D3DXVECTOR3(SCREEN_WIDTH / 2 + B_0_POS_INTERVAL_X,
														SCREEN_HEIGHT / 2 + 60,0);

//========================================================================================
// public:
//========================================================================================
//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Description : �R���X�g���N�^
//	Arguments   : 
//	Returns     : 
//����������������������������������������������������������������������������������������
CGameOver::CGameOver()
{
	m_nPhase	= 0;
	m_nCurrent	= 0;
	m_nGo		= 0;

	m_pWnd				= NULL;

	m_pButtonReset		= NULL;
	m_pButtonGoSelect	= NULL;

}

//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : �I�u�W�F�N�g�𐶐�����
//	Arguments   : pszFName / �ǂݍ��݃t�@�C����
//	Returns     : �I�u�W�F�N�g�f�[�^
//����������������������������������������������������������������������������������������
CGameOver* CGameOver::Create()
{
	// ----- �ϐ��錾
	CGameOver* pObj;

	// ----- ����������
	pObj = new CGameOver();
	
	return pObj;
}
//����������������������������������������������������������������������������������������
//	Name        : ��ԍŏ�������
//	Description : 
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameOver::Initialize()
{
		// �E�B���h�E�쐬
	m_pWnd				= CObject2D::Create(TEX_FILENAME[TEX_WND_0]);
	m_pWnd->Init(W_0_DEFAULET_SIZE,D3DXVECTOR3(W_0_DEFAULET_POS.x,W_0_DEFAULET_POS.y,0));
	
	// �{�^���쐬
	m_pButtonReset		= CButton::Create(TEX_FILENAME[TEX_BUTTON_0]);
	m_pButtonGoSelect	= CButton::Create(TEX_FILENAME[TEX_BUTTON_0]);

	m_pButtonReset->Init(B_0_DEFAULET_SIZE,D3DXVECTOR3(B_0_DEFAULET_POS.x,B_0_DEFAULET_POS.y,0));
	m_pButtonGoSelect->Init(B_0_DEFAULET_SIZE,D3DXVECTOR3(B_1_DEFAULET_POS.x,B_1_DEFAULET_POS.y,0));
	
	m_pButtonReset->SetName("Reset");
	m_pButtonGoSelect->SetName("Select");
		
	m_vecButton.push_back(m_pButtonReset);
	m_vecButton.push_back(m_pButtonGoSelect);
}
//����������������������������������������������������������������������������������������
//	Name        : �������
//	Description : 
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameOver::Release()
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
void CGameOver::Init()
{
	m_nPhase = GAME_STOP_PHASE_INIT;
	m_nCurrent = RESET_BUTTON;
	m_nGo		= GO_RESET;

	// �ŏ��̑I���́u�Q�[���ɖ߂�v
	m_vecButton[RESET_BUTTON]->SetPhase(B_PHASE_CHOICE);

	// �f�o�b�O�p
	m_pWnd->SetColor(D3DXVECTOR3(128,128,128));
	m_pWnd->SetAlpha(190);

	for(unsigned int i = 0;i < m_vecButton.size();i++)
		m_vecButton[i]->SetAlpha(190);
}
//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : 
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameOver::Uninit()
{
	
}
//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �����ȍX�V
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameOver::Update()
{
	switch(m_nPhase)
	{
	case GAME_STOP_PHASE_INIT:
	case GAME_STOP_PHASE_WAIT:
		Wait();
		break;
	case GAME_STOP_PHASE_ENTER:
		Enter();
		break;
	case GAME_STOP_PHASE_UNINIT:
		m_nPhase++;
	case GAME_STOP_PHASE_END:
		break;
	}
}
//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �����ȕ`��
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameOver::Draw()
{
	m_pWnd->DrawScreenAlpha();

	for(unsigned int i = 0;i < m_vecButton.size();i++){
		m_vecButton[i]->DrawScreen();
	}
}
//����������������������������������������������������������������������������������������
//	Name        : ����҂�
//	Description : 
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameOver::Wait()
{
	// �I���@���E�L�[
	if(GetTrgKey(DIK_RIGHT)){
		CGameMain::PlaySE(SE_CHOICE);
		if(m_nCurrent < MAX_BUTTON - 1)
			m_nCurrent++;
	}
	if(GetTrgKey(DIK_LEFT)){
		CGameMain::PlaySE(SE_CHOICE);
		if(m_nCurrent > 0)
			m_nCurrent--;
	}

	// ���ݑI������Ă�{�^��
	for(unsigned int i = 0;i < m_vecButton.size();i++){

		if(i == m_nCurrent)
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
		m_vecButton[m_nCurrent]->SetPhase(B_PHASE_ENTER);
		m_nPhase = GAME_STOP_PHASE_ENTER;
	}
}
//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : 
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameOver::Enter()
{
	for(unsigned int i = 0;i < m_vecButton.size();i++){
		if(m_vecButton[i]->GetPhase() == B_PHASE_ENTER){
			switch(i)
			{
			case RESET_BUTTON:
				m_nGo = GO_RESET;
				break;
			case GOSELECT_BUTTON:
				m_nGo = GO_SELECT;
				break;
			}
		}
	}
	
	m_nPhase++;
}
//========================================================================================
//	End of File
//========================================================================================