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
		DP_COLFLG,			// �����蔻��̗L��
		DP_TYPE,			// ���

		MAX_DATAPARAM	// �p�����[�^��
	};

	static const int	INIT_OBJECT_NUM;	// �����I�u�W�F�N�g��

// ===== �����o�ϐ�
private:
	static LPFIELDOBJECT_ARRAY	m_pFieldObj;	// �t�B�[���h�I�u�W�F�N�g���X�g

// ===== �����o�֐�
public:
	static CMapData& GetInstance();	// �C���X�^���X�擾

	static bool LoadData(int id);	// �}�b�v�f�[�^���[�h

	static void GetFieldObjList(LPFIELDOBJECT_ARRAY* pObjList);		// �t�B�[���h�I�u�W�F�N�g���X�g�擾
	
private:
	CMapData();
	CMapData(const CMapData&) {}
	CMapData &operator=(const CMapData&) {}
	virtual ~CMapData();
};


//========================================================================================
//	End of File
//========================================================================================