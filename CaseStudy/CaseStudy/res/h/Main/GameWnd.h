//========================================================================================
//		File        : GameWnd.h
//		Program     : �Q�[���p�E�B���h�E�N���X
//
//		Description : �Q�[���p�E�B���h�E�N���X�̒�`
//
//		History     : 2014/04/17	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================

#pragma once

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../System/PreInclude.h"
#
#include "../Main/Window.h"
#ifdef __OPT_HIGH_TIMER
	#include "../System/Timer.h"
#endif
#include "../System/Graphics.h"
#include "../System/Input.h"
#include "../System/Sound.h"
#include "../Scene/GameMain.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CGameWindow : public CWindow
{
// ===== �����o�ϐ�
private:
#ifdef __OPT_WINSOCK
	CWinSock*	m_pWinSock;			// WinSock�ʐM �N���X
#endif

#ifdef __OPT_HIGH_TIMER
	CTimer*		m_pTimer;			// �^�C�}�[�����N���X
	double		m_dFPSLastTime;		// FPS�`��p
#else
	DWORD		m_dwExecLastTime;	// FPS�v���p
	DWORD		m_dwFPSLastTime;	// FPS�`��p
	DWORD		m_dwFrameCount;		// �t���[���J�E���^
#endif

	CGraphics*	m_pGraph;			// �`��f�o�C�X �N���X
	CInput*		m_pInput;			// ���o�̓f�o�C�X �N���X
	CSound*		m_pSound;			// �T�E���h�f�o�C�X �N���X
	CGameMain*	m_pGameMain;		// �Q�[�����C��

	bool		m_bWindow;			// �E�B���h�E / �t���X�N���[��
	
// ===== �����o�֐�
private:
	bool InitInstance();
	int ExitInstance();
	bool OnIdle(long lCount);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	bool OnEraseBkgnd(HDC hdc);
	bool OnSetCursor(HWND hwnd, UINT nHitTest, UINT uMouseMsg);
};


//========================================================================================
//	End of File
//========================================================================================