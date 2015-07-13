//========================================================================================
//		File        : Flower.h
//		Program     : ��
//
//		Description : 
//
//		History     : 2015/05/26	�쐬�J�n
//						   
//
//																Author : ���񂽂܃Y
//========================================================================================


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/Input.h"
#include "../../h/Object/Stone.h"

//========================================================================================
// �萔��`
//========================================================================================
const LPCTSTR CStone::COL_TEX_FILENAME = {
	_T("res/img/GameScene/Object/block.png"),
};

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CStone::CStone()
{
	m_nPhase = STONE_PHASE_INIT;
}
//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : ������
//	Arguments   : 
//	Returns     : 
//����������������������������������������������������������������������������������������
void CStone::Init(D3DXVECTOR3 pos,D3DXVECTOR3 dir)
{
	
	// �L�����N�^�[�̏�����
	CCharacter::Init();

	Resize(D3DXVECTOR2(STONE_SIZE_X,STONE_SIZE_Y));
	pos += dir * (STONE_SIZE_Y / 3);
	Translate(pos);

	m_angle = AngleOf2Vector(dir,D3DXVECTOR3(0,1,0));

	m_col->Init(D3DXVECTOR2(STONE_SIZE_X / 2, STONE_SIZE_Y / 2),
			pos);
	m_col->UVDivision(0, 1, 1);

	if(dir.x > 0){
		RotateZ(-(float)m_angle);
		m_col->RotateZ(-(float)m_angle);
	}
	if(dir.x < 0){
		RotateZ((float)m_angle);
		m_col->RotateZ((float)m_angle);
	}

	// �A�j���[�V����������
	StartAnimation();

	UVDivision(0, STONE_ANIME_SIZE_X, STONE_ANIME_SIZE_Y);
}
//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : ������
//	Arguments   : 
//	Returns     : 
//����������������������������������������������������������������������������������������
void CStone::Uninit()
{
	CCharacter::Uninit();

	m_col->Uninit();
}
//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : �I�u�W�F�N�g�𐶐�����
//	Arguments   : pszFName / �ǂݍ��݃t�@�C����
//	Returns     : �I�u�W�F�N�g�f�[�^
//����������������������������������������������������������������������������������������
CStone* CStone::Create(const LPCTSTR pszFName)
{
	// ----- �ϐ��錾
	CStone* pObj;
	// ----- ����������
	pObj = new CStone();
	if (pObj)
	{
		if (!pObj->Initialize(pszFName))
		{
			SAFE_DELETE(pObj);
		}
	}

	return pObj;
}
//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �I�u�W�F�N�g������������
//	Arguments   : pszFName / �t�@�C����
//	Returns     : ����
//����������������������������������������������������������������������������������������
bool CStone::Initialize(const LPCTSTR pszFName)
{
	// ----- �e�N�X�`���ǂݍ���
	if (!CCharacter::Initialize(pszFName))
		return false;

	m_col = CCharacter::Create(COL_TEX_FILENAME);
	if (!m_col)
		return false;
	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �����ȍX�V
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CStone::Update()
{	

	switch(m_nPhase)
	{
	case STONE_PHASE_INIT:
		m_nPhase++;
		break;
	case STONE_PHASE_START:
		m_nPhase++;
		break;
	case STONE_PHASE_FLOWER:
		break;
	case STONE_PHASE_WAIT:
		break;
	case STONE_PHASE_UNINIT:
		break;
	}

	Translate(m_pos);

	Animation();

}
//����������������������������������������������������������������������������������������
//	Name        : �A�j��
//	Description : �A�j���[�����
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CStone::Animation()
{
	// ��Ԃɂ���ăA�j���[�V�����ω�
	FrameAnimation(1, 1, 1, 1, 0.5f);
}
//����������������������������������������������������������������������������������������
//	Name        : �A�j��
//	Description : �A�j���[�����
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CStone::Draw()
{
	DrawAlpha();
	//m_col->DrawAlpha();
}

//========================================================================================
//	End of File
//========================================================================================