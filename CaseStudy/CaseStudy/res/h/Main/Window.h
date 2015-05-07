//========================================================================================
//		File        : Window.h
//		Program     : �E�B���h�E�N���X
//
//		Description : �E�B���h�E�N���X�̒�`
//
//		History     : 2014/04/17	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================

#pragma once
#ifndef _WIN32_WINNT
#define _WIN32_WINNT	0x0500
#endif

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../System/PreInclude.h"
#
#include <windows.h>
#include <tchar.h>

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CWindow
{
// ===== �����o�ϐ�
private:
	HWND		m_hWnd;				// �E�B���h�E �n���h��
	HINSTANCE	m_hInstance;		// �C���X�^���X �n���h��
	ATOM		m_Atom;				// �E�B���h�E �N���X�o�^���� ATOM
	LPTSTR		m_pszClassName;		// �N���X��
	WNDPROC		m_lpfnOldWndProc;	// �E�B���h�E �v���V�[�W�� �o�b�t�@
	bool		m_bDialog;			// �_�C�A���O �t���O
	MSG			m_msgCur;			// ���݂̃��b�Z�[�W
	POINT		m_ptCursorLast;		// �}�E�X�J�[�\���̍ŐV���W
	UINT		m_nMsgLast;			// �ŐV�̃��b�Z�[�W
	// ���b�Z�[�W��U�蕪����E�B���h�E(�_�C�A���O)�v���V�[�W��
	static LRESULT CALLBACK WndMapProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
// ===== �����o�֐�
public:
	CWindow();
	virtual ~CWindow();

	bool Create(LPCTSTR pszWindowName,
		DWORD dwStyle = WS_OVERLAPPEDWINDOW, DWORD dwExStyle = 0,
		int nX = CW_USEDEFAULT, int nY = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT,
		HWND hwndParent = NULL, HMENU nIDorHMenu = NULL, LPVOID pParam = NULL);
	bool Create(LPCTSTR pszWindowName, DWORD dwStyle, DWORD dwExStyle,
		const RECT& rc, CWindow* pParentWnd, UINT nID, LPVOID pParam = NULL);
	bool CreateFrame(LPCTSTR pszWindowName,
		DWORD dwStyle = WS_OVERLAPPEDWINDOW, DWORD dwExStyle = 0,
		int nX = CW_USEDEFAULT, int nY = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT,
		HWND hwndParent = NULL, HMENU nIDorHMenu = NULL, LPVOID pParam = NULL);
	void Close() {OnClose();}

	// �E�B���h�E�n���h����CWindow�I�u�W�F�N�g�����ѕt����
	bool Attach(HWND hWnd);
	// �E�B���h�E�n���h����CWindow�I�u�W�F�N�g����؂藣��
	HWND Detach();

	// ������
	virtual bool InitInstance();

	// �f�t�H���g�̃��b�Z�[�W ���[�v
	virtual int Run();
	virtual bool PreTranslateMessage(MSG* pMsg);
	virtual bool PumpMessage();
	virtual bool OnIdle(long lCount);
	virtual bool IsIdleMessage(MSG* pMsg);

	// �I������
	virtual int ExitInstance();

	// �E�B���h�E �n���h����Ԃ�
	HWND GetHwnd() const {return (this) ? m_hWnd : NULL;}
	operator HWND() const {return GetHwnd();}

	// �C���X�^���X �n���h����Ԃ�
	HINSTANCE GetInstance() const {return (this) ? m_hInstance : NULL;}
	operator HINSTANCE() const {return GetInstance();}

	// �E�B���h�E�̕\��
	bool Show(int nCmdShow) {return ::ShowWindow(m_hWnd, nCmdShow) != FALSE;}
	void Update() {::UpdateWindow(m_hWnd);}

	// ���b�Z�[�W �{�b�N�X�̕\��
	int MessageBox(LPCTSTR pszText, LPCTSTR pszCaption = NULL, UINT nType = MB_OK);

	// �E�B���h�E �T�C�Y
	bool GetClientRect(LPRECT pRect) {return ::GetClientRect(m_hWnd, pRect) != FALSE;}

protected:
	// �I�[�o�[���C�h�\�ȃE�B���h�E(�_�C�A���O)�v���V�[�W��
	virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	// �E�B���h�E�̃N���C�A���g�̈��`��
	virtual void OnDraw(HDC hdc);

	virtual LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual bool OnCommand(WPARAM wParam, LPARAM lParam);

	virtual int OnCreate(LPCREATESTRUCT pcs);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnPaint();
	virtual bool OnEraseBkgnd(HDC hdc);
	virtual void OnClose();
	virtual void OnDestroy();
	virtual bool OnSetCursor(HWND hwnd, UINT nHitTest, UINT uMouseMsg);
	virtual void OnMouseMove(UINT nFlags, POINT pt);
	virtual void OnDropFiles(HDROP hDropInfo);
	virtual bool OnMouseWheel(UINT nFlags, short zDelta, POINT pt);

	bool RegisterClass();
};


//========================================================================================
//	End of File
//========================================================================================