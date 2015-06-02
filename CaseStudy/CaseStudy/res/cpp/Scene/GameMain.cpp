//========================================================================================
//		File        : GameMain.cpp
//		Program     : �Q�[���̃��C���N���X
//
//		Description : �Q�[���̃��C���N���X�̎���
//
//		History     : 2014/04/17	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#
#include "../../h/System/PreInclude.h"
#
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "../../h/System/System.h"
#include "../../h/System/Input.h"
#include "../../h/Scene/GameMain.h"
#include "../../h/Scene/Title.h"
#include "../../h/Scene/Select.h"
#include "../../h/Scene/Game.h"
#include "../../h/Scene/Result.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// using�錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
using namespace Input;

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �����o���̐錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
CGraphics*	CGameMain::m_pGraph;		// �O���t�B�b�N�f�o�C�X
CSound*		CGameMain::m_pSound;		// �T�E���h�f�o�C�X

TCHAR	CGameMain::m_szDebug[1024];		// �f�o�b�O�p������
double	CGameMain::m_fps;				// �t���[�����J�E���g�p

CScene* CGameMain::m_sceneList[MAX_SCENEID];	// �S�V�[���̃��X�g(SCENE_ID�ɂĎ��)
bool	CGameMain::m_bEnd = false;				// �Q�[���I���t���O

LPDIRECTSOUNDBUFFER8 CGameMain::m_pBGM[MAX_BGMID];	// BGM���X�g
LPDIRECTSOUNDBUFFER8 CGameMain::m_pSE[MAX_SEID][CSound::MAX_DUP];	// SE���X�g
int		CGameMain::m_lastPlaySE[MAX_SEID];		// ���߂ɍĐ�����SE�ԍ�

CScene* CGameMain::m_pScene;			// ���݂̃V�[��
int		CGameMain::m_curSceneID;		// ���݂̃V�[��ID

CMapData*	CGameMain::m_pMapData;		// �}�b�v�f�[�^


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CGameMain::CGameMain()
{
	m_pGraph		= NULL;
	m_pSound		= NULL;
	m_szDebug[0]	= _T('\0');
	m_fps			= 0.0;

	for(int nCntBGM = 0; nCntBGM < MAX_BGMID; ++nCntBGM)
		m_pBGM[nCntBGM] = NULL;
	for(int nCntSE = 0; nCntSE < MAX_SEID; ++nCntSE) {
		for(int nCntDup = 0; nCntDup < CSound::MAX_DUP; ++nCntDup) {
			m_pSE[nCntSE][nCntDup] = NULL;
		}
		m_lastPlaySE[nCntSE] = 0;
	}

	m_pScene		= NULL;
	m_curSceneID	= MAX_SCENEID;

	m_pMapData		= NULL;

// ----- �f�o�b�O�p�R���\�[������
#ifdef _DEBUG
	if(AllocConsole() == 0)
	{
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CWinSock::�R���\�[���̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
	}
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
#endif
}

//����������������������������������������������������������������������������������������
//	Name        : �f�X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CGameMain::~CGameMain()
{
// ----- �f�o�b�O�p�R���\�[���j��
#ifdef _DEBUG
	if(FreeConsole() == 0)
	{
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CWinSock::�R���\�[���̔j���Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
	}
#endif
}

//����������������������������������������������������������������������������������������
//	Name        : ��������
//	Description : �Q�[�����C���N���X�𐶐�����
//	Arguments   : pGraph / �O���t�B�b�N�N���X
//				  pSound / �T�E���h�N���X
//	Returns     : �Q�[�����C���N���X
//����������������������������������������������������������������������������������������
CGameMain* CGameMain::Create(CGraphics* pGraph, CSound* pSound)
{
	CGameMain* pGameMain = new CGameMain();
	if (pGameMain) {
		if (!pGameMain->Initialize(pGraph, pSound)) {
			SAFE_DELETE(pGameMain);
		}
	}
	return pGameMain;
}

//����������������������������������������������������������������������������������������
//	Name        : �������
//	Description : �Q�[�����C���N���X���������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameMain::Release()
{
	Finalize();
	delete this;
}

//����������������������������������������������������������������������������������������
//	Name        : �`�揈��
//	Description : �Q�[����`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameMain::Render()
{
	if (m_pGraph->Begin()) {	// �`��J�n

		Draw();				// �`�揈��

		m_pGraph->End();		// �`��I��
	}
	m_pGraph->SwapBuffer();		// �o�b�N�o�b�t�@����
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V����
//	Description : �Q�[�����C������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameMain::Update()
{
	// ----- �V�[���X�V
	m_pScene->Update();
}

//����������������������������������������������������������������������������������������
//	Name        : ��Ԑ؂�ւ�
//	Description : ���݂̃Q�[���X�e�[�g��C�ӂɐ؂�ւ���
//	Arguments   : id / �X�e�[�gID
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameMain::SetScene(int id)
{
	// ----- ���̃V�[����
	if(m_pScene)
	{
		m_pScene->Uninit();
	}
	if(id >= 0 && id < MAX_SCENEID)
	{
		m_pScene = m_sceneList[id];
		m_pScene->Init();
	}
}

//����������������������������������������������������������������������������������������
//	Name        : BGM�Đ�
//	Description : �C�ӂ�BGM���Đ�����
//	Arguments   : id       / BGM��ID
//				  loop     / ���[�v�t���O(0:���[�v�Ȃ�, 1:���[�v����)
//				  priority / �D��x
//	Returns     : ��������
//����������������������������������������������������������������������������������������
HRESULT CGameMain::PlayBGM(int id, int loop, int priority)
{
	m_pBGM[id]->SetCurrentPosition(0);
	return m_pBGM[id]->Play(0, priority, loop);
}

//����������������������������������������������������������������������������������������
//	Name        : SE�Đ�
//	Description : �C�ӂ�SE���Đ�����
//	Arguments   : id       / SE��ID
//				  loop     / ���[�v�t���O(0:���[�v�Ȃ�, 1:���[�v����)
//				  priority / �D��x
//	Returns     : ��������
//����������������������������������������������������������������������������������������
HRESULT CGameMain::PlaySE(int id, int loop, int priority)
{
	// ----- �ϐ��錾
	DWORD status;				// SE�Đ����
	LPDIRECTSOUNDBUFFER8* ppSE;	// SE�̃o�b�t�@���X�g

	// ----- ����������
	status	= 0;
	ppSE	= m_pSE[id];	// SE���X�g���擾(������������SE�̃o�b�t�@���X�g)

	// ----- ���O����
	ppSE[0]->GetStatus(&status);	// SE�̍Đ���Ԃ��擾

	// ----- �Đ�����
	if(status & DSBSTATUS_PLAYING)
	{
		// �Đ��\���`�F�b�N
		for(int i = 1; i < CSound::MAX_DUP; ++i)
		{
			// �Đ����Ȃ疢����
			ppSE[i]->GetStatus(&status);
			if(status & DSBSTATUS_PLAYING)
				continue;

			// �Đ�����
			ppSE[i]->SetCurrentPosition(0);				// �Đ��ʒu��������
			m_lastPlaySE[id] = i;						// �Đ�SE�ԍ���ۑ�
			return ppSE[i]->Play(0, priority, loop);	// �Đ�
		}

		// ��ԌÂ��Đ�����SE���~���A�V�����Đ�����
		int playNum = m_lastPlaySE[id] + 1;
		if(playNum >= CSound::MAX_DUP)
			playNum = 0;
		ppSE[playNum]->Stop();							// SE���~
		ppSE[playNum]->SetCurrentPosition(0);			// �Đ��ʒu��������
		m_lastPlaySE[id] = playNum;						// �Đ�SE�ԍ���ۑ�
		return ppSE[playNum]->Play(0, priority, loop);	// �Đ�
	}
	ppSE[0]->SetCurrentPosition(0);				// �Đ��ʒu��������
	m_lastPlaySE[id] = 0;						// �Đ�SE�ԍ���ۑ�
	return ppSE[0]->Play(0, priority, loop);	// �Đ�
}

//����������������������������������������������������������������������������������������
//	Name        : BGM��~
//	Description : �C�ӂ�BGM���~����
//	Arguments   : id / BGM��ID
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameMain::StopBGM(int id)
{
	m_pBGM[id]->Stop();
}

//����������������������������������������������������������������������������������������
//	Name        : SE��~
//	Description : �S�Ă�SE���~����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameMain::StopAllSE()
{
	for(int nCntSE = 0; nCntSE < MAX_SEID; ++nCntSE) {
		for(int nCntDup = 0; nCntDup < CSound::MAX_DUP; ++nCntDup) {
			m_pSE[nCntSE][nCntDup]->Stop();
		}
	}
}


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �f�o�C�X�A���\�[�X������������
//	Arguments   : pGraph / �O���t�B�b�N�N���X
//				  pSound / �T�E���h�N���X
//	Returns     : ����(true:����)
//����������������������������������������������������������������������������������������
bool CGameMain::Initialize(CGraphics* pGraph, CSound* pSound)
{
	// ----- �V�X�e��������
	srand(timeBeginPeriod(1));	// �����̎��ݒ�

	m_pGraph = pGraph;
	m_pSound = pSound;
	
	// ----- �V�[��������
	m_sceneList[SID_TITLE]	= CTitle::Create();		// �^�C�g��
	m_sceneList[SID_SELECT]	= CSelect::Create();	// �y�ȑI��
	m_sceneList[SID_GAME]	= CGame::Create();		// �Q�[���{��
	m_sceneList[SID_RESULT]	= CResult::Create();	// ���U���g

	// ----- BGM������
	for(int nCntBGM = 0; nCntBGM < MAX_BGMID; ++nCntBGM)
		m_pBGM[nCntBGM] = m_pSound->LoadSound(BGM_FILENAME[nCntBGM]);	// BGM�ǂݍ���

	// ----- SE������
	for(int nCntSE = 0; nCntSE < MAX_SEID; ++nCntSE)
	{
		m_pSE[nCntSE][0] = m_pSound->LoadSound(SE_FILENAME[nCntSE]);	// SE�ǂݍ���
		m_lastPlaySE[nCntSE] = -1;		// ���߂ɍĐ�����SE�ԍ���������
	}
	m_pSound->CopyBuffer(m_pSE, MAX_SEID);		// �Z�J���_���o�b�t�@���R�s�[

	// ----- �}�b�v�f�[�^����
	m_pMapData = &CMapData::GetInstance();

	// ----- �ŏ��̃V�[�����Z�b�g
//	SetScene(SID_TITLE);	// �^�C�g����
	SetScene(SID_GAME);	// �^�C�g����

	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �f�o�C�X�A���\�[�X���������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameMain::Finalize()
{
	// ----- �Q�[���p�I�u�W�F�N�g�̌�n��
	for(int nCntSE = MAX_SEID - 1; nCntSE >= 0; --nCntSE)
	{
		for(int nCntDup = CSound::MAX_DUP - 1; nCntDup >= 0; --nCntDup)
		{
			SAFE_RELEASE(m_pSE[nCntSE][nCntDup]);		// SE���
		}
	}
	for(int nCntBGM = MAX_BGMID - 1; nCntBGM >= 0; --nCntBGM)
		SAFE_RELEASE(m_pBGM[nCntBGM]);		// BGM���
	for(int nCntScene = MAX_SCENEID - 1; nCntScene >= 0; --nCntScene)
		SAFE_RELEASE(m_sceneList[nCntScene]);		// �V�[���e�[�u�����
}

//����������������������������������������������������������������������������������������
//	Name        : �`�揈��
//	Description : �Q�[����`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameMain::Draw()
{
#ifdef _DEBUG
	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���

	// FPS ����ʂɕ`�悷�邽�߂̕�������쐬
	TCHAR	str[256];
	_stprintf(str, _T("FPS = %.2f\n"), m_fps);
	lstrcat(m_szDebug, str);
#endif
	
	// ----- �V�[���`��
	m_pScene->Draw();
	
#ifdef _DEBUG
	// �f�o�b�O������`��
	m_pGraph->DrawText(0, 0, m_szDebug);
#endif
}


//========================================================================================
//	End of File
//========================================================================================