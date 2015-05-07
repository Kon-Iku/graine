//========================================================================================
//		File        : Main.cpp
//		Program     : ���C������
//
//		Description : �Q�[���̃��C������
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
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include "../../h/Main/GameWnd.h"
#include "../../h/System/System.h"

// ----- ���C�u�����̃����N
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#define CAPTION_NAME	_T("CaseStudy")		// �L���v�V������


//����������������������������������������������������������������������������������������
//	Name        : ���C��
//	Description : ���C������
//	Arguments   : hInstance / �C���X�^���X�n���h��
//				  hPrevInst / ���O�̃C���X�^���X�n���h��
//				  lpCmdLine / �R�}���h���C��������
//				  iCmdShow  / �E�B���h�E���
//	Returns     : ���U���g
//����������������������������������������������������������������������������������������
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int iCmdShow)
{
	// �E�B���h�E���쐬
	int nResult = EXIT_FAILURE;
	CGameWindow* pWnd = new CGameWindow();
	if (pWnd->CreateFrame(CAPTION_NAME,				// �E�B���h�E �L���v�V����
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, 0,	// �E�B���h�E �X�^�C���C�g���X�^�C��
		CW_USEDEFAULT, CW_USEDEFAULT,				// �E�B���h�E�ʒu
		SCREEN_WIDTH, SCREEN_HEIGHT)) {				// �N���C�A���g�̈�T�C�Y
		pWnd->Show(iCmdShow);						// �E�B���h�E��\��
		pWnd->Update();								// �E�B���h�E�\�����X�V
		nResult = pWnd->Run();						// ���b�Z�[�W ���[�v
	}
	delete pWnd;
	return nResult;
}


//========================================================================================
//	End of File
//========================================================================================