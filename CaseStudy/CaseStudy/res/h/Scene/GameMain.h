//========================================================================================
//		File        : GameMain.h
//		Program     : �Q�[���̃��C���N���X
//
//		Description : �Q�[���̃��C���N���X�̒�`
//
//		History     : 2014/04/17	�쐬�J�n
//						   05/23	�t�@�C�����ύX
//
//																Author : Kei Hashimoto
//========================================================================================

#pragma once

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../System/PreInclude.h"
#
#include "../System/Graphics.h"
#include "../System/Sound.h"
#include "../System/ChangeScene.h"
#include "../System/MapData.h"
#include "../Scene/Scene.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CGameMain
{
// ===== �����o�ϐ�
private:
	static CGraphics*	m_pGraph;			// �O���t�B�b�N�f�o�C�X
	static CSound*		m_pSound;			// �T�E���h�f�o�C�X

	static TCHAR	m_szDebug[];			// �f�o�b�O�p������
	static double	m_fps;					// �t���[�����J�E���g�p

	// ----- �Q�[���p�I�u�W�F�N�g
	static CScene*	m_sceneList[];			// �S�V�[���̃��X�g(SCENE_ID�ɂĎ��)
	static bool		m_bEnd;					// �Q�[���I���t���O

	static LPDIRECTSOUNDBUFFER8	m_pBGM[];	// BGM���X�g
	static LPDIRECTSOUNDBUFFER8	m_pSE[][CSound::MAX_DUP];	// SE���X�g
	static int		m_lastPlaySE[];		// ���߂ɍĐ�����SE�ԍ�

	static CScene*	m_pScene;			// ���݂̃V�[��
	static int		m_curSceneID;		// ���݂̃V�[��ID

	static CChangeScene*	m_pChangeScene;		// �V�[���J�ڃV�X�e��
	static CMapData*		m_pMapData;			// �}�b�v�f�[�^
	
// ===== �����o�֐�
public:
	CGameMain();
	virtual ~CGameMain();

	static CGameMain* Create(CGraphics*, CSound*);
	void Release();
	void Render();
	void Update();
	void SetFPS(double fps) {m_fps = fps;}
	static void AddDebugStr(LPCTSTR psz) {lstrcat(m_szDebug, psz);}	// �f�o�b�O�p������Z�b�g

	// ----- �Z�b�^�[
	static void SetScene(int id);				// �V�[���؂�ւ�
	
	bool GetEndFlg(void) {return m_bEnd;}			// �Q�[���I���t���O�擾
	static void	GameEnd(void) {m_bEnd = true;}		// �Q�[���I��

	// ----- �T�E���h�֘A
	static HRESULT	PlayBGM(int id, int loop = 0, int priority = 0);	// BGM�Đ�
	static HRESULT	PlaySE(int id, int loop = 0, int priority = 0);		// SE�Đ�
	static void		StopBGM(int id);									// BGM��~
	static void		StopAllSE();										// SE��~

private:
	bool Initialize(CGraphics*, CSound*);
	void Finalize();
	void Draw();
};


//========================================================================================
//	End of File
//========================================================================================