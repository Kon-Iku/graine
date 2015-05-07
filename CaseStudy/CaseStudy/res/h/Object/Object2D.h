//========================================================================================
//		File        : CObject2D.h
//		Program     : 2D�I�u�W�F�N�g�x�[�X
//
//		Description : 2D�I�u�W�F�N�g�x�[�X�̒�`
//					  ���_�F�|���S���̒���
//
//		History     : 2014/06/11	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================

#pragma once

#ifndef __USE_INPUT_OBJECT2D
#define __USE_INPUT_OBJECT2D
#endif

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../System/PreInclude.h"
#
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include <vector>
#include "../System/System.h"
#include "../System/Graphics.h"
#include "../System/Timer.h"
#include "../Object/Object.h"
#include "../Object/Texture.h"

#ifdef __USE_INPUT_OBJECT2D
#include "../System/Input.h"
#endif

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
const D3DMATERIAL9 DEFAULT_MATERIAL = {	// �ėp�}�e���A���ݒ�
	{1.0f, 1.0f, 1.0f, 1.0f},		// Diffuse
	{0.1f, 0.1f, 0.1f, 0.1f},		// Ambient
	{0.1f, 0.1f, 0.1f, 0.1f},		// Specular
	{0.1f, 0.1f, 0.1f, 0.1f},		// Emissive
	1.0f							// Power
};

// �����蔻��
enum _eCollision2D {
	COL2D_BOUNDINGBOX = 0,		// �o�E���f�B���O�{�b�N�X
	COL2D_BOUNDINGCIRCLE,		// �o�E���f�B���O�T�[�N��
	COL2D_SQUARECIRCLE,			// ��`�Ɖ~�Ƃ̓����蔻��(����Ώۂ��~�̏ꍇ, ��`����]���Ă��Ă���)
	COL2D_CIRCLESQUARE,			// ��`�Ɖ~�Ƃ̓����蔻��(����Ώۂ���`�̏ꍇ, ��`����]���Ă��Ă���)
	COL2D_SQUARESQUARE,			// ��`���m�̓����蔻��(��]���Ă��Ă���)

	MAX_COLLISION2D
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �\���̒�`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
typedef struct _tVertex3D
{
	D3DXVECTOR3	vtx;		// ���_���W
	D3DCOLOR	col;		// ���ˌ�
	D3DXVECTOR2	uv;			// �e�N�X�`�����W
} VERTEX3D;

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CObject2D : public CObject
{
// ===== �����o�ϐ�
protected:
	// 2D�I�u�W�F�N�g�f�[�^���X�g
	static struct OBJ2D_INFO
	{
		struct OBJ2D_INFO*	pPrev;			// ��O�̃f�[�^
		struct OBJ2D_INFO*	pNext;			// ���̃f�[�^
		LPDIRECT3DTEXTURE9	pTexture;		// �e�N�X�`��
		LPCSTR				pszFName;		// �e�N�X�`���t�@�C����
		D3DXIMAGE_INFO		info;			// �e�N�X�`�����
		DWORD				dwReference;	// ����e�N�X�`���̎g�p��
	}*					m_pObj2DInfoTop;
	
	LPDIRECT3DDEVICE9	m_pDevice;		// �f�o�C�X
	LPDIRECT3DTEXTURE9	m_pTexture;		// �e�N�X�`��
	OBJ2D_INFO*			m_pObj2DInfo;	// 2D�I�u�W�F�N�g�f�[�^

	VERTEX3D			m_vtx[4];		// ���_���
	D3DMATERIAL9		m_material;		// �}�e���A��
	D3DXVECTOR2			m_size;			// �I�u�W�F�N�g�T�C�Y
	D3DXVECTOR2			m_halfSize;		// �I�u�W�F�N�g�T�C�Y(����)
	D3DXVECTOR2			m_defSize;		// �I�u�W�F�N�g�̃f�t�H���g�T�C�Y
	D3DXVECTOR2			m_offset;		// �`��I�t�Z�b�g

	float				m_colRadius;	// �����蔻��p���a

// ===== �����o�֐�
public:
	CObject2D();			// �R���X�g���N�^
	virtual ~CObject2D();	// �f�X�g���N�^

	virtual void Init();		// �f�t�H���g�l�ŏ�����
	virtual void Init(const D3DXVECTOR2& size);	// �T�C�Y���w�肵�ď�����
	virtual void Init(const float width, const float height);	// �T�C�Y���w�肵�ď�����
	virtual void Init(const D3DXVECTOR2& size, const D3DXVECTOR3& pos);	// �T�C�Y���w�肵�ď�����
	virtual void Init(const float width, const float height,
						const float x, const float y, const float z);	// �T�C�Y���w�肵�ď�����
	virtual void Uninit();		// ��n��
	virtual void Update();		// �X�V
	virtual void Draw();		// �`��(�A���t�@����)
	virtual void DrawAlpha();	// �`��(�A���t�@�L��)
	virtual void DrawBillBoard(const D3DXVECTOR3& target);		// �r���{�[�h�`��(�A���t�@����)
	virtual void DrawBillBoardAlpha(const D3DXVECTOR3& target);	// �r���{�[�h�`��(�A���t�@�L��)

	static CObject2D* Create(const LPCTSTR pszFName);	// ����
	virtual void Release();								// �j��
	
	// ----- �Z�b�^�[
	virtual void SetColor(const D3DXVECTOR3& color);	// ���_�J���[�ݒ�(0�`255)
	virtual void SetAlpha(float alpha);					// ���ߓx�ݒ�(0�`255)
	virtual void SetColRadius(float radius) {m_colRadius = radius;}		// �����蔻��p���a�ݒ�

	// ----- �Q�b�^�[
	virtual D3DXVECTOR2 GetSize() const {return m_size;}			// �T�C�Y�擾
	virtual float GetWidth() const {return m_size.x;}				// �I�u�W�F�N�g���擾
	virtual float GetHeight() const {return m_size.y;}				// �I�u�W�F�N�g�����擾
	virtual D3DXVECTOR2 GetHalfSize() const {return m_halfSize;}	// �n�[�t�T�C�Y�擾
	virtual float GetHalfWidth() const {return m_halfSize.x;}		// �n�[�t�T�C�Y�擾(��)
	virtual float GetHalfHeight() const {return m_halfSize.y;}		// �n�[�t�T�C�Y�擾(����)
	virtual D3DXVECTOR2 GetDefaultSize() const {return m_defSize;}	// �f�t�H���g�T�C�Y�擾
	virtual float GetDefaultWidth() const {return m_defSize.x;}		// �f�t�H���g�T�C�Y�擾(��)
	virtual float GetDefaultHeight() const {return m_defSize.y;}	// �f�t�H���g�T�C�Y�擾(����)
	virtual D3DXVECTOR3 GetColor() const {return D3DCOLOR_RGBA_TO_RGB(m_vtx[0].col);}	// ���_�J���[�擾
	virtual float GetAlpha() const {return (float)D3DCOLOR_RGBA_TO_ALPHA(m_vtx[0].col);}	// ���ߓx�擾
	virtual float GetLeftPos() const {return m_pos.x - m_halfSize.x;}	// �I�u�W�F�N�g�̍��[���W���擾
	virtual float GetRightPos() const {return m_pos.x + m_halfSize.x;}	// �I�u�W�F�N�g�̉E�[���W���擾
	virtual float GetTopPos() const {return m_pos.y + m_halfSize.y;}	// �I�u�W�F�N�g�̏�[���W���擾
	virtual float GetBottomPos() const {return m_pos.y - m_halfSize.y;}	// �I�u�W�F�N�g�̉��[���W���擾
	virtual VERTEX3D GetVertex(int num) const {return m_vtx[num];}		// ���_���擾
	virtual float GetColRadius() const {return m_colRadius;}			// �����蔻��p���a�擾
	
	// ----- �s��ϊ�
	virtual void Translation(const D3DXVECTOR3& vec);	// ���Έړ�
	virtual void TranslationX(float x);					// ���Έړ�(X���W)
	virtual void TranslationY(float y);					// ���Έړ�(Y���W)
	virtual void TranslationZ(float z);					// ���Έړ�(Z���W)
	virtual void Translate(const D3DXVECTOR3& pos);		// ��Έړ�
	virtual void TranslateX(float x);					// ��Έړ�(X���W)
	virtual void TranslateY(float y);					// ��Έړ�(Y���W)
	virtual void TranslateZ(float z);					// ��Έړ�(Z���W)
	virtual void Rotation(const D3DXVECTOR3& angle);	// ���Ή�]
	virtual void RotationX(float angle);				// ���Ή�](X��)
	virtual void RotationY(float angle);				// ���Ή�](Y��)
	virtual void RotationZ(float angle);				// ���Ή�](Z��)
//	virtual void RotationQuaternion(const D3DXVECTOR3* pV, float angle);	// ���΃N�H�[�^�j�I����]
	virtual void Rotate(const D3DXVECTOR3& angle);		// ��Ή�]
	virtual void RotateX(float angle);					// ��Ή�](X��)
	virtual void RotateY(float angle);					// ��Ή�](Y��)
	virtual void RotateZ(float angle);					// ��Ή�](Z��)
//	virtual void RotateQuaternion(const D3DXVECTOR3* pV, float angle);		// ��΃N�H�[�^�j�I����]
	virtual void Scaling(const D3DXVECTOR3& scale);		// ���Ίg�k
	virtual void ScalingX(float x);						// ���Ίg�k(X����)
	virtual void ScalingY(float y);						// ���Ίg�k(Y����)
	virtual void Scale(const D3DXVECTOR3& scale);		// ��Ίg�k
	virtual void ScaleX(float x);						// ��Ίg�k(X����)
	virtual void ScaleY(float y);						// ��Ίg�k(Y����)

	// ----- �����蔻��֘A
	virtual bool CollisionEnter(int id, const CObject2D* pCol);		// ���������u��
	virtual bool CollisionStay(int id, const CObject2D* pCol);		// �������Ă����
	virtual bool CollisionExit(int id, const CObject2D* pCol);		// ���ꂽ�u��

	// ----- �t�F�[�h�֘A
	virtual void FadeColor(int nFade);			// �t�F�[�h����(���)
	virtual bool FadeInColor(int nFade);		// �t�F�[�h�C��(����)
	virtual bool FadeOutColor(int nFade);		// �t�F�[�h�A�E�g(����)
	virtual void FadeAlpha(int nFade);			// ���߃t�F�[�h����(���)
	virtual bool FadeInAlpha(int nFade);		// ���߃t�F�[�h�C��(����)
	virtual bool FadeOutAlpha(int nFade);		// ���߃t�F�[�h�A�E�g(����)

	virtual void Resize(const D3DXVECTOR2& size);	// �I�u�W�F�N�g�T�C�Y�ύX
	virtual void Resize(const float width, const float height);	// �I�u�W�F�N�g�T�C�Y�ύX

	virtual void UVDivision(int num, int width, int height);		// UV�l�𕪊�
	virtual void FrameAnimation(int start, int end, int width, int height, double time);	// �t���[���A�j���[�V����(�b�w��ŃA�j���[�V����)

protected:
	virtual bool Initialize(const LPCTSTR pszFName);	// ������
	virtual void Finalize();							// ��n��
	
	virtual HRESULT Load(const LPDIRECT3DDEVICE9 pDevice, const LPCTSTR pszFName);	// �e�N�X�`���ǂݍ���

	// �����蔻��
	virtual bool BoundingBox(const CObject2D* pCol);			// �o�E���f�B���O�{�b�N�X
	virtual bool BoundingCircle(const CObject2D* pCol);			// �o�E���f�B���O�T�[�N��
	virtual bool JudgeSquareCircle(const CObject2D* pCol);		// ��`�Ɖ~�Ƃ̓����蔻��(����Ώۂ��~�̏ꍇ, ��`����]���Ă��Ă���)
	virtual bool JudgeCircleSquare(const CObject2D* pCol);		// ��`�Ɖ~�Ƃ̓����蔻��(����Ώۂ���`�̏ꍇ, ��`����]���Ă��Ă���)
	virtual bool JudgeSquareSquare(const CObject2D* pCol);		// ��`���m�̓����蔻��(��]���Ă��Ă���)
	
#ifdef __USE_INPUT_OBJECT2D
	// ----- �}�E�X����֘A
	virtual bool CheckMouseOverBox();					// �}�E�X�Ƃ̓����蔻��(�l�p�`)
	virtual bool CheckMouseOverCircle(float radius);	// �}�E�X�Ƃ̓����蔻��(�~)
#endif
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ���[�U�^��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
typedef std::vector<CObject2D*>		LPOBJECT2D_ARRAY;		// �I�u�W�F�N�g�QD�N���X�̃��X�g
typedef LPOBJECT2D_ARRAY::iterator	LPOBJECT2D_ARRAY_IT;	// �I�u�W�F�N�g�QD�N���X���X�g�̃C�e���[�^


//========================================================================================
//	End of File
//========================================================================================