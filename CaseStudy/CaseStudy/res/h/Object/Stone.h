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
#include "../Object/Flower.h"
#include "../Object/Stage.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
const int STONE_ANIME_SIZE_X = 1;	// �e�N�X�`��
const int STONE_ANIME_SIZE_Y = 1;

const float STONE_POS_DEFAULT_X = -200;
const float STONE_POS_DEFAULT_Y = 100;

const float STONE_SIZE_X = 512;
const float STONE_SIZE_Y = 512;

enum
{
	STONE_PHASE_INIT = 10,
	STONE_PHASE_START,
	STONE_PHASE_FLOWER,
	STONE_PHASE_WAIT,
	STONE_PHASE_UNINIT
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CStone : public CFlower
{
private:
	CCharacter *m_col;
	LPCTSTR		m_lpCol;		// Player�̃e�N�X�`��

	static const LPCTSTR COL_TEX_FILENAME;

	bool Initialize(const LPCTSTR pszFName);	// ������
protected:
		
public:
	CStone();
	virtual void Init(D3DXVECTOR3 pos,D3DXVECTOR3 dir);			// ������
	virtual void Uninit();
	virtual void Update();
	virtual void Animation();// �A�j��			����N���X�ɂ������������̂���
	virtual void Draw();
	static CStone* Create(const LPCTSTR pszFName);			// ����

	// ----- �Z�b�^�[
	void SetPhase(int no){m_nPhase = no;}

	// ----- �Q�b�^�[
	int GetPhase(){return m_nPhase;}
	CCharacter* GetCol(){return m_col;}

};
 
//========================================================================================
//	End of File
//========================================================================================