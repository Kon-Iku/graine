//========================================================================================
//		File        : CObject.h
//		Program     : �I�u�W�F�N�g�x�[�X
//
//		Description : �I�u�W�F�N�g�x�[�X�̒�`
//
//		History     : 2014/06/11	�쐬�J�n
//						   06/18	�����o�ϐ��ǉ�
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
#include "../System/System.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CObject
{
// ===== �����o�ϐ�
protected:
	D3DXMATRIX	m_world;		// ���[���h�ϊ��s��
	D3DXVECTOR3	m_pos;			// ���݈ʒu
	D3DXVECTOR3	m_rot;			// ��]�p(0�`359)
	D3DXVECTOR3	m_scale;		// �g�k��
	bool		m_bExist;		// ���݃t���O
	bool		m_bDraw;		// �`��t���O

// ===== �����o�֐�
public:
	CObject();				// �R���X�g���N�^
	virtual ~CObject();		// �f�X�g���N�^

	virtual void Init() = 0;		// ������
	virtual void Uninit() = 0;		// ��n��
	virtual void Update() = 0;		// �X�V
	virtual void Draw() = 0;		// �`��
	virtual void Release();			// ���

	// ----- �Q�b�^�[
	virtual D3DXMATRIX GetMatrix() const {return m_world;}	// ���[���h�ϊ��s��擾
	virtual D3DXVECTOR3 GetPosition() const {return m_pos;}	// ���݈ʒu�擾
	virtual float GetPosX() const {return m_pos.x;}			// ���݈ʒu�擾(X���W)
	virtual float GetPosY() const {return m_pos.y;}			// ���݈ʒu�擾(Y���W)
	virtual float GetPosZ() const {return m_pos.z;}			// ���݈ʒu�擾(Z���W)
	virtual D3DXVECTOR3 GetRotation() const {return m_rot;}	// ��]�p�擾
	virtual float GetRotX() const {return m_rot.x;}			// ��]�p�擾(X����)
	virtual float GetRotY() const {return m_rot.y;}			// ��]�p�擾(Y����)
	virtual float GetRotZ() const {return m_rot.z;}			// ��]�p�擾(Z����)
	virtual D3DXVECTOR3 GetScale() const {return m_scale;}	// �g�k���擾
	virtual float GetScaleX() const {return m_scale.x;}		// �g�k���擾(X����)
	virtual float GetScaleY() const {return m_scale.y;}		// �g�k���擾(Y����)
	virtual float GetScaleZ() const {return m_scale.z;}		// �g�k���擾(Z����)
	virtual bool GetExistFlg() const {return m_bExist;}		// ���݃t���O�擾
	virtual bool GetDrawFlg() const {return m_bDraw;}		// �`��t���O�擾
	
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
	virtual void ScalingZ(float z);						// ���Ίg�k(Z����)
	virtual void Scale(const D3DXVECTOR3& scale);		// ��Ίg�k
	virtual void ScaleX(float x);						// ��Ίg�k(X����)
	virtual void ScaleY(float y);						// ��Ίg�k(Y����)
	virtual void ScaleZ(float z);						// ��Ίg�k(Z����)

	virtual void Enable() {m_bExist = true;}			// ���݂�L����
	virtual void Disable() {m_bExist = false;}			// ���݂𖳌���
	virtual void RenderEnable() {m_bDraw = true;}		// �`��@�\��L����
	virtual void RenderDisable() {m_bDraw = false;}		// �`��@�\�𖳌���

protected:
	virtual bool Initialize();		// ������
	virtual void Finalize() = 0;	// ��n��
	virtual void RecalcMatrix();	// ���[���h�ϊ��s��Čv�Z
};


//========================================================================================
//	End of File
//========================================================================================