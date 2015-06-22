//========================================================================================
//		File        : Select.cpp
//		Program     : �y�ȑI���N���X
//
//		Description : �y�ȑI���N���X�̒�`
//
//		History     : 2013/12/18	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/PreInclude.h"
#
#include <tchar.h>
#include "../../h/System/System.h"
#include "../../h/System/Input.h"
#include "../../h/Scene/GameMain.h"
#include "../../h/Scene/Select.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// using�錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
using namespace Input;
using namespace System;

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �����o���̐錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ----- �����o�萔
// private:
const LPCTSTR CSelect::TEX_FILENAME[MAX_TEXLIST] =	// �e�N�X�`���t�@�C����
{
	_T("res/img/BG.jpg"),			// �w�i�e�N�X�`���t�@�C����
	_T("res/img/Fade.jpg"),			// �t�F�[�h�p�e�N�X�`���t�@�C����
	_T("res/img/GameScene/Object/player_0.png"),
	_T("res/img/SelectArrow.png"),
	_T("res/img/SelectStage1.png"),
	_T("res/img/SelectStage2.png"),
	_T("res/img/SelectVisual.png"),
};
const D3DXVECTOR3 CSelect::INIT_CAMERA_EYE(0, 0, -1000);	// �J�����̏������_
const D3DXVECTOR3 CSelect::INIT_CAMERA_LOOK(0, 0, 0);		// �J�����̏��������_
const D3DXVECTOR3 CSelect::INIT_TEXTURE_POS[MAX_TEXLIST] =	// �e�N�X�`���̏����ʒu
{
	D3DXVECTOR3(0.0f, 0.0f, FAR_CLIP),	// �w�i
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �t�B���^�[
};

// ----- �t�F�[�h�֘A
const int CSelect::FADEIN_TIME	= 10;	// �t�F�[�h�C���Ԋu(�A���t�@�l:0�`255)
const int CSelect::FADEOUT_TIME	= 10;	// �t�F�[�h�A�E�g�Ԋu(�A���t�@�l:0�`255)


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CSelect::CSelect()
{
	m_pCamera		= NULL;
	m_pFilter		= NULL;

	m_phase			= MAX_PHASE;
	
	for (int i = 0; i < MAX_OBJECTLIST; i++)
		m_pSelectPlayer[MAX_OBJECTLIST] = NULL;

	m_nStatus		= S_STATUS_WAIT;
	m_nStage		= S_STAGE_1;
}

//����������������������������������������������������������������������������������������
//	Name        : �f�X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CSelect::~CSelect()
{
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �y�ȑI��������������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CSelect::Init(void)
{
	// ----- �J����������
	m_pCamera->Init();
	D3DXVECTOR3 eye = INIT_CAMERA_EYE;
	D3DXVECTOR3 look = INIT_CAMERA_LOOK;
	D3DXVECTOR3 up = D3DXVECTOR3(0, 1, 0);
	m_pCamera->SetParameter(eye, look, up);

	// ----- �e�N�X�`��������
	m_pBG->Init(D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT), INIT_TEXTURE_POS[TL_BG]);			// �w�i
	m_pFilter->Init(D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT), INIT_TEXTURE_POS[TL_FADE]);		// �t�B���^�[

	m_pSelectPlayer[OL_PLAYER]->Init(D3DXVECTOR2(192, 192), D3DXVECTOR3((float)PLAYER_INIT_POS_X, (float)PLAYER_INIT_POS_Y, 0));
	m_pSelectPlayer[OL_ARROW_LEFT]->Init(D3DXVECTOR2(192, 192), D3DXVECTOR3((float)LEFT_ARROW_INIT_POS_X, (float)LEFT_ARROW_INIT_POS_Y, 0));
	m_pSelectPlayer[OL_ARROW_RIGHT]->Init(D3DXVECTOR2(192, 192), D3DXVECTOR3((float)RIGHT_ARROW_INIT_POS_X, (float)RIGHT_ARROW_INIT_POS_Y, 0));
	m_pSelectPlayer[OL_ROGO1]->Init(D3DXVECTOR2(384, 192), D3DXVECTOR3((float)ROGO_INIT_POS_X, (float)ROGO_INIT_POS_Y, 0));
	m_pSelectPlayer[OL_ROGO2]->Init(D3DXVECTOR2(384, 192), D3DXVECTOR3((float)ROGO_SCREEN_OUT_POS_X, (float)ROGO_SCREEN_OUT_POS_Y, 0));
	m_pSelectPlayer[OL_STAGE]->Init(D3DXVECTOR2(SCREEN_RIGHT * 2, SCREEN_RIGHT * 2), D3DXVECTOR3((float)STAGE_INIT_POS_X, (float)STAGE_INIT_POS_Y, 0));

	// ----- BGM�Đ�
//	CGameMain::PlayBGM(BGM_SELECT, DSBPLAY_LOOPING);

	// ----- ���̃t�F�[�Y��
	m_phase = PHASE_FADEIN;		// �t�F�[�h�C���J�n
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �y�ȑI���̏I������������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CSelect::Uninit(void)
{
	// ----- �I�u�W�F�N�g��n��
	m_pCamera->Uninit();		// �J����

	// ----- �e�N�X�`����n��
	m_pBG->Uninit();			// �w�i
	m_pFilter->Uninit();	// �t�B���^�[
	
	// ----- BGM��~
//	CGameMain::StopBGM(BGM_SELECT);
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �y�ȑI�����X�V����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CSelect::Update(void)
{
	// ----- �I�u�W�F�N�g�X�V
	m_pCamera->Update();		// �J����
			
	switch(m_phase)
	{
		// �t�F�[�h�C��
		case PHASE_FADEIN:
			if(m_pFilter->FadeOutAlpha(FADEIN_TIME)) {
				m_phase = PHASE_MAIN;		// �y�ȑI��{�ҊJ�n
			}
			break;

		// ���̃V�[���փt�F�[�h�A�E�g
		case PHASE_FADEOUT:
			if(m_pFilter->FadeInAlpha(FADEOUT_TIME)) {
				Uninit();						// ��n��
				CGameMain::SetScene(SID_GAME);	// �Q�[���{�҂�
			}
			break;

		// �y�ȑI��{��
		case PHASE_MAIN:
			Main();
			break;
			
		default:
			break;
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �y�ȑI����ʂ�`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CSelect::Draw(void)
{
	// ----- �J�����`��
	m_pCamera->Draw();

	// ----- �e�N�X�`���`��
	m_pBG->DrawAlpha();		// �w�i

	switch(m_phase)
	{
		// �t�F�[�h�C���E�A�E�g
		case PHASE_FADEIN:
		case PHASE_FADEOUT:
			m_pFilter->DrawAlpha();
			break;

		// �y�ȑI��{��
		case PHASE_MAIN:
			break;
			
		default:
			break;
	}
	for (int i = 0; i < MAX_OBJECTLIST; i++)
		m_pSelectPlayer[i]->DrawAlpha();
}

//����������������������������������������������������������������������������������������
//	Name        : ��������
//	Description : �y�ȑI���f�[�^�𐶐�����
//	Arguments   : None.
//	Returns     : �y�ȑI���f�[�^
//����������������������������������������������������������������������������������������
CSelect* CSelect::Create()
{
	// ----- �ϐ��錾
	CSelect* pSelect;

	// ----- ����������
	pSelect = new CSelect();
	if(pSelect)
	{
		if(!pSelect->Initialize())
		{
			SAFE_DELETE(pSelect);
		}
	}

	return pSelect;
}


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �y�ȑI��������������
//	Arguments   : None.
//	Returns     : ����(true:����)
//����������������������������������������������������������������������������������������
bool CSelect::Initialize()
{
	// ----- �J��������
	m_pCamera = CCamera::Create();
	if(m_pCamera == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CSelect::Camera�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}

	// ----- �e�N�X�`������
	// �w�i
	m_pBG = CTexture::Create(TEX_FILENAME[TL_BG]);
	if(m_pBG == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CSelect::BG�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}
	// �t�F�[�h�p�t�B���^�[
	m_pFilter = CTexture::Create(TEX_FILENAME[TL_FADE]);
	if(m_pFilter == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CSelect::Filter�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}

	m_pSelectPlayer[OL_PLAYER] = CSelectObject::Create(TEX_FILENAME[TL_PLAYER]);
	m_pSelectPlayer[OL_ARROW_LEFT] = CSelectObject::Create(TEX_FILENAME[TL_ARROW]);
	m_pSelectPlayer[OL_ARROW_RIGHT] = CSelectObject::Create(TEX_FILENAME[TL_ARROW]);
	m_pSelectPlayer[OL_ROGO1] = CSelectObject::Create(TEX_FILENAME[TL_ROGO1]);
	m_pSelectPlayer[OL_ROGO2] = CSelectObject::Create(TEX_FILENAME[TL_ROGO2]);
	m_pSelectPlayer[OL_STAGE] = CSelectObject::Create(TEX_FILENAME[TL_STAGE]);

	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �y�ȑI���̏I������������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CSelect::Finalize(void)
{
	// ----- �e�N�X�`�����
	SAFE_RELEASE(m_pFilter);	// �t�B���^�[
	SAFE_RELEASE(m_pBG);		// �w�i

	// ----- �J�������
	SAFE_RELEASE(m_pCamera)
}

//����������������������������������������������������������������������������������������
//	Name        : ���C��
//	Description : �y�ȑI���̃��C������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CSelect::Main()
{
	if (GetTrgKey(DIK_LEFT))		// ��
	{
		m_nStatus = S_STATUS_LEFT;
		if (m_nStage == S_STAGE_1)
			m_nStage = S_STAGE_2;
		else
			m_nStage = S_STAGE_1;
	}
	if (GetTrgKey(DIK_RIGHT))		// �E
	{
		m_nStatus = S_STATUS_RIGHT;
		if (m_nStage == S_STAGE_1)
			m_nStage = S_STAGE_2;
		else
			m_nStage = S_STAGE_1;
	}

	m_nStatus = m_pSelectPlayer[OL_PLAYER]->PlayerUpdate(m_nStatus);
	m_pSelectPlayer[OL_ROGO1]->RogoUpdate(1,m_nStatus,m_nStage);
	m_pSelectPlayer[OL_ROGO2]->RogoUpdate(2,m_nStatus,m_nStage);
	m_nStatus = m_pSelectPlayer[OL_STAGE]->StageUpdate(m_nStatus,m_nStage);
	m_nStatus = m_pSelectPlayer[OL_ARROW_LEFT]->ArrowUpdate(1,m_nStatus);
	m_nStatus = m_pSelectPlayer[OL_ARROW_RIGHT]->ArrowUpdate(2,m_nStatus);

	// ----- ���̃V�[����
	if(GetTrgKey(DIK_RETURN)) {
		m_phase = PHASE_FADEOUT;		// ���̃V�[���փt�F�[�h�A�E�g�J�n
	}
}


//========================================================================================
//	End of File
//========================================================================================