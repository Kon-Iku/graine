//========================================================================================
//		File        : Camera.h
//		Program     : �J�����N���X
//
//		Description : �J�����N���X�̒�`
//
//		History     : 2013/11/26	�쐬�J�n
//					  2014/05/23	�t�@�C�����ύX
//						   07/02	Object�N���X����p��
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
#include "../Object/Camera.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CGameCamera : public CCamera
{
private:
	static const float DEFAULT_CAMERA_POS_Z;
	static const D3DXVECTOR3 CAMERA_DEFAULT_POS;
	static const float C_LENGTH_0;
	static const float C_LENGTH_1;
	static const float C_LENGTH_2;
	static const float C_MOVE_SPD;

private:
// ===== �����o�ϐ�

	int				m_nPhase;	// �t�F�C�Y
	bool			m_bMove;
	D3DXVECTOR3		m_vNextEye;	// ������
// ===== �����o�֐�
public:
	CGameCamera();
	virtual ~CGameCamera();

	virtual void Init();		// ������
	virtual void Uninit();		// ��n��
	virtual void Update();		// �X�V
	virtual void Draw();		// �`��
	virtual void Release();		// ���

	void cameraControllMain();	// �J��������i���C�����j

	static CGameCamera* Create();	// �J��������

	// ----- �Z�b�^�[
	void SetPhase(int no){m_nPhase = no;}
	void SetNextEye(D3DXVECTOR3 eye){m_vNextEye = eye; m_vNextEye.z = DEFAULT_CAMERA_POS_Z;}

	// -----�Q�b�^�[
	int GetPhase(){return m_nPhase;}
	D3DXVECTOR3 GetNextEye(){return m_vNextEye;}

private:
	void			SyncEyeLook();		// �J�����̈ʒu�ƒ����_�̓���
	virtual bool	Initialize();		// ������
	virtual void	Finalize();			// ��n��
};


//========================================================================================
//	End of File
//========================================================================================