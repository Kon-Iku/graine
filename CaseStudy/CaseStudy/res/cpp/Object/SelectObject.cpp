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
#include "../../h/System/MapData.h"
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
	m_bAnime = false;
	for(int i = 0; i < 5; i++)
	{
		m_nClearLeft[i] = 0;
		m_nClearRight[i] = 0;
	}
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
//	Name        : �w�i�X�V
//	Description : 
//	Arguments   : nNo		 / 1 = �N���A�w�i,2 = ���N���A�w�i
//				  nStatus    / WAIT = 0 ������,LEFT = 1 ���L�[����,RIGHT = 2 ���L�[����
//				  bClear	 / �X�e�[�W���N���A�ς݂�
//				  bAnime	 / �w�i�������Ă��邩
//	Returns     : �w�i�̓���L��(true:���쒆)
//����������������������������������������������������������������������������������������
bool CSelectObject::BGUpdate(int nNo, int nStatus, int nClear, bool bAnime)
{
	static float fTransX1 = 0.0f;
	static float fTransX2 = 0.0f;
	static bool bMove = false;

	if (bAnime)
	{
		if (m_pos.x >= SCREEN_WIDTH + SCREEN_RIGHT)
			Init(D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT), D3DXVECTOR3((float)(SCREEN_LEFT + 1),(float)(SCREEN_HEIGHT / 2), 0));
		if (m_pos.x <= SCREEN_LEFT)
			Init(D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT), D3DXVECTOR3((float)(SCREEN_WIDTH + SCREEN_RIGHT - 1),(float)(SCREEN_HEIGHT / 2), 0));
	}

	if (nNo == 1)
	{
		switch (nStatus)
		{
		case S_STATUS_WAIT:
			if (nClear)
			{
				if (m_pos.x >= SCREEN_RIGHT - 50 && m_pos.x <= SCREEN_RIGHT + 50)
				{
					Init(D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT), D3DXVECTOR3((float)SCREEN_RIGHT, (float)(SCREEN_HEIGHT / 2), 0));
				}
				if (m_pos.x == SCREEN_RIGHT)
				{
					fTransX1 = 0.0f;
					return false;
				}
				else
				{
					TranslationX(fTransX1);
				}
			}
			else
			{
				if (m_pos.x >= SCREEN_WIDTH + SCREEN_RIGHT - 1 || m_pos.x <= SCREEN_LEFT + 1)
				{
					fTransX1 = 0.0f;
					return false;
				}
				else
					TranslationX(fTransX1);
			}
			break;

		case S_STATUS_LEFT:
			fTransX1 = SCREEN_RIGHT / MOVE_COUNT;
			return true;
			break;
		case S_STATUS_RIGHT:
			fTransX1 = -(SCREEN_RIGHT / MOVE_COUNT);
			return true;
			break;
		}
	}
	else
	{
		switch (nStatus)
		{
		case S_STATUS_WAIT:
			if (nClear)
			{
				if (m_pos.x >= SCREEN_WIDTH + SCREEN_RIGHT - 1 || m_pos.x <= SCREEN_LEFT + 1)
				{
					fTransX2 = 0.0f;
					return false;
				}
				else
					TranslationX(fTransX2);
			}
			else
			{
				if (m_pos.x >= SCREEN_RIGHT - 50 && m_pos.x <= SCREEN_RIGHT + 50)
					Init(D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT), D3DXVECTOR3((float)SCREEN_RIGHT, (float)(SCREEN_HEIGHT / 2), 0));
				if (m_pos.x == SCREEN_RIGHT)
				{
					fTransX2 = 0.0f;
					return false;
				}
				else
					TranslationX(fTransX2);
			}
			break;
		case S_STATUS_LEFT:
			fTransX2 = SCREEN_RIGHT / MOVE_COUNT;
			return true;
			break;
		case S_STATUS_RIGHT:
			fTransX2 = -(SCREEN_RIGHT / MOVE_COUNT);
			return true;
			break;
		}
	}
	return bAnime;
}

//����������������������������������������������������������������������������������������
//	Name        : ���˂ۂ�X�V
//	Description : 
//	Arguments   : bAnime	 / ���˂ۂ񂪈ړ����L��(true:�ҋ@��)
//				  nStatus    / WAIT = 0 ������,LEFT = 1 ���L�[����,RIGHT = 2 ���L�[����
//	Returns     : �Ȃ�
//����������������������������������������������������������������������������������������
void CSelectObject::PlayerUpdate(bool bAnime, int nStatus)
{
	if (!bAnime)
	{
		switch (nStatus)
		{
		case S_STATUS_WAIT:
			break;
		case S_STATUS_LEFT:
			if (GetScaleX() < 0.0f)
				ScaleX(1.0f);
			break;
		case S_STATUS_RIGHT:
			if (GetScaleX() > 0.0f)
				ScaleX(-1.0f);
			break;
		}
		FrameAnimation(0, 11, SELECT_ANIME_SIZE_X, SELECT_ANIME_SIZE_Y, 0.05f);
	}
	else
		FrameAnimation(60, 61, SELECT_ANIME_SIZE_X, SELECT_ANIME_SIZE_Y, 0.5f);

	CCharacter::Update();
}

//����������������������������������������������������������������������������������������
//	Name        : �G�p�X�V
//	Description : 
//	Arguments   : bAnime	 / ���˂ۂ�ړ����L��(true:�ҋ@��)
//				  nStatus    / WAIT = 0 ������,LEFT = 1 ���L�[����,RIGHT = 2 ���L�[����
//	Returns     : �Ȃ�
//����������������������������������������������������������������������������������������
void CSelectObject::TactileUpdate(bool bAnime, int nStatus)
{
	if (!bAnime)
	{
		switch (nStatus)
		{
		case S_STATUS_WAIT:
			break;
		case S_STATUS_LEFT:
			if (GetScaleX() < 0.0f)
				ScaleX(1.0f);
			break;
		case S_STATUS_RIGHT:
			if (GetScaleX() > 0.0f)
				ScaleX(-1.0f);
			break;
		}
		FrameAnimation(0, 11, SELECT_ANIME_SIZE_X, SELECT_ANIME_SIZE_Y, 0.05f);
	}
	else
		FrameAnimation(60, 61, SELECT_ANIME_SIZE_X, SELECT_ANIME_SIZE_Y, 0.5f);

	CCharacter::Update();
}

//����������������������������������������������������������������������������������������
//	Name        : ���X�V
//	Description : 
//	Arguments   : nNo		 / 1 = �����,2 = �E���
//				  nStatus    / WAIT = 0 ������,LEFT = 1 ���L�[����,RIGHT = 2 ���L�[����
//	Returns     : nStatus������e
//����������������������������������������������������������������������������������������
int CSelectObject::ArrowUpdate(int nNo, int nStatus)
{
#define ARROW_LEFT	1
#define ARROW_RIGHT 2

	static bool bMoveRight = false;
	static bool bMoveLeft = false;
	static bool bWaitLeft = false;
	static bool bWaitRight = false;

	if (nNo == ARROW_RIGHT)
		if (GetScaleX() > 0.0f)
			ScaleX(-1.0f);

	switch (nStatus)
	{
	case S_STATUS_WAIT:
		if (nNo == ARROW_LEFT)
		{
			if (bMoveLeft)
			{
				ScaleX(1.5f);
				ScaleY(1.5f);
				if (m_pos.x < LEFT_ARROW_INIT_POS_X)
					TranslationX(1.0f);
				else
				{
					bMoveLeft = false;
					bWaitLeft = false;
					ScaleX(1.0f);
					ScaleY(1.0f);
				}
			}
			else
			{
				ScaleX(1.0f);
				ScaleY(1.0f);
				if (bWaitLeft)
				{
					TranslationX(0.2f);
					if (m_pos.x >= LEFT_ARROW_INIT_POS_X)
						bWaitLeft = false;
				}
				else
				{
					TranslationX(-0.2f);
					if (m_pos.x < LEFT_ARROW_INIT_POS_X - 5)
						bWaitLeft = true;
				}
			}
		}
		else
		{
			if (bMoveRight)
			{
				ScaleX(-1.5f);
				ScaleY(-1.5f);
				if (m_pos.x > RIGHT_ARROW_INIT_POS_X)
					TranslationX(-1.0f);
				else
				{
					bMoveRight = false;
					bWaitRight = false;
					ScaleX(-1.0f);
					ScaleY(-1.0f);
				}
			}
			else
			{
				ScaleX(-1.0f);
				ScaleY(-1.0f);
				if (bWaitRight)
				{
					TranslationX(-0.2f);
					if (m_pos.x <= RIGHT_ARROW_INIT_POS_X)
						bWaitRight = false;
				}
				else
				{
					TranslationX(0.2f);
					if (m_pos.x > RIGHT_ARROW_INIT_POS_X + 5)
						bWaitRight = true;
				}
			}
		}
		break;
	case S_STATUS_LEFT:
		bMoveLeft = true;
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
			else
				bMoveRight = false;
		}
		break;
	case S_STATUS_RIGHT:
		bMoveRight = true;
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
			else
				bMoveLeft = false;
		}
		break;
	}
	CCharacter::Update();

	return nStatus;
}
//����������������������������������������������������������������������������������������
//	Name        : �X�e�[�W���S�X�V
//	Description : 
//	Arguments   : nNo		 / 1 = STAGE_1,2 = STAGE_2,3 = STAGE_3,4 = STAGE_4,5 = STAGE_5
//				  nStatus    / WAIT = 0 ������,LEFT = 1 ���L�[����,RIGHT = 2 ���L�[����
//				  nStage	 / �I�𒆂̃X�e�[�W
//	Returns     : �Ȃ�
//����������������������������������������������������������������������������������������
void CSelectObject::RogoUpdate(int nNo, int nStatus, int nStage)
{
#define ROGO_STAGE_1	1
#define ROGO_STAGE_2	2
#define ROGO_STAGE_3	3
#define ROGO_STAGE_4	4
#define ROGO_STAGE_5	5

	switch (nStatus)
	{
	case S_STATUS_WAIT:
		switch (nNo)
		{
		case ROGO_STAGE_1:
			if (nStage == CMapData::ID_STAGE1)
			{
				TranslateX(ROGO_INIT_POS_X);
				TranslateY(ROGO_INIT_POS_Y);
			}
			else
			{
				TranslateX(ROGO_SCREEN_OUT_POS_X);
				TranslateY(ROGO_SCREEN_OUT_POS_Y);
			}
			break;
		case ROGO_STAGE_2:
			if (nStage == CMapData::ID_STAGE2)
			{
				TranslateX(ROGO_INIT_POS_X);
				TranslateY(ROGO_INIT_POS_Y);
			}
			else
			{
				TranslateX(ROGO_SCREEN_OUT_POS_X);
				TranslateY(ROGO_SCREEN_OUT_POS_Y);
			}
			break;
		case ROGO_STAGE_3:
			if (nStage == CMapData::ID_STAGE3)
			{
				TranslateX(ROGO_INIT_POS_X);
				TranslateY(ROGO_INIT_POS_Y);
			}
			else
			{
				TranslateX(ROGO_SCREEN_OUT_POS_X);
				TranslateY(ROGO_SCREEN_OUT_POS_Y);
			}
			break;
		case ROGO_STAGE_4:
			if (nStage == CMapData::ID_STAGE4)
			{
				TranslateX(ROGO_INIT_POS_X);
				TranslateY(ROGO_INIT_POS_Y);
			}
			else
			{
				TranslateX(ROGO_SCREEN_OUT_POS_X);
				TranslateY(ROGO_SCREEN_OUT_POS_Y);
			}
			break;
		case ROGO_STAGE_5:
			if (nStage == CMapData::ID_STAGE5)
			{
				TranslateX(ROGO_INIT_POS_X);
				TranslateY(ROGO_INIT_POS_Y);
			}
			else
			{
				TranslateX(ROGO_SCREEN_OUT_POS_X);
				TranslateY(ROGO_SCREEN_OUT_POS_Y);
			}
			break;
		}
		break;
	case S_STATUS_LEFT:
		break;
	case S_STATUS_RIGHT:
		break;
	}


	CCharacter::Update();
}
//����������������������������������������������������������������������������������������
//	Name        : �X�e�[�W�X�V
//	Description : 
//	Arguments   : nNo		 / 1 = �㉺�N���A�ς�,2 = �N���A�E���N���A,3 = �㉺���N���A
//				  nStatus    / WAIT = 0 ������,LEFT = 1 ���L�[����,RIGHT = 2 ���L�[����
//				  nStage	 / �I�𒆃X�e�[�W
//	Returns     : ���쒆�L��(true:�ҋ@��)
//����������������������������������������������������������������������������������������
bool CSelectObject::StageUpdate(int nNo,int nStatus, int nStage)
{
	static float fRotateZ = 0.0f;
	static int   bMove = S_STATUS_WAIT;
	static int	 nStageNo = nStage;

	switch (nStatus)
	{
	case S_STATUS_WAIT:
		switch (nStageNo)
		{
		case CMapData::ID_STAGE1:
			if (m_rot.z == 0.0f || m_rot.z == -180.0f || m_rot.z == 180.0f)
			{
				if (bMove == S_STATUS_RIGHT)
				{
					StageChange(nNo, m_nClearRight[CMapData::ID_STAGE1]);
					RotationZ(fRotateZ);
					return false;
				}
				else if (bMove == S_STATUS_LEFT)
				{
					StageChange(nNo, m_nClearLeft[CMapData::ID_STAGE1]);
					RotationZ(fRotateZ);
					return false;
				}

				nStageNo = nStage;
				bMove = S_STATUS_WAIT;
				return true;
			}
			else
			{
				RotationZ(fRotateZ);
				if (m_rot.z == 0.0f || m_rot.z == -180.0f || m_rot.z == 180.0f)
					bMove = S_STATUS_WAIT;
			}
			break;
		case CMapData::ID_STAGE2:
			if (m_rot.z == 0.0f || m_rot.z == -180.0f || m_rot.z == 180.0f)
			{
				if (bMove == S_STATUS_RIGHT)
				{
					StageChange(nNo, m_nClearRight[CMapData::ID_STAGE2]);
					RotationZ(fRotateZ);
					return false;
				}
				else if (bMove == S_STATUS_LEFT)
				{
					StageChange(nNo, m_nClearLeft[CMapData::ID_STAGE2]);
					RotationZ(fRotateZ);
					return false;
				}

				nStageNo = nStage;
				bMove = S_STATUS_WAIT;
				return true;
			}
			else
			{
				RotationZ(fRotateZ);
				bMove = S_STATUS_WAIT;
			}
			break;
		case CMapData::ID_STAGE3:
			if (m_rot.z == 0.0f || m_rot.z == -180.0f || m_rot.z == 180.0f)
			{
				if (bMove == S_STATUS_RIGHT)
				{
					StageChange(nNo, m_nClearRight[CMapData::ID_STAGE3]);
					RotationZ(fRotateZ);
					return false;
				}
				else if (bMove == S_STATUS_LEFT)
				{
					StageChange(nNo, m_nClearLeft[CMapData::ID_STAGE3]);
					RotationZ(fRotateZ);
					return false;
				}

				nStageNo = nStage;
				bMove = S_STATUS_WAIT;
				return true;
			}
			else
			{
				RotationZ(fRotateZ);
				if (m_rot.z == 0.0f || m_rot.z == -180.0f || m_rot.z == 180.0f)
					bMove = S_STATUS_WAIT;
			}
			break;
		case CMapData::ID_STAGE4:
			if (m_rot.z == 0.0f || m_rot.z == -180.0f || m_rot.z == 180.0f)
			{
				if (bMove == S_STATUS_RIGHT)
				{
					StageChange(nNo, m_nClearRight[CMapData::ID_STAGE4]);
					RotationZ(fRotateZ);
					return false;
				}
				else if (bMove == S_STATUS_LEFT)
				{
					StageChange(nNo, m_nClearLeft[CMapData::ID_STAGE4]);
					RotationZ(fRotateZ);
					return false;
				}

				nStageNo = nStage;
				bMove = S_STATUS_WAIT;
				return true;
			}
			else
			{
				RotationZ(fRotateZ);
				if (m_rot.z == 0.0f || m_rot.z == -180.0f || m_rot.z == 180.0f)
					bMove = S_STATUS_WAIT;
			}
			break;
		case CMapData::ID_STAGE5:
			if (m_rot.z == 0.0f || m_rot.z == -180.0f || m_rot.z == 180.0f)
			{
				if (bMove == S_STATUS_RIGHT)
				{
					StageChange(nNo, m_nClearRight[CMapData::ID_STAGE5]);
					RotationZ(fRotateZ);
					return false;
				}
				else if (bMove == S_STATUS_LEFT)
				{
					StageChange(nNo, m_nClearLeft[CMapData::ID_STAGE5]);
					RotationZ(fRotateZ);
					return false;
				}

				nStageNo = nStage;
				bMove = S_STATUS_WAIT;
				return true;
			}
			else
			{
				RotationZ(fRotateZ);
				if (m_rot.z == 0.0f || m_rot.z == -180.0f || m_rot.z == 180.0f)
					bMove = S_STATUS_WAIT;
			}
			break;
		}
		if (m_rot.z >= 360.0f)
			RotateZ(-180.0f);
		if (m_rot.z <= -360.0f)
			RotateZ(0.0f);
		break;
	case S_STATUS_LEFT:
		fRotateZ = 6.0f;
		bMove = S_STATUS_LEFT;
		break;
	case S_STATUS_RIGHT:
		fRotateZ = -6.0f;
		bMove = S_STATUS_RIGHT;
		break;
	}

	CCharacter::Update();
	return false;
}

void CSelectObject::RingUpdate(int nNo,int nStatus,int nClear)
{
	static float fRotationZ = 0.0f;
	static int nCount = 0;

	SetAlpha(90);
	RotationZ(fRotationZ);

	switch (nStatus)
	{
	case S_STATUS_WAIT:
		break;
	case S_STATUS_LEFT:
		fRotationZ = -1.5f;
		nCount = 0;
		break;
	case S_STATUS_RIGHT:
		fRotationZ = 1.5f;
		nCount = 0;
		break;
	}
	if (nCount == 30 || nCount == 29)
	{
		if (nNo == 1)
		{
			if (nClear)
			{
				if (m_pos.x > SCREEN_RIGHT)
					Init(D3DXVECTOR2(1280, 1280), D3DXVECTOR3((float)SCREEN_RIGHT, (float)SCREEN_HEIGHT / 2 + 100, 0));
			}
			else
				Init(D3DXVECTOR2(1280, 1280), D3DXVECTOR3((float)SCREEN_WIDTH * 2, (float)SCREEN_HEIGHT / 2 + 100, 0));
		}
		if (nNo == 2)
		{
			if (nClear)
				Init(D3DXVECTOR2(1280, 1280), D3DXVECTOR3((float)SCREEN_WIDTH * 2, (float)SCREEN_HEIGHT / 2 + 100, 0));
			else
			{
				if (m_pos.x > SCREEN_RIGHT)
					Init(D3DXVECTOR2(1280, 1280), D3DXVECTOR3((float)SCREEN_RIGHT, (float)SCREEN_HEIGHT / 2 + 100, 0));
			}
		}
	}
	if (nCount >= 60)
	{
		fRotationZ = 0.0f;
		nCount = 0;
	}
	if (fRotationZ >= 1.5f || fRotationZ <= -1.5f)
		nCount++;

	static int ScaleCount = 0;

	if (ScaleCount < 100)
	{
		ScalingX(0.001f);
		ScalingY(0.001f);
	}
	else
	{
		ScalingX(-0.001f);
		ScalingY(-0.001f);
	}
	if (ScaleCount >= 200)
		ScaleCount = 0;
	else
		ScaleCount++;

	CCharacter::Update();
}


//����������������������������������������������������������������������������������������
//	Name        : �X�e�[�W�ύX
//	Description : �X�e�[�W�摜�̒u������
//	Arguments   : nNo		/ 1 = �㉺�N���A�ς�,2 = �N���A�E���N���A,3 = �㉺���N���A
//				  nClear    / SC_�I�𒆃N���A�L��_�I���N���A�L��
//	Returns     : �Ȃ�
//����������������������������������������������������������������������������������������
void CSelectObject::StageChange(int nNo,int nClear)
{
	switch (nClear)
	{
	case SC_CLEAR_CLEAR:
		if (nNo == 1)
		{
			Init(D3DXVECTOR2(SCREEN_RIGHT * 2, SCREEN_RIGHT * 2), D3DXVECTOR3((float)STAGE_INIT_POS_X, (float)STAGE_INIT_POS_Y, 0));
			RotateZ(0.0f);
		}
		else
			Init(D3DXVECTOR2(SCREEN_RIGHT * 2, SCREEN_RIGHT * 2), D3DXVECTOR3((float)SCREEN_WIDTH + SCREEN_RIGHT, (float)STAGE_INIT_POS_Y, 0));
		break;
	case SC_CLEAR_FALSE:
		if (nNo == 2)
		{
			Init(D3DXVECTOR2(SCREEN_RIGHT * 2, SCREEN_RIGHT * 2), D3DXVECTOR3((float)STAGE_INIT_POS_X, (float)STAGE_INIT_POS_Y, 0));
			RotateZ(0.0f);
		}
		else
			Init(D3DXVECTOR2(SCREEN_RIGHT * 2, SCREEN_RIGHT * 2), D3DXVECTOR3((float)SCREEN_WIDTH + SCREEN_RIGHT, (float)STAGE_INIT_POS_Y, 0));
		break;
	case SC_FALSE_CLEAR:
		if (nNo == 2)
		{
			Init(D3DXVECTOR2(SCREEN_RIGHT * 2, SCREEN_RIGHT * 2), D3DXVECTOR3((float)STAGE_INIT_POS_X, (float)STAGE_INIT_POS_Y, 0));
			RotateZ(180.0f);
		}
		else
			Init(D3DXVECTOR2(SCREEN_RIGHT * 2, SCREEN_RIGHT * 2), D3DXVECTOR3((float)SCREEN_WIDTH + SCREEN_RIGHT, (float)STAGE_INIT_POS_Y, 0));
		break;
	case SC_FALSE_FALSE:
		if (nNo == 3)
		{
			Init(D3DXVECTOR2(SCREEN_RIGHT * 2, SCREEN_RIGHT * 2), D3DXVECTOR3((float)STAGE_INIT_POS_X, (float)STAGE_INIT_POS_Y, 0));
			RotateZ(0.0f);
		}
		else
			Init(D3DXVECTOR2(SCREEN_RIGHT * 2, SCREEN_RIGHT * 2), D3DXVECTOR3((float)SCREEN_WIDTH + SCREEN_RIGHT, (float)STAGE_INIT_POS_Y, 0));
		break;
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �N���A�󋵎擾
//	Description : 
//	Arguments   : nStage1	 / �X�e�[�W1�N���A�L��
//				  nStage2    / �X�e�[�W2�N���A�L��
//				  nStage3	 / �X�e�[�W3�N���A�L��
//				  nStage4	 / �X�e�[�W4�N���A�L��
//				  nStage5	 / �X�e�[�W5�N���A�L��
//	Returns     : �Ȃ�
//����������������������������������������������������������������������������������������
void CSelectObject::ClearSave(int nStage1, int nStage2, int nStage3, int nStage4, int nStage5)
{
	if (nStage1)
	{
		if (nStage2)
		{
			m_nClearRight[0] = SC_CLEAR_CLEAR;
		}
		else
		{
			m_nClearRight[0] = SC_CLEAR_FALSE;
		}

		if (nStage5)
		{
			m_nClearLeft[0] = SC_CLEAR_CLEAR;
		}
		else
		{
			m_nClearLeft[0] = SC_CLEAR_FALSE;
		}
	}
	else
	{
		if (nStage2)
		{
			m_nClearRight[0] = SC_FALSE_CLEAR;
		}
		else
		{
			m_nClearRight[0] = SC_FALSE_FALSE;
		}

		if (nStage5)
		{
			m_nClearLeft[0] = SC_FALSE_CLEAR;
		}
		else
		{
			m_nClearLeft[0] = SC_FALSE_FALSE;
		}
	}

	if (nStage2)
	{
		if (nStage3)
		{
			m_nClearRight[1] = SC_CLEAR_CLEAR;
		}
		else
		{
			m_nClearRight[1] = SC_CLEAR_FALSE;
		}

		if (nStage1)
		{
			m_nClearLeft[1] = SC_CLEAR_CLEAR;
		}
		else
		{
			m_nClearLeft[1] = SC_CLEAR_FALSE;
		}
	}
	else
	{
		if (nStage3)
		{
			m_nClearRight[1] = SC_FALSE_CLEAR;
		}
		else
		{
			m_nClearRight[1] = SC_FALSE_FALSE;
		}

		if (nStage1)
		{
			m_nClearLeft[1] = SC_FALSE_CLEAR;
		}
		else
		{
			m_nClearLeft[1] = SC_FALSE_FALSE;
		}
	}

	if (nStage3)
	{
		if (nStage4)
		{
			m_nClearRight[2] = SC_CLEAR_CLEAR;
		}
		else
		{
			m_nClearRight[2] = SC_CLEAR_FALSE;
		}

		if (nStage2)
		{
			m_nClearLeft[2] = SC_CLEAR_CLEAR;
		}
		else
		{
			m_nClearLeft[2] = SC_CLEAR_FALSE;
		}
	}
	else
	{
		if (nStage4)
		{
			m_nClearRight[2] = SC_FALSE_CLEAR;
		}
		else
		{
			m_nClearRight[2] = SC_FALSE_FALSE;
		}

		if (nStage2)
		{
			m_nClearLeft[2] = SC_FALSE_CLEAR;
		}
		else
		{
			m_nClearLeft[2] = SC_FALSE_FALSE;
		}
	}

	if (nStage4)
	{
		if (nStage5)
		{
			m_nClearRight[3] = SC_CLEAR_CLEAR;
		}
		else
		{
			m_nClearRight[3] = SC_CLEAR_FALSE;
		}

		if (nStage3)
		{
			m_nClearLeft[3] = SC_CLEAR_CLEAR;
		}
		else
		{
			m_nClearLeft[3] = SC_CLEAR_FALSE;
		}
	}
	else
	{
		if (nStage5)
		{
			m_nClearRight[3] = SC_FALSE_CLEAR;
		}
		else
		{
			m_nClearRight[3] = SC_FALSE_FALSE;
		}

		if (nStage3)
		{
			m_nClearLeft[3] = SC_FALSE_CLEAR;
		}
		else
		{
			m_nClearLeft[3] = SC_FALSE_FALSE;
		}
	}

	if (nStage5)
	{
		if (nStage1)
		{
			m_nClearRight[4] = SC_CLEAR_CLEAR;
		}
		else
		{
			m_nClearRight[4] = SC_CLEAR_FALSE;
		}

		if (nStage4)
		{
			m_nClearLeft[4] = SC_CLEAR_CLEAR;
		}
		else
		{
			m_nClearLeft[4] = SC_CLEAR_FALSE;
		}
	}
	else
	{
		if (nStage1)
		{
			m_nClearRight[4] = SC_FALSE_CLEAR;
		}
		else
		{
			m_nClearRight[4] = SC_FALSE_FALSE;
		}

		if (nStage4)
		{
			m_nClearLeft[4] = SC_FALSE_CLEAR;
		}
		else
		{
			m_nClearLeft[4] = SC_FALSE_FALSE;
		}
	}
}
//========================================================================================
//	End of File
//========================================================================================