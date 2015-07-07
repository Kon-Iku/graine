//========================================================================================
//		File        : FieldBlock.h
//		Program     : �t�B�[���h�u���b�N�x�[�X
//
//		Description : �t�B�[���h�u���b�N�x�[�X�̒�`
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

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CFieldBlock : public CCharacter
{
// ===== �����o�萔
protected:
	static const int INITIALIZE_ELEMENT_NUM;		// �����u���b�N�v�f��

// ===== �����o�ϐ�
protected:
	bool				m_bCol;			// �����������ǂ���
	int					m_nType;		// �u���b�N�̃^�C�v
	LPCHARACTER_ARRAY	m_pElement;		// �u���b�N�̗v�f���X�g

	int		m_nFlower;

// ===== �����o�֐�
public:
	virtual void Init();		// ������
	virtual void Init(const D3DXVECTOR2& size, const D3DXVECTOR3& pos);	// �T�C�Y���w�肵�ď�����
	virtual void Uninit();		// ��n��
	virtual void Update();		// �X�V
	virtual void Draw();		// �`��(���߂Ȃ�)
	virtual void DrawAlpha();	// �`��(���߂���)

	// ----- �Q�b�^�[
	bool GetCol(){ return m_bCol; }
	int GetType(){ return m_nType; }					// ��ގ擾
	int GetFloawerNum(){ return m_nFlower; }
	int GetElementNum() const { return m_pElement.size(); }		// �p�f���擾
	CCharacter* GetElement(int num) const { return num >= 0 && num < (int)m_pElement.size() ? m_pElement[num] : m_pElement[0]; }		// �v�f�擾

	// ----- �Z�b�^�[
	void SetType(int type){ m_nType = type; }		// �v���C���[�̑���ݒ�
	void SetElement(CCharacter* pElem) { m_pElement.push_back(pElem); }		// �v�f�ݒ�

	void AddFlower(int no){ m_nFlower += no; }
	void SubFlower(int no){ m_nFlower -= no; }

	void EnableCol(){ m_bCol = true; }
	void DisableCol(){ m_bCol = false; }

	CFieldBlock();
	virtual ~CFieldBlock();
	static CFieldBlock* Create();	// ����

private:
	bool Initialize();		// ������
	void Finalize();		// ��n��
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ���[�U�^��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
typedef std::vector<CFieldBlock*>		LPFIELDBLOCK_ARRAY;		// �t�B�[���h�u���b�N���X�g
typedef LPFIELDBLOCK_ARRAY::iterator	LPFIELDBLOCK_ARRAY_IT;	// �t�B�[���h�u���b�N���X�g�̃C�e���[�^


//========================================================================================
//	End of File
//========================================================================================