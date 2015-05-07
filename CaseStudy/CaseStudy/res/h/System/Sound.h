//========================================================================================
//		File        : Sound.h
//		Program     : �T�E���h�N���X
//
//		Description : �T�E���h�N���X�̒�`
//
//		History     : 2013/07/04	�쐬�J�n
//					  2014/05/23	�t�@�C�����ύX
//						   08/07	�V���O���g���N���X��
//
//																Author : Kei Hashimoto
//========================================================================================

#pragma once
#define DIRECTSOUND_VERSION	(0x0800)

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../System/PreInclude.h"
#
#include <dsound.h>

// ----- ���C�u�����̃����N
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CSound
{
// ===== �����o�萔
public:
	static const int MAX_DUP = 16;	// �ő哯��������

// ===== �����o�ϐ�
private:
	static LPDIRECTSOUND8	m_pDirectSound;		// DirectSound�I�u�W�F�N�g

// ===== �����o�֐�
public:
	static CSound& GetInstance();							// �C���X�^���X�擾
	HRESULT InitSound(HWND hWnd);							// �T�E���h�֘A������
	void Release(void);										// �T�E���h�֘A��n��
	static LPDIRECTSOUNDBUFFER8 LoadSound(LPTSTR file);		// �T�E���h�̃��[�h
	HRESULT CopyBuffer(LPDIRECTSOUNDBUFFER8 pBuffer[][MAX_DUP], int elem);	// �Z�J���_���o�b�t�@�̃R�s�[

private:
	CSound();
	CSound(const CSound&) {}
	CSound &operator=(const CSound&) {}
	virtual ~CSound();
};


//========================================================================================
//	End of File
//========================================================================================