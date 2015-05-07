//========================================================================================
//		File        : Timer.h
//		Program     : �^�C�}�[�����N���X
//
//		Description : �^�C�}�[�����N���X�̒�`
//
//		History     : 2014/08/03	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================

#pragma once

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../System/PreInclude.h"
#
#include <windows.h>

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CTimer
{
// ===== �����o�萔
protected:
	static const int DEFAULT_FPS = 60;		// �f�t�H���gFPS

// ===== �����o�ϐ�
protected:
	static bool		m_bPerform;		// ���𑜓x�^�C�}�[���T�|�[�g����Ă��邩
	static LONGLONG	m_sysFreq;		// �V�X�e�����g��
	static LONGLONG	m_startQuad;	// �J�n���g��
	static int		m_fps;			// �t���[�����[�g
	static int		m_count;		// �o�߃t���[����
	static double	m_time;			// �o�ߎ���(�b)
	static double	m_startTime;	// �J�n����(�b)
	static double	m_frameTime;	// �o�߃t���[���̌o�ߎ���(�b)
	
// ===== �����o�֐�
public:
	static CTimer& GetInstance();	// �C���X�^���X�擾

	bool	Start(int fps = DEFAULT_FPS);	// ���荞�݃X�^�[�g
	int		Run();							// �t���[�����Ăяo��

	// ----- �Q�b�^�[
	static double	GetFps() {return (double)m_count / m_time;}	// �t���[�����擾
	static double	GetTime() {return m_time;}					// �Q�[���J�n������̌o�ߎ��Ԃ��擾(�b)
	static double	GetStartTime() {return m_startTime;}		// �J�n���Ԃ��擾(�b)
	static double	GetFrameTime() {return m_frameTime;}		// �o�߃t���[���̌o�ߎ��Ԏ擾(�b)
	
private:
	CTimer();
	CTimer(const CTimer&) {}
	CTimer &operator=(const CTimer&) {}
	virtual ~CTimer();
};


//========================================================================================
//	End of File
//========================================================================================