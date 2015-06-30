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
#include "../Object/FieldObject.h"


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CStage
{
private:
	LPCTSTR			m_lpColTex;					// �����蔻��p�u���b�N�̃e�N�X�`��

	int					m_nMaxColBox;			// �����蔻��p�u���b�N�ő吔
	LPFIELDOBJECT_ARRAY	m_vecColBox;			// �t�B�[���h�I�u�W�F�N�g���X�g

	int					m_nMaxLayoutBox;		// ���C�A�E�g�p�u���b�N�ő吔
	LPCHARACTER_ARRAY	m_vecLayoutBox;			// ���C�A�E�g�I�u�W�F�N�g���X�g

	int				m_nMaxClearBox;				// �����蔻��p�u���b�N�ő吔
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
	int GetColBoxMax(){ return m_nMaxColBox; }
	int GetLayoutBoxMax(){ return m_nMaxLayoutBox; }
	CFieldObject* GetColBox(int no);
	CCharacter* GetLayoutBox(int no);
	D3DXVECTOR3 GetStart(){ return D3DXVECTOR3(m_vStart.x, m_vStart.y, 0.0f); }

	// ----- �f�o�b�O�p
	void SetStage(int stageID);

	static CStage* Create();	// ����
	void Release();
};
//========================================================================================
//	End of File
//========================================================================================