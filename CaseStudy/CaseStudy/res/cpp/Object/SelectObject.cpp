//========================================================================================
//		File        : SelectObject.cpp
//		Program     : �V�[���J�ڃV�X�e��
//
//		Description : �V�[���J�ڃV�X�e���̎���
//
//		History     : 2015/02/20	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/PreInclude.h"
#
#include <tchar.h>
#include "../../h/System/System.h"
#include "../../h/Object/SelectObject.h"
#include "../../h/System/Input.h"


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CSelectObject::CSelectObject()
{

}
//����������������������������������������������������������������������������������������
//	Name        : �f�X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CSelectObject::~CSelectObject()
{

}

//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : �I�u�W�F�N�g�𐶐�����
//	Arguments   : pszFName / �ǂݍ��݃t�@�C����
//	Returns     : �I�u�W�F�N�g�f�[�^
//����������������������������������������������������������������������������������������
CSelectObject* CSelectObject::Create(const LPCTSTR pszFName)
{
	// ----- �ϐ��錾
	CSelectObject* pObj;

	// ----- ����������
	pObj = new CSelectObject();
	if (pObj)
	{
		if (!pObj->Initialize(pszFName))
		{
			SAFE_DELETE(pObj);
		}
	}

	return pObj;
}

//����������������������������������������������������������������������������������������
//	Name        : �V�[���J�� ��2 (��ʂ���o��)
//	Description : �ォ��o��
//	Arguments   : pTex / �e�N�X�`��
//				  y    / Y�����ړ���
//	Returns     : �����t���O(true:�J�ڊ���)
//����������������������������������������������������������������������������������������
int CSelectObject::PlayerUpdate(int nStatus)
{
	if (m_scale.x > 0)
		ScaleX(-1.0f);

	switch (nStatus)
	{
	case S_STATUS_WAIT:

		break;
	case S_STATUS_LEFT:
		break;
	case S_STATUS_RIGHT:
		break;
	}

	CCharacter::Update();

	return nStatus;
}
//����������������������������������������������������������������������������������������
//	Name        : �V�[���J�� ��2 (��ʂ���o��)
//	Description : �ォ��o��
//	Arguments   : pTex / �e�N�X�`��
//				  y    / Y�����ړ���
//	Returns     : �����t���O(true:�J�ڊ���)
//����������������������������������������������������������������������������������������
int CSelectObject::ArrowUpdate(int nNo,int nStatus)
{
#define ARROW_LEFT	1
#define ARROW_RIGHT 2

	if (nNo == ARROW_RIGHT)
		if (GetScaleX() > 0.0f)
			ScaleX(-1.0f);
	
	switch (nStatus)
	{
		case S_STATUS_WAIT:
			if (nNo == ARROW_LEFT)
			{
				if (m_pos.x < LEFT_ARROW_INIT_POS_X)
					TranslationX(1.0f);
			}
			else
			{
				if (m_pos.x > RIGHT_ARROW_INIT_POS_X)
					TranslationX(-1.0f);
			}
			break;
		case S_STATUS_LEFT:
			if (nNo == ARROW_LEFT)
			{
				for (int i = 0; i <= MOVE_COUNT; i++)
				{
					if (m_pos.x > LEFT_ARROW_INIT_POS_X - MOVE_COUNT)
						TranslationX(-1.0f);

					if (i >= MOVE_COUNT)
						return S_STATUS_WAIT;
				}
			}
			else
			{
				if (m_pos.x > RIGHT_ARROW_INIT_POS_X)
					TranslationX(-1.0f);
			}
			break;
		case S_STATUS_RIGHT:
			if (nNo == ARROW_RIGHT)
			{
				for (int i = 0; i <= MOVE_COUNT; i++)
				{
					if (m_pos.x < RIGHT_ARROW_INIT_POS_X + MOVE_COUNT)
						TranslationX(1.0f);
					if (i >= MOVE_COUNT)
						return S_STATUS_WAIT;
				}
			}
			else
			{
				if (m_pos.x < LEFT_ARROW_INIT_POS_X)
					TranslationX(1.0f);
			}
			break;
	}

	CCharacter::Update();

	return nStatus;
}
//����������������������������������������������������������������������������������������
//	Name        : �V�[���J�� ��2 (��ʂ���o��)
//	Description : �ォ��o��
//	Arguments   : pTex / �e�N�X�`��
//				  y    / Y�����ړ���
//	Returns     : �����t���O(true:�J�ڊ���)
//����������������������������������������������������������������������������������������
void CSelectObject::RogoUpdate(int nNo,int nStatus,int nStage)
{
#define ROGO_STAGE_1	1
#define ROGO_STAGE_2	2
	switch (nStatus)
	{
	case S_STATUS_WAIT:
		break;
	case S_STATUS_LEFT:
		if (nNo == ROGO_STAGE_1)
		{
			if (nStage == S_STAGE_1)
			{
				TranslateX(ROGO_INIT_POS_X);
				TranslateY(ROGO_INIT_POS_Y);
			}
			else
			{
				TranslateX(ROGO_SCREEN_OUT_POS_X);
				TranslateY(ROGO_SCREEN_OUT_POS_Y);
			}
		}
		else
		{
			if (nStage == S_STAGE_2)
			{
				TranslateX(ROGO_INIT_POS_X);
				TranslateY(ROGO_INIT_POS_Y);
			}
			else
			{
				TranslateX(ROGO_SCREEN_OUT_POS_X);
				TranslateY(ROGO_SCREEN_OUT_POS_Y);
			}
		}
		break;
	case S_STATUS_RIGHT:
		if (nNo == ROGO_STAGE_1)
		{
			if (nStage == S_STAGE_1)
			{
				TranslateX(ROGO_INIT_POS_X);
				TranslateY(ROGO_INIT_POS_Y);
			}
			else
			{
				TranslateX(ROGO_SCREEN_OUT_POS_X);
				TranslateY(ROGO_SCREEN_OUT_POS_Y);
			}
		}
		else
		{
			if (nStage == S_STAGE_2)
			{
				TranslateX(ROGO_INIT_POS_X);
				TranslateY(ROGO_INIT_POS_Y);
			}
			else
			{
				TranslateX(ROGO_SCREEN_OUT_POS_X);
				TranslateY(ROGO_SCREEN_OUT_POS_Y);
			}
		}
		break;
	}


	CCharacter::Update();
}
//����������������������������������������������������������������������������������������
//	Name        : �V�[���J�� ��2 (��ʂ���o��)
//	Description : �ォ��o��
//	Arguments   : pTex / �e�N�X�`��
//				  y    / Y�����ړ���
//	Returns     : �����t���O(true:�J�ڊ���)
//����������������������������������������������������������������������������������������
int CSelectObject::StageUpdate(int nStatus,int nStage)
{
	switch (nStatus)
	{
	case S_STATUS_WAIT:
		if (nStage == S_STAGE_1)
		{

			if (m_rot.z != 0.0f)
				RotationZ(2.0f);
		}
		else
		{
			if (m_rot.z != 180.0f)
				RotationZ(2.0f);
		}
		if (m_rot.z >= 360.0f)
			RotateZ(0.0f);
		break;
	case S_STATUS_LEFT:
		break;
	case S_STATUS_RIGHT:
		break;
	}

	CCharacter::Update();

	return nStatus;
}
//========================================================================================
//	End of File
//========================================================================================