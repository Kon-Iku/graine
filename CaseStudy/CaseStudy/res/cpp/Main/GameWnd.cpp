//========================================================================================
//		File        : GameWnd.cpp
//		Program     : �Q�[���p�E�B���h�E�N���X
//
//		Description : �Q�[���p�E�B���h�E�N���X�̎���
//
//		History     : 2014/04/17	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/PreInclude.h"
#
#include "../../h/Main/GameWnd.h"
#include "../../h/System/System.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#ifdef __OPT_HIGH_TIMER
const double SET_FPS_TIME = 0.5;	// FPS�`�掞��
#else
const int SET_FPS_TIME = 500;		// FPS�v�Z����
#endif


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �E�B���h�E������������
//	Arguments   : None.
//	Returns     : ����(true:����)
//����������������������������������������������������������������������������������������
bool CGameWindow::InitInstance()
{
	if (!CWindow::InitInstance()) return false;

	//m_bWindow = false;
	//if (IDYES == MessageBox(_T("�E�B���h�E���[�h�Ŏ��s���܂����H"), _T("��ʃ��[�h"), MB_YESNO))
	m_bWindow = true;

	// �^�C�}�[�����̎��O����
#ifdef __OPT_HIGH_TIMER
	// ���𑜓x�^�C�}�[������
	m_pTimer = &CTimer::GetInstance();
#else
	::timeBeginPeriod(1);	// �^�C�}�̕���\���ŏ��ɃZ�b�g
#endif

#ifdef __OPT_WINSOCK
	// WinSock�ʐM������
	m_pWinSock = &CWinSock::GetInstance();
#endif

	// �O���t�B�b�N�f�o�C�X������
	m_pGraph = CGraphics::Create(GetHwnd(), SCREEN_WIDTH, SCREEN_HEIGHT, m_bWindow);
	if (!m_pGraph) return false;
	
	// �T�E���h�f�o�C�X������
	m_pSound = &CSound::GetInstance();
	m_pSound->InitSound(GetHwnd());

	// ���o�̓f�o�C�X������
	m_pInput = &CInput::GetInstance();
	m_pInput->InitInput(GetInstance(), GetHwnd());

	// �V�[��������
	m_pGameMain = CGameMain::Create(m_pGraph, m_pSound);
	if (!m_pGameMain) return false;

	// �^�C�}�[�����J�n
#ifdef __OPT_HIGH_TIMER
	// ���𑜓x�^�C�}�[�Ƃ��ď������J�n(���Ή��̏ꍇ�͓����Œ�𑜓x�^�C�}�[�Ƃ��ē���)
	m_pTimer->Start();
	m_dFPSLastTime = m_pTimer->GetTime();
#else
	m_dwFPSLastTime = ::timeGetTime();
	m_dwExecLastTime = m_dwFPSLastTime - (DWORD)FRAME_RATE;// �K���ŏ��� m_pGameMain->Update() �����s
	m_dwFrameCount = 0;
#endif

	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : �I������
//	Description : �E�B���h�E���������
//	Arguments   : None.
//	Returns     : ���s�t�@�C���̖߂�l
//����������������������������������������������������������������������������������������
int CGameWindow::ExitInstance()
{
	// �V�[�����
	SAFE_RELEASE(m_pGameMain);

	// ���o�̓f�o�C�X���
	SAFE_RELEASE(m_pInput);

	// �T�E���h�f�o�C�X���
	SAFE_RELEASE(m_pSound);

	// �O���t�B�b�N �f�o�C�X���
	SAFE_RELEASE(m_pGraph);

#ifdef __OPT_HIGH_TIMER
	// ���𑜓x�^�C�}�[�̉��(���݂͖�����)
	#ifdef __TIMER_SINGLETON
	#else
	//SAFE_RELEASE(m_pTimer);
	#endif
#else
	::timeEndPeriod(1);				// �^�C�}�̕���\�����ɖ߂�
#endif

	return CWindow::ExitInstance();	// ���s�t�@�C���̖߂�l
}

//����������������������������������������������������������������������������������������
//	Name        : �A�C�h������
//	Description : �A�C�h��������
//	Arguments   : lCount / �A�C�h���J�E���^
//	Returns     : ����(true:����)
//����������������������������������������������������������������������������������������
bool CGameWindow::OnIdle(long lCount)
{
	// �t���[������
#ifdef __OPT_HIGH_TIMER
	// �o�߃t���[�������擾
	int cnt = m_pTimer->Run();

	// �o�߃t���[�������̏��������s
	for(int i = 0; i < cnt; ++i)
	{
		if(m_pGameMain)
		{
			if(m_pTimer->GetTime() - m_dFPSLastTime >= SET_FPS_TIME)	// 0.5�b���Ƃɕ`��
			{
				m_pGameMain->SetFPS(m_pTimer->GetFps());	// �t���[�������擾�E�Z�b�g
				m_dFPSLastTime = m_pTimer->GetTime();		// �^�C�}�l���X�V
			}
		}
#else
	// ���̕ӂŃt���[�����J�E���g
	DWORD dwCurrentTime = ::timeGetTime();		// ���݂̃^�C�}�l���擾
	if (dwCurrentTime - m_dwFPSLastTime >= SET_FPS_TIME) {	// 0.5 �b���ƂɌv��
		// �t���[�������v�Z
		if (m_pGameMain) {
			m_pGameMain->SetFPS(m_dwFrameCount * 1000 / (dwCurrentTime - m_dwFPSLastTime));
		}
		m_dwFPSLastTime = dwCurrentTime;	// �^�C�}�l���X�V
		m_dwFrameCount = 0;					// �t���[���J�E���^�����Z�b�g
	}
	// ���̕ӂŎ��ԊǗ�
	while (dwCurrentTime - m_dwExecLastTime >= FRAME_RATE) {	// ��莞�Ԃ��o�߂�����c
		m_dwExecLastTime += (DWORD)FRAME_RATE;					// �^�C�}�l���X�V
#endif

		if (m_pGameMain) {
#ifdef __OPT_WINSOCK
			m_pWinSock->Update();				// WinSock�ʐM �X�V
#endif
			m_pInput->UpdateInput(GetHwnd());	// ���̓f�o�C�X���X�V
			m_pGameMain->Update();				// �Q�[�� ���C������
		}
		
#ifdef __OPT_HIGH_TIMER
#else
		m_dwFrameCount++;					// �t���[���J�E���g�{�P
#endif
	}
	if (m_pGameMain) {
		m_pGameMain->Render();			// �����_�����O����
	}
	if(m_pGameMain->GetEndFlg())		// �Q�[���I��
		OnClose();

	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : �n���h��
//	Description : WM_KEYDOWN �n���h��
//	Arguments   : nChar   / �L�[�R�[�h
//				  nRepCnt / ���s�[�g�J�E���g
//				  nFlags  / �t���O
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CGameWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// [Esc] ��������Ă�����
	//if (nChar == VK_ESCAPE) {
	//	// �E�B���h�E�����
	//	OnClose();
	//}
}

//����������������������������������������������������������������������������������������
//	Name        : �n���h��
//	Description : WM_ERASEBKGND �n���h��
//	Arguments   : hdc / �f�o�C�X�R���e�L�X�g
//	Returns     : None.
//����������������������������������������������������������������������������������������
bool CGameWindow::OnEraseBkgnd(HDC hdc)
{
	// �w�i�������Ȃ��ŏ����ς݂Ƃ��ĕԂ�
	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : �n���h��
//	Description : WM_SETCURSOR �n���h��
//	Arguments   : hwnd      / �E�B���h�E�n���h��
//				  nHitTest  / �q�b�g�e�X�g�R�[�h
//				  uMouseMsg / �}�E�X���b�Z�[�WID
//	Returns     : ����(true:����)
//����������������������������������������������������������������������������������������
bool CGameWindow::OnSetCursor(HWND hwnd, UINT nHitTest, UINT uMouseMsg)
{
	// �S��ʃ��[�h���A�}�E�X�J�[�\�����W���N���C�A���g�̈���Ȃ�
	if (!m_bWindow || nHitTest == HTCLIENT) {
		// �}�E�X�J�[�\������
//		::SetCursor(NULL);
		return true;
	}
	return false;
}


//========================================================================================
//	End of File
//========================================================================================