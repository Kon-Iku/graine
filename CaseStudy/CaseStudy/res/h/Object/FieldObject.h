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

	MAX_BLOCK_TYPE
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CFieldObject : public CCharacter
{
private:
	bool	m_bCol;
	int		m_nType;
	int		m_nFlower;
public:
	// ----- �Q�b�^�[
	bool GetCol(){return m_bCol;}
	int GetType(){return m_nType;}					// ��ގ擾
	int GetFloawerNum(){return m_nFlower;}

	// ----- �Z�b�^�[
	void SetrType(int type){m_nType = type;}	// �v���C���[�̑���ݒ�

	void AddFlower(int no){m_nFlower += no;}
	void SubFlower(int no){m_nFlower -= no;}

	void EnableCol(){m_bCol = true;}
	void DisableCol(){m_bCol = false;}

	CFieldObject();
	static CFieldObject* Create(const LPCTSTR pszFName);	// ����
	virtual void Release();								// �j��
};
//========================================================================================
//	End of File
//========================================================================================