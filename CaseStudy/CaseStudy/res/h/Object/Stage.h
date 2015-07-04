//========================================================================================
//		File        : Stage
//		Program     : 
//
//		Description : �X�e�[�W��̃I�u�W�F�N�g�Ǘ��iPlayer�ȊO�j
//						
//						
//
//		History     : 2015/05/18	�쐬�J�n
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
#include "../System/Input.h"
#include "../System/System.h"
#include "../System/MapData.h"
#include "../Object/Character.h"
#include "../Object/FieldBlock.h"


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CStage
{
private:
	LPCTSTR			m_lpColTex;					// �����蔻��p�u���b�N�̃e�N�X�`��

	int					m_maxFieldBlock;		// �t�B�[���h�u���b�N�ő吔
	LPFIELDBLOCK_ARRAY	m_pFieldBlock;			// �t�B�[���h�u���b�N���X�g

	int					m_maxLayoutBlock;		// ���C�A�E�g�u���b�N�ő吔
	LPCHARACTER_ARRAY	m_pLayoutBlock;			// ���C�A�E�g�u���b�N���X�g

	int				m_maxClearBlock;			// �N���A����u���b�N�ő吔
	D3DXVECTOR2		m_vStart;

public:
	CStage();
	void Init(int stageID);
	void Uninit();
	void Update();
	void Draw();

	// ----- �Z�b�^�[
	void SetColBoxTexture(const LPCTSTR tex){ m_lpColTex = tex; }


	// ----- �Q�b�^�[
	int GetMaxFieldBlock(){ return m_maxFieldBlock; }
	int GetMaxLayoutBlock(){ return m_maxFieldBlock; }
	CFieldBlock* GetFieldBlock(int num) const { return num >= 0 && num < (int)m_pFieldBlock.size() ? m_pFieldBlock[num] : m_pFieldBlock[0]; };
	CCharacter* GetLayoutBlock(int num) const { return num >= 0 && num < (int)m_pLayoutBlock.size() ? m_pLayoutBlock[num] : m_pLayoutBlock[0]; };
	D3DXVECTOR3 GetStart(){ return D3DXVECTOR3(m_vStart.x, m_vStart.y, 0.0f); }

	// ----- �f�o�b�O�p
	void SetStage(int stageID);

	static CStage* Create();	// ����
	void Release();
};
//========================================================================================
//	End of File
//========================================================================================