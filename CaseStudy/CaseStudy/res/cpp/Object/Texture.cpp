//========================================================================================
//		File        : Texture.cpp
//		Program     : �e�N�X�`���N���X
//
//		Description : �e�N�X�`���N���X�̎���
//					  ���_�F�e�N�X�`���̍��㒸�_
//
//		History     : 2014/06/18	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/PreInclude.h"
#
#include "../../h/Object/Texture.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �����o���̐錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
CTexture::TEX_INFO* CTexture::m_pTexInfoTop = NULL;


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CTexture::CTexture()
{
	m_pDevice	= NULL;
	m_pTexture	= NULL;
	m_pTexInfo	= NULL;

	// ���_�f�[�^������
	for(int i = 0; i < 4; ++i)
	{
		m_vtx[i].vtx = DEFAULT_VTX2D_VTX[i];	// ��ʑS��
		m_vtx[i].col = DEFAULT_VTX_COL_W;		// ���F
		m_vtx[i].uv  = DEFAULT_VTX_UV[i];		// UV�S��
	}
	
	m_pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size		= D3DXVECTOR2(0.0f, 0.0f);
	m_offset	= D3DXVECTOR2(0.0f, 0.0f);
}

//����������������������������������������������������������������������������������������
//	Name        : �f�X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CTexture::~CTexture()
{
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �e�N�X�`���f�[�^���f�t�H���g�l�ŏ���������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::Init()
{
	// ���_�f�[�^������
	for(int i = 0; i < 4; ++i)
	{
		m_vtx[i].vtx = DEFAULT_VTX2D_VTX[i];	// ��ʑS��
		m_vtx[i].col = DEFAULT_VTX_COL_W;		// ���F
		m_vtx[i].uv  = DEFAULT_VTX_UV[i];		// UV�S��
	}
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �e�N�X�`���f�[�^������������
//	Arguments   : size / �e�N�X�`���T�C�Y
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::Init(const D3DXVECTOR2& size)
{
	// ���_�f�[�^������
	Init();

	// �T�C�Y�ݒ�
	Resize(size);
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �e�N�X�`���f�[�^������������
//	Arguments   : width  / �e�N�X�`����
//				  height / �e�N�X�`������
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::Init(const float width, const float height)
{
	// ���_�f�[�^������
	Init(D3DXVECTOR2(width, height));
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �e�N�X�`���f�[�^������������
//	Arguments   : size / �e�N�X�`���T�C�Y
//				  pos  / �o���ʒu(�e�N�X�`���̍��㒸�_)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::Init(const D3DXVECTOR2& size, const D3DXVECTOR3& pos)
{
	// ���_�f�[�^������
	Init();

	// �`��ʒu�ݒ�
	SetPosition(pos);

	// �T�C�Y�ݒ�
	Resize(size);
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �e�N�X�`���f�[�^������������
//	Arguments   : width  / �e�N�X�`����
//				  height / �e�N�X�`������
//				  x      / �o���ʒu(X���W)
//				  y      / �o���ʒu(Y���W)
//				  z      / �o���ʒu(Z���W)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::Init(const float width, const float height, const float x, const float y, const float z)
{
	Init(D3DXVECTOR2(width, height), D3DXVECTOR3(x, y, z));
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �e�N�X�`���f�[�^�̌�n��������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::Uninit(void)
{
	memset(m_vtx, 0, sizeof(m_vtx));	// ���_���N���A
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �e�N�X�`���𓧉ߖ����ŕ`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::Draw()
{
	// ----- �f�o�C�X���ݒ肳��Ă��Ȃ���Ζ�����
	if(m_pDevice == NULL) return;

	// ----- ���_�t�H�[�}�b�g�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX2D);

	// ----- �w�i�e�N�X�`���̐ݒ�y�у|���S���̕`��
	m_pDevice->SetTexture(0, m_pTexture);
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_vtx, sizeof(VERTEX2D));
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �e�N�X�`���𓧉ߗL��ŕ`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::DrawAlpha()
{
	// ----- �f�o�C�X���ݒ肳��Ă��Ȃ���Ζ�����
	if(m_pDevice == NULL) return;

	// ----- ���_�t�H�[�}�b�g�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX2D);

	 // ----- �A���t�@ �u�����h�L����
    m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			
	// ----- �w�i�e�N�X�`���̐ݒ�y�у|���S���̕`��
	m_pDevice->SetTexture(0, m_pTexture);
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_vtx, sizeof(VERTEX2D));
	
    // ----- �A���t�@ �u�����h������
    m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : �e�N�X�`���f�[�^�𐶐�����
//	Arguments   : pszFName / �ǂݍ��݃t�@�C����
//	Returns     : �e�N�X�`���f�[�^
//����������������������������������������������������������������������������������������
CTexture* CTexture::Create(const LPCTSTR pszFName)
{
	// ----- �ϐ��錾
	CTexture* pTexture;

	// ----- ����������
	pTexture = new CTexture();
	if(pTexture)
	{
		if(!pTexture->Initialize(pszFName))
		{
			SAFE_DELETE(pTexture);
		}
	}

	return pTexture;
}

//����������������������������������������������������������������������������������������
//	Name        : �������
//	Description : �e�N�X�`���f�[�^���������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::Release()
{
	Finalize();
	delete this;
}

//����������������������������������������������������������������������������������������
//	Name        : ���_�J���[�ݒ�
//	Description : �e�N�X�`���̒��_�J���[��ݒ肷��
//	Arguments   : color / ���_�J���[(RGB)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::SetColor(const D3DXVECTOR3& color)
{
	// ���_�J���[�ݒ�
	for(int i = 0; i < 4; ++i)
		m_vtx[i].col = D3DCOLOR_RGBA((int)color.x, (int)color.y, (int)color.z, D3DCOLOR_RGBA_TO_ALPHA(m_vtx[i].col));
}

//����������������������������������������������������������������������������������������
//	Name        : ���ߓx�ݒ�
//	Description : �e�N�X�`���̓��ߓx��ݒ肷��
//	Arguments   : alpha / ���ߓx
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::SetAlpha(float alpha)
{
	// ���ߓx�ݒ�
	for(int i = 0; i < 4; ++i)
		m_vtx[i].col = D3DCOLOR_RGBA(D3DCOLOR_RGBA_TO_R(m_vtx[i].col),
									 D3DCOLOR_RGBA_TO_G(m_vtx[i].col),
									 D3DCOLOR_RGBA_TO_B(m_vtx[i].col),
									 (int)alpha);
}

//����������������������������������������������������������������������������������������
//	Name        : ���݈ʒu�X�V
//	Description : �e�N�X�`���̌��݈ʒu���X�V����
//	Arguments   : pos / �o���ʒu
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::SetPosition(const D3DXVECTOR3& pos)
{
	// ���݈ʒu�X�V
	m_pos = pos;

	// �e�N�X�`���ɔ��f
	Update();
}

//����������������������������������������������������������������������������������������
//	Name        : ���݈ʒu�X�V
//	Description : �e�N�X�`���̌��݈ʒu���X�V����
//	Arguments   : x / �o���ʒu(X���W)
//				  y / �o���ʒu(Y���W)
//				  z / �o���ʒu(Z���W)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::SetPosition(const float x, const float y, const float z)
{
	SetPosition(D3DXVECTOR3(x, y, z));
}

//����������������������������������������������������������������������������������������
//	Name        : ���݈ʒu�X�V
//	Description : �e�N�X�`���̌��݈ʒu(X���W)���X�V����
//	Arguments   : x / �o���ʒu(X���W)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::SetPosX(const float x)
{
	SetPosition(D3DXVECTOR3(x, m_pos.y, m_pos.z));
}

//����������������������������������������������������������������������������������������
//	Name        : ���݈ʒu�X�V
//	Description : �e�N�X�`���̌��݈ʒu(Y���W)���X�V����
//	Arguments   : y / �o���ʒu(Y���W)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::SetPosY(const float y)
{
	SetPosition(D3DXVECTOR3(m_pos.x, y, m_pos.z));
}

//����������������������������������������������������������������������������������������
//	Name        : ���݈ʒu�X�V
//	Description : �e�N�X�`���̌��݈ʒu(Z���W)���X�V����
//	Arguments   : z / �o���ʒu(Z���W)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::SetPosZ(const float z)
{
	SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y, z));
}

//����������������������������������������������������������������������������������������
//	Name        : ���݈ʒu�X�V
//	Description : �e�N�X�`�������݈ʒu����ړ�����
//	Arguments   : vec / �ړ���
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::AddPosition(const D3DXVECTOR3& vec)
{
	// ���݈ʒu�X�V
	m_pos += vec;

	// �e�N�X�`���ɔ��f
	Update();
}

//����������������������������������������������������������������������������������������
//	Name        : ���݈ʒu�X�V
//	Description : �e�N�X�`�������݈ʒu����ړ�����
//	Arguments   : x / �ړ���(X���W)
//				  y / �ړ���(Y���W)
//				  z / �ړ���(Z���W)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::AddPosition(const float x, const float y, const float z)
{
	AddPosition(D3DXVECTOR3(x, y, z));
}

//����������������������������������������������������������������������������������������
//	Name        : ���݈ʒu�X�V
//	Description : �e�N�X�`�������݈ʒu����X�����Ɉړ�����
//	Arguments   : x / �ړ���(X���W)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::AddPosX(const float x)
{
	AddPosition(D3DXVECTOR3(x, 0.0f, 0.0f));
}

//����������������������������������������������������������������������������������������
//	Name        : ���݈ʒu�X�V
//	Description : �e�N�X�`�������݈ʒu����Y�����Ɉړ�����
//	Arguments   : y / �ړ���(Y���W)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::AddPosY(const float y)
{
	AddPosition(D3DXVECTOR3(0.0f, y, 0.0f));
}

//����������������������������������������������������������������������������������������
//	Name        : ���E���]
//	Description : �e�N�X�`�������E���]����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::HorizonFlip()
{
	// ----- �ϐ��錾
	float tmp;

	// ----- ���]����
	tmp = m_vtx[0].uv.x;
	m_vtx[0].uv.x = m_vtx[1].uv.x;
	m_vtx[1].uv.x = tmp;
	tmp = m_vtx[2].uv.x;
	m_vtx[2].uv.x = m_vtx[3].uv.x;
	m_vtx[3].uv.x = tmp;
}

//����������������������������������������������������������������������������������������
//	Name        : �㉺���]
//	Description : �e�N�X�`�����㉺���]����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::VerticalFlip()
{
	// ----- �ϐ��錾
	float tmp;

	// ----- ���]����
	tmp = m_vtx[0].uv.y;
	m_vtx[0].uv.y = m_vtx[2].uv.y;
	m_vtx[2].uv.y = tmp;
	tmp = m_vtx[1].uv.y;
	m_vtx[1].uv.y = m_vtx[3].uv.y;
	m_vtx[3].uv.y = tmp;
}

//����������������������������������������������������������������������������������������
//	Name        : ���݈ʒu�X�V
//	Description : �e�N�X�`�������݈ʒu����Z�����Ɉړ�����
//	Arguments   : z / �ړ���(Z���W)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::AddPosZ(const float z)
{
	AddPosition(D3DXVECTOR3(0.0f, 0.0f, z));
}

//����������������������������������������������������������������������������������������
//	Name        : �t�F�[�h����
//	Description : �Ώۂ̃e�N�X�`����C�ӂ̊Ԋu�Ńt�F�[�h��������
//	Arguments   : nFade / �t�F�[�h�Ԋu
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::FadeColor(int nFade)
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
//	Description : �Ώۂ̃e�N�X�`����C�ӂ̊Ԋu�Ńt�F�[�h�C������
//	Arguments   : nFade / �t�F�[�h�Ԋu
//	Returns     : �����t���O(true:����)
//����������������������������������������������������������������������������������������
bool CTexture::FadeInColor(int nFade)
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
//	Description : �Ώۂ̃e�N�X�`����C�ӂ̊Ԋu�Ńt�F�[�h�A�E�g����
//	Arguments   : nFade / �t�F�[�h�Ԋu
//	Returns     : �����t���O(true:����)
//����������������������������������������������������������������������������������������
bool CTexture::FadeOutColor(int nFade)
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
//	Description : �Ώۂ̃e�N�X�`����C�ӂ̊Ԋu�œ��ߓI�Ƀt�F�[�h��������
//	Arguments   : nFade / �t�F�[�h�Ԋu
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::FadeAlpha(int nFade)
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
//	Description : �Ώۂ̃e�N�X�`����C�ӂ̊Ԋu�œ��ߓI�Ƀt�F�[�h�C������
//	Arguments   : nFade / �t�F�[�h�Ԋu
//	Returns     : �����t���O(true:����)
//����������������������������������������������������������������������������������������
bool CTexture::FadeInAlpha(int nFade)
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
//	Description : �Ώۂ̃e�N�X�`����C�ӂ̊Ԋu�œ��ߓI�Ƀt�F�[�h�A�E�g����
//	Arguments   : nFade / �t�F�[�h�Ԋu
//	Returns     : �����t���O(true:����)
//����������������������������������������������������������������������������������������
bool CTexture::FadeOutAlpha(int nFade)
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
//	Name        : �e�N�X�`���T�C�Y�ύX
//	Description : �e�N�X�`���̃T�C�Y��ύX����
//	Arguments   : size / �e�N�X�`���T�C�Y
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::Resize(const D3DXVECTOR2& size)
{
	// �T�C�Y�ݒ�
	m_size = size;

	// �e�N�X�`���ɔ��f
	Update();
}

//����������������������������������������������������������������������������������������
//	Name        : �e�N�X�`���T�C�Y�ύX
//	Description : �e�N�X�`���̃T�C�Y��ύX����
//	Arguments   : width  / �e�N�X�`����
//				  height / �e�N�X�`������
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::Resize(const float width, const float height)
{
	Resize(D3DXVECTOR2(width, height));
}

//����������������������������������������������������������������������������������������
//	Name        : UV�l�𕪊�
//	Description : UV�l��C�ӂ̐��ɕ������A���݂̐��l��UV�l��ݒ肷��
//				  �����ォ��E���Ɍ������Đ��l�𐔂���
//	Arguments   : num    / �Q�Ɛ��l
//				  width  / ��������
//				  height / �c������
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::UVDivision(const int num, const int width, const int height)
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


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �e�N�X�`���f�[�^������������
//	Arguments   : pszFName / �ǂݍ��݃t�@�C����
//	Returns     : ����
//����������������������������������������������������������������������������������������
bool CTexture::Initialize(const LPCTSTR pszFName)
{
	// ----- �e�N�X�`���ǂݍ���
	if(FAILED(Load(CGraphics::GetDevice(), pszFName)))
	{
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("CTexture::Initialize �e�N�X�`���̓ǂݍ��݂Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
		return false;
	}

	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �e�N�X�`���f�[�^�̌�n��������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::Finalize(void)
{
	if (m_pTexInfo) {
		if (--(m_pTexInfo->dwReference) == 0) {
			SAFE_RELEASE(m_pTexInfo->pTexture);
			free((void*)m_pTexInfo->pszFName);
			for (TEX_INFO* p = m_pTexInfoTop; p; p = p->pNext) {
				if (m_pTexInfo == p) {
					if (p->pPrev)
						m_pTexInfo->pPrev->pNext = p->pNext;
					else
						m_pTexInfoTop = p->pNext;
					if (p->pNext)
						p->pNext->pPrev = p->pPrev;
					break;
				}
			}
			delete m_pTexInfo;
		}
		m_pTexture = NULL;
		m_pTexInfo = NULL;
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
HRESULT CTexture::Load(const LPDIRECT3DDEVICE9 pDevice, const LPCTSTR pszFName)
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
	for (TEX_INFO* p = m_pTexInfoTop; p; p = p->pNext) {
		if (_stricmp(p->pszFName, fname) == 0) {
			++(p->dwReference);
			m_pTexture = p->pTexture;
			m_pTexInfo = p;
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
	m_pTexInfo = new TEX_INFO;
	if (m_pTexInfo == NULL) {
		free(pszDup);
		delete fname;
		return E_OUTOFMEMORY;
	}

	m_pTexInfo->pPrev = NULL;
	m_pTexInfo->pNext = m_pTexInfoTop;
	if (m_pTexInfoTop)
		m_pTexInfoTop->pPrev = m_pTexInfo;
	m_pTexInfoTop = m_pTexInfo;

	m_pTexInfo->pTexture = m_pTexture;
	m_pTexInfo->pszFName = pszDup;
	m_pTexInfo->info = info;
	m_pTexInfo->dwReference = 1;
	m_offset = D3DXVECTOR2(0.0f, 0.0f);
	m_size = D3DXVECTOR2((float)info.Width, (float)info.Height);
	
	delete fname;

	return hr;
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �e�N�X�`���f�[�^���X�V����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CTexture::Update(void)
{
	m_vtx[0].vtx.x = m_pos.x;
	m_vtx[0].vtx.y = m_pos.y;
	m_vtx[0].vtx.z = m_pos.z;
	m_vtx[1].vtx.x = m_pos.x + m_size.x;
	m_vtx[1].vtx.y = m_pos.y;
	m_vtx[1].vtx.z = m_pos.z;
	m_vtx[2].vtx.x = m_pos.x;
	m_vtx[2].vtx.y = m_pos.y + m_size.y;
	m_vtx[2].vtx.z = m_pos.z;
	m_vtx[3].vtx.x = m_pos.x + m_size.x;
	m_vtx[3].vtx.y = m_pos.y + m_size.y;
	m_vtx[3].vtx.z = m_pos.z;
}


//========================================================================================
//	End of File
//========================================================================================