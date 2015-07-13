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
#include "../../h/System/ChangeScene.h"
#include "../../h/Scene/GameMain.h"
#include "../../h/Scene/Select.h"
#include "../../h/Scene/Game.h"

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
	_T("res/img/Select/BG/saisyo_haikei.png"),			// �w�i�e�N�X�`���t�@�C����
	_T("res/img/Select/BG/saisyo_haikei_2.png"),			// �w�i�e�N�X�`���t�@�C����
	_T("res/img/GameScene/Object/Tactile_1.png"),
	_T("res/img/GameScene/Object/player_0.png"),
	_T("res/img/Select/Object/yajirusi.png"),
	_T("res/img/Select/Object/stage1.png"),
	_T("res/img/Select/Object/stage2.png"),
	_T("res/img/Select/Object/stage3.png"),
	_T("res/img/Select/Object/stage4.png"),
	_T("res/img/Select/Object/stage5.png"),
	_T("res/img/Select/Object/serekuto_1.png"),
	_T("res/img/Select/Object/serekuto_2.png"),
	_T("res/img/Select/Object/serekuto_3.png"),
	_T("res/img/Select/Effect/New_maru.png"),
};
const D3DXVECTOR3 CSelect::INIT_CAMERA_EYE(0, 0, -1000);	// �J�����̏������_
const D3DXVECTOR3 CSelect::INIT_CAMERA_LOOK(0, 0, 0);		// �J�����̏��������_
const D3DXVECTOR3 CSelect::INIT_TEXTURE_POS[MAX_TEXLIST] =	// �e�N�X�`���̏����ʒu
{
	D3DXVECTOR3(0.0f, 0.0f, FAR_CLIP),	// �w�i
};

// ----- �t�F�[�h�֘A
const float CSelect::FADE_POSZ = -100.0f;	// �t�F�[�h�p�e�N�X�`����Z���W
const int CSelect::FADEIN_TIME = 10;		// �t�F�[�h�C���Ԋu(�A���t�@�l:0�`255)
const int CSelect::FADEOUT_TIME = 10;		// �t�F�[�h�A�E�g�Ԋu(�A���t�@�l:0�`255)


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CSelect::CSelect()
{
	m_pCamera = NULL;

	m_phase = MAX_PHASE;

	for (int i = 0; i < MAX_OBJECTLIST; i++)
		m_pSelectPlayer[i] = NULL;

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		m_pSelectEffect[i] = NULL;
		m_pSelectEffect_White[i] = NULL;
	}

	m_nClear = SC_CLEAR_CLEAR;
	m_nStatus = S_STATUS_WAIT;
	m_nStage = CMapData::ID_STAGE1;
	m_bEffect = false;

//	for (int i = 0; i < 5; i++)
//		m_bClear[i] = false;
	m_bClear[CMapData::ID_STAGE1] = true;
	m_bClear[CMapData::ID_STAGE2] = true;
	m_bClear[CMapData::ID_STAGE3] = false;
	m_bClear[CMapData::ID_STAGE4] = false;
	m_bClear[CMapData::ID_STAGE5] = false;

	m_bAnime = false;
	m_bBG1Anime = false;
	m_bBG2Anime = false;
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
	// �A�j���[�V����������
	m_pSelectPlayer[OL_TACTILE]->StartAnimation();
	m_pSelectPlayer[OL_TACTILE]->UVDivision(0, SELECT_ANIME_SIZE_X, SELECT_ANIME_SIZE_Y);
	m_pSelectPlayer[OL_TACTILE]->Init(D3DXVECTOR2(192, 192),D3DXVECTOR3(PLAYER_INIT_POS_X, PLAYER_INIT_POS_Y, 0));
	m_pSelectPlayer[OL_TACTILE]->SetColor(D3DXVECTOR3(128, 255, 128));
	m_pSelectPlayer[OL_TACTILE]->TactileUpdate(true, m_nStatus);

	m_pSelectPlayer[OL_PLAYER]->StartAnimation();
	m_pSelectPlayer[OL_PLAYER]->UVDivision(0, SELECT_ANIME_SIZE_X, SELECT_ANIME_SIZE_Y);
	m_pSelectPlayer[OL_PLAYER]->Init(D3DXVECTOR2(192, 192), D3DXVECTOR3((float)PLAYER_INIT_POS_X, (float)PLAYER_INIT_POS_Y, 0));
	m_pSelectPlayer[OL_PLAYER]->SetColor(D3DXVECTOR3(128, 255, 128));
	m_pSelectPlayer[OL_PLAYER]->PlayerUpdate(true, m_nStatus);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		m_pSelectEffect[i]->StartAnimation();
		m_pSelectEffect[i]->UVDivision(0, 8, 8);
		switch (i)
		{
		case 0:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)0, (float)0, 0));
			break;
		case 1:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)300, (float)0, 0));
			break;
		case 2:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)100, (float)200, 0));
			break;
		case 3:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)400, (float)200, 0));
			break;
		case 4:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)200, (float)400, 0));
			break;
		case 5:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)500, (float)400, 0));
			break;
		case 6:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)0, (float)600, 0));
			break;
		case 7:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)400, (float)600, 0));
			break;
		case 8:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1000, (float)0, 0));
			break;
		case 9:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1200, (float)0, 0));
			break;
		case 10:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1000, (float)300, 0));
			break;
		case 11:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)800, (float)300, 0));
			break;
		case 12:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1300, (float)600, 0));
			break;
		case 13:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1000, (float)600, 0));
			break;
		case 14:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)800, (float)800, 0));
			break;
		case 15:
			m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1000, (float)800, 0));
			break;
		}

		m_pSelectEffect[i]->SetColor(D3DXVECTOR3(128, 255, 128));
		m_pSelectEffect[i]->EffectUpdate(i,true);

		m_pSelectEffect_White[i]->StartAnimation();
		m_pSelectEffect_White[i]->UVDivision(0, 8, 8);
		switch (i)
		{
		case 0:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)500, (float)100, 0));
			break;
		case 1:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)900, (float)100, 0));
			break;
		case 2:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)600, (float)300, 0));
			break;
		case 3:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1000, (float)300, 0));
			break;
		case 4:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)700, (float)500, 0));
			break;
		case 5:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1100, (float)500, 0));
			break;
		case 6:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)500, (float)700, 0));
			break;
		case 7:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)900, (float)700, 0));
			break;
		case 8:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1900, (float)100, 0));
			break;
		case 9:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)2200, (float)100, 0));
			break;
		case 10:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1300, (float)300, 0));
			break;
		case 11:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1800, (float)300, 0));
			break;
		case 12:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1600, (float)500, 0));
			break;
		case 13:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1900, (float)500, 0));
			break;
		case 14:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)2000, (float)700, 0));
			break;
		case 15:
			m_pSelectEffect_White[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1500, (float)700, 0));
			break;
		}
		m_pSelectEffect_White[i]->EffectUpdate(i,true);
	}

	// ----- �J����������
	m_pCamera->Init();
	D3DXVECTOR3 eye = INIT_CAMERA_EYE;
	D3DXVECTOR3 look = INIT_CAMERA_LOOK;
	D3DXVECTOR3 up = D3DXVECTOR3(0, 1, 0);
	m_pCamera->SetParameter(eye, look, up);

	m_pSelectPlayer[OL_BG_1]->Init(D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT), D3DXVECTOR3((float)SCREEN_RIGHT, SCREEN_HEIGHT / 2, 0));			// �w�i
	m_pSelectPlayer[OL_BG_2]->Init(D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT), D3DXVECTOR3((float)SCREEN_WIDTH + SCREEN_RIGHT, SCREEN_HEIGHT / 2, 0));			// �w�i			// �w�i

	m_pSelectPlayer[OL_ARROW_LEFT]->Init(D3DXVECTOR2(100, 130), D3DXVECTOR3((float)LEFT_ARROW_INIT_POS_X, (float)LEFT_ARROW_INIT_POS_Y, 0));
	m_pSelectPlayer[OL_ARROW_RIGHT]->Init(D3DXVECTOR2(100, 130), D3DXVECTOR3((float)RIGHT_ARROW_INIT_POS_X, (float)RIGHT_ARROW_INIT_POS_Y, 0));
	m_pSelectPlayer[OL_ROGO_1]->Init(D3DXVECTOR2(473, 192), D3DXVECTOR3((float)ROGO_INIT_POS_X, (float)ROGO_INIT_POS_Y, 0));
	for (int i = OL_ROGO_2; i <= OL_ROGO_5; i++)
		m_pSelectPlayer[i]->Init(D3DXVECTOR2(473, 192), D3DXVECTOR3((float)ROGO_SCREEN_OUT_POS_X, (float)ROGO_SCREEN_OUT_POS_Y, 0));
	m_pSelectPlayer[OL_STAGE_1]->Init(D3DXVECTOR2(SCREEN_RIGHT * 2, SCREEN_RIGHT * 2), D3DXVECTOR3((float)STAGE_INIT_POS_X, (float)STAGE_INIT_POS_Y, 0));
	m_pSelectPlayer[OL_STAGE_2]->Init(D3DXVECTOR2(SCREEN_RIGHT * 2, SCREEN_RIGHT * 2), D3DXVECTOR3((float)SCREEN_WIDTH + SCREEN_RIGHT, (float)STAGE_INIT_POS_Y, 0));
	m_pSelectPlayer[OL_STAGE_3]->Init(D3DXVECTOR2(SCREEN_RIGHT * 2, SCREEN_RIGHT * 2), D3DXVECTOR3((float)SCREEN_WIDTH + SCREEN_RIGHT, (float)STAGE_INIT_POS_Y, 0));


	m_pSelectPlayer[OL_STAGE_1]->ClearSave(m_bClear[CMapData::ID_STAGE1],m_bClear[CMapData::ID_STAGE2],m_bClear[CMapData::ID_STAGE3],m_bClear[CMapData::ID_STAGE4],m_bClear[CMapData::ID_STAGE5]);
	m_pSelectPlayer[OL_STAGE_2]->ClearSave(m_bClear[CMapData::ID_STAGE1], m_bClear[CMapData::ID_STAGE2], m_bClear[CMapData::ID_STAGE3], m_bClear[CMapData::ID_STAGE4], m_bClear[CMapData::ID_STAGE5]);
	m_pSelectPlayer[OL_STAGE_3]->ClearSave(m_bClear[CMapData::ID_STAGE1], m_bClear[CMapData::ID_STAGE2], m_bClear[CMapData::ID_STAGE3], m_bClear[CMapData::ID_STAGE4], m_bClear[CMapData::ID_STAGE5]);
	// ----- �t�F�[�h�ݒ�
	CChangeScene::SetNormalFadeAlpha(255);

	// ----- BGM�Đ�
	CGameMain::PlayBGM(BGM_SELECT, DSBPLAY_LOOPING);

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
//	m_pBG->Uninit();			// �w�i

	// ----- BGM��~
	CGameMain::StopBGM(BGM_SELECT);
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

	switch (m_phase)
	{
		// �t�F�[�h�C��
	case PHASE_FADEIN:
		if (CChangeScene::NormalFadeOut(FADE_POSZ, FADEIN_TIME)) {
			m_phase = PHASE_MAIN;		// �y�ȑI��{�ҊJ�n
		}
		break;

		// ���̃V�[���փt�F�[�h�A�E�g
	case PHASE_FADEOUT:
		if (CChangeScene::NormalFadeIn(FADE_POSZ, FADEOUT_TIME)) {
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
	//m_pBG->DrawScreenAlpha();		// �w�i
	for (int i = 0; i < 2; i++)
		m_pSelectPlayer[i]->DrawScreenAlpha();

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		m_pSelectEffect[i]->DrawScreenAlpha();
		m_pSelectEffect_White[i]->DrawScreenAlpha();
	}

	for (int i = 2; i < MAX_OBJECTLIST; i++)
		m_pSelectPlayer[i]->DrawScreenAlpha();


	switch (m_phase)
	{
		// �t�F�[�h�C���E�A�E�g
	case PHASE_FADEIN:
	case PHASE_FADEOUT:
		CChangeScene::DrawNormalFade();
		break;

		// �y�ȑI��{��
	case PHASE_MAIN:
		m_pSelectPlayer[OL_TACTILE]->SetColor(D3DXVECTOR3(128, 255, 128));
		m_pSelectPlayer[OL_PLAYER]->SetColor(D3DXVECTOR3(128, 255, 128));
		for (int i = 0; i < EFFECT_MAX; i++)
			m_pSelectEffect[i]->SetColor(D3DXVECTOR3(128, 255, 128));
		break;

	default:
		break;
	}
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
	if (pSelect)
	{
		if (!pSelect->Initialize())
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
	if (m_pCamera == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CSelect::Camera�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}

	// ----- �e�N�X�`������
	// �w�i
/*
	m_pBG = CObject2D::Create(TEX_FILENAME[TL_BG]);
	if (m_pBG == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CSelect::BG�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}
*/
	m_pSelectPlayer[OL_BG_2] = CSelectObject::Create(TEX_FILENAME[TL_BG_2]);
	m_pSelectPlayer[OL_BG_1] = CSelectObject::Create(TEX_FILENAME[TL_BG_1]);
	m_pSelectPlayer[OL_TACTILE] = CSelectObject::Create(TEX_FILENAME[TL_TACTILE]);
	m_pSelectPlayer[OL_PLAYER] = CSelectObject::Create(TEX_FILENAME[TL_PLAYER]);
	m_pSelectPlayer[OL_ARROW_LEFT] = CSelectObject::Create(TEX_FILENAME[TL_ARROW]);
	m_pSelectPlayer[OL_ARROW_RIGHT] = CSelectObject::Create(TEX_FILENAME[TL_ARROW]);
	m_pSelectPlayer[OL_ROGO_1] = CSelectObject::Create(TEX_FILENAME[TL_ROGO_1]);
	m_pSelectPlayer[OL_ROGO_2] = CSelectObject::Create(TEX_FILENAME[TL_ROGO_2]);
	m_pSelectPlayer[OL_ROGO_3] = CSelectObject::Create(TEX_FILENAME[TL_ROGO_3]);
	m_pSelectPlayer[OL_ROGO_4] = CSelectObject::Create(TEX_FILENAME[TL_ROGO_4]);
	m_pSelectPlayer[OL_ROGO_5] = CSelectObject::Create(TEX_FILENAME[TL_ROGO_5]);
	m_pSelectPlayer[OL_STAGE_1] = CSelectObject::Create(TEX_FILENAME[TL_STAGE_1]);
	m_pSelectPlayer[OL_STAGE_2] = CSelectObject::Create(TEX_FILENAME[TL_STAGE_2]);
	m_pSelectPlayer[OL_STAGE_3] = CSelectObject::Create(TEX_FILENAME[TL_STAGE_3]);
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		m_pSelectEffect[i] = CSelectObject::Create(TEX_FILENAME[TL_EFFECT]);
		m_pSelectEffect_White[i] = CSelectObject::Create(TEX_FILENAME[TL_EFFECT]);
	}

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
//	SAFE_RELEASE(m_pBG);		// �w�i

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
	if (m_bAnime)
	{
		if (GetTrgKey(DIK_LEFT))		// ��
		{
			CGameMain::PlaySE(SE_CHOICE);
			m_nStatus = S_STATUS_LEFT;
			switch (m_nStage)
			{
			case CMapData::ID_STAGE1:
				if (m_bClear[m_nStage])
				{
					if (m_bClear[CMapData::ID_STAGE5])
						m_nClear = SC_CLEAR_CLEAR;
					else
						m_nClear = SC_CLEAR_FALSE;
				}
				else
				{
					if (m_bClear[CMapData::ID_STAGE5])
						m_nClear = SC_FALSE_CLEAR;
					else
						m_nClear = SC_FALSE_FALSE;
				}

				m_nStage = CMapData::ID_STAGE5;
				break;
			case CMapData::ID_STAGE2:
				if (m_bClear[m_nStage])
				{
					if (m_bClear[CMapData::ID_STAGE1])
						m_nClear = SC_CLEAR_CLEAR;
					else
						m_nClear = SC_CLEAR_FALSE;
				}
				else
				{
					if (m_bClear[CMapData::ID_STAGE1])
						m_nClear = SC_FALSE_CLEAR;
					else
						m_nClear = SC_FALSE_FALSE;
				}

				m_nStage = CMapData::ID_STAGE1;
				break;
			case CMapData::ID_STAGE3:
				if (m_bClear[m_nStage])
				{
					if (m_bClear[CMapData::ID_STAGE2])
						m_nClear = SC_CLEAR_CLEAR;
					else
						m_nClear = SC_CLEAR_FALSE;
				}
				else
				{
					if (m_bClear[CMapData::ID_STAGE2])
						m_nClear = SC_FALSE_CLEAR;
					else
						m_nClear = SC_FALSE_FALSE;
				}

				m_nStage = CMapData::ID_STAGE2;
				break;
			case CMapData::ID_STAGE4:
				if (m_bClear[m_nStage])
				{
					if (m_bClear[CMapData::ID_STAGE3])
						m_nClear = SC_CLEAR_CLEAR;
					else
						m_nClear = SC_CLEAR_FALSE;
				}
				else
				{
					if (m_bClear[CMapData::ID_STAGE3])
						m_nClear = SC_FALSE_CLEAR;
					else
						m_nClear = SC_FALSE_FALSE;
				}

				m_nStage = CMapData::ID_STAGE3;
				break;
			case CMapData::ID_STAGE5:
				if (m_bClear[m_nStage])
				{
					if (m_bClear[CMapData::ID_STAGE4])
						m_nClear = SC_CLEAR_CLEAR;
					else
						m_nClear = SC_CLEAR_FALSE;
				}
				else
				{
					if (m_bClear[CMapData::ID_STAGE4])
						m_nClear = SC_FALSE_CLEAR;
					else
						m_nClear = SC_FALSE_FALSE;
				}

				m_nStage = CMapData::ID_STAGE4;
				break;
			}
			if (m_nClear == SC_FALSE_CLEAR)
				Effect(true);
			if (m_nClear == SC_CLEAR_FALSE)
				Effect(false);
		}
		if (GetTrgKey(DIK_RIGHT))		// �E
		{
			CGameMain::PlaySE(SE_CHOICE);
			m_nStatus = S_STATUS_RIGHT;
			switch (m_nStage)
			{
			case CMapData::ID_STAGE1:
				if (m_bClear[m_nStage])
				{
					if (m_bClear[CMapData::ID_STAGE2])
						m_nClear = SC_CLEAR_CLEAR;
					else
						m_nClear = SC_CLEAR_FALSE;
				}
				else
				{
					if (m_bClear[CMapData::ID_STAGE2])
						m_nClear = SC_FALSE_CLEAR;
					else
						m_nClear = SC_FALSE_FALSE;
				}

				m_nStage = CMapData::ID_STAGE2;
				break;
			case CMapData::ID_STAGE2:
				if (m_bClear[m_nStage])
				{
					if (m_bClear[CMapData::ID_STAGE3])
						m_nClear = SC_CLEAR_CLEAR;
					else
						m_nClear = SC_CLEAR_FALSE;
				}
				else
				{
					if (m_bClear[CMapData::ID_STAGE3])
						m_nClear = SC_FALSE_CLEAR;
					else
						m_nClear = SC_FALSE_FALSE;
				}

				m_nStage = CMapData::ID_STAGE3;
				break;
			case CMapData::ID_STAGE3:
				if (m_bClear[m_nStage])
				{
					if (m_bClear[CMapData::ID_STAGE4])
						m_nClear = SC_CLEAR_CLEAR;
					else
						m_nClear = SC_CLEAR_FALSE;
				}
				else
				{
					if (m_bClear[CMapData::ID_STAGE4])
						m_nClear = SC_FALSE_CLEAR;
					else
						m_nClear = SC_FALSE_FALSE;
				}

				m_nStage = CMapData::ID_STAGE4;
				break;
			case CMapData::ID_STAGE4:
				if (m_bClear[m_nStage])
				{
					if (m_bClear[CMapData::ID_STAGE5])
						m_nClear = SC_CLEAR_CLEAR;
					else
						m_nClear = SC_CLEAR_FALSE;
				}
				else
				{
					if (m_bClear[CMapData::ID_STAGE5])
						m_nClear = SC_FALSE_CLEAR;
					else
						m_nClear = SC_FALSE_FALSE;
				}

				m_nStage = CMapData::ID_STAGE5;
				break;
			case CMapData::ID_STAGE5:
				if (m_bClear[m_nStage])
				{
					if (m_bClear[CMapData::ID_STAGE1])
						m_nClear = SC_CLEAR_CLEAR;
					else
						m_nClear = SC_CLEAR_FALSE;
				}
				else
				{
					if (m_bClear[CMapData::ID_STAGE1])
						m_nClear = SC_FALSE_CLEAR;
					else
						m_nClear = SC_FALSE_FALSE;
				}

				m_nStage = CMapData::ID_STAGE1;
				break;
			}
			if (m_nClear == SC_FALSE_CLEAR)
				Effect(true);
			if (m_nClear == SC_CLEAR_FALSE)
				Effect(false);
		}
	}

	m_bBG2Anime = m_pSelectPlayer[OL_BG_2]->BGUpdate(2, m_nStatus, m_bClear[m_nStage], m_bBG2Anime);
	m_bBG1Anime = m_pSelectPlayer[OL_BG_1]->BGUpdate(1, m_nStatus, m_bClear[m_nStage], m_bBG1Anime);
	m_bAnime = m_pSelectPlayer[OL_STAGE_1]->StageUpdate(1,m_nStatus, m_nStage);
	m_bAnime = m_pSelectPlayer[OL_STAGE_2]->StageUpdate(2,m_nStatus, m_nStage);
	m_bAnime = m_pSelectPlayer[OL_STAGE_3]->StageUpdate(3,m_nStatus, m_nStage);
	m_pSelectPlayer[OL_TACTILE]->TactileUpdate(m_bAnime, m_nStatus);
	m_pSelectPlayer[OL_PLAYER]->PlayerUpdate(m_bAnime, m_nStatus);
	m_pSelectPlayer[OL_ROGO_1]->RogoUpdate(1, m_nStatus, m_nStage);
	m_pSelectPlayer[OL_ROGO_2]->RogoUpdate(2, m_nStatus, m_nStage);
	m_pSelectPlayer[OL_ROGO_3]->RogoUpdate(3, m_nStatus, m_nStage);
	m_pSelectPlayer[OL_ROGO_4]->RogoUpdate(4, m_nStatus, m_nStage);
	m_pSelectPlayer[OL_ROGO_5]->RogoUpdate(5, m_nStatus, m_nStage);
	m_nStatus = m_pSelectPlayer[OL_ARROW_LEFT]->ArrowUpdate(1, m_nStatus);
	m_nStatus = m_pSelectPlayer[OL_ARROW_RIGHT]->ArrowUpdate(2, m_nStatus);
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		m_pSelectEffect[i]->EffectUpdate(1,m_bEffect);
		m_pSelectEffect_White[i]->EffectUpdate(2,m_bEffect);
	}
	if (m_nClear == SC_CLEAR_CLEAR || m_nClear == SC_FALSE_CLEAR)
		m_bEffect = true;
	else
		m_bEffect = false;

	// ----- ���̃V�[����
	if (GetTrgKey(DIK_RETURN)) {
		CGameMain::PlaySE(SE_ENTER);
		CGame::SetStageID(m_nStage);
		m_phase = PHASE_FADEOUT;		// ���̃V�[���փt�F�[�h�A�E�g�J�n
	}
}

void CSelect::Effect(bool bDrow)
{
	if (bDrow)
	{
		for (int i = 0; i < EFFECT_MAX; i++)
		{
			m_pSelectEffect[i]->FadeInAlpha(0);
				switch (i)
				{
				case 0:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)0, (float)0, 0));
					break;
				case 1:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)300, (float)0, 0));
					break;
				case 2:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)100, (float)200, 0));
					break;
				case 3:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)400, (float)200, 0));
					break;
				case 4:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)200, (float)400, 0));
					break;
				case 5:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)500, (float)400, 0));
					break;
				case 6:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)0, (float)600, 0));
					break;
				case 7:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)400, (float)600, 0));
					break;
				case 8:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1000, (float)0, 0));
					break;
				case 9:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1200, (float)0, 0));
					break;
				case 10:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1000, (float)300, 0));
					break;
				case 11:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)800, (float)300, 0));
					break;
				case 12:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1300, (float)600, 0));
					break;
				case 13:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1000, (float)600, 0));
					break;
				case 14:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)800, (float)800, 0));
					break;
				case 15:
					m_pSelectEffect[i]->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3((float)1000, (float)800, 0));
					break;
				}
		}
	}
	else
	{
		for (int i = 0; i < EFFECT_MAX; i++)
		{
			m_pSelectEffect[i]->FadeAlpha(0);
		}
	}
}

//========================================================================================
//	End of File
//========================================================================================