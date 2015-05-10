//========================================================================================
//		File        : PlayerGroups.h
//		Program     : �v���C���[�ǂ�
//
//		Description : �v���C���[�ǂ��ʂ̓���
//						�v���C���[�̏������͂����ł͂Ȃ��Ƃ��ł����
//						�v���C���[�̌�n���͂����ňꊇ�ōs��
//
//		History     : 2015/05/11	�쐬�J�n
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
#include "../Object/Player.h"
#include "../Object/Object2Dsub.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CPlayersGroup : public CObject2D
{
private:
		
	int								m_nCurrentControllNo;		// ���݂̔ԍ�

	std::list<CPlayer*>				m_list;						// �틤(�ǉ��ƍ폜���y�����Ƃ�������������)
	std::list<CPlayer*>::iterator	m_listIt;					// �C�e���[�^(�����ς��g�����������炱���ɗp�ӂ��Ƃ�)

	// ----- �f�o�b�O�p
	LPCTSTR		m_lpTex;							// Player�̃e�N�X�`��

public:	
	CPlayersGroup();
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	void AddPlayer(CPlayer* p);							// �W����Player��ǉ�

	// ----- �Z�b�^�[
	//void SetControllPlayer(int no);
	void SetTexture(const LPCTSTR tex){m_lpTex = tex;}

	// ----- �Q�b�^�[
	int GetGroupSize(){return m_list.size();}
	CPlayer* GetPlayer(int no);
	
	// ----- �f�o�b�O�p
	void		AddPlayer();						// �v���C���[�ǉ�
	void		RedusePlayer();						// �v���C���[�폜

	static CPlayersGroup* Create(const LPCTSTR pszFName);	// ����
};
//========================================================================================
//	End of File
//========================================================================================