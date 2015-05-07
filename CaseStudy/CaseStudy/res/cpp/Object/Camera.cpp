//========================================================================================
//		File        : Camera.cpp
//		Program     : �J�����N���X
//
//		Description : �J�����N���X�̎���
//
//		History     : 2013/11/26	�쐬�J�n
//					  2014/05/23	�t�@�C�����ύX
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
#include "../../h/System/Graphics.h"
#include "../../h/Object/Camera.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔�E�}�N����`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �J�������
enum _eCameraType {
	CT_FIXED = 0,		// ��_
	CT_FIRSTPERSON,		// ��l��
	CT_THIRDPERSON,		// �O�l��

	MAX_CAMERATYPE		// �J������ʐ�
};


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CCamera::CCamera()
{
	m_eye	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_look	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_up	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type	= MAX_CAMERATYPE;
}

//����������������������������������������������������������������������������������������
//	Name        : �f�X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CCamera::~CCamera()
{
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �J�����f�[�^������������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCamera::Init(void)
{
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �J�����f�[�^���������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCamera::Uninit(void)
{
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �J�����f�[�^���X�V����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCamera::Update()
{
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �J������`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCamera::Draw(void)
{	
	// ----- ���݂��Ă��Ȃ���Ζ�����
	if(!m_bExist)
		return;

	// ----- �ϐ��錾
	D3DXMATRIX	matView;		// �r���[ �}�g���b�N�X

	// ----- �J�����ʒu�X�V
	D3DXMatrixLookAtLH(&matView,
						&m_eye,		// ���_���W
						&m_look,	// �����_���W
						&m_up);		// �A�b�v�x�N�g��
	CGraphics::GetDevice()->SetTransform(D3DTS_VIEW, &matView);
}

//����������������������������������������������������������������������������������������
//	Name        : ���
//	Description : �J�����f�[�^���������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCamera::Release(void)
{
	Finalize();
	delete this;
}

//����������������������������������������������������������������������������������������
//	Name        : ��������
//	Description : �J�����f�[�^�𐶐�����
//	Arguments   : None.
//	Returns     : �J�����f�[�^
//����������������������������������������������������������������������������������������
CCamera* CCamera::Create(void)
{
	// ----- �ϐ��錾
	CCamera* pCamera;

	// ----- ����������
	pCamera = new CCamera();
	if(pCamera)
	{
		if(!pCamera->Initialize())
		{
			SAFE_DELETE(pCamera);
		}
	}

	return pCamera;
}

//����������������������������������������������������������������������������������������
//	Name        : �J�����p�����[�^�Z�b�g
//	Description : �J�����̃p�����[�^���Z�b�g����
//	Arguments   : eye	/ ���_���W
//				  look	/ �����_���W
//				  up	/ ����x�N�g��
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCamera::SetParameter(D3DXVECTOR3& eye, D3DXVECTOR3& look, D3DXVECTOR3& up)
{
	// ���_���W�Z�b�g
	if(eye != NULL) {
		SetEye(eye);
	} else {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CCamera::SetParameter��eye��NULL�ł��B"), _T("error"), MB_OK);
#endif
	}

	// �����_���W�Z�b�g
	if(look != NULL) {
		SetLook(look);
	} else {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CCamera::SetParameter��look��NULL�ł��B"), _T("error"), MB_OK);
#endif
	}
	
	// ����x�N�g���Z�b�g
	if(up != NULL) {
		SetUp(up);
	} else {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CCamera::SetParameter��up��NULL�ł��B"), _T("error"), MB_OK);
#endif
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �J�����p�����[�^�Z�b�g
//	Description : �J�����̃p�����[�^���Z�b�g����
//	Arguments   : eye	/ ���_���W
//				  look	/ �����_���W
//				  up	/ ����x�N�g��
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCamera::SetParameter(const D3DXVECTOR3& eye, const D3DXVECTOR3& look, const D3DXVECTOR3& up)
{
	// ���_���W�Z�b�g
	if(eye != NULL) {
		SetEye(eye);
	} else {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CCamera::SetParameter��eye��NULL�ł��B"), _T("error"), MB_OK);
#endif
	}

	// �����_���W�Z�b�g
	if(look != NULL) {
		SetLook(look);
	} else {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CCamera::SetParameter��look��NULL�ł��B"), _T("error"), MB_OK);
#endif
	}

	// ����x�N�g���Z�b�g
	if(up != NULL) {
		SetUp(up);
	} else {
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CCamera::SetParameter��up��NULL�ł��B"), _T("error"), MB_OK);
#endif	
	}
}

//����������������������������������������������������������������������������������������
//	Name        : ���_���W�Z�b�g
//	Description : �J�����̎��_���W���Z�b�g����
//	Arguments   : eye / ���_���W
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCamera::SetEye(D3DXVECTOR3& eye)
{
	SetEyeX(eye.x);
	SetEyeY(eye.y);
	SetEyeZ(eye.z);
}

//����������������������������������������������������������������������������������������
//	Name        : ���_���W�Z�b�g
//	Description : �J�����̎��_���W���Z�b�g����
//	Arguments   : eye / ���_���W
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCamera::SetEye(const D3DXVECTOR3& eye)
{
	SetEyeX(eye.x);
	SetEyeY(eye.y);
	SetEyeZ(eye.z);
}

//����������������������������������������������������������������������������������������
//	Name        : �����_���W�Z�b�g
//	Description : �J�����̒����_���W���Z�b�g����
//	Arguments   : look / �����_���W
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCamera::SetLook(D3DXVECTOR3& look)
{
	SetLookX(look.x);
	SetLookY(look.y);
	SetLookZ(look.z);
}

//����������������������������������������������������������������������������������������
//	Name        : �����_���W�Z�b�g
//	Description : �J�����̒����_���W���Z�b�g����
//	Arguments   : look / �����_���W
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCamera::SetLook(const D3DXVECTOR3& look)
{
	SetLookX(look.x);
	SetLookY(look.y);
	SetLookZ(look.z);
}

//����������������������������������������������������������������������������������������
//	Name        : ����x�N�g���Z�b�g
//	Description : �J�����̏���x�N�g�����Z�b�g����
//	Arguments   : up / ����x�N�g��
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCamera::SetUp(D3DXVECTOR3& up)
{
	SetUpX(up.x);
	SetUpY(up.y);
	SetUpZ(up.z);
}

//����������������������������������������������������������������������������������������
//	Name        : ����x�N�g���Z�b�g
//	Description : �J�����̏���x�N�g�����Z�b�g����
//	Arguments   : up / ����x�N�g��
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCamera::SetUp(const D3DXVECTOR3& up)
{
	SetUpX(up.x);
	SetUpY(up.y);
	SetUpZ(up.z);
}


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �u���b�N��������������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
bool CCamera::Initialize(void)
{
	m_bExist = true;
	m_type	= CT_FIXED;

	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �u���b�N���̎��㏈��������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCamera::Finalize(void)
{
}


//========================================================================================
//	End of File
//========================================================================================