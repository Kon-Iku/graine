//========================================================================================
//		File        : Block.h
//		Program     : �u���b�N�x�[�X
//
//		Description : �u���b�N�x�[�X�̒�`
//
//		History     : 2015/06/30	�쐬�J�n
//						   
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
class CBlock : public CCharacter
{
// ===== �����o�萔
protected:
	static const int INITIALIZE_ELEMENT_NUM;		// �����u���b�N�v�f��

// ===== �����o�ϐ�
protected:
	int					m_nType;		// �u���b�N�̃^�C�v
	LPCHARACTER_ARRAY	m_pElement;		// �u���b�N�̗v�f���X�g

	int		m_nFlower;
	
// ===== �����o�֐�
public:
	virtual void Init();		// ������
	virtual void Init(const D3DXVECTOR2& size, const D3DXVECTOR3& pos);	// �T�C�Y���w�肵�ď�����
	virtual void Uninit();		// ��n��
	virtual void Update();		// �X�V

	// ----- �Q�b�^�[
	int GetType(){return m_nType;}					// ��ގ擾
	int GetFloawerNum(){return m_nFlower;}

	// ----- �Z�b�^�[
	void SetType(int type){m_nType = type;}		// �v���C���[�̑���ݒ�
	void SetElement(CCharacter* pElem) { m_pElement.push_back(pElem); }		// �v�f�ݒ�

	void AddFlower(int no){m_nFlower += no;}
	void SubFlower(int no){m_nFlower -= no;}

	CBlock();
	virtual ~CBlock();
	static CBlock* Create(const LPCTSTR pszFName);	// ����
	
protected:
	bool Initialize(const LPCTSTR pszFName);	// ������
	void Finalize();		// ��n��
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ���[�U�^��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
typedef std::vector<CBlock*>	LPBLOCK_ARRAY;		// �u���b�N���X�g
typedef LPBLOCK_ARRAY::iterator	LPBLOCK_ARRAY_IT;	// �u���b�N���X�g�̃C�e���[�^


//========================================================================================
//	End of File
//========================================================================================