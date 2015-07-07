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
#include "../../h/System/ChangeScene.h"
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
	_T("res/img/GameScene/BG/pantsu.png"),		// �w�i�e�N�X�`���t�@�C����
	_T("res/img/GameScene/Object/player_0.png"),	// �v���C���[�e�N�X�`����
	_T("res/img/GameScene/Object/block.png"),	// �u���b�N�e�N�X�`����
	_T("res/img/GameScene/Object/flower_0.png"),
	_T("res/img/GameScene/Object/kuki.png"),
	_T("res/img/GameScene/Object/turu_0.png"),
};
const D3DXVECTOR3 CGame::INIT_TEXTURE_POS[MAX_TEXLIST] = {	// �e�N�X�`���̏����ʒu
	D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, FAR_CLIP),	// �w�i
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),							// �t�B���^�[
};

// �t�F�[�h�֘A
const float CGame::FADE_POSZ = -100.0f;	// �t�F�[�h�p�e�N�X�`����Z���W
const int CGame::FADEIN_TIME = 5;		// �t�F�[�h�C���Ԋu(�A���t�@�l:0�`255)
const int CGame::FADEOUT_TIME = 10;		// �t�F�[�h�A�E�g�Ԋu(�A���t�@�l:0�`255)

// ----- �����o�ϐ�
// private:
int CGame::m_stageID;		// �I�������X�e�[�W��ID


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CGame::CGame()
{
	m_pBG = NULL;
	m_pCamera = NULL;

	m_pStage = NULL;
	m_stageID = 0;

	m_pGameStop = NULL;
	m_pGameOver = NULL;
	m_pGameClear = NULL;
	m_pPlayersGroup = NULL;

	m_phase = MAX_PHASE;
	m_pNextScene = SID_RESULT;

	srand((unsigned)time(NULL));
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

	// ----- �J����������
	m_pCamera->Init();

	// ----- ���̃t�F�[�Y��
	m_phase = PHASE_FADEIN;		// �t�F�[�h�C���J�n
	m_pNextScene = SID_RESULT;

	// �X�e�[�W������
	m_pStage->Init(m_stageID);

	m_pPlayersGroup->Init();
	m_pPlayersGroup->SetStage(m_pStage);

	m_pGameStop->Init();
	m_pGameOver->Init();
	m_pGameClear->Init();

	// ----- �t�F�[�h�ݒ�
	CChangeScene::SetNormalFadeAlpha(255);

	// ----- BGM�Đ�
	CGameMain::PlayBGM(BGM_RESULT, DSBPLAY_LOOPING);
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

	// ----- �I�u�W�F�N�g��n��
	m_pCamera->Uninit();			// �J����

	m_pStage->Uninit();

	m_pGameStop->Uninit();
	m_pGameOver->Uninit();
	m_pGameClear->Uninit();

	m_pPlayersGroup->Uninit();

	// ----- BGM��~
	CGameMain::StopBGM(BGM_RESULT);

	for (unsigned int i = 0; i < m_listFlower.size(); i++){
		m_listFlower[i]->Uninit();
		SAFE_RELEASE(m_listFlower[i])
	}
	m_listFlower.clear();
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

	// �J����

	if (m_pPlayersGroup->GetPlayer(m_pPlayersGroup->GetPlayNo())){
		m_pCamera->SetNextEye(m_pPlayersGroup->GetPlayer(m_pPlayersGroup->GetPlayNo())->GetPosition());
	}
	else{

	}

	// �J�����̃t�F�C�Y�𓯊�
	m_pCamera->SetPhase(m_phase);

	m_pCamera->Update();

	switch (m_phase)
	{
		// �t�F�[�h�C��
	case PHASE_FADEIN:
		if (CChangeScene::NormalFadeOut(FADE_POSZ, FADEIN_TIME))
			m_phase = PHASE_MAIN;		// �J�n����
		break;

		// ���̃V�[���փt�F�[�h�A�E�g
	case PHASE_FADEOUT:
		if (CChangeScene::NormalFadeIn(FADE_POSZ, FADEOUT_TIME))
		{	// ���̃V�[����
			Uninit();							// ��n��
			CGameMain::SetScene(m_pNextScene);	// ���U���g��
		}
		break;

		// �Q�[���{��
	case PHASE_MAIN:
		Main();
		break;
	case PHASE_STOP:
		Stop();
		break;
	case PHASE_OVER:
		Over();
		break;
	case PHASE_CLEAR:
		Clear();
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
	m_pBG->DrawScreen();		// �w�i

	switch (m_phase)
	{
		// �t�F�[�h�C���E�A�E�g
	case PHASE_FADEIN:
	case PHASE_FADEOUT:
		CChangeScene::DrawNormalFade();
		break;

		// �Q�[���{��
	case PHASE_MAIN:
		DrawMain();
		break;

	case PHASE_STOP:
		DrawStop();
		break;
	case PHASE_OVER:
		DrawOver();
		break;
	case PHASE_CLEAR:
		DrawClear();
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
	if (pGame)
	{
		if (!pGame->Initialize())
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
	m_pBG = CObject2D::Create(TEX_FILENAME[TL_BG]);
	if (m_pBG == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CGame::BG�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}

	// ----- �I�u�W�F�N�g����
	// �J����
	m_pCamera = CGameCamera::Create();
	if (m_pCamera == NULL) {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CGame::Camera�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}

	/*�@�����݂��񂪒ǉ�������@*/
	// �u���b�N
	m_pStage = CStage::Create();
	m_pStage->SetColBoxTexture(TEX_FILENAME[TL_BLOCK_0]);

	m_pGameStop = CGameStop::Create();
	m_pGameStop->Initialize();

	m_pGameOver = CGameOver::Create();
	m_pGameOver->Initialize();

	m_pGameClear = CGameClear::Create();
	m_pGameClear->Initialize();

	// �v���C���[
	m_pPlayersGroup = CPlayersGroup::Create(TEX_FILENAME[TL_PLAYER_0]);
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
	SAFE_RELEASE(m_pBG);		// �w�i

	SAFE_RELEASE(m_pStage);		// �u���b�N

	SAFE_RELEASE(m_pGameStop);
	SAFE_RELEASE(m_pGameOver);
	SAFE_RELEASE(m_pGameClear);

	SAFE_RELEASE(m_pPlayersGroup);
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
	if (GetTrgKey(DIK_RETURN)) {
		m_phase = PHASE_FADEOUT;	// ���̃V�[���փt�F�[�h�A�E�g
	}

	if (GetTrgKey(DIK_RSHIFT)) {
		CGameMain::PlaySE(SE_POSE);
		m_phase = PHASE_STOP;	// ���̃V�[���փt�F�[�h�A�E�g
	}

	// �Q�[���I�[�o
	if (m_pPlayersGroup->GetOver()){
		m_phase = PHASE_OVER;
	}

	// �Q�[���N���A
	bool Clear = false;
	for (int i = 0; i < m_pStage->GetMaxFieldBlock(); i++){
		CFieldBlock* pFieldBlock = m_pStage->GetFieldBlock(i);
		if (pFieldBlock->GetType() == CMapData::BT_CLEAR){
			if (pFieldBlock->GetFloawerNum())
				Clear = true;
			else
				Clear = false;
		}
	}
	
	// �Q�[���N���A���o�J�n
	//	if(Clear){
	if (Clear || GetTrgKey(DIK_Q)) {	// �f�o�b�O�p
		m_phase = PHASE_CLEAR;

		// �J�����������������Z�o
		float widthDist = CMapData::GetRightLimit() - CMapData::GetLeftLimit();
		float heightDist = CMapData::GetTopLimit() - CMapData::GetBottomLimit();
		if (widthDist > heightDist)
			m_pGameClear->SetDirectionDistance(widthDist);
		else
			m_pGameClear->SetDirectionDistance(heightDist);

		// �J�����Z�b�g
		D3DXVECTOR2 cameraPos(CMapData::GetRightLimit() - widthDist * 0.5f, CMapData::GetTopLimit() - heightDist * 0.5f);
		m_pGameClear->SetCameraStartPos(cameraPos);
		m_pGameClear->SetCamera(m_pCamera);

		//		m_phase = PHASE_FADEOUT;
	}

	// ���X�g���S���X�V
	m_pStage->Update();

	// �v���C���[�̍X�V
	m_pPlayersGroup->Update();

	// �v���C���[�̃R�[���Ɏ���̓z�͑Ή�����
	for (int i = 0; i < m_pPlayersGroup->GetGroupSize(); i++){
		if (m_pPlayersGroup->GetPlayer(i)){
			if (m_pPlayersGroup->GetPlayer(i)->GetStatus() & ST_CALL){
				for (int j = 0; j < m_pPlayersGroup->GetGroupSize(); j++){
					if (m_pPlayersGroup->GetPlayer(j)->GetType() == P_TYPE_WAIT){
						float length = D3DXVec3Length(&(m_pPlayersGroup->GetPlayer(j)->GetPosition() - m_pPlayersGroup->GetPlayer(i)->GetPosition()));
						if (length < 300){
							m_pPlayersGroup->GetPlayer(j)->SetType(P_TYPE_OTHER);
						}
					}
				}
				m_pPlayersGroup->GetPlayer(i)->SubStatus(ST_CALL);
			}
		}
	}
	// �v���C���[���ԏ�ԂɂȂ�����ԍ炩��
	for(int i = 0;i < m_pPlayersGroup->GetGroupSize();i++){
		if(m_pPlayersGroup->GetPlayer(i)){
			if(m_pPlayersGroup->GetPlayer(i)->GetType() == P_TYPE_FLOWER){
				D3DXVECTOR3 pos = D3DXVECTOR3(m_pPlayersGroup->GetPlayer(i)->GetLastColLinePos().x,m_pPlayersGroup->GetPlayer(i)->GetLastColLinePos().y,m_pPlayersGroup->GetPlayer(i)->GetPosZ() + 1);
				D3DXVECTOR3 dir;
				D3DXVECTOR3 vec = D3DXVECTOR3(m_pPlayersGroup->GetPlayer(i)->GetLastColLine().x,m_pPlayersGroup->GetPlayer(i)->GetLastColLine().y,0);
				D3DXVec3Cross(&dir,&vec,&D3DXVECTOR3(0,0,1));
				D3DXVec3Normalize(&dir,&dir);

				switch(m_pPlayersGroup->GetPlayer(i)->GetGrane()){
					case PLAYER_NORMAL:
						CreateFlower(pos,dir);
						break;
					case PLAYER_JACK:
						CreateJack(pos,dir);
						break;
					case PLAYER_STONE:
						//CreateFlower(pos,dir);
						break;
				}
				(m_pPlayersGroup)->GetPlayer(i)->EnableDelete();
			}
		}
	}

	for (unsigned int i = 0; i < m_listFlower.size(); i++)
	{
		m_listFlower[i]->Update();

		// �ԏ�Ԃ̂Ƃ��Ɏ�𑝂₷
		if (m_listFlower[i]->GetPhase() == FLOWER_PHASE_FLOWER){
			D3DXVECTOR3 move;
			D3DXVECTOR3 pos1;
			D3DXVec3Cross(&move,&m_listFlower[i]->GetPosition(),&D3DXVECTOR3(0,0,1));
			D3DXVec3Normalize(&move,&move);
			pos1 = m_listFlower[i]->GetPosition() + (move * (FLOWER_SIZE_X / 2));
			D3DXVECTOR3 pos2;
			D3DXVec3Cross(&move,&m_listFlower[i]->GetPosition(),&D3DXVECTOR3(0,0,-1));
			D3DXVec3Normalize(&move,&move);
			pos2 = m_listFlower[i]->GetPosition() + (move * (FLOWER_SIZE_X / 2));
			
			m_pPlayersGroup->AddPlayer(pos1);
			m_pPlayersGroup->AddPlayer(pos2);
			m_listFlower[i]->SetPhase(FLOWER_PHASE_WAIT);
		}
	}
}
//����������������������������������������������������������������������������������������
//	Name        : ���C��
//	Description : �Q�[���{�҂̃��C���`��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGame::DrawMain()
{
	// �X�e�[�W�`��
	m_pStage->Draw();

	// �v���C���[�`��
	m_pPlayersGroup->Draw();

	// �Ԃ̕`��
	for (unsigned int i = 0; i < m_listFlower.size(); i++)
	{
		m_listFlower[i]->DrawAlpha();
	}
}
//����������������������������������������������������������������������������������������
//	Name        : �ꎞ��~
//	Description : �Q�[���{�҂̈ꎞ��~����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGame::Stop()
{
	m_pGameStop->Update();

	if (m_pGameStop->GetPhase() == GAME_STOP_PHASE_END){
		switch (m_pGameStop->GetGo())
		{
		case GO_GAME:
			m_phase = PHASE_MAIN;
			break;
		case GO_RESET:
			m_phase = PHASE_FADEOUT;
			m_pNextScene = SID_GAME;
			break;
		case GO_SELECT:
			m_phase = PHASE_FADEOUT;
			m_pNextScene = SID_SELECT;
			break;
		}
		m_pGameStop->Init();
	}
}
//����������������������������������������������������������������������������������������
//	Name        : �ꎞ��~
//	Description : �Q�[���{�҂̈ꎞ��~�`��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGame::DrawStop()
{
	DrawMain();
	m_pGameStop->Draw();
}
//����������������������������������������������������������������������������������������
//	Name        : �ꎞ��~
//	Description : �Q�[���{�҂̈ꎞ��~����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGame::Over()
{
	m_pGameOver->Update();

	if (m_pGameOver->GetPhase() == GAME_STOP_PHASE_END){
		switch (m_pGameOver->GetGo())
		{
		case 0:
			m_phase = PHASE_FADEOUT;
			m_pNextScene = SID_GAME;
			break;
		case 1:
			m_phase = PHASE_FADEOUT;
			m_pNextScene = SID_SELECT;
			break;
		}
		m_pGameOver->Init();
	}
}
//����������������������������������������������������������������������������������������
//	Name        : �ꎞ��~
//	Description : �Q�[���{�҂̈ꎞ��~�`��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGame::DrawOver()
{
	DrawMain();
	m_pGameOver->Draw();
}

//����������������������������������������������������������������������������������������
//	Name        : �Q�[���N���A���C��
//	Description : �Q�[���N���A���̃��C������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGame::Clear()
{
	m_pGameClear->Update();

	if (m_pGameClear->GetPhase() == CGameClear::PHASE_END){
		switch (m_pGameClear->GetGo())
		{
		case 0:
			m_phase = PHASE_FADEOUT;
			m_pNextScene = SID_GAME;
			break;
		case 1:
			m_phase = PHASE_FADEOUT;
			m_pNextScene = SID_SELECT;
			break;
		}
		m_pGameClear->Init();
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �Q�[���N���A�`��
//	Description : �Q�[���N���A���̕`�揈��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGame::DrawClear()
{
	DrawMain();
	m_pGameClear->Draw();
}

//����������������������������������������������������������������������������������������
//	Name        : �Ԃ̐���
//	Description :�@
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGame::CreateFlower(D3DXVECTOR3 pos,D3DXVECTOR3 dir)
{
	CFlower* flower;
	flower = CFlower::Create(TEX_FILENAME[TL_FLOWER_0]);
	flower->Init(pos,dir,TEX_FILENAME[TL_FLOWER_1]);

	m_listFlower.push_back(flower);
}
//����������������������������������������������������������������������������������������
//	Name        : �Ԃ̐���
//	Description :�@
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGame::CreateJack(D3DXVECTOR3 pos,D3DXVECTOR3 dir)
{
	CJack* flower;
	flower = CJack::Create(TEX_FILENAME[TL_JACK_0]);
	flower->Init(pos,dir);

	m_listFlower.push_back(flower);
}


//========================================================================================
//	End of File
//========================================================================================