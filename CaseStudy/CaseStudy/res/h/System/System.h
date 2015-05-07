//========================================================================================
//		File        : System.h
//		Program     : �Q�[�����ʃf�[�^/�V�X�e��
//
//		Description : �Q�[���̋��ʃf�[�^�y�уV�X�e���̒�`
//
//		History     : 2013/12/05	�쐬�J�n
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
#include <vector>

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ���[�U�^��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
typedef std::vector<ULONG>		ULONG_ARRAY;		// ULONG�^�z��
typedef ULONG_ARRAY::iterator	ULONG_ARRAY_IT;		// ULONG�^�z��C�e���[�^
typedef std::vector<LPTSTR>		LPTSTR_ARRAY;		// LPTSTR�^�z��
typedef LPTSTR_ARRAY::iterator	LPTSTR_ARRAY_IT;	// LPTSTR�^�z��C�e���[�^
typedef std::vector<LPCTSTR>	LPCTSTR_ARRAY;		// LPCTSTR�^�z��
typedef LPCTSTR_ARRAY::iterator	LPCTSTR_ARRAY_IT;	// LPCTSTR�^�z��C�e���[�^

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ----- �Q�[���E�B���h�E�֘A
const int	SCREEN_WIDTH		= 1136;								// �X�N���[���̕�	// �t���X�N���[���ɂ���Ȃ�F1024
const int	SCREEN_HEIGHT		= 640;								// �X�N���[���̍���	//							 768
const int	SCREEN_LEFT			= (int)(-SCREEN_WIDTH * 0.5f);		// �X�N���[���̍��[
const int	SCREEN_RIGHT		= (int)(SCREEN_WIDTH * 0.5f);		// �X�N���[���̉E�[
const int	SCREEN_TOP			= (int)(SCREEN_HEIGHT * 0.5f);		// �X�N���[���̏�[
const int	SCREEN_BOTTOM		= (int)(-SCREEN_HEIGHT * 0.5f);		// �X�N���[���̉��[
const float	FRAME_RATE			= 1000.0f / 60.0f;					// �t���[�����[�g
const float	FPS					= 60.0f;							// FPS

// ----- �����t���O
static enum _eDirect
{
	DIR_LEFT = 0,	// ������
	DIR_RIGHT,		// �E����
	DIR_UP,			// �����
	DIR_DOWN,		// ������
	DIR_FRONT,		// �O����
	DIR_BACK,		// �����
	DIR_NONE,		// �Ȃ�

	MAX_DIRECT
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �}�N����`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ----- �e�N�X�`���A�j���[�V�����p
#define TEX_ANIME_LEFT(num, width)				((1.0f / width) * ((num) % width))
#define TEX_ANIME_RIGHT(num, width)				((1.0f / width) * ((num) % width) + (1.0f / width))				
#define TEX_ANIME_TOP(num, width, height)		((1.0f / height) * ((num) / width))				
#define TEX_ANIME_BOTTOM(num, width, height)	((1.0f / height) * ((num) / width) + (1.0f / height))

// ----- ����p
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)			if(x){ x->Release(); x=NULL; }
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)			if(x){ delete x; x=NULL; }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if(x){ delete[] x; x=NULL; }
#endif

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ���O��Ԓ�`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
namespace System
{
	D3DXVECTOR3 CalcScreenLeft3D(const D3DXVECTOR3* pCamera, const D3DXVECTOR3* pTarget);

	void SearchFileName(LPTSTR_ARRAY *pflist, LPCTSTR path);		// �t�@�C������
}


//========================================================================================
//	End of File
//========================================================================================