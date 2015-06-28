//========================================================================================
//		File        : ChangeScene.cpp
//		Program     : �V�[���J�ڃV�X�e��
//
//		Description : �V�[���J�ڃV�X�e���̎���
//
//		History     : 2015/02/20	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/PreInclude.h"
#
#include <tchar.h>
#include "../../h/System/System.h"
#include "../../h/System/ChangeScene.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �O���[�o���ϐ��錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
static CChangeScene& g_changeScene = CChangeScene::GetInstance();		// �V�[���J�ڃV�X�e���̎��̐���

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �����o���̐錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ----- �����o�萔
// private:
const LPCTSTR CChangeScene::TEX_FILENAME[MAX_TEXLIST] = {
	_T("res/img/Fade.jpg"),		// �P�F�t�F�[�h�p�e�N�X�`���t�@�C����
};

// ----- �����o�ϐ�
// private:
CObject2D* CChangeScene::m_pNormalFade;


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �C���X�^���X�擾
//	Description : �V�[���J�ڃV�X�e���̃C���X�^���X���擾����
//	Arguments   : None.
//	Returns     : �V�[���J�ڃV�X�e��
//����������������������������������������������������������������������������������������
CChangeScene& CChangeScene::GetInstance()
{
	// ----- �C���X�^���X����
	static CChangeScene changeScene;

	return changeScene;
}

//����������������������������������������������������������������������������������������
//	Name        : �ʒu�ݒ�
//	Description : �P�F�t�F�[�h�p�I�u�W�F�N�g�̈ʒu��ݒ肷��
//	Arguments   : pos / �o���ʒu
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CChangeScene::SetNormalFadePos(const D3DXVECTOR3& pos)
{
	CreateNormalFade();

	m_pNormalFade->Translate(pos);
}

//����������������������������������������������������������������������������������������
//	Name        : ���_�J���[�ݒ�
//	Description : �P�F�t�F�[�h�p�I�u�W�F�N�g�̒��_�J���[��ݒ肷��(0�`255)
//	Arguments   : color / ���_�J���[(RGB)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CChangeScene::SetNormalFadeColor(const D3DXVECTOR3& color)
{
	CreateNormalFade();

	m_pNormalFade->SetColor(color);
}

//����������������������������������������������������������������������������������������
//	Name        : ���ߓx�ݒ�
//	Description : �P�F�t�F�[�h�p�I�u�W�F�N�g�̓��ߓx��ݒ肷��(0�`255)
//	Arguments   : alpha / ���ߓx
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CChangeScene::SetNormalFadeAlpha(int alpha)
{
	CreateNormalFade();

	m_pNormalFade->SetAlpha(alpha);
}

//����������������������������������������������������������������������������������������
//	Name        : �t�F�[�h�C��
//	Description : �P�F�œ��߂���t�F�[�h�C������
//	Arguments   : z     / �`��ʒu(Z���W)
//				  alpha / ���Z����A���t�@�l
//	Returns     : �����t���O(true:����)
//����������������������������������������������������������������������������������������
bool CChangeScene::NormalFadeIn(float z, int alpha)
{
	// ----- ���O����
	CreateNormalFade();		// �I�u�W�F�N�g����(�������Ȃ�)

	// ----- �t�F�[�h����
	bool ret = m_pNormalFade->FadeInAlpha(alpha);
	
	// ----- �`��ʒu����
	m_pNormalFade->TranslateZ(z);

	return ret;
}

//����������������������������������������������������������������������������������������
//	Name        : �t�F�[�h�A�E�g
//	Description : �P�F�œ��߂���t�F�[�h�A�E�g����
//	Arguments   : z     / �`��ʒu(Z���W)
//				  alpha / ���Z����A���t�@�l
//	Returns     : �����t���O(true:����)
//����������������������������������������������������������������������������������������
bool CChangeScene::NormalFadeOut(float z, int alpha)
{
	// ----- ���O����
	CreateNormalFade();		// �I�u�W�F�N�g����(�������Ȃ�)

	// ----- �t�F�[�h����
	bool ret = m_pNormalFade->FadeOutAlpha(alpha);

	// ----- �`��ʒu����
	m_pNormalFade->TranslateZ(z);

	return ret;
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �P�F�t�F�[�h�p�I�u�W�F�N�g��`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CChangeScene::DrawNormalFade()
{
	// ----- �`�揈��
	m_pNormalFade->DrawScreenAlpha();
}


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CChangeScene::CChangeScene()
{
	m_pNormalFade = NULL;
}

//����������������������������������������������������������������������������������������
//	Name        : �f�X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CChangeScene::~CChangeScene()
{
}

//����������������������������������������������������������������������������������������
//	Name        : �e�N�X�`������
//	Description : �P�F�t�F�[�h�p�e�N�X�`���𐶐�����
//	Arguments   : None.
//	Returns     : 0:���s, 1:����, 2:�����ς�
//����������������������������������������������������������������������������������������
int CChangeScene::CreateNormalFade()
{
	// ----- �I�u�W�F�N�g����������������V�K�Ő���
	if(!m_pNormalFade) {
		m_pNormalFade = CObject2D::Create(TEX_FILENAME[TL_NORMALFADE]);
		if(m_pNormalFade == NULL) {
#ifdef _DEBUG_MESSAGEBOX
			::MessageBox(NULL, _T("CChangeScene::NormalFade�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
			return 0;
		}

		// ����������
		m_pNormalFade->Init();
		m_pNormalFade->Translate(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));

		return 1;
	}

	return 2;
}


//========================================================================================
// namespace:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : ���E�̑J��(��ʂɏo��)
//	Description : ��ʂɏo������悤�A���E�Ɋ���悤�ȑJ��
//	Arguments   : pTex / �e�N�X�`��
//				  x    / X�����ړ���
//	Returns     : �����t���O(true:�J�ڊ���)
//����������������������������������������������������������������������������������������
bool ChangeScene::SideSliderIn(CObject2D* pTex, float x)
{
	// ----- �ړ�����
	bool bLeft = true;
	if(x < 0)
		bLeft = false;

	// ----- �ړ�����
	pTex->TranslationX(x);
	// ���E����
	if(bLeft) {
		if(pTex->GetPosX() > SCREEN_WIDTH) {
			pTex->TranslateX((float)SCREEN_WIDTH);
			return true;
		}
	} else {
		if(pTex->GetPosX() + pTex->GetWidth() < 0.0f) {
			pTex->TranslateX(-pTex->GetWidth());
			return true;
		}
	}

	return false;
}

//����������������������������������������������������������������������������������������
//	Name        : ���E�̑J��(��ʂ���ޔ�)
//	Description : ��ʂ���ޔ�����悤�A���E�Ɋ���悤�ȑJ��
//	Arguments   : pTex / �e�N�X�`��
//				  x    / X�����ړ���
//	Returns     : �����t���O(true:�J�ڊ���)
//����������������������������������������������������������������������������������������
bool ChangeScene::SideSliderOut(CObject2D* pTex, float x)
{
	// ----- �ړ�����
	bool bLeft = true;
	if(x < 0)
		bLeft = false;

	// ----- �ړ�����
	pTex->TranslationX(x);
	// ���E����
	if(bLeft) {
		if(pTex->GetPosX() + pTex->GetWidth() > SCREEN_WIDTH) {
			pTex->TranslateX((float)SCREEN_WIDTH - pTex->GetWidth());
			return true;
		}
	} else {
		if(pTex->GetPosX() < 0.0f) {
			pTex->TranslateX(0.0f);
			return true;
		}
	}

	return false;
}


//========================================================================================
//	End of File
//========================================================================================