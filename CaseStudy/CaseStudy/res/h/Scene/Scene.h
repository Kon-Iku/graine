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

	MAX_SCENEID,		// �V�[����
};

// ----- BGM�֘A
enum _eBGMID
{
	BGM_TITLE = 0,		// �^�C�g��
	BGM_SELECT,			// �y�ȑI��
	BGM_GAME,			// �Q�[���{��
	BGM_PAUSE,

	MAX_BGMID
};
const LPTSTR BGM_FILENAME[MAX_BGMID] = {
	_T("res/bgm/title2.wav"),	// �^�C�g��
	_T("res/bgm/Select.wav"),			// �y�ȑI��
	_T("res/bgm/gamemain.wav"),		// �Q�[���{��
	_T("res/bgm/pause.wav"),		// �|�[�Y
};

// ----- SE�֘A
enum _eSEID
{
	/*SE_HAND_CLAP = 0,	// �n���h�N���b�v
	SE_SELECT,			// �I����
	SE_MUSIC_FIX,		// �y�Ȍ��艹*/
	SE_WALK,			// ����
	SE_POSE,			// �|�[�Y
	SE_CHOICE,			// �I��
	SE_ENTER,			// ����
	SE_JUMP,			// �W�����v
	SE_BORN,			// �Y�܂����
	SE_THROW,			// ������
	SE_GOUSEI,			// �������
	SE_RIDE,			// �悹��
	SE_UMARU,			// ���܂�
	MAX_SEID
};
const LPTSTR SE_FILENAME[MAX_SEID] = {
	/*_T("res/se/HandClap.wav"),	// �n���h�N���b�v
	_T("res/se/Select.wav"),	// �I����
	_T("res/se/MusicFix.wav"),	// �y�Ȍ��艹*/
	_T("res/se/walk.wav"),		// ����
	_T("res/se/pose.wav"),		// �|�[�Y
	_T("res/se/cursormove.wav"),// �I��
	_T("res/se/enter.wav"),		// ����
	_T("res/se/jump.wav"),		// �W�����v
	_T("res/se/born.wav"),		// �炭
	_T("res/se/Throw.wav"),		// ������
	_T("res/se/gousei.wav"),	// ����
	_T("res/se/ride.wav"),		// �悹��
	_T("res/se/umaru.wav"),		// ���܂�
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