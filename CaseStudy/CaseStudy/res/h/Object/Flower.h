//========================================================================================
//		File        : Player.h
//		Program     : �v���C���[
//
//		Description : �v���C���[�ʂ̓���
//
//		History     : 2015/05/6	�쐬�J�n
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
#include "../System/Input.h"
#include "../System/System.h"
#include "../Object/Character.h"
#include "../Object/Stage.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
const int FLOWER_ANIME_SIZE_X = 1;	// �e�N�X�`��
const int FLOWER_ANIME_SIZE_Y = 1;

const float FLOWER_POS_DEFAULT_X = -200;
const float FLOWER_POS_DEFAULT_Y = 100;

const float FLOWER_SIZE_X = 147;
const float FLOWER_SIZE_Y = 151;

enum
{
	FLOWER_PHASE_INIT = 0,
	FLOWER_PHASE_START,
	FLOWER_PHASE_FLOWER,
	FLOWER_PHASE_WAIT,
	FLOWER_PHASE_UNINIT
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CFlower : public CCharacter
{
private:
	CObject2D* m_kuki;
	
protected:
	double	m_angle;
	int		m_nPhase;

public:
	CFlower();
	virtual void Init(D3DXVECTOR3 pos,D3DXVECTOR3 dir,const LPCTSTR pszFName);			// ������
	virtual void Uninit();
	virtual void Update();
	virtual void Animation();// �A�j��			����N���X�ɂ������������̂���
	virtual void Draw();
	static CFlower* Create(const LPCTSTR pszFName);			// ����

	// ----- �Z�b�^�[
	void SetPhase(int no){m_nPhase = no;}

	// ----- �Q�b�^�[
	int GetPhase(){return m_nPhase;}

};

double AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B );
//========================================================================================
//	End of File
//========================================================================================