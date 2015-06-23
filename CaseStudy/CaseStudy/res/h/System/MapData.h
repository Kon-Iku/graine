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
#include "../Object/FieldObject.h"

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

		MAX_STAGEID
	};

	// �}�b�v�f�[�^�̃p�����[�^
	static enum _eDataParam
	{
		DP_ID = 0,			// ID
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

		MAX_BLOCKTYPE
	};

	static const int	INIT_OBJECT_NUM;	// �����I�u�W�F�N�g��


// ===== �����o�ϐ�
private:
	static LPFIELDOBJECT_ARRAY	m_pFieldObj;	// �t�B�[���h�I�u�W�F�N�g���X�g
	static LPCHARACTER_ARRAY	m_pLayoutObj;	// ���C�A�E�g�I�u�W�F�N�g���X�g
	static D3DXVECTOR2			m_startPoint;	// �J�n�ʒu

// ===== �����o�֐�
public:
	static CMapData& GetInstance();	// �C���X�^���X�擾

	static bool LoadData(int id);	// �}�b�v�f�[�^���[�h
	static void DeleteData();		// �}�b�v�f�[�^�j��

	// ----- �Q�b�^�[
	static void GetFieldObjList(LPFIELDOBJECT_ARRAY* pObjList);		// �t�B�[���h�I�u�W�F�N�g���X�g�擾
	static void GetLayoutObjList(LPCHARACTER_ARRAY* pObjList);		// ���C�A�E�g�I�u�W�F�N�g���X�g�擾
	static D3DXVECTOR2& GetStartPoint() {return m_startPoint;}		// �J�n�ʒu�擾
	static int GetClearBlockNum();									// �N���A�����u���b�N���擾
	
private:
	CMapData();
	CMapData(const CMapData&) {}
	CMapData &operator=(const CMapData&) {}
	virtual ~CMapData();
};


//========================================================================================
//	End of File
//========================================================================================