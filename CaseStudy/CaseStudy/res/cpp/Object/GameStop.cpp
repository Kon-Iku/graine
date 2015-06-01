//========================================================================================
//		File        : Button.h
//		Program     : �{�^���x�[�X
//
//		Description : �{�^���x�[�X�̒�`
//
//		History     : 2015/05/29	�쐬�J�n
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
#include "../../h/Object/GameStop.h"
#include "../../h/System/Input.h"
#include <tchar.h>

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// using�錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
using namespace System;
using namespace Input;


// ----- �����o�萔
// private:
const LPCTSTR CGameStop::TEX_FILENAME[MAX_TEX] = {
	_T("res/img/GameScene/Object/block.png"),		// �E�B���h�E�e�N�X�`���t�@�C����
	_T("res/img/GameScene/Object/block.png"),		// �{�^���e�N�X�`���t�@�C����
};

//========================================================================================
// public:
//========================================================================================
//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Description : �R���X�g���N�^
//	Arguments   : 
//	Returns     : 
//����������������������������������������������������������������������������������������
CGameStop::CGameStop()
{
	m_nPhase	= 0;
	m_nCurrent	= 0;
	m_nGo		= 0;

	m_pWnd				= NULL;

	m_pButtonGoGame		= NULL;
	m_pButtonReset		= NULL;
	m_pButtonGoSelect	= NULL;

}

//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : �I�u�W�F�N�g�𐶐�����
//	Arguments   : pszFName / �ǂݍ��݃t�@�C����
//	Returns     : �I�u�W�F�N�g�f�[�^
//����������������������������������������������������������������������������������������
CGameStop* CGameStop::Create()
{
	// ----- �ϐ��錾
	CGameStop* pObj;

	// ----- ����������
	pObj = new CGameStop();
	
	return pObj;
}
//����������������������������������������������������������������������������������������
//	Name        : ��ԍŏ�������
//	Description : 
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameStop::Initialize()
{
		// �E�B���h�E�쐬
	m_pWnd				= CTexture::Create(TEX_FILENAME[TEX_WND_0]);
	m_pWnd->Init(W_0_DEFAULET_SIZE,D3DXVECTOR3(W_0_DEFAULET_POS.x,W_0_DEFAULET_POS.y,0));
	
	// �{�^���쐬
	m_pButtonGoGame		= CButton::Create(TEX_FILENAME[TEX_BUTTON_0]);
	m_pButtonReset		= CButton::Create(TEX_FILENAME[TEX_BUTTON_0]);
	m_pButtonGoSelect	= CButton::Create(TEX_FILENAME[TEX_BUTTON_0]);

	m_pButtonGoGame->Init(B_0_DEFAULET_SIZE,D3DXVECTOR3(B_0_DEFAULET_POS.x - B_0_POS_INTERVAL_X,B_0_DEFAULET_POS.y,0));
	m_pButtonReset->Init(B_0_DEFAULET_SIZE,D3DXVECTOR3(B_0_DEFAULET_POS.x,B_0_DEFAULET_POS.y,0));
	m_pButtonGoSelect->Init(B_0_DEFAULET_SIZE,D3DXVECTOR3(B_0_DEFAULET_POS.x + B_0_POS_INTERVAL_X,B_0_DEFAULET_POS.y,0));
	
	m_pButtonGoGame->SetName("GoGame");
	m_pButtonReset->SetName("Reset");
	m_pButtonGoSelect->SetName("Select");
		
	m_vecButton.push_back(m_pButtonGoGame);
	m_vecButton.push_back(m_pButtonReset);
	m_vecButton.push_back(m_pButtonGoSelect);
}
//����������������������������������������������������������������������������������������
//	Name        : �������
//	Description : 
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameStop::Release()
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
void CGameStop::Init()
{
	m_nPhase = GAME_STOP_PHASE_INIT;
	m_nCurrent = GOGAME_BUTTON;
	m_nGo		= GO_GAME;

	// �ŏ��̑I���́u�Q�[���ɖ߂�v
	m_vecButton[GOGAME_BUTTON]->SetPhase(B_PHASE_CHOICE);

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
void CGameStop::Uninit()
{
	
}
//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �����ȍX�V
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameStop::Update()
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
void CGameStop::Draw()
{
	m_pWnd->DrawAlpha();

	for(unsigned int i = 0;i < m_vecButton.size();i++){
		m_vecButton[i]->Draw();
	}
}
//����������������������������������������������������������������������������������������
//	Name        : ����҂�
//	Description : 
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CGameStop::Wait()
{
	// �I���@���E�L�[
	if(GetTrgKey(DIK_RIGHT)){
		if(m_nCurrent < MAX_BUTTON - 1)
			m_nCurrent++;
	}
	if(GetTrgKey(DIK_LEFT)){
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
void CGameStop::Enter()
{
	for(unsigned int i = 0;i < m_vecButton.size();i++){
		if(m_vecButton[i]->GetPhase() == B_PHASE_ENTER){
			switch(i)
			{
			case GOGAME_BUTTON:
				m_nGo = GO_GAME;
				break;
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