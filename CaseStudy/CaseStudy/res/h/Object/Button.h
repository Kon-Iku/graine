//========================================================================================
//		File        : Button.h
//		Program     : �{�^���x�[�X
//
//		Description : �{�^���x�[�X�̒�`
//
//		History     : 2015/05/29	�쐬�J�n
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
#include "../Object/Object2D.h"


enum
{
	B_PHASE_WAIT = 0,
	B_PHASE_CHOICE,
	B_PHASE_ENTER,
};

using namespace std;

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CButton : public CObject2D
{
private:
	
	int				m_nPhase;
	string			m_strName;
	
public:
	virtual void Init(D3DXVECTOR2 pos,D3DXVECTOR3 size);
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	// ----- �Q�b�^�[
	int GetPhase(){return m_nPhase;}
	string GetName(){return m_strName;}
	

	// ----- �Z�b�^�[
	void SetPhase(int no){m_nPhase = no;}
	void SetName(string str){m_strName = str;}

	CButton();
	static CButton* Create(const LPCTSTR pszFName);	// ����
};
//========================================================================================
//	End of File
//========================================================================================