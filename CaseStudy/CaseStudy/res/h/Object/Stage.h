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
#include "../Object/FieldObject.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\

// �f�o�b�O�p�萔
const int MAX_COLLISION_BOX = 5;		// �u���b�N�̐�

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CStage
{
private:
	LPCTSTR			m_lpColTex;					// �����蔻��p�u���b�N�̃e�N�X�`��

	int				m_nMaxColBox;				// �����蔻��p�u���b�N�ő吔
	std::vector<CFieldObject*>	m_vecColBox;	// �t�B�[���h�I�u�W�F�N�g���X�g

	int				m_nMaxClearBox;				// �����蔻��p�u���b�N�ő吔


public:	
	CStage();
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// ----- �Z�b�^�[
	void SetColBoxTexture(const LPCTSTR tex){m_lpColTex = tex;}


	// ----- �Q�b�^�[
	int GetColBoxMax(){return m_nMaxColBox;}
	CFieldObject* GetColBox(int no);
	
	// ----- �f�o�b�O�p
	void SetStage();
	
	static CStage* Create();	// ����
	void Release();
};
//========================================================================================
//	End of File
//========================================================================================