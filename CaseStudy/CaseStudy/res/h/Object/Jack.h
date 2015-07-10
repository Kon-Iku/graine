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
const int JACK_ANIME_SIZE_X = 1;	// �e�N�X�`��
const int JACK_ANIME_SIZE_Y = 1;

const float JACK_POS_DEFAULT_X = -200;
const float JACK_POS_DEFAULT_Y = 100;

const float JACK_SIZE_X = 314;
const float JACK_SIZE_Y = 1024;

enum
{
	JACK_PHASE_INIT = 10,
	JACK_PHASE_START,
	JACK_PHASE_FLOWER,
	JACK_PHASE_WAIT,
	JACK_PHASE_UNINIT
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CJack : public CFlower
{
private:
	
protected:
		
public:
	CJack();
	virtual void Init(D3DXVECTOR3 pos,D3DXVECTOR3 dir);			// ������
	virtual void Uninit();
	virtual void Update();
	virtual void Animation();// �A�j��			����N���X�ɂ������������̂���
	virtual void Draw();
	static CJack* Create(const LPCTSTR pszFName);			// ����

	// ----- �Z�b�^�[
	void SetPhase(int no){m_nPhase = no;}

	// ----- �Q�b�^�[
	int GetPhase(){return m_nPhase;}

};
 
//========================================================================================
//	End of File
//========================================================================================