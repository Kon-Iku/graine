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
	m_maxFieldBlock = 0;
	m_maxLayoutBlock = 0;

	m_maxClearBlock = 0;
	m_vStart = D3DXVECTOR2(0, 0);
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
//	Arguments   : stageID / �X�e�[�W��ID
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CStage::Init(int stageID)
{
	SetStage(stageID);
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
	for (LPFIELDBLOCK_ARRAY_IT it = m_pFieldBlock.begin(); it != m_pFieldBlock.end(); ++it)
		(*it)->Uninit();
	for (LPCHARACTER_ARRAY_IT it = m_pLayoutBlock.begin(); it != m_pLayoutBlock.end(); ++it)
		(*it)->Uninit();

	m_pFieldBlock.clear();		// �I�u�W�F�N�g���X�g
	m_pLayoutBlock.clear();		// �I�u�W�F�N�g���X�g
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �����ȍX�V
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CStage::Update()
{
	for (LPFIELDBLOCK_ARRAY_IT it = m_pFieldBlock.begin(); it != m_pFieldBlock.end(); ++it)
		(*it)->Update();
	for (LPCHARACTER_ARRAY_IT it = m_pLayoutBlock.begin(); it != m_pLayoutBlock.end(); ++it)
		(*it)->Update();

}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �����ȍX�V
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CStage::DrawFieldBlock()
{
#ifdef _DEBUG
	static bool drawFlg = false;
	if (GetAsyncKeyState('C') & 1)
		drawFlg = !drawFlg;
	if (drawFlg) {
		for (LPFIELDBLOCK_ARRAY_IT it = m_pFieldBlock.begin(); it != m_pFieldBlock.end(); ++it)
			(*it)->DrawAlpha();
	}
#endif
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �����ȍX�V
//	Arguments   : num / �u���b�N�ԍ�
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CStage::DrawLayoutBlock(int num)
{
	if (num < 0) {
		for (LPCHARACTER_ARRAY_IT it = m_pLayoutBlock.begin(); it != m_pLayoutBlock.end(); ++it)
			(*it)->DrawAlpha();
	} else {
		if (m_pLayoutBlock[num] != NULL) {
			m_pLayoutBlock[num]->DrawAlpha();
		}
	}
}

//����������������������������������������������������������������������������������������
//	Name        : Stage�쐬
//	Description : Stage�쐬
//	Arguments   : stageID / �X�e�[�W��ID
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CStage::SetStage(int stageID)
{
	CMapData::LoadData(stageID);	// �}�b�v�f�[�^�ǂݍ���
	CMapData::GetFieldBlockList(&m_pFieldBlock);
	CMapData::GetLayoutBlockList(&m_pLayoutBlock);

	m_vStart = CMapData::GetStartPoint();

	m_maxFieldBlock = m_pFieldBlock.size();
	m_maxLayoutBlock = m_pLayoutBlock.size();


#ifdef _DEBUG
	for (LPFIELDBLOCK_ARRAY_IT it = m_pFieldBlock.begin(); it != m_pFieldBlock.end(); ++it) {
		for (int i = 0; i < (*it)->GetElementNum(); ++i) {
			(*it)->GetElement(i)->TranslationZ(-10.0f);
		}
	}
#endif
}

//========================================================================================
//	End of File
//========================================================================================