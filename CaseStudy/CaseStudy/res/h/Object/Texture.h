//========================================================================================
//		File        : Texture.h
//		Program     : �e�N�X�`���N���X
//
//		Description : �e�N�X�`���N���X�̒�`
//					  ���_�F�e�N�X�`���̍��㒸�_
//
//		History     : 2014/06/18	�쐬�J�n
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
#include <tchar.h>
#include "../System/System.h"
#include "../System/Graphics.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ���_�t�H�[�}�b�g( ���_���W / ���ˌ� / �e�N�X�`�����W )
#define FVF_VERTEX2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX3D	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

const D3DXVECTOR4	DEFAULT_VTX2D_VTX[4]		=	{	D3DXVECTOR4(               0.0f,                 0.0f, 0.0f, 1.0f),		// �f�t�H���g���_���W(��ʑS��)
														D3DXVECTOR4((float)SCREEN_WIDTH,                 0.0f, 0.0f, 1.0f),
														D3DXVECTOR4(               0.0f, (float)SCREEN_HEIGHT, 0.0f, 1.0f),
														D3DXVECTOR4((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, 1.0f),
													};
const D3DXVECTOR3	DEFAULT_VTX3D_VTX[4]		=	{	D3DXVECTOR3(               0.0f,                 0.0f, 0.0f),		// �f�t�H���g���_���W(��ʑS��)
														D3DXVECTOR3((float)SCREEN_WIDTH,                 0.0f, 0.0f),
														D3DXVECTOR3(               0.0f, (float)SCREEN_HEIGHT, 0.0f),
														D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f),
													};
const D3DCOLOR		DEFAULT_VTX_COL_W			=	D3DCOLOR_RGBA(255, 255, 255, 255);		// �f�t�H���g���ˌ�(���F������)
const D3DCOLOR		DEFAULT_VTX_COL_W_ALPHA		=	D3DCOLOR_RGBA(255, 255, 255, 0);		// �f�t�H���g���ˌ�(���F����)
const D3DCOLOR		DEFAULT_VTX_COL_B			=	D3DCOLOR_RGBA(0, 0, 0, 255);			// �f�t�H���g���ˌ�(���F������)
const D3DCOLOR		DEFAULT_VTX_COL_B_ALPHA		=	D3DCOLOR_RGBA(0, 0, 0, 0);				// �f�t�H���g���ˌ�(���F����)
const D3DXVECTOR2	DEFAULT_VTX_UV[4]			=	{	D3DXVECTOR2(0.0f, 0.0f),			// �f�t�H���g�e�N�X�`�����W(�摜�S��)
														D3DXVECTOR2(1.0f, 0.0f),
														D3DXVECTOR2(0.0f, 1.0f),
														D3DXVECTOR2(1.0f, 1.0f),
													};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �}�N����`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#define D3DCOLOR_RGBA_TO_R(x)		((x >> 16) & 0xff)	// R�l�𒊏o
#define D3DCOLOR_RGBA_TO_G(x)		((x >> 8) & 0xff)	// G�l�𒊏o
#define D3DCOLOR_RGBA_TO_B(x)		(x & 0xff)			// B�l�𒊏o
#define D3DCOLOR_RGBA_TO_RGB(x)		(D3DXVECTOR3((float)D3DCOLOR_RGBA_TO_R(x), (float)D3DCOLOR_RGBA_TO_G(x), (float)D3DCOLOR_RGBA_TO_B(x)))	// RGB�l�𒊏o
#define D3DCOLOR_RGBA_TO_ALPHA(x)	(((x >> 24) & 0xff))	// �A���t�@�l�𒊏o

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �\���̒�`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
typedef struct _tVertex2D
{
	D3DXVECTOR4	vtx;		// ���_���W
	D3DCOLOR	col;		// ���ˌ�
	D3DXVECTOR2	uv;			// �e�N�X�`�����W
} VERTEX2D;

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CTexture
{
// ===== �����o�ϐ�
protected:
	// �e�N�X�`���f�[�^���X�g
	static struct TEX_INFO
	{
		struct TEX_INFO*	pPrev;			// ��O�̃f�[�^
		struct TEX_INFO*	pNext;			// ���̃f�[�^
		LPDIRECT3DTEXTURE9	pTexture;		// �e�N�X�`��
		LPCSTR				pszFName;		// �e�N�X�`���t�@�C����
		D3DXIMAGE_INFO		info;			// �e�N�X�`�����
		DWORD				dwReference;	// ����e�N�X�`���̎g�p��
	}*					m_pTexInfoTop;
	
	LPDIRECT3DDEVICE9	m_pDevice;		// �f�o�C�X
	LPDIRECT3DTEXTURE9	m_pTexture;		// �e�N�X�`��
	TEX_INFO*			m_pTexInfo;		// �e�N�X�`���f�[�^

	VERTEX2D			m_vtx[4];		// ���_���
	D3DXVECTOR3			m_pos;			// ���݈ʒu(�e�N�X�`���̍��㒸�_)
	D3DXVECTOR2			m_size;			// �T�C�Y
	D3DXVECTOR2			m_offset;		// �`��I�t�Z�b�g

// ===== �����o�֐�
public:
	CTexture();				// �R���X�g���N�^
	virtual ~CTexture();	// �f�X�g���N�^

	void Init();		// �f�t�H���g�l�ŏ�����
	void Init(const D3DXVECTOR2& size);	// ������
	void Init(const float width, const float height);	// ������
	void Init(const D3DXVECTOR2& size, const D3DXVECTOR3& pos);	// ������
	void Init(const float width, const float height,
				const float x, const float y, const float z);	// ������
	void Uninit();		// ��n��
	void Draw();		// �`��(�A���t�@����)
	void DrawAlpha();	// �`��(�A���t�@�L��)

	static CTexture* Create(const LPCTSTR pszFName);		// ����
	void Release();											// �j��
	
	// ----- �Z�b�^�[
	void SetColor(const D3DXVECTOR3& color);			// ���_�J���[�ݒ�
	void SetAlpha(float alpha);							// ���ߓx�ݒ�
	
	// ----- �Q�b�^�[
	D3DXVECTOR3& GetPosition() {return m_pos;}				// ���݈ʒu�擾(�e�N�X�`���̍��㒸�_)
	float GetPosX() const {return m_pos.x;}					// ���݈ʒu�擾(X���W)
	float GetPosY() const {return m_pos.y;}					// ���݈ʒu�擾(Y���W)
	float GetPosZ() const {return m_pos.z;}					// ���݈ʒu�擾(Z���W)
	D3DXVECTOR2& GetSize() {return m_size;}					// �T�C�Y�擾
	float GetWidth() const {return m_size.x;}				// �e�N�X�`�����擾
	float GetHeight() const {return m_size.y;}				// �e�N�X�`�������擾
	D3DXVECTOR3 GetColor() {return D3DCOLOR_RGBA_TO_RGB(m_vtx[0].col);}	// ���_�J���[�擾
	float GetAlpha() const {return (float)D3DCOLOR_RGBA_TO_ALPHA(m_vtx[0].col);}	// ���ߓx�擾
	float GetLeftPos() const {return m_pos.x;}				// �I�u�W�F�N�g�̍��[���W���擾
	float GetRightPos() const {return m_pos.x + m_size.x;}	// �I�u�W�F�N�g�̉E�[���W���擾
	float GetTopPos() const {return m_pos.y;}				// �I�u�W�F�N�g�̏�[���W���擾
	float GetBottomPos() const {return m_pos.y + m_size.y;}	// �I�u�W�F�N�g�̉��[���W���擾

	// ----- �A�t�B���ϊ�
	void SetPosition(const D3DXVECTOR3& pos);			// ���݈ʒu�X�V(�e�N�X�`���̍��㒸�_)
	void SetPosition(const float x, const float y, const float z);		// ���݈ʒu�X�V(�e�N�X�`���̍��㒸�_)
	void SetPosX(const float x);						// ���݈ʒu�X�V(X���W)
	void SetPosY(const float y);						// ���݈ʒu�X�V(Y���W)
	void SetPosZ(const float z);						// ���݈ʒu�X�V(Z���W)
	void AddPosition(const D3DXVECTOR3& pos);			// ���݈ʒu�X�V
	void AddPosition(const float x, const float y, const float z);		// ���݈ʒu�X�V
	void AddPosX(const float x);						// ���݈ʒu�X�V(X���W)
	void AddPosY(const float y);						// ���݈ʒu�X�V(Y���W)
	void AddPosZ(const float z);						// ���݈ʒu�X�V(Z���W)
	void HorizonFlip();									// ���E���]
	void VerticalFlip();								// �㉺���]

	// ----- �t�F�[�h�֘A
	void FadeColor(int nFade);			// �t�F�[�h����(���)
	bool FadeInColor(int nFade);		// �t�F�[�h�C��(����)
	bool FadeOutColor(int nFade);		// �t�F�[�h�A�E�g(����)
	void FadeAlpha(int nFade);			// ���߃t�F�[�h����(���)
	bool FadeInAlpha(int nFade);		// ���߃t�F�[�h�C��(����)
	bool FadeOutAlpha(int nFade);		// ���߃t�F�[�h�A�E�g(����)
	
	void Resize(const D3DXVECTOR2& size);				// �e�N�X�`���T�C�Y�ύX
	void Resize(const float width, const float height);	// �e�N�X�`���T�C�Y�ύX
	
	void UVDivision(const int num, const int width, const int height);	// UV�l�𕪊�

protected:
	bool Initialize(const LPCTSTR pszFName);	// ������
	void Finalize();							// ��n��

	HRESULT Load(const LPDIRECT3DDEVICE9 pDevice, const LPCTSTR pszFName);	// �e�N�X�`���ǂݍ���

	void Update();		// �X�V
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ���[�U�^��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
typedef std::vector<CTexture*>		LPTEXTURE_ARRAY;		// �e�N�X�`���N���X�̃��X�g
typedef LPTEXTURE_ARRAY::iterator	LPTEXTURE_ARRAY_IT;		// �e�N�X�`���N���X���X�g�̃C�e���[�^


//========================================================================================
//	End of File
//========================================================================================