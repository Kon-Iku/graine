//========================================================================================
//		File        : Title.cpp
//		Program     : �^�C�g���N���X
//
//		Description : �^�C�g���N���X�̒�`
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
#include "../../h/System/ChangeScene.h"
#include "../../h/Scene/GameMain.h"
#include "../../h/Scene/Title.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// using�錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
using namespace Input;
using namespace System;

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ----- ���\�[�X���
const LPCTSTR CTitle::TEX_FILENAME[MAX_TEXLIST] =	// �e�N�X�`���t�@�C����
{
	_T("res/img/BG.jpg"),			// �w�i�e�N�X�`���t�@�C����
	_T("res/img/Fade.jpg"),			// �t�F�[�h�p�e�N�X�`���t�@�C����
};
const D3DXVECTOR3 CTitle::INIT_CAMERA_EYE(0, 0, -1000);		// �J�����̏������_
const D3DXVECTOR3 CTitle::INIT_CAMERA_LOOK(0, 0, 0);		// �J�����̏��������_
const D3DXVECTOR3 CTitle::INIT_TEXTURE_POS[MAX_TEXLIST] = {	// �e�N�X�`���̏����ʒu
	D3DXVECTOR3(0.0f, 0.0f, FAR_CLIP),	// �w�i
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �t�B���^�[
};

// ----- �t�F�[�h�֘A
const int CTitle::FADEIN_TIME	= 10;	// �t�F�[�h�C���Ԋu(�A���t�@�l:0�`255)
const int CTitle::FADEOUT_TIME	= 10;	// �t�F�[�h�A�E�g�Ԋu(�A���t�@�l:0�`255)


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CTitle::CTitle()
{
	m_pCamera	= NULL;
	m_pBG		= NULL;
	m_pFilter	= NULL;

	m_phase		= MAX_PHASE;



	m_pPlayer	= NULL;
	m_pEnemy	= NULL;

	m_pFieldObj.reserve(CMapData::INIT_OBJECT_NUM);
}

//����������������������������������������������������������������������������������������
//	Name        : �f�X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CTitle::~CTitle()
{
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �^�C�g��������������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTitle::Init(void)
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
//	CGameMain::PlayBGM(BGM_TITLE, DSBPLAY_LOOPING);

	// ----- ���̃t�F�[�Y��
	m_phase = PHASE_FADEIN;		// �t�F�[�h�C���J�n



	m_pPlayer->Init(D3DXVECTOR2(128, 1), D3DXVECTOR3(-256, 0, 0));
	m_pEnemy->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3(256, 0, 0));

	CMapData::LoadData(CMapData::ID_STAGE1);	// �}�b�v�f�[�^�ǂݍ���
	CMapData::GetFieldObjList(&m_pFieldObj);
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �^�C�g���̏I������������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTitle::Uninit(void)
{
	// ----- �t�F�[�h�A�E�g�J�n
	if(m_phase != PHASE_FADEOUT)
		m_phase = PHASE_FADEOUT;

	// ----- �e�N�X�`����n��
	m_pBG->Uninit();			// �w�i
	m_pFilter->Uninit();	// �t�B���^�[

	// ----- BGM��~
//	CGameMain::StopBGM(BGM_TITLE);




	m_pPlayer->Uninit();
	m_pEnemy->Uninit();

	for(LPFIELDOBJECT_ARRAY_IT it = m_pFieldObj.begin(); it != m_pFieldObj.end(); ++it) {
		(*it)->Uninit();
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �^�C�g�����X�V����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTitle::Update(void)
{
	// ----- �I�u�W�F�N�g�X�V
	m_pCamera->Update();		// �J����
	
	switch(m_phase)
	{
		// �t�F�[�h�C��
		case PHASE_FADEIN:
			if(m_pFilter->FadeOutAlpha(FADEIN_TIME)) {
//			if(ChangeScene::SideSliderIn(m_pFilter, 3.0f)) {
//				m_pFilter->SetPosX(-m_pFilter->GetWidth());		// �t�F�[�h�A�E�g�p����
				m_phase = PHASE_MAIN;							// �^�C�g���{�ҊJ�n
			}
			break;

		// �t�F�[�h�A�E�g
		case PHASE_FADEOUT:
			if(m_pFilter->FadeInAlpha(FADEOUT_TIME))
//			if(ChangeScene::SideSliderOut(m_pFilter, 3.0f))
			{	// ���̃V�[����
				Uninit();							// ��n��
				CGameMain::SetScene(SID_SELECT);	// �y�ȑI����ʂ�
			}
			break;

		// �^�C�g���{��
		case PHASE_MAIN:
			Main();
			break;
			
		default:
			break;
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �^�C�g����ʂ�`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTitle::Draw(void)
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

		// �^�C�g���{��
		case PHASE_MAIN:
			break;
			
		default:
			break;
	}




	m_pPlayer->DrawAlpha();
	m_pEnemy->DrawAlpha();

	for(LPFIELDOBJECT_ARRAY_IT it = m_pFieldObj.begin(); it != m_pFieldObj.end(); ++it) {
  		(*it)->DrawAlpha();
	}
}

//����������������������������������������������������������������������������������������
//	Name        : ��������
//	Description : �^�C�g���f�[�^�𐶐�����
//	Arguments   : None.
//	Returns     : �^�C�g���f�[�^
//����������������������������������������������������������������������������������������
CTitle* CTitle::Create()
{
	// ----- �ϐ��錾
	CTitle* pTitle;

	// ----- ����������
	pTitle = new CTitle();
	if(pTitle)
	{
		if(!pTitle->Initialize())
		{
			SAFE_DELETE(pTitle);
		}
	}

	return pTitle;
}


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �^�C�g��������������
//	Arguments   : None.
//	Returns     : ����(true:����)
//����������������������������������������������������������������������������������������
bool CTitle::Initialize()
{
	// �J��������
	m_pCamera = CCamera::Create();
	if(m_pCamera == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CTitle::Camera�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}

	// ----- �e�N�X�`������
	// �w�i
	m_pBG = CTexture::Create(TEX_FILENAME[TL_BG]);
	if(m_pBG == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CTitle::BG�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}
	// �t�F�[�h�p�t�B���^�[
	m_pFilter = CTexture::Create(TEX_FILENAME[TL_FADE]);
	if(m_pFilter == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CTitle::Filter�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}



	m_pPlayer = CCharacter::Create(TEX_FILENAME[TL_BG]);
	m_pEnemy = CCharacter::Create(TEX_FILENAME[TL_FADE]);



	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �^�C�g���̏I������������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTitle::Finalize(void)
{
	// ----- �e�N�X�`�����
	SAFE_RELEASE(m_pFilter);	// �t�B���^�[
	SAFE_RELEASE(m_pBG);		// �w�i

	// ----- �J�������
	SAFE_RELEASE(m_pCamera);

	SAFE_RELEASE(m_pPlayer);
	SAFE_RELEASE(m_pEnemy);
}

//����������������������������������������������������������������������������������������
//	Name        : ���C��
//	Description : �^�C�g���̃��C������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTitle::Main()
{
	// ----- ���̃V�[����
	if(GetTrgKey(DIK_RETURN)) {
		m_phase = PHASE_FADEOUT;		// �t�F�[�h�A�E�g�J�n
	}

	m_pPlayer->Update();
	m_pEnemy->Update();

	const float SPD = 10.0f;

	if(GetPrsKey(DIK_RIGHT))
		m_pPlayer->TranslationX(SPD);
	if(GetPrsKey(DIK_LEFT))
		m_pPlayer->TranslationX(-SPD);
	if(GetPrsKey(DIK_UP))
		m_pPlayer->TranslationY(SPD);
	if(GetPrsKey(DIK_DOWN))
		m_pPlayer->TranslationY(-SPD);

	if(GetPrsKey(DIK_O))
		m_pPlayer->RotationZ(1.0f);
	
	if(GetPrsKey(DIK_D))
		m_pEnemy->TranslationX(SPD);
	if(GetPrsKey(DIK_A))
		m_pEnemy->TranslationX(-SPD);
	if(GetPrsKey(DIK_W))
		m_pEnemy->TranslationY(SPD);
	if(GetPrsKey(DIK_S))
		m_pEnemy->TranslationY(-SPD);
	
	if(GetPrsKey(DIK_P))
		m_pEnemy->RotationZ(-1.0f);

	D3DXVECTOR2 pos = D3DXVECTOR2(m_pPlayer->GetPosX(), m_pPlayer->GetPosY());
	pos.x -= 64.0f;
	m_pPlayer->SetColStartLine(pos);
	pos.x += 128.0f;
	m_pPlayer->SetColEndLine(pos);
	int id = COL2D_LINESQUARE;
	if(m_pPlayer->CollisionEnter(id, m_pEnemy)) {
		printf("true\n");
		if(id == COL2D_LINESQUARE || id == COL2D_SQUARELINE) {
			printf("X���W:%f\n", m_pPlayer->GetLastColLinePos().x);
			printf("Y���W:%f\n", m_pPlayer->GetLastColLinePos().y);
			printf("\n");
		}
	}
	
	for(LPFIELDOBJECT_ARRAY_IT it = m_pFieldObj.begin(); it != m_pFieldObj.end(); ++it) {
		(*it)->Update();
	}
	// �}�b�v�f�[�^�`��(���̂�)
	if(GetTrgKey(DIK_SPACE)) {
		for(LPFIELDOBJECT_ARRAY_IT it = m_pFieldObj.begin(); it != m_pFieldObj.end(); ++it) {
			printf("X���W         :%f\n", (*it)->GetPosX());
			printf("Y���W         :%f\n", (*it)->GetPosY());
			printf("Z���W         :%f\n", (*it)->GetPosZ());
			printf("��            :%f\n", (*it)->GetWidth());
			printf("����          :%f\n", (*it)->GetHeight());
			printf("��]�p�x      :%f\n", (*it)->GetRotZ());
			printf("�����蔻��L��:%d\n", (*it)->GetCol());
			printf("���          :%d\n", (*it)->GetType());
			printf("\n");
		}
	}
}


//========================================================================================
//	End of File
//========================================================================================