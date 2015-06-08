//========================================================================================
//		File        : FieldObject.h
//		Program     : �t�B�[���I�u�W�F�N�g�x�[�X
//
//		Description : �t�B�[���h�I�u�W�F�N�g�x�[�X�̒�`
//
//		History     : 2015/05/6	�쐬�J�n
//						   
//
//																Author : ���񂽂܃Y
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
#include "../Object/Character.h"


enum
{
	BLOCK_TYPE_0 = 0,
	BLOCK_TYPE_CLEAR,
	BLOCK_TYPE_OVER,
	BLOCK_TYPE_LAYOUT,

	MAX_BLOCK_TYPE
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CFieldObject : public CCharacter
{
// ===== using�錾
public:
	using CObject2D::Init;

// ===== �����o�ϐ�
protected:
	bool	m_bCol;
	int		m_nType;
	
// ===== �����o�֐�
public:
	virtual void Init();		// ������
	virtual void Uninit();		// ��n��
	virtual void Update();		// �X�V

	// ----- �Q�b�^�[
	bool GetCol(){return m_bCol;}
	int GetType(){return m_nType;}					// ��ގ擾

	// ----- �Z�b�^�[
	void SetType(int type){m_nType = type;}		// �v���C���[�̑���ݒ�

	void EnableCol(){m_bCol = true;}
	void DisableCol(){m_bCol = false;}

	CFieldObject();
	virtual ~CFieldObject();
	static CFieldObject* Create(const LPCTSTR pszFName);	// ����
	
private:
	bool Initialize(const LPCTSTR pszFName);	// ������
	void Finalize();		// ��n��
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ���[�U�^��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
typedef std::vector<CFieldObject*>		LPFIELDOBJECT_ARRAY;	// �t�B�[���h�I�u�W�F�N�g���X�g
typedef LPFIELDOBJECT_ARRAY::iterator	LPFIELDOBJECT_ARRAY_IT;	// �t�B�[���h�I�u�W�F�N�g���X�g�̃C�e���[�^


//========================================================================================
//	End of File
//========================================================================================