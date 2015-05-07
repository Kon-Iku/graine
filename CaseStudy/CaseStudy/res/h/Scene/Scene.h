//========================================================================================
//		File        : Scene.h
//		Program     : �V�[���x�[�X
//
//		Description : �Q�[���V�[���̃x�[�X����
//
//		History     : 2013/12/18	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================

#pragma once

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../System/PreInclude.h"
#
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
enum _eSceneId
{
	SID_TITLE = 0,		// �^�C�g��
	SID_SELECT,			// �y�ȑI��
	SID_GAME,			// �Q�[���{��
	SID_RESULT,			// ���U���g

	MAX_SCENEID,		// �V�[����
};

// ----- BGM�֘A
enum _eBGMID
{
	BGM_TITLE = 0,		// �^�C�g��
	BGM_SELECT,			// �y�ȑI��
	BGM_RESULT,			// ���U���g

	MAX_BGMID
};
const LPTSTR BGM_FILENAME[MAX_BGMID] = {
	_T("res/bgm/Title.wav"),		// �^�C�g��
	_T("res/bgm/Select.wav"),		// �y�ȑI��
	_T("res/bgm/Result.wav"),		// ���U���g
};

// ----- SE�֘A
enum _eSEID
{
	SE_HAND_CLAP = 0,	// �n���h�N���b�v
	SE_SELECT,			// �I����
	SE_MUSIC_FIX,		// �y�Ȍ��艹

	MAX_SEID
};
const LPTSTR SE_FILENAME[MAX_SEID] = {
	_T("res/se/HandClap.wav"),	// �n���h�N���b�v
	_T("res/se/Select.wav"),	// �I����
	_T("res/se/MusicFix.wav"),	// �y�Ȍ��艹
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CScene
{
// ===== �����o�ϐ�
protected:

// ===== �����o�֐�
public:		 
	CScene();
	virtual ~CScene();

	virtual void Init() = 0;		// ������
	virtual void Uninit() = 0;		// ��n��
	virtual void Update() = 0;		// �X�V
	virtual void Draw() = 0;		// �`��
	virtual void Release();			// ���
				 
protected:		 
	//virtual bool Initialize(CMesh** ppMesh, LPDIRECTSOUNDBUFFER8 pBGM) = 0;		// ������
	virtual bool Initialize() = 0;		// ������
	virtual void Finalize() = 0;		// ��n��
};


//========================================================================================
//	End of File
//========================================================================================