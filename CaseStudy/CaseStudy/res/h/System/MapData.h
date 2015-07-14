//========================================================================================
//		File        : MapData.h
//		Program     : �}�b�v�f�[�^�N���X
//
//		Description : �}�b�v�f�[�^�N���X�̒�`
//
//		History     : 2015/05/18	�쐬�J�n
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
#include "../Object/Character.h"
#include "../Object/FieldBlock.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CMapData
{
	// ===== �����o�萔
private:
	static LPCTSTR	MAPDATA_LIST[];		// �}�b�v�f�[�^�̃t�@�C�������X�g

public:
	// �}�b�v�̃X�e�[�WID���X�g(�t�@�C�������X�g)
	static enum _eStageID
	{
		ID_STAGE1 = 0,
		ID_STAGE2,
		ID_STAGE3,
		ID_STAGE4,
		ID_STAGE5,

		MAX_STAGEID
	};

	// �}�b�v�f�[�^�̃p�����[�^
	static enum _eDataParam
	{
		DP_BID = 0,			// �u���b�N��ID
		DP_EID,				// �u���b�N�̗v�f��ID
		DP_TEX,				// �e�N�X�`����
		DP_POSX,			// X���W
		DP_POSY,			// Y���W
		DP_POSZ,			// Z���W
		DP_WIDTH,			// ��
		DP_HEIGHT,			// ����
		DP_ANGLE,			// ��]�p�x
		DP_COLR,			// R�l
		DP_COLG,			// G�l
		DP_COLB,			// B�l
		DP_COLA,			// A�l
		DP_COLFLG,			// �����蔻��̗L��
		DP_TYPE,			// ���

		MAX_DATAPARAM	// �p�����[�^��
	};

	// �u���b�N���
	static enum _eBlockType
	{
		BT_NORMAL = 0,	// 0:���ʂ̃t�B�[���h�u���b�N
		BT_CLEAR,		// 1:�N���A�����t�B�[���h�u���b�N
		BT_OVER,		// 2:��Q�t�B�[���h�u���b�N
		BT_LAYOUT,		// 3:���C�A�E�g�u���b�N
		BT_LAYOUTOBJ,	// 4:���C�A�E�g�I�u�W�F�N�g
		BT_JACK,		// 5:���̖�

		MAX_BLOCKTYPE
	};

	static const int	INIT_OBJECT_NUM;	// �����I�u�W�F�N�g��


	// ===== �����o�ϐ�
private:
	static LPFIELDBLOCK_ARRAY	m_pFieldBlock;	// �t�B�[���h�u���b�N���X�g
	static LPCHARACTER_ARRAY	m_pLayoutBlock;	// ���C�A�E�g�u���b�N���X�g
	static D3DXVECTOR2			m_startPoint;	// �J�n�ʒu

	static float	m_leftWallX;		// ����X���W
	static float	m_rightWallX;		// �E��X���W
	static float	m_topWallY;			// ���Y���W
	static float	m_bottomWallY;		// ����Y���W

	// ===== �����o�֐�
public:
	static CMapData& GetInstance();	// �C���X�^���X�擾

	static bool LoadData(int id);	// �}�b�v�f�[�^���[�h
	static void DeleteData();		// �}�b�v�f�[�^�j��

	// ----- �Q�b�^�[
	static void GetFieldBlockList(LPFIELDBLOCK_ARRAY* pObjList);		// �t�B�[���h�u���b�N���X�g�擾
	static void GetLayoutBlockList(LPCHARACTER_ARRAY* pObjList);		// ���C�A�E�g�u���b�N���X�g�擾
	static D3DXVECTOR2& GetStartPoint() { return m_startPoint; }		// �J�n�ʒu�擾
	static int GetClearBlockNum();										// �N���A�����u���b�N���擾
	static float GetLeftWallX() { return m_leftWallX; }					// ����X���W�擾
	static float GetRightWallX() { return m_rightWallX; }				// �E��X���W�擾
	static float GetTopWallY() { return m_topWallY; }					// ���Y���W�擾
	static float GetBottomWallY() { return m_bottomWallY; }				// ����Y���W�擾

private:
	CMapData();
	CMapData(const CMapData&) {}
	CMapData &operator=(const CMapData&) {}
	virtual ~CMapData();
};


//========================================================================================
//	End of File
//========================================================================================