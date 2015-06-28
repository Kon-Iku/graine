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
#include "../../h/Object/Stage.h"

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CStage::CStage()
{
	m_nMaxColBox = 0;
	m_nMaxLayoutBox = 0;

	m_nMaxClearBox = 0;
	m_vStart = D3DXVECTOR2(0,0);
}
//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : �I�u�W�F�N�g�𐶐�����
//	Arguments   : pszFName / �ǂݍ��݃t�@�C����
//	Returns     : �I�u�W�F�N�g�f�[�^
//����������������������������������������������������������������������������������������
CStage* CStage::Create()
{
	// ----- �ϐ��錾
	CStage* pObj;

	// ----- ����������
	pObj = new CStage();


	return pObj;
}
//����������������������������������������������������������������������������������������
//	Name        : ���
//	Description : �I�u�W�F�N�g���������
//	Arguments   : 
//	Returns     : 
//����������������������������������������������������������������������������������������
void CStage::Release()
{
	delete this;
}
//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �����ȏ�����
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CStage::Init()
{
	SetStage();
}
//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �����Ȍ�n��
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CStage::Uninit()
{
	// ���X�g���S����n��
	for (unsigned int i = 0;i < m_vecColBox.size(); ++i)
		m_vecColBox[i]->Uninit();
	for (LPCHARACTER_ARRAY_IT it = m_vecLayoutBox.begin(); it != m_vecLayoutBox.end(); ++it)
		(*it)->Uninit();

	m_vecColBox.clear();		// �I�u�W�F�N�g���X�g
	m_vecLayoutBox.clear();		// �I�u�W�F�N�g���X�g
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �����ȍX�V
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CStage::Update()
{
	for (unsigned int i = 0;i < m_vecColBox.size(); ++i)
		m_vecColBox[i]->Update();
	for (LPCHARACTER_ARRAY_IT it = m_vecLayoutBox.begin(); it != m_vecLayoutBox.end(); ++it)
		(*it)->Update();

}
//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �����ȍX�V
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CStage::Draw()
{
	for (unsigned int i = 0;i < m_vecColBox.size(); ++i){
		m_vecColBox[i]->DrawAlpha();
	}
	for (LPCHARACTER_ARRAY_IT it = m_vecLayoutBox.begin(); it != m_vecLayoutBox.end(); ++it)
		(*it)->DrawAlpha();
}
//����������������������������������������������������������������������������������������
//	Name        : ColBox���擾
//	Description : ColBox���擾
//	Arguments   : ColBox�̔ԍ�
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
CFieldObject* CStage::GetColBox(int no)
{
	return m_vecColBox[no];

}
//����������������������������������������������������������������������������������������
//	Name        : LayoutBox���擾
//	Description : LayoutBox���擾
//	Arguments   : LayoutBox�̔ԍ�
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
CCharacter* CStage::GetLayoutBox(int no)
{
	return m_vecLayoutBox[no];
}
//����������������������������������������������������������������������������������������
//	Name        : Stage�쐬
//	Description : Stage�쐬
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CStage::SetStage()
{
	CMapData::LoadData(CMapData::ID_STAGE1);	// �}�b�v�f�[�^�ǂݍ���
	CMapData::GetFieldObjList(&m_vecColBox);
	CMapData::GetLayoutObjList(&m_vecLayoutBox);

	m_vStart = CMapData::GetStartPoint();

	m_nMaxColBox = m_vecColBox.size();
	m_nMaxLayoutBox = m_vecLayoutBox.size();


	// ----- �X�e�[�W�T�C�Y����(�e�X�g�p)
	m_vecLayoutBox[0]->ScaleX(1.3f);
	m_vecLayoutBox[0]->ScaleY(1.3f);
	m_vecLayoutBox[0]->TranslateZ(-10.0f);
}

//========================================================================================
//	End of File
//========================================================================================