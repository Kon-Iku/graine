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

	m_nMaxClearBox = 0;
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

	m_vecColBox.clear();		// �I�u�W�F�N�g���X�g
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
//	Name        : Stage�쐬
//	Description : Stage�쐬
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CStage::SetStage()
{
	m_nMaxColBox = MAX_COLLISION_BOX;

	// �I�u�W�F�N�g��
	//m_vecColBox.resize(m_nMaxColBox);

	// ----- �u���b�N�ݒ�
	CFieldObject* f_0;
	f_0 = CFieldObject::Create(m_lpColTex);
	f_0->Init(D3DXVECTOR2(800, 64), D3DXVECTOR3(480, -256, 0));
	f_0->SetAlpha(190);

	CFieldObject* f_1;
	f_1 = CFieldObject::Create(m_lpColTex);
	f_1->Init(D3DXVECTOR2(64, 256), D3DXVECTOR3(480, -96, 0));
	f_1->SetAlpha(190);

	CFieldObject* f_2;
	f_2 = CFieldObject::Create(m_lpColTex);
	f_2->Init(D3DXVECTOR2(256, 64), D3DXVECTOR3(-540, 0, 0));
	f_2->SetAlpha(190);

	CFieldObject* f_3;
	f_3 = CFieldObject::Create(m_lpColTex);
	f_3->Init(D3DXVECTOR2(800, 64), D3DXVECTOR3(-480, -256, 0));
//	f_3->RotateZ(10);
	f_3->SetAlpha(190);


	CFieldObject* f_C_0;
	f_C_0 = CFieldObject::Create(m_lpColTex);
	f_C_0->Init(D3DXVECTOR2(128, 128), D3DXVECTOR3(1024, 0, 0));
	f_C_0->SetColor(D3DXVECTOR3(255,255,128));
	f_C_0->RotateZ(45);
	f_C_0->SetAlpha(190);
	f_C_0->SetrType(BLOCK_TYPE_CLEAR);

	CFieldObject* f_Over_0;
	f_Over_0 = CFieldObject::Create(m_lpColTex);
	f_Over_0->Init(D3DXVECTOR2(1600, 64), D3DXVECTOR3(0, -1024, 0));
	f_Over_0->SetColor(D3DXVECTOR3(255,128,128));
	f_Over_0->SetrType(BLOCK_TYPE_OVER);


	// ::::: ���X�g�ɒǉ� ::::: //
	m_vecColBox.push_back(f_0);
	m_vecColBox.push_back(f_1);
	m_vecColBox.push_back(f_2);
	m_vecColBox.push_back(f_3);
	m_vecColBox.push_back(f_C_0);
	m_vecColBox.push_back(f_Over_0);

}
//========================================================================================
//	End of File
//========================================================================================