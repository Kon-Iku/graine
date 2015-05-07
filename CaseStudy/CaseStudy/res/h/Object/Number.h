//========================================================================================
//		File        : Number.h
//		Program     : �����N���X
//
//		Description : �����N���X�̒�`
//
//		History     : 2014/11/27	�쐬�J�n
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
#include "../Object/Object2D.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CNumber : public CObject2D
{
// ===== �����o�萔
private:

// ===== �����o�ϐ�
private:

// ===== �����o�֐�
public:
	CNumber();				// �R���X�g���N�^
	virtual ~CNumber();		// �f�X�g���N�^
	
	void Init();		// �f�t�H���g�l�ŏ�����
	void Init(const D3DXVECTOR2& size);	// ������
	void Init(const float width, const float height);	// ������
	void Uninit();		// ��n��
	void Update();		// �X�V

	static CNumber* Create(const LPCTSTR pszFName);		// ����
	void Release();										// �j��

private:
	bool Initialize(const LPCTSTR pszFName);	// ������
	void Finalize();							// ��n��
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ���[�U�^��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
typedef std::vector<CNumber*>		LPNUMBER_ARRAY;		// �����N���X�̃��X�g
typedef LPNUMBER_ARRAY::iterator	LPNUMBER_ARRAY_IT;	// �����N���X���X�g�̃C�e���[�^


//========================================================================================
//	End of File
//========================================================================================