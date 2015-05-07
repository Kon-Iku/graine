//========================================================================================
//		File        : Score.h
//		Program     : �X�R�A�N���X
//
//		Description : �X�R�A�N���X�̒�`
//
//		History     : 2014/11/27	�쐬�J�n
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
#include "../System/System.h"
#include "../Object/Number.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CScore
{
// ===== �����o�萔
public:
	static const LONG			MAX_SCORE;			// �X�R�A�̍ő�l
	static const int			SCORE_DIGIT;		// �ő�X�R�A�̌���

private:
	static const LPCTSTR		TEX_FILENAME;		// �e�N�X�`���̃t�@�C����
	static const D3DXVECTOR2	OBJ_SIZE;			// �I�u�W�F�N�g�T�C�Y
	static const int			WIDTH_FRAME;		// �A�j���[�V�����t���[���̉�������
	static const int			HEIGHT_FRAME;		// �A�j���[�V�����t���[���̏c������

// ===== �����o�ϐ�
private:
	LPNUMBER_ARRAY	m_pNumberList;		// �����I�u�W�F�N�g
	LONG			m_score;			// �`��X�R�A

// ===== �����o�֐�
public:
	CScore();				// �R���X�g���N�^
	virtual ~CScore();		// �f�X�g���N�^
	
	void Init(const D3DXVECTOR3& pos);	// ������
	void Uninit();		// ��n��
	void Update();		// �X�V
	void Draw();		// �`��(�A���t�@����)
	void DrawAlpha();	// �`��(�A���t�@�L��)

	static CScore* Create();	// ����
	void Release();				// �j��

	void Translate(const D3DXVECTOR3& pos);	// �ړ�����
	void SetScore(LONG score);				// �`��X�R�A���X�V

private:
	bool Initialize();	// ������
	void Finalize();	// ��n��
};


//========================================================================================
//	End of File
//========================================================================================