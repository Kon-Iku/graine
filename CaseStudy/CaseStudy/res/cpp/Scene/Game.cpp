//========================================================================================
//		File        : Game.cpp
//		Program     : �Q�[���{�҃N���X
//
//		Description : �Q�[���{�҃N���X�̎���
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
#include <math.h>
#include "../../h/System/System.h"
#include "../../h/System/Input.h"
#include "../../h/Scene/GameMain.h"
#include "../../h/Scene/Game.h"

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
const LPCTSTR CGame::TEX_FILENAME[MAX_TEXLIST] = {
	_T("res/img/GameScene/BG/pantsu.jpg"),		// �w�i�e�N�X�`���t�@�C����
	_T("res/img/GameScene/Object/player.png"),	// �v���C���[�e�N�X�`����
	_T("res/img/GameScene/Object/block.png"),	// �u���b�N�e�N�X�`����
	_T("res/img/Fade.jpg"),		// �t�F�[�h�p�e�N�X�`���t�@�C����
};
const D3DXVECTOR3 CGame::INIT_CAMERA_EYE(0, 0, -1000);		// �J�����̏������_
const D3DXVECTOR3 CGame::INIT_CAMERA_LOOK(0, 0, 0);			// �J�����̏��������_
const D3DXVECTOR3 CGame::INIT_TEXTURE_POS[MAX_TEXLIST] = {	// �e�N�X�`���̏����ʒu
	D3DXVECTOR3(0.0f, 0.0f, FAR_CLIP),						// �w�i
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),							// �t�B���^�[
};

// ----- �t�F�[�h�֘A
const int CGame::FADEIN_TIME		= 5;	// �t�F�[�h�C���Ԋu(�A���t�@�l:0�`255)
const int CGame::FADEOUT_TIME		= 10;	// �t�F�[�h�A�E�g�Ԋu(�A���t�@�l:0�`255)


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CGame::CGame()
{
	m_pBG			= NULL;
	m_pFilter		= NULL;
	m_pCamera		= NULL;

	m_pBlock		= NULL;

	m_pPlayer		= NULL;

	m_phase		= MAX_PHASE;
}

//����������������������������������������������������������������������������������������
//	Name        : �f�X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CGame::~CGame()
{
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �Q�[���{�҂�����������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGame::Init(void)
{
	// ----- �e�N�X�`��������
	m_pBG->Init(D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT), INIT_TEXTURE_POS[TL_BG]);				// �w�i
	m_pFilter->Init(D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT), INIT_TEXTURE_POS[TL_FADE]);			// �t�B���^�[

	// ----- �J����������
	m_pCamera->Init();
	D3DXVECTOR3 eye = INIT_CAMERA_EYE;
	D3DXVECTOR3 look = INIT_CAMERA_LOOK;
	D3DXVECTOR3 up = D3DXVECTOR3(0, 1, 0);
	m_pCamera->SetParameter(eye, look, up);

	// ----- ���̃t�F�[�Y��
	m_phase = PHASE_FADEIN;		// �t�F�[�h�C���J�n

	// �I�u�W�F�N�g��
	vecFieldObj.reserve(MAX_OBJECT);

	// ----- �u���b�N������
	m_pBlock->Init(D3DXVECTOR2(512, 64), D3DXVECTOR3(-256, -256, 0));

	// ::::: ���X�g�ɒǉ� ::::: //
	vecFieldObj.push_back(m_pBlock);

	m_pPlayer->Init(D3DXVECTOR2(PLAYER_SIZE_X, PLAYER_SIZE_Y), D3DXVECTOR3(-256, 0, 0));
	m_pPlayer->UVDivision(0, PLAYER_ANIME_SIZE_X, PLAYER_ANIME_SIZE_Y);

}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �Q�[���{�҂̏I������������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGame::Uninit(void)
{
	// ----- �e�N�X�`����n��
	m_pBG->Uninit();				// �w�i
	m_pFilter->Uninit();		// �t�B���^�[

	// ----- �I�u�W�F�N�g��n��
	m_pCamera->Uninit();			// �J����

	// ���X�g���S����n��
	for (LPOBJECT2D_ARRAY_IT it = vecFieldObj.begin(); it != vecFieldObj.end(); ++it)
		(*it)->Uninit();
	vecFieldObj.clear();		// �I�u�W�F�N�g���X�g

	m_pPlayer->Uninit();
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �Q�[���{�҂��X�V����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGame::Update(void)
{
	// ----- �I�u�W�F�N�g�X�V
	m_pCamera->Update();			// �J����
				
	switch(m_phase)
	{
		// �t�F�[�h�C��
		case PHASE_FADEIN:
			if(m_pFilter->FadeOutAlpha(FADEIN_TIME))
				m_phase = PHASE_MAIN;		// �J�n����
			break;

		// ���̃V�[���փt�F�[�h�A�E�g
		case PHASE_FADEOUT:
			if(m_pFilter->FadeInAlpha(FADEOUT_TIME))
			{	// ���̃V�[����
				Uninit();							// ��n��
				CGameMain::SetScene(SID_RESULT);	// ���U���g��
			}
			break;

		// �Q�[���{��
		case PHASE_MAIN:
			Main();
			break;
			
		default:
			break;
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �Q�[���{�҂�`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGame::Draw(void)
{
	// ----- �J�����`��
	m_pCamera->Draw();

	// ----- �e�N�X�`���`��
	m_pBG->DrawAlpha();			// �w�i

	switch(m_phase)
	{
		// �t�F�[�h�C���E�A�E�g
		case PHASE_FADEIN:
		case PHASE_FADEOUT:
			m_pFilter->DrawAlpha();
			break;

		// �Q�[���{��
		case PHASE_MAIN:
			// �I�u�W�F�N�g���X�g�S���`��
			for (unsigned int i = 0; i < vecFieldObj.size(); i++)
				vecFieldObj[i]->DrawAlpha();
			
			m_pPlayer->DrawAlpha();
			break;
			
		default:
			break;
	}
}

//����������������������������������������������������������������������������������������
//	Name        : ��������
//	Description : �Q�[���{�҃f�[�^�𐶐�����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
CGame* CGame::Create()
{
	// ----- �ϐ��錾
	CGame* pGame;

	// ----- ����������
	pGame = new CGame();
	if(pGame)
	{
		if(!pGame->Initialize())
		{
			SAFE_DELETE(pGame);
		}
	}

	return pGame;
}


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �Q�[���{�҂�����������
//	Arguments   : None.
//	Returns     : ����(true;����)
//����������������������������������������������������������������������������������������
bool CGame::Initialize()
{
	// ----- �e�N�X�`������
	// �w�i
	m_pBG = CTexture::Create(TEX_FILENAME[TL_BG]);
	if(m_pBG == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CGame::BG�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}
	// �t�F�[�h�p�t�B���^�[
	m_pFilter = CTexture::Create(TEX_FILENAME[TL_FADE]);
	if(m_pFilter == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CGame::Filter�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}

	// ----- �I�u�W�F�N�g����
	// �J����
	m_pCamera = CCamera::Create();
	if(m_pCamera == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CGame::Camera�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}

	/*�@�����݂��񂪒ǉ�������@*/
	// �u���b�N
	m_pBlock = CFieldObject::Create(TEX_FILENAME[TL_BLOCK_0]);
	// �v���C���[
	m_pPlayer = CPlayer::Create(TEX_FILENAME[TL_PLAYER_0]);
	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �Q�[���{�҂̏I������������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGame::Finalize(void)
{
	// ----- �I�u�W�F�N�g���
	SAFE_RELEASE(m_pCamera);	// �J�����f�[�^
	
	// ----- �e�N�X�`�����
	SAFE_RELEASE(m_pFilter);	// �t�B���^�[
	SAFE_RELEASE(m_pBG);		// �w�i

	SAFE_RELEASE(m_pBlock);		// �u���b�N
	SAFE_RELEASE(m_pPlayer);	// �v���C���[
}

//����������������������������������������������������������������������������������������
//	Name        : ���C��
//	Description : �Q�[���{�҂̃��C������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGame::Main()
{
	// ----- ���̃V�[����
	if(GetTrgKey(DIK_RETURN)) {
		m_phase = PHASE_FADEOUT;	// ���̃V�[���փt�F�[�h�A�E�g
	}

	// ���X�g���S���X�V
	for (unsigned int i = 0; i < vecFieldObj.size(); i++)
		vecFieldObj[i]->Update();

	// �v���C���[�̍X�V
	m_pPlayer->Update();

	if (m_pPlayer->CollisionStay(COL2D_BOUNDINGBOX, m_pBlock)){
		m_pPlayer->SetGravity(GRAVITY_ZERO);

	}
	else{
		m_pPlayer->SetGravity(GRAVITY_CASE_2);
	}
}


//========================================================================================
//	End of File
//========================================================================================