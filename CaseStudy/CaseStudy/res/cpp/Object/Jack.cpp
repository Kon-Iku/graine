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
#include "../../h/Object/Jack.h"

//========================================================================================
// �萔��`
//========================================================================================
const LPCTSTR CJack::COL_TEX_FILENAME = {
	_T("res/img/GameScene/Object/block.png"),
};

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CJack::CJack()
{
	m_nPhase = JACK_PHASE_INIT;
}
//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : ������
//	Arguments   : 
//	Returns     : 
//����������������������������������������������������������������������������������������
void CJack::Init(D3DXVECTOR3 pos,D3DXVECTOR3 dir)
{
	
	// �L�����N�^�[�̏�����
	CCharacter::Init();

	Resize(D3DXVECTOR2(JACK_SIZE_X,JACK_SIZE_Y));
	pos += dir * (JACK_SIZE_Y / 3);
	Translate(pos);

	m_angle = AngleOf2Vector(dir,D3DXVECTOR3(0,1,0));

	m_col->Init(D3DXVECTOR2(JACK_SIZE_X / 3, JACK_SIZE_Y / 1.5),pos);
	m_col->UVDivision(0, 1, 1);
	m_col->SetType(1);

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

	UVDivision(0, JACK_ANIME_SIZE_X, JACK_ANIME_SIZE_Y);
}
//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : ������
//	Arguments   : 
//	Returns     : 
//����������������������������������������������������������������������������������������
void CJack::Uninit()
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
CJack* CJack::Create(const LPCTSTR pszFName)
{
	// ----- �ϐ��錾
	CJack* pObj;
	// ----- ����������
	pObj = new CJack();
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
bool CJack::Initialize(const LPCTSTR pszFName)
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
void CJack::Update()
{	

	switch(m_nPhase)
	{
	case JACK_PHASE_INIT:
		m_nPhase++;
		break;
	case JACK_PHASE_START:
		m_nPhase++;
		break;
	case JACK_PHASE_FLOWER:
		break;
	case JACK_PHASE_WAIT:
		break;
	case JACK_PHASE_UNINIT:
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
void CJack::Animation()
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
void CJack::Draw()
{

	DrawAlpha();
	m_col->DrawAlpha();
}

//========================================================================================
//	End of File
//========================================================================================