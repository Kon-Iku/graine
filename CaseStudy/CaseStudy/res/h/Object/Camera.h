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
#include "../Object/Object.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CCamera : public CObject
{
// ===== �����o�萔
protected:
	// �J�������
	enum _eType {
		TYPE_FIXED = 0,		// ��_
		TYPE_FIRSTPERSON,	// ��l��
		TYPE_THIRDPERSON,	// �O�l��
	
		MAX_TYPE			// �J������ʐ�
	};

// ===== �����o�ϐ�
protected:
	D3DXVECTOR3	m_eye;		// ���_���W
	D3DXVECTOR3	m_look;		// �����_���W
	D3DXVECTOR3	m_up;		// �A�b�v�x�N�g��
	D3DXVECTOR3	m_newEye;	// �����_���W
	D3DXVECTOR3	m_newLook;	// ���������W
	D3DXVECTOR3	m_newUp;	// ���A�b�v�x�N�g��
	int			m_type;		// �J�������

// ===== �����o�֐�
public:
	CCamera();
	virtual ~CCamera();

	virtual void Init();		// ������
	virtual void Uninit();		// ��n��
	virtual void Update();		// �X�V
	virtual void Draw();		// �`��
	virtual void Release();		// ���

	static CCamera* Create();	// �J��������

	// ----- �Z�b�^�[
	void SetParameter(D3DXVECTOR3& eye, D3DXVECTOR3& look, D3DXVECTOR3& up);	// �J�����p�����[�^�Z�b�g
	void SetParameter(const D3DXVECTOR3& eye, const D3DXVECTOR3& look, const D3DXVECTOR3& up);	// �J�����p�����[�^�Z�b�g
	void SetEye(D3DXVECTOR3& eye);							// ���_���W�Z�b�g
	void SetEye(const D3DXVECTOR3& eye);					// ���_���W�Z�b�g
	void SetEyeX(float x) {m_eye.x = x;}					// ���_X���W�Z�b�g
	void SetEyeY(float y) {m_eye.y = y;}					// ���_Y���W�Z�b�g
	void SetEyeZ(float z) {m_eye.z = z;}					// ���_Z���W�Z�b�g
	void SetLook(D3DXVECTOR3& look);						// �����_���W�Z�b�g
	void SetLook(const D3DXVECTOR3& look);					// �����_���W�Z�b�g
	void SetLookX(float x) {m_look.x = x;}					// �����_X���W�Z�b�g
	void SetLookY(float y) {m_look.y = y;}					// �����_Y���W�Z�b�g
	void SetLookZ(float z) {m_look.z = z;}					// �����_Z���W�Z�b�g
	void SetUp(D3DXVECTOR3& up);							// ����x�N�g���Z�b�g
	void SetUp(const D3DXVECTOR3& up);						// ����x�N�g���Z�b�g
	void SetUpX(float x) {m_up.x = x;}						// ����x�N�g��(X������)�Z�b�g
	void SetUpY(float y) {m_up.y = y;}						// ����x�N�g��(Y������)�Z�b�g
	void SetUpZ(float z) {m_up.z = z;}						// ����x�N�g��(Z������)�Z�b�g
	void SetType(int type) {m_type = type;}					// �J������ʃZ�b�g
	
	// ----- �Q�b�^�[
	D3DXVECTOR3 GetEye() const	{return m_eye;}		// ���_���W�擾
	D3DXVECTOR3 GetLook() const	{return m_look;}	// �����_���W�擾
	D3DXVECTOR3 GetUp() const	{return m_up;}		// �A�b�v�x�N�g���擾

private:
	virtual bool	Initialize();		// ������
	virtual void	Finalize();			// ��n��
};


//========================================================================================
//	End of File
//========================================================================================