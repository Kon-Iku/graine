//========================================================================================
//		File        : ChangeScene.h
//		Program     : �V�[���J�ڃV�X�e��
//
//		Description : �V�[���J�ڃV�X�e���̒�`
//
//		History     : 2015/02/20	�쐬�J�n
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
#include "../Object/Object2D.h"

////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//// �萔��`
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//// ----- �t�F�[�h�֘A
//const LPCTSTR SELECT_FADE_FILENAME = _T("res/img/RainbowArrow.png");	// �Z���N�g��ʂ���̉�ʑJ�ڗp�e�N�X�`���t�@�C����
//
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//// �\���̒�`
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//typedef struct _tSelectFade		// �Z���N�g��ʂ���̉�ʑJ�ڗp�e�N�X�`�����X�g
//{
//	CTexture*	pRed;		// ��
//	CTexture*	pOrange;	// ��
//	CTexture*	pYellow;	// ��
//	CTexture*	pYelGreen;	// ����
//	CTexture*	pGreen;		// ��
//	CTexture*	pSyan;		// ���F
//	CTexture*	pBlue;		// ��
//	CTexture*	pPurple;	// ��
//} SELECTFADE;

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CChangeScene
{
// ===== �����o�萔
private:
	static const LPCTSTR TEX_FILENAME[];	// �e�N�X�`���̃t�@�C����
	
	// ----- �e�N�X�`�����X�g
	static enum _eTexList
	{
		TL_NORMALFADE = 0,		// �P�F�t�F�[�h�p�e�N�X�`��

		MAX_TEXLIST
	};

// ===== �����o�ϐ�
private:
	static CObject2D*	m_pNormalFade;		// �P�F�t�F�[�h�p�e�N�X�`��

// ===== �����o�֐�
public:
	// ----- �Q�b�^�[
	static CChangeScene& GetInstance();		// �C���X�^���X�擾

	// ----- �Z�b�^�[
	static void SetNormalFadePos(const D3DXVECTOR3& pos);		// �P�F�t�F�[�h�p�I�u�W�F�N�g�̈ʒu�ݒ�
	static void SetNormalFadeColor(const D3DXVECTOR3& color);	// �P�F�t�F�[�h�p�I�u�W�F�N�g�̒��_�J���[�ݒ�(0�`255)
	static void SetNormalFadeAlpha(int alpha);					// �P�F�t�F�[�h�p�I�u�W�F�N�g�̓��ߓx�ݒ�(0�`255)

	// ----- ���o�֘A
	static bool NormalFadeIn(float z, int alpha);	// �P�F�œ��߂���t�F�[�h�C��
	static bool NormalFadeOut(float z, int alpha);	// �P�F�œ��߂���t�F�[�h�A�E�g

	// ----- �`��
	static void DrawNormalFade();		// �P�F�t�F�[�h�p�I�u�W�F�N�g��`��

private:
	CChangeScene();
	CChangeScene(const CChangeScene&) {}
	CChangeScene &operator=(const CChangeScene&) {}
	virtual ~CChangeScene();

	static int CreateNormalFade();	// �P�F�t�F�[�h�p�e�N�X�`������(�߂�l[0:���s, 1:����, 2:�����ς�])
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ���O��Ԓ�`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
namespace ChangeScene
{
	bool SideSliderIn(CObject2D* pTex, float x);		// ���E�Ɋ���悤�ȑJ��(��ʂɏo��)
	bool SideSliderOut(CObject2D* pTex, float x);	// ���E�Ɋ���悤�ȑJ��(��ʂ���ޔ�)
}


//========================================================================================
//	End of File
//========================================================================================