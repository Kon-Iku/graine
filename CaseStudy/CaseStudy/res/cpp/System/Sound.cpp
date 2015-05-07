//========================================================================================
//		File        : Sound.cpp
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


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/PreInclude.h"
#
#include "../../h/System/Sound.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �}�N����`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)			if(x){ x->Release(); x=NULL; }
#endif

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �����o���̐錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
LPDIRECTSOUND8	CSound::m_pDirectSound;

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �O���[�o���ϐ��錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
static CSound& g_sound = CSound::GetInstance();		// �T�E���h�N���X�̎��̐���


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �C���X�^���X�擾
//	Description : �T�E���h�N���X�̃C���X�^���X���擾����
//	Arguments   : None.
//	Returns     : �T�E���h�N���X
//����������������������������������������������������������������������������������������
CSound& CSound::GetInstance()
{
	// ----- �C���X�^���X����
	static CSound sound;

	return sound;
}

//����������������������������������������������������������������������������������������
//	Name        : �T�E���h�����̏�����
//	Description : �T�E���h����������������
//	Arguments   : hWnd / �E�B���h�E�n���h��
//	Returns     : ����
//����������������������������������������������������������������������������������������
HRESULT CSound::InitSound(HWND hWnd)
{
	// ----- DirectSound�I�u�W�F�N�g�̍쐬
	if(FAILED(DirectSoundCreate8(NULL, &m_pDirectSound, NULL)))
		return E_FAIL;

	// ----- �������x���ݒ�
	if(FAILED(m_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
		return E_FAIL;

	return S_OK;
}

//����������������������������������������������������������������������������������������
//	Name        : �T�E���h�̉��
//	Description : �T�E���h���������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CSound::Release(void)
{
	SAFE_RELEASE(m_pDirectSound);
}

//����������������������������������������������������������������������������������������
//	Name        : �T�E���h�̃��[�h
//	Description : �T�E���h�����[�h����
//	Arguments   : file / �T�E���h�f�[�^�̃t�@�C����
//	Returns     : �Z�J���_���o�b�t�@
//����������������������������������������������������������������������������������������
LPDIRECTSOUNDBUFFER8 CSound::LoadSound(LPTSTR file)
{
	// ----- MMIO(�}���`���f�B�A���o��)
	LPDIRECTSOUNDBUFFER		pBaseBuffer = NULL;		// �ȃf�[�^�̑����o�b�t�@
	LPDIRECTSOUNDBUFFER8	pBuffer = NULL;			// �ȃf�[�^�̃o�b�t�@
	DSBUFFERDESC buff;								// �o�b�t�@�ݒ�\����

	HMMIO hMmio = NULL;								// MMIO�n���h��
	MMIOINFO mmioInfo;								// �}���`���f�B�A�f�[�^�\����

	MMRESULT mmRes;									// MM�������ʊi�[�ϐ�
	MMCKINFO riffChunk, formatChunk, dataChunk;		// �`�����N�f�[�^�\����
	DWORD size;										// �f�[�^�T�C�Y�i�[�p
	WAVEFORMATEX pcm;								// �ȃf�[�^�t�H�[�}�b�g�\����

	LPVOID	pBlock;		// �Z�J���_���o�b�t�@�̃f�[�^�������ݐ�A�h���X
	DWORD	dwSize;		// �Z�J���_���o�b�t�@�̃T�C�Y

	// ----- �P�D�n���h�������ƂɃt�@�C�����J��
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen(file, &mmioInfo, MMIO_READ);
	if(!hMmio)
		return NULL;

	// ----- �Q�D�t�@�C����͇@ RIFF�`�����N����
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');					// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);		// �L�[���[�h�����ƂɌ���

	if(mmRes != MMSYSERR_NOERROR)		// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// ----- �R�D�t�@�C����͇A �t�H�[�}�b�g�`�����N����
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');							// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);		// �L�[���[�h�����ƂɌ���

	if(mmRes != MMSYSERR_NOERROR)		// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	size = mmioRead(hMmio, (HPSTR)&pcm, formatChunk.cksize);		// �����������Ƃɓǂݍ���

	if(size != formatChunk.cksize)		// �������ǂݍ��߂Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	mmioAscend(hMmio, &formatChunk, 0);

	// ----- �S�D�t�@�C����͇B �f�[�^�`�����N����
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');						// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);		// �L�[���[�h�����ƂɌ���

	if(mmRes != MMSYSERR_NOERROR)		// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// ----- �T�D�f�[�^�Ǎ�
	char *pData = new char[dataChunk.cksize];					// �K�v�ȑ傫���̗̈���m��
	size = mmioRead(hMmio, (HPSTR)pData, dataChunk.cksize);		// �f�[�^��ǂݍ���

	if(size != dataChunk.cksize)		// �������ǂݍ��߂Ȃ�������ُ�I��
	{
		delete[] pData;
		return NULL;
	}

	// ----- �U�D�Ȃ�ǂݍ��ށu�Z�J���_���o�b�t�@�v��p��
	ZeroMemory(&buff, sizeof(DSBUFFERDESC));		// ������
	buff.dwSize = sizeof(DSBUFFERDESC);				// �e��ݒ�
	buff.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER;
	buff.dwBufferBytes = size;
	buff.lpwfxFormat = &pcm;

	// ----- �����o�b�t�@�쐬
	if(FAILED(m_pDirectSound->CreateSoundBuffer(&buff, &pBaseBuffer, NULL)))
		return NULL;

	// ----- �T�E���h�o�b�t�@�����o��
	if(FAILED(pBaseBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID *)&pBuffer)))
		return NULL;

	// ----- �����o�b�t�@�j��
	pBaseBuffer->Release();

	// ----- �V�D�Z�J���_���o�b�t�@�Ƀf�[�^��]��
	// ----- �o�b�t�@�����b�N
	if(FAILED(pBuffer->Lock(0, 0, &pBlock, &dwSize, NULL, NULL, DSBLOCK_ENTIREBUFFER)))
		return NULL;

	memcpy(pBlock, pData, dwSize);		// �f�[�^�]��
	delete[] pData;						// ���̓ǂݍ��ݗ̈�j��

	// ----- �o�b�t�@���b�N����
	pBuffer->Unlock(pBlock, dwSize, 0, 0);

	// ----- �Z�J���_���o�b�t�@��Ԃ�
	return pBuffer;
}

//����������������������������������������������������������������������������������������
//	Name        : �Z�J���_���o�b�t�@�̃R�s�[
//	Description : �Z�J���_���o�b�t�@��MAX_DUP���R�s�[����
//	Arguments   : pBuffer / �Z�J���_���o�b�t�@���X�g
//				  elem    / �z��̗v�f��(���ڂ̐�)
//	Returns     : ��������
//����������������������������������������������������������������������������������������
HRESULT CSound::CopyBuffer(LPDIRECTSOUNDBUFFER8 pBuffer[][MAX_DUP], int elem)
{
	// ----- �ϐ��錾
	HRESULT hr;		// ��������

	// ----- �R�s�[����
	for(int i = 0; i < elem; ++i)
	{
		for(int j = 1; j < MAX_DUP; ++j)
		{
			hr = m_pDirectSound->DuplicateSoundBuffer(pBuffer[i][0], (LPDIRECTSOUNDBUFFER*)&pBuffer[i][j]);
			if(FAILED(hr))
				return hr;
		}
	}

	return hr;
}


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CSound::CSound()
{
	m_pDirectSound = NULL;
}

//����������������������������������������������������������������������������������������
//	Name        : �f�X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CSound::~CSound()
{
}


//========================================================================================
//	End of File
//========================================================================================