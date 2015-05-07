//========================================================================================
//		File        : CObject2Dsub.h
//		Program     : �I�u�W�F�N�g�x�[�X�̊g��
//
//		Description : �I�u�W�F�N�g�x�[�X�̊g���A�Ȃ�ƂȂ��x�[�X�ɐG�肽���Ȃ������B
//
//		History     : 2015/5/6	�쐬�J�n
//						   
//
//																Author : ���񂽂܃Y
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
#include "../System/Timer.h"

#include "../Object/Object2D.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\

#define		GRAVITY_DEFAULT	(9.8f)	// ���ʂقǑ������Q�[�����ۂ��Ȃ�
#define		GRAVITY_CASE_1	(0.1f)
#define		GRAVITY_CASE_2	(0.1f)
#define		GRAVITY_ZERO	(0.00f)

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CObject2Dsub : public CObject2D
{
protected:
	int			m_nPhase;			// ���

	D3DXVECTOR3 m_accel;			// ��������
	
	// ----- �A�j���[�V�����p
	CTimer*		m_pTimer;
	float		m_fLastTime;
	int			m_nCurrentFrame;
	bool		m_bAnimeInit;		// �A�j���̏������t���O

	float		m_fGravity;			// �d��
	float		m_fGAccel;			// �������x
public:
	CObject2Dsub();			// �R���X�g���N�^

	virtual void Update();
	void TimeAnimation(int minNo, int maxNo, int width, int height,float time);	// �b�����Ƃ̃p���p���A�j��

	// ----- �Z�b�^�[
	void SetGravity(float g);

	// ----- �Q�b�^�[
	float GetGravity(){ return m_fGravity; }
};
//========================================================================================
//	End of File
//========================================================================================