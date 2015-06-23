//========================================================================================
//		File        : Object2D.cpp
//		Program     : 2D�I�u�W�F�N�g�x�[�X
//
//		Description : 2D�I�u�W�F�N�g�x�[�X�̎���
//					  ���_�F�|���S���̒���
//
//		History     : 2014/06/11	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/PreInclude.h"
#
#include <math.h>
#include "../../h/Object/Object2D.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �����o���̐錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
CObject2D::OBJ2D_INFO* CObject2D::m_pObj2DInfoTop = NULL;


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CObject2D::CObject2D()
{
	m_pDevice		= NULL;
	m_pTexture		= NULL;
	m_pObj2DInfo	= NULL;

	// ���_�f�[�^������
	for(int i = 0; i < 4; ++i)
	{
		m_vtx[i].vtx = DEFAULT_VTX3D_VTX[i];	// ��ʑS��
		m_vtx[i].col = DEFAULT_VTX_COL_W;		// ���F
		m_vtx[i].uv  = DEFAULT_VTX_UV[i];		// UV�S��
	}
	
	m_size		= D3DXVECTOR2(0.0f, 0.0f);
	m_halfSize	= D3DXVECTOR2(0.0f, 0.0f);
	m_defSize	= D3DXVECTOR2(0.0f, 0.0f);
	m_offset	= D3DXVECTOR2(0.0f, 0.0f);
}

//����������������������������������������������������������������������������������������
//	Name        : �f�X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CObject2D::~CObject2D()
{
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �I�u�W�F�N�g���f�t�H���g�l�ŏ���������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::Init()
{
	// ----- ���_�f�[�^������
	for(int i = 0; i < 4; ++i)
	{
		m_vtx[i].vtx = DEFAULT_VTX3D_VTX[i];	// ��ʑS��
		m_vtx[i].col = DEFAULT_VTX_COL_W;		// ���F
		m_vtx[i].uv  = DEFAULT_VTX_UV[i];		// UV�S��
	}
	m_material	= DEFAULT_MATERIAL;		// �}�e���A��

	Resize(D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT));

	m_bExist	= true;		// ���݃t���O
	m_bDraw		= true;		// �`��t���O
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �I�u�W�F�N�g������������
//	Arguments   : size / �I�u�W�F�N�g�T�C�Y
//				  pos  / �o���ʒu(�I�u�W�F�N�g�̒���)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::Init(const D3DXVECTOR2& size, const D3DXVECTOR3& pos)
{
	// ----- ���_�f�[�^������
	CObject2D::Init();

	// ----- �T�C�Y�ݒ�
	Resize(size);

	// ----- �`��ʒu�ݒ�
	Translate(pos);
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �I�u�W�F�N�g�̌�n��������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::Uninit(void)
{
	memset(m_vtx, 0, sizeof(m_vtx));	// ���_���N���A
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �I�u�W�F�N�g���X�V����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::Update(void)
{
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �I�u�W�F�N�g�𓧉ߖ����ŕ`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::Draw()
{
	// ----- �`��ΏۂłȂ���Ζ��`��
	if(!m_bDraw)
		return;

	// ----- ���[���h�ϊ��s���ݒ�
    m_pDevice->SetTransform(D3DTS_WORLD, &m_world);

	// ----- ���_�t�H�[�}�b�g�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX3D);

	// ----- �e�햳����
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	// ���C�e�B���O������

	// ----- �w�i�e�N�X�`���̐ݒ�y�у|���S���̕`��
	m_pDevice->SetMaterial(&m_material);
	m_pDevice->SetTexture(0, m_pTexture);
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_vtx, sizeof(VERTEX3D));
	
	// ----- �e��L����
	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);	// ���C�e�B���O�L����
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �I�u�W�F�N�g�𓧉ߗL��ŕ`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::DrawAlpha()
{
	// ----- �`��ΏۂłȂ���Ζ��`��
	if(!m_bDraw)
		return;

	// ----- ���[���h�ϊ��s���ݒ�
    m_pDevice->SetTransform(D3DTS_WORLD, &m_world);

	// ----- ���_�t�H�[�}�b�g�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX3D);

	// ----- �e�햳����
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	// ���C�e�B���O������
	
	// ----- �A���t�@ �u�����h�L����
    m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ----- �A���t�@ �e�X�g�L����
    m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
    m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
    m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	
	// ----- �w�i�e�N�X�`���̐ݒ�y�у|���S���̕`��
	m_pDevice->SetMaterial(&m_material);
	m_pDevice->SetTexture(0, m_pTexture);
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_vtx, sizeof(VERTEX3D));
	
    // ----- �A���t�@ �u�����h������
    m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	// ----- �A���t�@ �e�X�g������
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	
	// ----- �e��L����
	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);	// ���C�e�B���O�L����
}

//����������������������������������������������������������������������������������������
//	Name        : �r���{�[�h�`��
//	Description : �I�u�W�F�N�g�𓧉ߖ����Ńr���{�[�h�Ƃ��ĕ`�悷��
//	Arguments   : target / �Ώۂ̍��W
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::DrawBillBoard(const D3DXVECTOR3& target)
{
	// ----- �`��ΏۂłȂ���Ζ��`��
	if(!m_bDraw)
		return;

	// ----- �r���{�[�h��]�s����Z�o
	// ����
	D3DXVECTOR3 pos = GetPosition();
	D3DXMATRIX rot;

	// �t�s��Z�o
	D3DXMatrixIdentity(&rot);
	D3DXMatrixLookAtLH(&rot, &target, &pos, &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixInverse(&rot, NULL, &rot);

	// ��]�s��݂̂ɂ���
	rot._41 = 0.0f;
	rot._42 = 0.0f;
	rot._43 = 0.0f;

	// ----- �r���{�[�h����
	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, pos.x, pos.y, pos.z);
	D3DXMatrixIdentity(&m_world);
	m_world *= rot * trans;

	// ----- �`�揈��
	Draw();
}

//����������������������������������������������������������������������������������������
//	Name        : �r���{�[�h�`��
//	Description : �I�u�W�F�N�g�𓧉ߗL��Ńr���{�[�h�Ƃ��ĕ`�悷��
//	Arguments   : target / �Ώۂ̍��W
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::DrawBillBoardAlpha(const D3DXVECTOR3& target)
{
	// ----- �`��ΏۂłȂ���Ζ��`��
	if(!m_bDraw)
		return;

	// ----- �r���{�[�h��]�s����Z�o
	// ����
	D3DXVECTOR3 pos = GetPosition();
	D3DXMATRIX rot;

	// �t�s��Z�o
	D3DXMatrixIdentity(&rot);
	D3DXMatrixLookAtLH(&rot, &target, &pos, &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixInverse(&rot, NULL, &rot);

	// ��]�s��݂̂ɂ���
	rot._41 = 0.0f;
	rot._42 = 0.0f;
	rot._43 = 0.0f;

	// ----- �r���{�[�h����
	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, pos.x, pos.y, pos.z);
	D3DXMatrixIdentity(&m_world);
	m_world *= rot * trans;

	// ----- �`�揈��
	DrawAlpha();
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �I�u�W�F�N�g���X�N���[�����W�ɓ��ߖ����ŕ`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::DrawScreen()
{
	// ----- �`��ΏۂłȂ���Ζ��`��
	if(!m_bDraw)
		return;

	// ----- ���_�t�H�[�}�b�g�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX2D);
	
	// ----- �w�i�e�N�X�`���̐ݒ�y�у|���S���̕`��
	VERTEX2D	vtx[4];
	for(int i = 0; i < 4; ++i) {
		vtx[i].vtx	= D3DXVECTOR4(	m_vtx[i].vtx.x,
									m_vtx[i].vtx.y,
									m_vtx[i].vtx.z,
									1.0f);
		vtx[i].col	= m_vtx[i].col;
		vtx[i].uv	= m_vtx[i].uv;

		D3DXVec4Transform(&vtx[i].vtx, &vtx[i].vtx, &m_world);
	}
	m_pDevice->SetTexture(0, m_pTexture);
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(VERTEX2D));
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �I�u�W�F�N�g���X�N���[�����W�ɓ��ߗL��ŕ`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::DrawScreenAlpha()
{
	// ----- �`��ΏۂłȂ���Ζ��`��
	if(!m_bDraw)
		return;

	// ----- ���_�t�H�[�}�b�g�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX2D);

	 // ----- �A���t�@ �u�����h�L����
    m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			
	// ----- �w�i�e�N�X�`���̐ݒ�y�у|���S���̕`��
	VERTEX2D	vtx[4];
	for(int i = 0; i < 4; ++i) {
		vtx[i].vtx	= D3DXVECTOR4(	m_vtx[i].vtx.x,
									m_vtx[i].vtx.y,
									m_vtx[i].vtx.z,
									1.0f);
		vtx[i].col	= m_vtx[i].col;
		vtx[i].uv	= m_vtx[i].uv;

		D3DXVec4Transform(&vtx[i].vtx, &vtx[i].vtx, &m_world);
	}
	m_pDevice->SetTexture(0, m_pTexture);
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(VERTEX2D));
	
    // ----- �A���t�@ �u�����h������
    m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : �I�u�W�F�N�g�𐶐�����
//	Arguments   : pszFName / �ǂݍ��݃t�@�C����
//	Returns     : �I�u�W�F�N�g�f�[�^
//����������������������������������������������������������������������������������������
CObject2D* CObject2D::Create(const LPCTSTR pszFName)
{
	// ----- �ϐ��錾
	CObject2D* pObj;

	// ----- ����������
	pObj = new CObject2D();
	if(pObj)
	{
		if(!pObj->Initialize(pszFName))
		{
			SAFE_DELETE(pObj);
		}
	}

	return pObj;
}

//����������������������������������������������������������������������������������������
//	Name        : ���_�J���[�ݒ�
//	Description : 2D�I�u�W�F�N�g�̒��_�J���[��ݒ肷��(0�`255)
//	Arguments   : color / ���_�J���[(RGB)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::SetColor(const D3DXVECTOR3& color)
{
	// ���_�J���[�ݒ�
	for(int i = 0; i < 4; ++i) {
		m_vtx[i].col = D3DCOLOR_RGBA((int)color.x, (int)color.y, (int)color.z, D3DCOLOR_RGBA_TO_ALPHA(m_vtx[i].col));
	}
}

//����������������������������������������������������������������������������������������
//	Name        : ���ߓx�ݒ�
//	Description : 2D�I�u�W�F�N�g�̓��ߓx��ݒ肷��(0�`255)
//	Arguments   : alpha / ���ߓx
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::SetAlpha(int alpha)
{
	// ���ߓx�ݒ�
	for(int i = 0; i < 4; ++i) {
		m_vtx[i].col = D3DCOLOR_RGBA(D3DCOLOR_RGBA_TO_R(m_vtx[i].col),
									 D3DCOLOR_RGBA_TO_G(m_vtx[i].col),
									 D3DCOLOR_RGBA_TO_B(m_vtx[i].col),
									 alpha);
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �ړ�����
//	Description : �I�u�W�F�N�g�𑊑Έʒu�ֈړ�����
//	Arguments   : vec / �ړ���
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::Translation(const D3DXVECTOR3& vec)
{
	CObject::Translation(vec);
}

//����������������������������������������������������������������������������������������
//	Name        : �ړ�����
//	Description : �I�u�W�F�N�g�𑊑Έʒu(X����)�ֈړ�����
//	Arguments   : x / �ړ���
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::TranslationX(float x)
{
	CObject::TranslationX(x);
}

//����������������������������������������������������������������������������������������
//	Name        : �ړ�����
//	Description : �I�u�W�F�N�g�𑊑Έʒu(Y����)�ֈړ�����
//	Arguments   : y / �ړ���
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::TranslationY(float y)
{
	CObject::TranslationY(y);
}

//����������������������������������������������������������������������������������������
//	Name        : �ړ�����
//	Description : �I�u�W�F�N�g�𑊑Έʒu(Z����)�ֈړ�����
//	Arguments   : z / �ړ���
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::TranslationZ(float z)
{
	CObject::TranslationZ(z);
}

//����������������������������������������������������������������������������������������
//	Name        : �ړ�����
//	Description : �I�u�W�F�N�g���Έʒu�ֈړ�����
//	Arguments   : pos / �ړ�����W
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::Translate(const D3DXVECTOR3& pos)
{
	CObject::Translate(pos);
}

//����������������������������������������������������������������������������������������
//	Name        : �ړ�����
//	Description : �I�u�W�F�N�g���Έʒu(X����)�ֈړ�����
//	Arguments   : x / �ړ�����W
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::TranslateX(float x)
{
	CObject::TranslateX(x);
}

//����������������������������������������������������������������������������������������
//	Name        : �ړ�����
//	Description : �I�u�W�F�N�g���Έʒu(Y����)�ֈړ�����
//	Arguments   : y / �ړ�����W
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::TranslateY(float y)
{
	CObject::TranslateY(y);
}

//����������������������������������������������������������������������������������������
//	Name        : �ړ�����
//	Description : �I�u�W�F�N�g���Έʒu(Z����)�ֈړ�����
//	Arguments   : z / �ړ�����W
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::TranslateZ(float z)
{
	CObject::TranslateZ(z);
}

//����������������������������������������������������������������������������������������
//	Name        : ��]����
//	Description : �I�u�W�F�N�g�𑊑ΓI�ɉ�]����
//	Arguments   : angle / ��]�p
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::Rotation(const D3DXVECTOR3& angle)
{
	CObject::Rotation(angle);
}

//����������������������������������������������������������������������������������������
//	Name        : ��]����
//	Description : �I�u�W�F�N�g�𑊑ΓI��X����]����
//	Arguments   : angle / ��]�p
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::RotationX(float angle)
{
	CObject::RotationX(angle);
}

//����������������������������������������������������������������������������������������
//	Name        : ��]����
//	Description : �I�u�W�F�N�g�𑊑ΓI��Y����]����
//	Arguments   : angle / ��]�p
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::RotationY(float angle)
{
	CObject::RotationY(angle);
}

//����������������������������������������������������������������������������������������
//	Name        : ��]����
//	Description : �I�u�W�F�N�g�𑊑ΓI��Z����]����
//	Arguments   : angle / ��]�p
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::RotationZ(float angle)
{
	CObject::RotationZ(angle);
}

//����������������������������������������������������������������������������������������
//	Name        : ��]����
//	Description : �I�u�W�F�N�g�𑊑ΓI�ɃN�H�[�^�j�I���ŔC�ӎ���]����
//	Arguments   : pV    / ��]���̕����x�N�g��
//				  angle / ��]�p
//	Returns     : None.
//����������������������������������������������������������������������������������������
//void CObject2D::RotationQuaternion(const D3DXVECTOR3* pV, float angle)
//{
//	CObject::RotationQuaternion(pV, angle);
//}

//����������������������������������������������������������������������������������������
//	Name        : ��]����
//	Description : �I�u�W�F�N�g���ΓI�ɉ�]����
//	Arguments   : angle / ��]�p
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::Rotate(const D3DXVECTOR3& angle)
{
	CObject::Rotate(angle);
}

//����������������������������������������������������������������������������������������
//	Name        : ��]����
//	Description : �I�u�W�F�N�g���ΓI��X����]����
//	Arguments   : angle / ��]�p
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::RotateX(float angle)
{
	CObject::RotateX(angle);
}

//����������������������������������������������������������������������������������������
//	Name        : ��]����
//	Description : �I�u�W�F�N�g���ΓI��Y����]����
//	Arguments   : angle / ��]�p
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::RotateY(float angle)
{
	CObject::RotateY(angle);
}

//����������������������������������������������������������������������������������������
//	Name        : ��]����
//	Description : �I�u�W�F�N�g���ΓI��Z����]����
//	Arguments   : angle / ��]�p
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::RotateZ(float angle)
{
	CObject::RotateZ(angle);
}

//����������������������������������������������������������������������������������������
//	Name        : ��]����
//	Description : �I�u�W�F�N�g���ΓI�ɃN�H�[�^�j�I���ŔC�ӎ���]����
//	Arguments   : pV    / ��]���̕����x�N�g��
//				  angle / ��]�p
//	Returns     : None.
//����������������������������������������������������������������������������������������
//void CObject2D::RotateQuaternion(const D3DXVECTOR3* pV, float angle)
//{
//	CObject::RotateQuaternion(pV, angle);
//}

//����������������������������������������������������������������������������������������
//	Name        : �g�k����
//	Description : �I�u�W�F�N�g�𑊑ΓI�Ɋg�k����
//	Arguments   : scale / �g�k��
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::Scaling(const D3DXVECTOR3& scale)
{
	// ----- �g�k����
	CObject::Scaling(scale);

	// ----- �T�C�Y�X�V
	m_size = D3DXVECTOR2(m_size.x * m_scale.x, m_size.y * m_scale.y);
	m_halfSize = m_size * 0.5f;
}

//����������������������������������������������������������������������������������������
//	Name        : �g�k����
//	Description : �I�u�W�F�N�g�𑊑ΓI��X�����Ɋg�k����
//	Arguments   : x / �g�k��
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::ScalingX(float x)
{
	// ----- �g�k����
	CObject::ScalingX(x);

	// ----- �T�C�Y�X�V
	m_size = D3DXVECTOR2(m_size.x * m_scale.x, m_size.y * m_scale.y);
	m_halfSize = m_size * 0.5f;
}

//����������������������������������������������������������������������������������������
//	Name        : �g�k����
//	Description : �I�u�W�F�N�g�𑊑ΓI��Y�����Ɋg�k����
//	Arguments   : y / �g�k��
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::ScalingY(float y)
{
	// ----- �g�k����
	CObject::ScalingY(y);

	// ----- �T�C�Y�X�V
	m_size = D3DXVECTOR2(m_size.x * m_scale.x, m_size.y * m_scale.y);
	m_halfSize = m_size * 0.5f;
}

//����������������������������������������������������������������������������������������
//	Name        : �g�k����
//	Description : �I�u�W�F�N�g���ΓI�Ɋg�k����
//	Arguments   : scale / �g�k��
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::Scale(const D3DXVECTOR3& scale)
{
	// ----- �g�k����
	CObject::Scale(scale);
	
	// ----- �T�C�Y�X�V
	m_size = D3DXVECTOR2(m_defSize.x * m_scale.x, m_defSize.y * m_scale.y);
	m_halfSize = m_size * 0.5f;
}

//����������������������������������������������������������������������������������������
//	Name        : �g�k����
//	Description : �I�u�W�F�N�g���ΓI��X�����Ɋg�k����
//	Arguments   : x / �g�k��
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::ScaleX(float x)
{
	// ----- �g�k����
	CObject::ScaleX(x);
	
	// ----- �T�C�Y�X�V
	m_size = D3DXVECTOR2(m_defSize.x * m_scale.x, m_defSize.y * m_scale.y);
	m_halfSize = m_size * 0.5f;
}

//����������������������������������������������������������������������������������������
//	Name        : �g�k����
//	Description : �I�u�W�F�N�g���ΓI��Y�����Ɋg�k����
//	Arguments   : y / �g�k��
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::ScaleY(float y)
{
	// ----- �g�k����
	CObject::ScaleY(y);
	
	// ----- �T�C�Y�X�V
	m_size = D3DXVECTOR2(m_defSize.x * m_scale.x, m_defSize.y * m_scale.y);
	m_halfSize = m_size * 0.5f;
}

//����������������������������������������������������������������������������������������
//	Name        : UV�l�𕪊�
//	Description : UV�l��C�ӂ̐��ɕ������A���݂̐��l��UV�l��ݒ肷��
//				  ������E�E��E�����E�E���̏��ɐ��l�𐔂���
//	Arguments   : num    / �Q�Ɣԍ�
//				  width  / ��������
//				  height / �c������
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::UVDivision(int num, int width, int height)
{
	// ----- UV�l���Z�o
	float left		= (1.0f / width) * ((num) % width);
	float right		= (1.0f / width) * ((num) % width) + (1.0f / width);
	float top		= (1.0f / height) * ((num) / width);
	float bottom	= (1.0f / height) * ((num) / width) + (1.0f / height);

	// ----- UV�l��ݒ�
	m_vtx[0].uv = D3DXVECTOR2(left,  top);
	m_vtx[1].uv = D3DXVECTOR2(right, top);
	m_vtx[2].uv = D3DXVECTOR2(left,  bottom);
	m_vtx[3].uv = D3DXVECTOR2(right, bottom);
}

//����������������������������������������������������������������������������������������
//	Name        : �t�F�[�h����
//	Description : �Ώۂ�2D�I�u�W�F�N�g��C�ӂ̊Ԋu�Ńt�F�[�h��������
//	Arguments   : nFade / �t�F�[�h�Ԋu
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::FadeColor(int nFade)
{
	// ----- �ϐ��錾
	DWORD dwTempRed;		// r�l�i�[�o�b�t�@
	DWORD dwTempGreen;		// g�l�i�[�o�b�t�@
	DWORD dwTempBlue;		// b�l�i�[�o�b�t�@

	// ----- ����������
	dwTempRed	= 0;
	dwTempGreen	= 0;
	dwTempBlue	= 0;

	// ----- �G���[����
	if(nFade < 0)
		nFade = 0;
	if(nFade > 255)
		nFade = 255;
	
	// ----- �t�F�[�h�C��
	for(int nCntVtx = 0; nCntVtx < 4; nCntVtx ++)
	{
		dwTempRed	= ((m_vtx + nCntVtx)->col & 0x00ff0000);					// r�l���o
		dwTempGreen	= ((m_vtx + nCntVtx)->col & 0x0000ff00);					// g�l���o
		dwTempBlue	= ((m_vtx + nCntVtx)->col & 0x000000ff);					// b�l���o
		(m_vtx + nCntVtx)->col ^= (dwTempRed | dwTempGreen | dwTempBlue);		// �A���t�@�l�N���A
		dwTempRed	>>= 16;														// �����֕ϊ�
		dwTempGreen	>>= 8;														// �����֕ϊ�
		dwTempRed = nFade;
		dwTempGreen = nFade;
		dwTempBlue = nFade;
		dwTempRed	<<= 16;														// r�ʒu�֖߂�
		dwTempGreen	<<= 8;														// g�ʒu�֖߂�
		(m_vtx + nCntVtx)->col |= (dwTempRed | dwTempGreen | dwTempBlue);		// �t�F�[�h���f
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �t�F�[�h�C��
//	Description : �Ώۂ�2D�I�u�W�F�N�g��C�ӂ̊Ԋu�Ńt�F�[�h�C������
//	Arguments   : nFade / �t�F�[�h�Ԋu
//	Returns     : �����t���O(true:����)
//����������������������������������������������������������������������������������������
bool CObject2D::FadeInColor(int nFade)
{
	// ----- �ϐ��錾
	DWORD dwTempRed;		// r�l�i�[�o�b�t�@
	DWORD dwTempGreen;		// g�l�i�[�o�b�t�@
	DWORD dwTempBlue;		// b�l�i�[�o�b�t�@
	bool  complete;			// �����t���O

	// ----- ����������
	dwTempRed	= 0;
	dwTempGreen	= 0;
	dwTempBlue	= 0;
	complete	= false;

	// ----- �G���[����
	if(nFade < 0)
		nFade = 0;
	if(nFade > 255)
		nFade = 255;
	
	// ----- �t�F�[�h�C��
	for(int nCntVtx = 0; nCntVtx < 4; nCntVtx ++)
	{
		dwTempRed	= ((m_vtx + nCntVtx)->col & 0x00ff0000);					// r�l���o
		dwTempGreen	= ((m_vtx + nCntVtx)->col & 0x0000ff00);					// g�l���o
		dwTempBlue	= ((m_vtx + nCntVtx)->col & 0x000000ff);					// b�l���o
		(m_vtx + nCntVtx)->col ^= (dwTempRed | dwTempGreen | dwTempBlue);		// �A���t�@�l�N���A
		dwTempRed	>>= 16;														// �����֕ϊ�
		dwTempGreen	>>= 8;														// �����֕ϊ�
		if(dwTempRed < 255)														// �t�F�[�h�X�V
			dwTempRed += nFade;
		if(dwTempGreen < 255)													// �t�F�[�h�X�V
			dwTempGreen += nFade;
		if(dwTempBlue < 255)													// �t�F�[�h�X�V
			dwTempBlue += nFade;
		if(dwTempRed >= 255)													// �G���[����
		{
			dwTempRed = 255;
			complete  = true;
		}
		if(dwTempGreen >= 255)													// �G���[����
		{
			dwTempGreen = 255;
			complete    = true;
		}
		if(dwTempBlue >= 255)													// �G���[����
		{
			dwTempBlue = 255;
			complete   = true;
		}
		dwTempRed	<<= 16;														// r�ʒu�֖߂�
		dwTempGreen	<<= 8;														// g�ʒu�֖߂�
		(m_vtx + nCntVtx)->col |= (dwTempRed | dwTempGreen | dwTempBlue);		// �t�F�[�h���f
	}

	return complete;
}

//����������������������������������������������������������������������������������������
//	Name        : �t�F�[�h�A�E�g
//	Description : �Ώۂ�2D�I�u�W�F�N�g��C�ӂ̊Ԋu�Ńt�F�[�h�A�E�g����
//	Arguments   : nFade / �t�F�[�h�Ԋu
//	Returns     : �����t���O(true:����)
//����������������������������������������������������������������������������������������
bool CObject2D::FadeOutColor(int nFade)
{
	// ----- �ϐ��錾
	DWORD dwTempRed;		// r�l�i�[�o�b�t�@
	DWORD dwTempGreen;		// g�l�i�[�o�b�t�@
	DWORD dwTempBlue;		// b�l�i�[�o�b�t�@
	int   nRed;				// r�l�i�[�o�b�t�@
	int   nGreen;			// g�l�i�[�o�b�t�@
	int   nBlue;			// b�l�i�[�o�b�t�@
	bool  complete;			// �����t���O

	// ----- ����������
	dwTempRed	= 0;
	dwTempGreen	= 0;
	dwTempBlue	= 0;
	nRed		= 0;
	nGreen		= 0;
	nBlue		= 0;
	complete	= false;

	// ----- �G���[����
	if(nFade < 0)
		nFade = 0;
	if(nFade > 255)
		nFade = 255;
	
	// ----- �t�F�[�h�A�E�g
	for(int nCntVtx = 0; nCntVtx < 4; nCntVtx ++)
	{
		dwTempRed	= ((m_vtx + nCntVtx)->col & 0x00ff0000);					// r�l���o
		dwTempGreen	= ((m_vtx + nCntVtx)->col & 0x0000ff00);					// g�l���o
		dwTempBlue	= ((m_vtx + nCntVtx)->col & 0x000000ff);					// b�l���o
		(m_vtx + nCntVtx)->col ^= (dwTempRed | dwTempGreen | dwTempBlue);		// �A���t�@�l�N���A
		nRed	= dwTempRed   >> 16;											// �����֕ϊ�
		nGreen	= dwTempGreen >> 8;												// �����֕ϊ�
		nBlue	= dwTempBlue;													// �����֕ϊ�
		if(nRed > 0)															// �t�F�[�h�X�V
			nRed -= nFade;
		if(nGreen > 0)															// �t�F�[�h�X�V
			nGreen -= nFade;
		if(nBlue > 0)															// �t�F�[�h�X�V
			nBlue -= nFade;
		if(nRed <= 0)															// �G���[����
		{
			nRed	 = 0;
			complete = true;
		}
		if(nGreen <= 0)															// �G���[����
		{
			nGreen	 = 0;
			complete = true;
		}
		if(nBlue <= 0)															// �G���[����
		{
			nBlue	 = 0;
			complete = true;
		}
		dwTempRed	= nRed   << 16;												// r�ʒu�֖߂�
		dwTempGreen	= nGreen << 8;												// g�ʒu�֖߂�
		dwTempBlue	= nBlue;													// b�ʒu�֖߂�
		(m_vtx + nCntVtx)->col |= (dwTempRed | dwTempGreen | dwTempBlue);		// �t�F�[�h���f
	}

	return complete;
}

//����������������������������������������������������������������������������������������
//	Name        : ���߃t�F�[�h����
//	Description : �Ώۂ�2D�I�u�W�F�N�g��C�ӂ̊Ԋu�œ��ߓI�Ƀt�F�[�h��������
//	Arguments   : nFade / �t�F�[�h�Ԋu
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::FadeAlpha(int nFade)
{
	// ----- �ϐ��錾
	DWORD dwTempAlpha;		// �A���t�@�l�i�[�o�b�t�@

	// ----- ����������
	dwTempAlpha = 0;

	// ----- �G���[����
	if(nFade < 0)
		nFade = 0;
	if(nFade > 255)
		nFade = 255;
	
	// ----- �t�F�[�h�C��
	for(int nCntVtx = 0; nCntVtx < 4; nCntVtx ++)
	{
		dwTempAlpha = ((m_vtx + nCntVtx)->col & 0xff000000);	// �A���t�@�l���o
		(m_vtx + nCntVtx)->col ^= dwTempAlpha;					// �A���t�@�l�N���A
		dwTempAlpha >>= 24;										// �����֕ϊ�
		dwTempAlpha = nFade;
		dwTempAlpha <<= 24;										// �A���t�@�ʒu�֖߂�
		(m_vtx + nCntVtx)->col |= dwTempAlpha;					// �t�F�[�h���f
	}
}

//����������������������������������������������������������������������������������������
//	Name        : ���߃t�F�[�h�C��
//	Description : �Ώۂ�2D�I�u�W�F�N�g��C�ӂ̊Ԋu�œ��ߓI�Ƀt�F�[�h�C������
//	Arguments   : nFade / �t�F�[�h�Ԋu
//	Returns     : �����t���O(true:����)
//����������������������������������������������������������������������������������������
bool CObject2D::FadeInAlpha(int nFade)
{
	// ----- �ϐ��錾
	DWORD dwTempAlpha;		// �A���t�@�l�i�[�o�b�t�@
	bool  complete;			// �����t���O

	// ----- ����������
	dwTempAlpha = 0;
	complete	= false;

	// ----- �G���[����
	if(nFade < 0)
		nFade = 0;
	if(nFade > 255)
		nFade = 255;
	
	// ----- �t�F�[�h�C��
	for(int nCntVtx = 0; nCntVtx < 4; nCntVtx ++)
	{
		dwTempAlpha = ((m_vtx + nCntVtx)->col & 0xff000000);	// �A���t�@�l���o
		(m_vtx + nCntVtx)->col ^= dwTempAlpha;					// �A���t�@�l�N���A
		dwTempAlpha >>= 24;										// �����֕ϊ�
		if(dwTempAlpha < 255)									// �t�F�[�h�X�V
			dwTempAlpha += nFade;
		if(dwTempAlpha >= 255)									// �G���[����
		{
			dwTempAlpha	= 255;
			complete	= true;
		}
		dwTempAlpha <<= 24;										// �A���t�@�ʒu�֖߂�
		(m_vtx + nCntVtx)->col |= dwTempAlpha;					// �t�F�[�h���f
	}

	return complete;
}

//����������������������������������������������������������������������������������������
//	Name        : ���߃t�F�[�h�A�E�g
//	Description : �Ώۂ�2D�I�u�W�F�N�g��C�ӂ̊Ԋu�œ��ߓI�Ƀt�F�[�h�A�E�g����
//	Arguments   : nFade / �t�F�[�h�Ԋu
//	Returns     : �����t���O(true:����)
//����������������������������������������������������������������������������������������
bool CObject2D::FadeOutAlpha(int nFade)
{
	// ----- �ϐ��錾
	DWORD dwTempAlpha;		// �A���t�@�l�i�[�o�b�t�@
	int   nAlpha;			// �A���t�@�l�i�[�o�b�t�@
	bool  complete;			// �����t���O

	// ----- ����������
	dwTempAlpha = 0;
	nAlpha		= 0;
	complete	= false;

	// ----- �G���[����
	if(nFade < 0)
		nFade = 0;
	if(nFade > 255)
		nFade = 255;
	
	// ----- �t�F�[�h�A�E�g
	for(int nCntVtx = 0; nCntVtx < 4; nCntVtx ++)
	{
		dwTempAlpha = ((m_vtx + nCntVtx)->col & 0xff000000);	// �A���t�@�l���o
		(m_vtx + nCntVtx)->col ^= dwTempAlpha;					// �A���t�@�l�N���A
		nAlpha = dwTempAlpha >> 24;								// �����֕ϊ�
		if(nAlpha > 0)											// �t�F�[�h�X�V
			nAlpha -= nFade;
		if(nAlpha <= 0)											// �G���[����
		{
			nAlpha	= 0;
			complete	= true;
		}
		dwTempAlpha = nAlpha << 24;								// �A���t�@�ʒu�֖߂�
		(m_vtx + nCntVtx)->col |= dwTempAlpha;					// �t�F�[�h���f
	}

	return complete;
}

//����������������������������������������������������������������������������������������
//	Name        : �I�u�W�F�N�g�T�C�Y�ύX
//	Description : �I�u�W�F�N�g�̃T�C�Y��ύX����
//	Arguments   : size / �I�u�W�F�N�g�T�C�Y
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::Resize(const D3DXVECTOR2& size)
{
	// ----- �T�C�Y�ݒ�
	m_size = size;
	m_halfSize = m_size * 0.5f;
	m_defSize = m_size;

	// ----- �I�u�W�F�N�g�ɔ��f
	m_vtx[0].vtx.x = -m_halfSize.x;
	m_vtx[0].vtx.y =  m_halfSize.y;
	m_vtx[1].vtx.x =  m_halfSize.x;
	m_vtx[1].vtx.y =  m_halfSize.y;
	m_vtx[2].vtx.x = -m_halfSize.x;
	m_vtx[2].vtx.y = -m_halfSize.y;
	m_vtx[3].vtx.x =  m_halfSize.x;
	m_vtx[3].vtx.y = -m_halfSize.y;
}

//����������������������������������������������������������������������������������������
//	Name        : �I�u�W�F�N�g�T�C�Y�ύX
//	Description : �I�u�W�F�N�g�̃T�C�Y��ύX����
//	Arguments   : width  / �I�u�W�F�N�g��
//				  height / �I�u�W�F�N�g����
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::Resize(const float width, const float height)
{
	Resize(D3DXVECTOR2(width, height));
}


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �I�u�W�F�N�g�f�[�^������������
//	Arguments   : pszFName / �ǂݍ��݃t�@�C����
//	Returns     : ����
//����������������������������������������������������������������������������������������
bool CObject2D::Initialize(const LPCTSTR pszFName)
{
	// ----- �I�u�W�F�N�g������
	if(!CObject::Initialize())
		return false;
	
	// ----- �e�N�X�`���ǂݍ���
	if(FAILED(Load(CGraphics::GetDevice(), pszFName)))
	{
		return false;
	}
	
	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �I�u�W�F�N�g�f�[�^�̌�n��������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CObject2D::Finalize(void)
{
	if (m_pObj2DInfo) {
		if (--(m_pObj2DInfo->dwReference) == 0) {
			SAFE_RELEASE(m_pObj2DInfo->pTexture);
			free((void*)m_pObj2DInfo->pszFName);
			for (OBJ2D_INFO* p = m_pObj2DInfoTop; p; p = p->pNext) {
				if (m_pObj2DInfo == p) {
					if (p->pPrev)
						m_pObj2DInfo->pPrev->pNext = p->pNext;
					else
						m_pObj2DInfoTop = p->pNext;
					if (p->pNext)
						p->pNext->pPrev = p->pPrev;
					break;
				}
			}
			delete m_pObj2DInfo;
		}
		m_pTexture   = NULL;
		m_pObj2DInfo = NULL;
	}
	m_pDevice = NULL;
}

//����������������������������������������������������������������������������������������
//	Name        : �e�N�X�`���ǂݍ���
//	Description : �e�N�X�`���f�[�^��ǂݍ���
//	Arguments   : pDevice  / �f�o�C�X
//				  pszFName / �e�N�X�`���t�@�C����
//	Returns     : None.
//����������������������������������������������������������������������������������������
HRESULT CObject2D::Load(const LPDIRECT3DDEVICE9 pDevice, const LPCTSTR pszFName)
{
	if (pDevice == NULL) {
		return E_POINTER;
	}

	// �f�o�C�X�ۑ�
	m_pDevice = pDevice;

//	Finalize();
	
	// �t�@�C�����ϊ�
	int strLen = lstrlen(pszFName);
	char* fname = new char[strLen + 1];
#ifdef _UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszFName, strLen, fname, strLen + 1, NULL, NULL);
	fname[strLen] = '\0';
#else
	lstrcpy(fname, pszFName);
	fname[strLen] = '\0';
#endif

	// �t�@�C�����������ꍇ������I��
	if (fname == NULL || *fname == '\0') {
		m_pTexture = NULL;
		delete fname;
		return S_OK;
	}

	// �e�N�X�`���v�[�����`�F�b�N
	for (OBJ2D_INFO* p = m_pObj2DInfoTop; p; p = p->pNext) {
		if (_stricmp(p->pszFName, fname) == 0) {
			++(p->dwReference);
			m_pTexture = p->pTexture;
			m_pObj2DInfo = p;
			delete fname;
			return S_OK;
		}
	}

	// �t�@�C�����̕������쐬
	LPSTR pszDup = _strdup(fname);
	if (pszDup == NULL) {
		delete fname;
		return E_OUTOFMEMORY;
	}

	// �e�N�X�`���t�@�C����ǂݍ���
	D3DXIMAGE_INFO info;
	HRESULT hr = D3DXCreateTextureFromFileExA(pDevice, fname,
		D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT,
		D3DX_DEFAULT, 0, &info, NULL, &m_pTexture);
	if (FAILED(hr)) {
		free(pszDup);
		delete fname;
		return hr;
	}

	// �e�N�X�`�� �v�[���ɒǉ�
	m_pObj2DInfo = new OBJ2D_INFO;
	if (m_pObj2DInfo == NULL) {
		free(pszDup);
		delete fname;
		return E_OUTOFMEMORY;
	}

	m_pObj2DInfo->pPrev = NULL;
	m_pObj2DInfo->pNext = m_pObj2DInfoTop;
	if (m_pObj2DInfoTop)
		m_pObj2DInfoTop->pPrev = m_pObj2DInfo;
	m_pObj2DInfoTop = m_pObj2DInfo;

	m_pObj2DInfo->pTexture = m_pTexture;
	m_pObj2DInfo->pszFName = pszDup;
	m_pObj2DInfo->info = info;
	m_pObj2DInfo->dwReference = 1;
	m_offset = D3DXVECTOR2(0.0f, 0.0f);
	m_size = D3DXVECTOR2((float)info.Width, (float)info.Height);
	
	delete fname;

	return hr;
}

#ifdef __USE_INPUT_OBJECT2D
//����������������������������������������������������������������������������������������
//	Name        : �}�E�X�Ƃ̓����蔻��(�l�p�`)
//	Description : �}�E�X�J�[�\�����I�u�W�F�N�g(�|���T�C�Y)�Ɠ������Ă��邩�`�F�b�N����
//	Arguments   : None.
//	Returns     : ���茋��(true:�������Ă���)
//����������������������������������������������������������������������������������������
bool CObject2D::CheckMouseOverBox()
{
	// ----- ���O����
	POINT curPos = Input::GetCurPos();	// �}�E�X�J�[�\���̍��W
	
	// ----- ���W�n�ϊ�
	curPos.x -= (int)(SCREEN_WIDTH * 0.5f);
	curPos.y = SCREEN_HEIGHT - curPos.y;
	curPos.y -= (int)(SCREEN_HEIGHT * 0.5f);

	// ----- �����蔻��
	if(	curPos.x > GetLeftPos()  &&
		curPos.x < GetRightPos() &&
		curPos.y > GetTopPos()   &&
		curPos.y < GetBottomPos()) {
		return true;
	}

	return false;
}

//����������������������������������������������������������������������������������������
//	Name        : �}�E�X�Ƃ̓����蔻��(�~)
//	Description : �}�E�X�J�[�\�����I�u�W�F�N�g(�w�蔼�a�T�C�Y)�Ɠ������Ă��邩�`�F�b�N����
//	Arguments   : radius / ���肷�锼�a
//	Returns     : ���茋��(true:�������Ă���)
//����������������������������������������������������������������������������������������
bool CObject2D::CheckMouseOverCircle(float radius)
{
	// ----- ���O����
	POINT curPos = Input::GetCurPos();	// �}�E�X�J�[�\���̍��W
	
	// ----- ���W�n�ϊ�
	curPos.x -= (int)(SCREEN_WIDTH * 0.5f);
	curPos.y = SCREEN_HEIGHT - curPos.y;
	curPos.y -= (int)(SCREEN_HEIGHT * 0.5f);

	// ----- �}�E�X�ƃI�u�W�F�N�g�̋������Z�o
	float x = curPos.x - m_pos.x;
	float y = curPos.y - m_pos.y;
	float dist = sqrt((x * x) + (y * y));

	// ----- �����蔻��
	if(dist < radius) {
		return true;
	}

	return false;
}
#endif


//========================================================================================
//	End of File
//========================================================================================