//========================================================================================
//		File        : Score.cpp
//		Program     : �X�R�A�N���X
//
//		Description : �X�R�A�N���X�̎���
//
//		History     : 2014/11/27	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/PreInclude.h"
#
#include "../../h/Object/Score.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �����o���̐錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// public:
const LONG	CScore::MAX_SCORE		= 1000000;		// �X�R�A�̍ő�l
const int	CScore::SCORE_DIGIT		= 7;			// �ő�X�R�A�̌���

// private:
const LPCTSTR		CScore::TEX_FILENAME	= _T("res/img/Score.png");		// �e�N�X�`���t�@�C����
const D3DXVECTOR2	CScore::OBJ_SIZE		= D3DXVECTOR2(48.0f, 48.0f);	// �I�u�W�F�N�g�T�C�Y
const int			CScore::WIDTH_FRAME		= 10;							// �A�j���[�V�����t���[���̉�������
const int			CScore::HEIGHT_FRAME	= 1;							// �A�j���[�V�����t���[���̏c������


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CScore::CScore()
{
	m_score = 0;	// �`��X�R�A
}

//����������������������������������������������������������������������������������������
//	Name        : �f�X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CScore::~CScore()
{
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �I�u�W�F�N�g�f�[�^������������
//	Arguments   : pos / �o���ʒu
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CScore::Init(const D3DXVECTOR3& pos)
{
	// ----- �f�[�^������
	m_score = 0;	// �`��X�R�A

	// ----- �I�u�W�F�N�g������
	int numCnt = 0;
	for(LPNUMBER_ARRAY_IT it = m_pNumberList.begin(); it != m_pNumberList.end(); ++it) {
		(*it)->Init(OBJ_SIZE);		// ������
		(*it)->Translate(D3DXVECTOR3(pos.x + (OBJ_SIZE.x * numCnt), pos.y, pos.z));	// �ړ�����
		(*it)->UVDivision(0, WIDTH_FRAME, HEIGHT_FRAME);	// �A�j���[�V��������

		++numCnt;
	}
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �I�u�W�F�N�g�f�[�^�̌�n��������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CScore::Uninit()
{
	for(LPNUMBER_ARRAY_IT it = m_pNumberList.begin(); it != m_pNumberList.end(); ++it) {
		(*it)->Uninit();
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �I�u�W�F�N�g���X�V����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CScore::Update()
{
	for(LPNUMBER_ARRAY_IT it = m_pNumberList.begin(); it != m_pNumberList.end(); ++it) {
		(*it)->Update();
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �I�u�W�F�N�g���A���t�@�����ŕ`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CScore::Draw()
{
	for(LPNUMBER_ARRAY_IT it = m_pNumberList.begin(); it != m_pNumberList.end(); ++it) {
		(*it)->Draw();
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �I�u�W�F�N�g���A���t�@�L���ŕ`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CScore::DrawAlpha()
{
	for(LPNUMBER_ARRAY_IT it = m_pNumberList.begin(); it != m_pNumberList.end(); ++it) {
		(*it)->DrawAlpha();
	}
}

//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : �I�u�W�F�N�g�𐶐�����
//	Arguments   : None.
//	Returns     : �I�u�W�F�N�g�f�[�^
//����������������������������������������������������������������������������������������
CScore* CScore::Create()
{
	// ----- �ϐ��錾
	CScore* pScore;

	// ----- ����������
	pScore = new CScore();
	if(pScore)
	{
		if(!pScore->Initialize())
		{
			SAFE_DELETE(pScore);
		}
	}

	return pScore;
}

//����������������������������������������������������������������������������������������
//	Name        : �������
//	Description : �I�u�W�F�N�g�f�[�^���������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CScore::Release()
{
	Finalize();
	delete this;
}

//����������������������������������������������������������������������������������������
//	Name        : �ړ�����
//	Description : �`��X�R�A���ړ�����
//	Arguments   : pos / �o�����W
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CScore::Translate(const D3DXVECTOR3& pos)
{
	// ----- �ړ�����
	int numCnt = 0;
	for(LPNUMBER_ARRAY_IT it = m_pNumberList.begin(); it != m_pNumberList.end(); ++it) {
		(*it)->Translate(D3DXVECTOR3(pos.x + (OBJ_SIZE.x * numCnt), pos.y, pos.z));
		++numCnt;
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �X�R�A�X�V
//	Description : �`��X�R�A���X�V����
//	Arguments   : score / �`��X�R�A
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CScore::SetScore(LONG score)
{
	// ----- �X�R�A�X�V
	m_score = score;

	// ----- �I�u�W�F�N�g�X�V
	int digit = SCORE_DIGIT - 1;	// �X�R�A���ԍ�
	while(score > 0) {
		int num = score % 10;	// �`�悷�鐔�����Z�o
		m_pNumberList[digit]->UVDivision(num, WIDTH_FRAME, HEIGHT_FRAME);	// �����𔽉f
		--digit;		// ���̌���
		score /= 10;	// ���̌���
	}
}


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �I�u�W�F�N�g�f�[�^������������
//	Arguments   : None.
//	Returns     : ����
//����������������������������������������������������������������������������������������
bool CScore::Initialize()
{
	// ----- �I�u�W�F�N�g����
	for(int i = 0; i < SCORE_DIGIT; ++i) {
		CNumber* pNum = CNumber::Create(TEX_FILENAME);
		if(pNum == NULL) {
#ifdef _DEBUG_MESSAGEBOX
			::MessageBox(NULL, _T("CScore::Initialize Number�̐����Ɏ��s���܂����B"), _T("error"), MB_OK);
#endif
			return false;
		}
		m_pNumberList.push_back(pNum);
	}
	
	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �I�u�W�F�N�g�f�[�^�̌�n��������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CScore::Finalize()
{
	for(LPNUMBER_ARRAY_IT it = m_pNumberList.begin(); it != m_pNumberList.end(); ++it) {
		SAFE_RELEASE((*it));
	}

	m_pNumberList.clear();
}


//========================================================================================
//	End of File
//========================================================================================