//========================================================================================
//		File        : Result.cpp
//		Program     : ���U���g�N���X
//
//		Description : ���U���g�N���X�̎���
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
#include "../../h/Scene/Result.h"

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
const LPCTSTR CResult::TEX_FILENAME[MAX_TEXLIST] =	// �e�N�X�`���t�@�C����
{
	_T("res/img/BG.jpg"),			// �w�i�e�N�X�`���t�@�C����
	_T("res/img/Fade.jpg"),			// �t�F�[�h�p�e�N�X�`���t�@�C����
};
const D3DXVECTOR3 CResult::INIT_CAMERA_EYE(0, 0, -1000);			// �J�����̏������_
const D3DXVECTOR3 CResult::INIT_CAMERA_LOOK(0, 0, 0);			// �J�����̏��������_
const D3DXVECTOR3 CResult::INIT_TEXTURE_POS[MAX_TEXLIST] = {	// �e�N�X�`���̏����ʒu
	D3DXVECTOR3(0.0f, 0.0f, FAR_CLIP),	// �w�i
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �t�B���^�[
};

// ----- �t�F�[�h�֘A
const int CResult::FADEIN_TIME	= 10;	// �t�F�[�h�C���Ԋu(�A���t�@�l:0�`255)
const int CResult::FADEOUT_TIME	= 10;	// �t�F�[�h�A�E�g�Ԋu(�A���t�@�l:0�`255)


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CResult::CResult()
{
	m_pCamera	= NULL;
	m_pBG		= NULL;
	m_pFilter	= NULL;
	
	m_phase	= MAX_PHASE;
}

//����������������������������������������������������������������������������������������
//	Name        : �f�X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CResult::~CResult()
{
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : ���U���g��ʂ�����������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CResult::Init(void)
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
	
	// ----- BGM�Đ�
//	CGameMain::PlayBGM(BGM_RESULT, DSBPLAY_LOOPING);

	// ----- ���̃t�F�[�Y��
	m_phase = PHASE_FADEIN;		// �t�F�[�h�C���J�n
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : ���U���g��ʂ̏I������������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CResult::Uninit(void)
{
	// ----- �J������n��
	m_pCamera->Uninit();

	// ----- �e�N�X�`����n��
	m_pBG->Uninit();			// �w�i
	m_pFilter->Uninit();	// �t�B���^�[

	// ----- BGM��~
//	CGameMain::StopBGM(BGM_RESULT);
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : ���U���g��ʂ��X�V����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CResult::Update(void)
{
	// ----- �I�u�W�F�N�g�X�V
	m_pCamera->Update();		// �J����

	switch(m_phase)
	{
		// �t�F�[�h�C��
		case PHASE_FADEIN:
			if(m_pFilter->FadeOutAlpha(FADEIN_TIME))
				m_phase = PHASE_MAIN;		// ���U���g�{�ҊJ�n
			break;

		// ���̃V�[���փt�F�[�h�A�E�g
		case PHASE_FADEOUT:
			if(m_pFilter->FadeInAlpha(FADEOUT_TIME))
			{	// ���̃V�[����
				Uninit();							// ��n��
				CGameMain::SetScene(SID_SELECT);	// �Z���N�g��ʂ�
			}
			break;

		// ���U���g�{��
		case PHASE_MAIN:
			Main();
			break;
			
		default:
			break;
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : ���U���g��ʂ�`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CResult::Draw(void)
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

		// ���U���g�{��
		case PHASE_MAIN:
			break;
			
		default:
			break;
	}
}

//����������������������������������������������������������������������������������������
//	Name        : ��������
//	Description : ���U���g��ʃf�[�^�𐶐�����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
CResult* CResult::Create()
{
	// ----- �ϐ��錾
	CResult* pResult;

	// ----- ����������
	pResult = new CResult();
	if(pResult)
	{
		if(!pResult->Initialize())
		{
			SAFE_DELETE(pResult);
		}
	}

	return pResult;
}


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : ���U���g��ʂ�����������
//	Arguments   : None.
//	Returns     : ����(true:����)
//����������������������������������������������������������������������������������������
bool CResult::Initialize()
{
	// ----- �J��������
	m_pCamera = CCamera::Create();
	if(m_pCamera == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CResult::Camera�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}

	// ----- �e�N�X�`������
	// �w�i
	m_pBG = CTexture::Create(TEX_FILENAME[TL_BG]);
	if(m_pBG == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CResult::BG�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}
	// �t�F�[�h�p�t�B���^�[
	m_pFilter = CTexture::Create(TEX_FILENAME[TL_FADE]);
	if(m_pFilter == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CResult::Filter�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}
	
	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : ���U���g��ʂ̏I������������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CResult::Finalize(void)
{
	// ----- �e�N�X�`�����
	SAFE_RELEASE(m_pFilter);	// �t�B���^�[
	SAFE_RELEASE(m_pBG);		// �w�i

	// ----- �J�������
	SAFE_RELEASE(m_pCamera);
}

//����������������������������������������������������������������������������������������
//	Name        : ���C��
//	Description : ���U���g�̃��C������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CResult::Main()
{
	// ----- ���̃V�[����
	if(GetTrgKey(DIK_RETURN)) {
		m_phase = PHASE_FADEOUT;		// �t�F�[�h�A�E�g�J�n
	}
}


//========================================================================================
//	End of File
//========================================================================================