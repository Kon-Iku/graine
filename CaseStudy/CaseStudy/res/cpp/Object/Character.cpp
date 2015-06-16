//========================================================================================
//		File        : Character.cpp
//		Program     : �L�����N�^�x�[�X
//
//		Description : �L�����N�^�x�[�X�̎���
//					  ���_�F�|���S���̒���
//
//		History     : 2015/05/11	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/PreInclude.h"
#
#include <math.h>
#include "../../h/System/System.h"
#include "../../h/Object/Character.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
const float	CCharacter::DEFAULT_GRAVITY	= 0.098f;		// �d�͂̃f�t�H���g�l


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CCharacter::CCharacter()
{
	m_status	= ST_NONE;
	m_gravity	= 0.0f;
	m_graAccel	= 0.0f;

	m_timeSeed		= 0.0;
	m_bSingleAnime	= false;

	m_colRadius			= 0.0f;
	m_colStartLine		= D3DXVECTOR2(0.0f, 0.0f);
	m_colEndLine		= D3DXVECTOR2(0.0f, 0.0f);
	m_lastColLine		= D3DXVECTOR2(0.0f, 0.0f);
	m_lastColLinePos	= D3DXVECTOR2(0.0f, 0.0f);
}

//����������������������������������������������������������������������������������������
//	Name        : �f�X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CCharacter::~CCharacter()
{
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �L�����N�^���f�t�H���g�l�ŏ���������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCharacter::Init()
{
	// ----- ���_�f�[�^������
	CObject2D::Init();

	// ----- �����蔻��p�p�����[�^�ݒ�
	m_colRadius = sqrt((m_vtx[1].vtx.x * m_vtx[1].vtx.x) + (m_vtx[1].vtx.y * m_vtx[1].vtx.y));	// ���a

	m_status	= ST_NONE;
	m_gravity	= DEFAULT_GRAVITY;
	m_graAccel	= 0.0f;

	m_bSingleAnime	= false;
	
	m_colStartLine		= D3DXVECTOR2(0.0f, 0.0f);
	m_colEndLine		= D3DXVECTOR2(0.0f, 0.0f);
	m_lastColLine		= D3DXVECTOR2(0.0f, 0.0f);
	m_lastColLinePos	= D3DXVECTOR2(0.0f, 0.0f);
}

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �L�����N�^������������
//	Arguments   : size / �I�u�W�F�N�g�T�C�Y
//				  pos  / �o���ʒu(�I�u�W�F�N�g�̒���)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCharacter::Init(const D3DXVECTOR2& size, const D3DXVECTOR3& pos)
{
	// ----- ���_�f�[�^������
	CCharacter::Init();

	// ----- �T�C�Y�ݒ�
	Resize(size);

	// ----- �`��ʒu�ݒ�
	Translate(pos);
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �L�����N�^�̌�n��������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCharacter::Uninit(void)
{
	CObject2D::Uninit();
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �L�����N�^���X�V����
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCharacter::Update(void)
{
	CObject2D::Update();

	// ----- �d�͏���
	if(CheckStatus(ST_FLYING)) {
		m_graAccel += m_gravity;	// �������x�����X�ɏグ�Ă���
		TranslationY(-m_graAccel);	// ��������
	} else {
		// �d�͉����x��������
		if(m_graAccel > 0.0f)
			m_graAccel = 0.0f;
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �L�����N�^�𓧉ߖ����ŕ`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCharacter::Draw()
{
	CObject2D::Draw();
}

//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �L�����N�^�𓧉ߗL��ŕ`�悷��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCharacter::DrawAlpha()
{
	CObject2D::DrawAlpha();
}

//����������������������������������������������������������������������������������������
//	Name        : �r���{�[�h�`��
//	Description : �L�����N�^�𓧉ߖ����Ńr���{�[�h�Ƃ��ĕ`�悷��
//	Arguments   : target / �Ώۂ̍��W
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCharacter::DrawBillBoard(const D3DXVECTOR3& target)
{
	CObject2D::DrawBillBoard(target);
}

//����������������������������������������������������������������������������������������
//	Name        : �r���{�[�h�`��
//	Description : �L�����N�^�𓧉ߗL��Ńr���{�[�h�Ƃ��ĕ`�悷��
//	Arguments   : target / �Ώۂ̍��W
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCharacter::DrawBillBoardAlpha(const D3DXVECTOR3& target)
{
	CObject2D::DrawBillBoardAlpha(target);
}

//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : �L�����N�^�𐶐�����
//	Arguments   : pszFName / �ǂݍ��݃t�@�C����
//	Returns     : �L�����N�^�f�[�^
//����������������������������������������������������������������������������������������
CCharacter* CCharacter::Create(const LPCTSTR pszFName)
{
	// ----- �ϐ��錾
	CCharacter* pChara;

	// ----- ����������
	pChara = new CCharacter();
	if(pChara)
	{
		if(!pChara->Initialize(pszFName))
		{
			SAFE_DELETE(pChara);
		}
	}

	return pChara;
}

//����������������������������������������������������������������������������������������
//	Name        : �t���[���A�j���[�V�����J�n����
//	Description : �t���[���A�j���[�V�����J�n���Ԃ�ݒ肵�A�Đ��������s��
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCharacter::StartAnimation()
{
	m_timeSeed		= CTimer::GetTime();
	m_bSingleAnime	= 0;
}

//����������������������������������������������������������������������������������������
//	Name        : �t���[���A�j���[�V����
//	Description : �A�j���[�V��������R�}�ԍ��ƁA�b���w�肵�āA�t���[���A�j���[�V�������s��
//	Arguments   : start  / �J�n�R�}�̎Q�Ɣԍ�
//				  end    / �ŏI�R�}�̎Q�Ɣԍ�
//				  width  / ��������
//				  height / �c������
//				  time   / �R�}����Ԋu(�b)
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCharacter::FrameAnimation(int start, int end, int width, int height, double time)
{
	if(SingleAnimation(start, end, width, height, time))
		RefreshSingleAnimation();
}

//����������������������������������������������������������������������������������������
//	Name        : �t���[���A�j���[�V����
//	Description : �A�j���[�V��������R�}�ԍ��ƁA�b���w�肵�āA1��̂ݍĐ�����t���[���A�j���[�V�������s��
//	Arguments   : start  / �J�n�R�}�̎Q�Ɣԍ�
//				  end    / �ŏI�R�}�̎Q�Ɣԍ�
//				  width  / ��������
//				  height / �c������
//				  time   / �R�}����Ԋu(�b)
//	Returns     : ����(true:�A�j���[�V��������)
//����������������������������������������������������������������������������������������
bool CCharacter::SingleAnimation(int start, int end, int width, int height, double time)
{
	// ----- �Đ��ς݂��`�F�b�N
	if(m_bSingleAnime)
		return true;

	// ----- ���O����
	double	subTime		= CTimer::GetTime() - m_timeSeed;		// �A�j���[�V�����o�ߎ���
	bool	bReverse	= end - start < 0 ? true : false;		// �t�Đ��t���O
	int		maxSeg		= 0;									// �A�j���[�V�����R�}��
	int		segment		= 0;									// �`��R�}�ԍ�
	
	// ----- �Đ�����
	if(bReverse) {
		// �t�Đ�
		maxSeg	= start - end + 1;
		segment	= start - ((int)floor(subTime / time) % maxSeg);

		// �Đ��񐔃`�F�b�N
		if(segment <= end) {
			m_bSingleAnime = true;
		}
	} else {
		// �ʏ�Đ�
		maxSeg	= end - start + 1;
		segment	= ((int)floor(subTime / time) % maxSeg) + start;

		// �Đ��񐔃`�F�b�N
		if(segment >= end) {
			m_bSingleAnime = true;
		}
	}

	// ----- �R�}����
	UVDivision(segment, width, height);

	return m_bSingleAnime;
}

//����������������������������������������������������������������������������������������
//	Name        : �A�j���[�V�����Đ��t���O��������
//	Description : 1��̂ݍĐ�����t���[���A�j���[�V�����̍Đ��t���O������������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCharacter::RefreshSingleAnimation()
{
	m_bSingleAnime = false;
}

//����������������������������������������������������������������������������������������
//	Name        : �����蔻��
//	Description : �ՓˑΏۂ�2D�L�����N�^�Ƃ̓����蔻����s��(���������u�Ԃ̂ݔ���)
//	Arguments   : id   / �����蔻��ID
//				  pCol / �ՓˑΏۃL�����N�^
//	Returns     : ���茋��(true:�������Ă���)
//����������������������������������������������������������������������������������������
bool CCharacter::CollisionEnter(int id, const CCharacter* pCol)
{
	// ----- ���O����
	static bool trg = false;	// �g���K�[����p
	bool ret = false;			// ���茋��

	// ----- �����蔻��
	switch(id)
	{
		// �o�E���f�B���O�{�b�N�X
		case COL2D_BOUNDINGBOX:
			ret = BoundingBox(pCol);
			break;
			
		// �o�E���f�B���O�T�[�N��
		case COL2D_BOUNDINGCIRCLE:
			ret = BoundingCircle(pCol);
			break;

		// ��`�Ɖ~�Ƃ̓����蔻��(�ՓˑΏۂ��~�̏ꍇ)
		case COL2D_SQUARECIRCLE:
			ret = JudgeSquareCircle(pCol);
			break;

		// ��`�Ɖ~�Ƃ̓����蔻��(�ՓˑΏۂ���`�̏ꍇ)
		case COL2D_CIRCLESQUARE:
			ret = JudgeCircleSquare(pCol);
			break;

		// ��`���m�̓����蔻��(��]���Ă��Ă���)
		case COL2D_SQUARESQUARE:
			ret = JudgeSquareSquare(pCol);
			break;

		// ��`�Ɛ����Ƃ̓����蔻��(�ՓˑΏۂ������̏ꍇ)
		case COL2D_SQUARELINE:
			ret = JudgeSquareLine(pCol);
			break;

		// ��`�Ɛ����Ƃ̓����蔻��(�ՓˑΏۂ���`�̏ꍇ)
		case COL2D_LINESQUARE:
			ret = JudgeLineSquare(pCol);
			break;

		// �������m�̓����蔻��
		case COL2D_LINELINE:
			ret = JudgeLineLine(pCol);
			break;

		default:
			break;
	}

	// ----- �g���K�[����
	if(!trg && ret) {
		trg = true;
		ret = true;
	} else {
		if(trg && !ret) {
			trg = false;
		}
		ret = false;
	}

	return ret;
}

//����������������������������������������������������������������������������������������
//	Name        : �����蔻��
//	Description : �ՓˑΏۂ�2D�L�����N�^�Ƃ̓����蔻����s��(�������Ă���Ԃ̂ݔ���)
//	Arguments   : id   / �����蔻��ID
//				  pCol / �ՓˑΏۃL�����N�^
//	Returns     : ���茋��(true:�������Ă���)
//����������������������������������������������������������������������������������������
bool CCharacter::CollisionStay(int id, const CCharacter* pCol)
{
	// ----- ���O����
	bool ret = false;		// ���茋��

	// ----- �����蔻��
	switch(id)
	{
		// �o�E���f�B���O�{�b�N�X
		case COL2D_BOUNDINGBOX:
			ret = BoundingBox(pCol);
			break;
			
		// �o�E���f�B���O�T�[�N��
		case COL2D_BOUNDINGCIRCLE:
			ret = BoundingCircle(pCol);
			break;
			
		// ��`�Ɖ~�Ƃ̓����蔻��(����Ώۂ��~�̏ꍇ)
		case COL2D_SQUARECIRCLE:
			ret = JudgeSquareCircle(pCol);
			break;

		// ��`�Ɖ~�Ƃ̓����蔻��(����Ώۂ���`�̏ꍇ)
		case COL2D_CIRCLESQUARE:
			ret = JudgeCircleSquare(pCol);
			break;

		// ��`���m�̓����蔻��(��]���Ă��Ă���)
		case COL2D_SQUARESQUARE:
			ret = JudgeSquareSquare(pCol);
			break;

		// ��`�Ɛ����Ƃ̓����蔻��(�ՓˑΏۂ������̏ꍇ)
		case COL2D_SQUARELINE:
			ret = JudgeSquareLine(pCol);
			break;

		// ��`�Ɛ����Ƃ̓����蔻��(�ՓˑΏۂ���`�̏ꍇ)
		case COL2D_LINESQUARE:
			ret = JudgeLineSquare(pCol);
			break;

		// �������m�̓����蔻��
		case COL2D_LINELINE:
			ret = JudgeLineLine(pCol);
			break;

		default:
			break;
	}

	return ret;
}


//����������������������������������������������������������������������������������������
//	Name        : �����蔻��
//	Description : �ՓˑΏۂ�2D�L�����N�^�Ƃ̓����蔻����s��(���ꂽ�u�Ԃ̂ݔ���)
//	Arguments   : id   / �����蔻��ID
//				  pCol / �ՓˑΏۃL�����N�^
//	Returns     : ���茋��(true:�������Ă���)
//����������������������������������������������������������������������������������������
bool CCharacter::CollisionExit(int id, const CCharacter* pCol)
{
	// ----- ���O����
	static bool rls = false;	// �����[�X����p
	bool ret = false;			// ���茋��

	// ----- �����蔻��
	switch(id)
	{
		// �o�E���f�B���O�{�b�N�X
		case COL2D_BOUNDINGBOX:
			ret = BoundingBox(pCol);
			break;
			
		// �o�E���f�B���O�T�[�N��
		case COL2D_BOUNDINGCIRCLE:
			ret = BoundingCircle(pCol);
			break;

		// ��`�Ɖ~�Ƃ̓����蔻��(����Ώۂ��~�̏ꍇ)
		case COL2D_SQUARECIRCLE:
			ret = JudgeSquareCircle(pCol);
			break;

		// ��`�Ɖ~�Ƃ̓����蔻��(����Ώۂ���`�̏ꍇ)
		case COL2D_CIRCLESQUARE:
			ret = JudgeCircleSquare(pCol);
			break;

		// ��`���m�̓����蔻��(��]���Ă��Ă���)
		case COL2D_SQUARESQUARE:
			ret = JudgeSquareSquare(pCol);
			break;

		// ��`�Ɛ����Ƃ̓����蔻��(�ՓˑΏۂ������̏ꍇ)
		case COL2D_SQUARELINE:
			ret = JudgeSquareLine(pCol);
			break;

		// ��`�Ɛ����Ƃ̓����蔻��(�ՓˑΏۂ���`�̏ꍇ)
		case COL2D_LINESQUARE:
			ret = JudgeLineSquare(pCol);
			break;

		// �������m�̓����蔻��
		case COL2D_LINELINE:
			ret = JudgeLineLine(pCol);
			break;

		default:
			break;
	}

	// ----- �����[�X����
	if(!rls && ret) {
		rls = true;
		ret = false;
	} else {
		if(rls && !ret) {
			rls = false;
			return true;
		}
		ret = false;
	}

	return ret;
}

//����������������������������������������������������������������������������������������
//	Name        : �L�����N�^�T�C�Y�ύX
//	Description : �L�����N�^�̃T�C�Y��ύX����
//	Arguments   : size / �L�����N�^�T�C�Y
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCharacter::Resize(const D3DXVECTOR2& size)
{
	// ----- �T�C�Y�ݒ�
	CObject2D::Resize(size);
	
	// ----- �����蔻��p�p�����[�^�ݒ�
	m_colRadius = sqrt((m_vtx[1].vtx.x * m_vtx[1].vtx.x) + (m_vtx[1].vtx.y * m_vtx[1].vtx.y));	// ���a
}

//����������������������������������������������������������������������������������������
//	Name        : �L�����N�^�T�C�Y�ύX
//	Description : �L�����N�^�̃T�C�Y��ύX����
//	Arguments   : width  / �L�����N�^��
//				  height / �L�����N�^����
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCharacter::Resize(const float width, const float height)
{
	CCharacter::Resize(D3DXVECTOR2(width, height));
}


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �L�����N�^�f�[�^������������
//	Arguments   : pszFName / �ǂݍ��݃t�@�C����
//	Returns     : ����
//����������������������������������������������������������������������������������������
bool CCharacter::Initialize(const LPCTSTR pszFName)
{
	// ----- �L�����N�^������
	if(!CObject2D::Initialize(pszFName))
		return false;
	
	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �L�����N�^�f�[�^�̌�n��������
//	Arguments   : None.
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CCharacter::Finalize(void)
{
	CObject2D::Finalize();
}

//����������������������������������������������������������������������������������������
//	Name        : �����蔻��
//	Description : �ՓˑΏۂ�2D�L�����N�^�ƃo�E���f�B���O�{�b�N�X�ɂ�铖���蔻����s��
//	Arguments   : pCol / �ՓˑΏۃL�����N�^
//	Returns     : ���茋��(true:�������Ă���)
//����������������������������������������������������������������������������������������
bool CCharacter::BoundingBox(const CCharacter* pCol)
{
	if(	this->GetLeftPos()	 < pCol->GetRightPos()	&&
		this->GetRightPos()	 > pCol->GetLeftPos()	&&
		this->GetTopPos()	 > pCol->GetBottomPos()	&&
		this->GetBottomPos() < pCol->GetTopPos())
		return true;

	return false;
}

//����������������������������������������������������������������������������������������
//	Name        : �����蔻��
//	Description : �ՓˑΏۂ�2D�L�����N�^�ƃo�E���f�B���O�T�[�N���ɂ�铖���蔻����s��
//	Arguments   : pCol / �ՓˑΏۃL�����N�^
//	Returns     : ���茋��(true:�������Ă���)
//����������������������������������������������������������������������������������������
bool CCharacter::BoundingCircle(const CCharacter* pCol)
{
	float dist	= (pCol->GetPosX() - this->GetPosX()) * (pCol->GetPosX() - this->GetPosX()) + (pCol->GetPosY() - this->GetPosY()) * (pCol->GetPosY() - this->GetPosY());	// �L�����N�^�Ԃ̋���
	float r		= m_colRadius + pCol->GetColRadius();		// �L�����N�^�Ԃ̏Փˋ���
	if(dist < (r * r))
		return true;

	return false;
}

//����������������������������������������������������������������������������������������
//	Name        : �����蔻��
//	Description : �ՓˑΏۂ�2D�L�����N�^�ƁA��`�Ɖ~�Ƃ̓����蔻����s��(�ՓˑΏۂ��~�̏ꍇ)
//				  ��`����]���Ă��Ă���
//	Arguments   : pCol / �ՓˑΏۃL�����N�^
//	Returns     : ���茋��(true:�������Ă���)
//����������������������������������������������������������������������������������������
bool CCharacter::JudgeSquareCircle(const CCharacter* pCol)
{
	// ----- �s�񉉎Z�ςݒ��_���Z�o
	D3DXVECTOR3 vtx[4] = {m_vtx[1].vtx, m_vtx[0].vtx, m_vtx[2].vtx, m_vtx[3].vtx};
	float vtxX[4];
	float vtxY[4];
	for(int i = 0; i < 4; ++i) {
		D3DXVec3TransformCoord(&vtx[i], &vtx[i], &m_world);
		vtxX[i] = vtx[i].x;
		vtxY[i] = vtx[i].y;
	}

	// ----- ��`��4���_�Ɖ~�Ƃ̓����蔻��
	for(int i = 0; i < 4; ++i) {
		float x = vtxX[i] - pCol->GetPosX();
		float y = vtxY[i] - pCol->GetPosY();
		float r = pCol->GetColRadius();

		if((x * x) + (y * y) < (r * r))
			return true;
	}

	// ----- ��`��4�ӂƉ~�Ƃ̓����蔻��
	for(int i = 0; i < 4; ++i) {
		float x = vtxX[(i + 1) % 4] - vtxX[i];
		float y = vtxY[(i + 1) % 4] - vtxY[i];
		float t = -(x * (vtxX[i] - pCol->GetPosX()) + y * (vtxY[i] - pCol->GetPosY()) / (x * x + y * y));
		if(t < 0)
			t = 0;
		if(t > 1)
			t = 1;

		x = vtxX[i] + x * t;
		y = vtxY[i] + y * t;

		if(sqrt((pCol->GetPosX() - x) * (pCol->GetPosX() - x) + (pCol->GetPosY() - y) * (pCol->GetPosY() - y)) < pCol->GetColRadius())
			return true;
	}

	// ----- ��`��(��)�Ɖ~�Ƃ̓����蔻��
	float x, y;
	float qx, qy;
	float t0, t1;
	
	x	= vtxX[1] - vtxX[0];
	y	= vtxY[1] - vtxY[0];
	qx	= pCol->GetPosX() - vtxX[0];
	qy	= pCol->GetPosY() - vtxY[0];
	t0	= atan2(x * qx + y * qy, x * qy - y * qx);

	x	= vtxX[3] - vtxX[2];
	y	= vtxY[3] - vtxY[2];
	qx	= pCol->GetPosX() - vtxX[2];
	qy	= pCol->GetPosY() - vtxY[2];
	t1	= atan2(x * qx + y * qy, x * qy - y * qx);
	
	if(t0 >= 0 && t0 <= M_PI / 2 && t1 >= 0 && t1 <= M_PI / 2)
		return true;

	return false;
}

//����������������������������������������������������������������������������������������
//	Name        : �����蔻��
//	Description : �ՓˑΏۂ�2D�L�����N�^�ƁA��`�Ɖ~�Ƃ̓����蔻����s��(�ՓˑΏۂ���`�̏ꍇ)
//				  ��`����]���Ă��Ă���
//	Arguments   : pCol / �ՓˑΏۃL�����N�^
//	Returns     : ���茋��(true:�������Ă���)
//����������������������������������������������������������������������������������������
bool CCharacter::JudgeCircleSquare(const CCharacter* pCol)
{
	// ----- �s�񉉎Z�ςݒ��_���Z�o
	D3DXVECTOR3 vtx[4] = {pCol->GetVertex(1).vtx, pCol->GetVertex(0).vtx, pCol->GetVertex(2).vtx, pCol->GetVertex(3).vtx};
	float vtxX[4];
	float vtxY[4];
	for(int i = 0; i < 4; ++i) {
		D3DXVec3TransformCoord(&vtx[i], &vtx[i], &pCol->GetMatrix());
		vtxX[i] = vtx[i].x;
		vtxY[i] = vtx[i].y;
	}

	// ----- ��`��4���_�Ɖ~�Ƃ̓����蔻��
	for(int i = 0; i < 4; ++i) {
		float x = vtxX[i] - GetPosX();
		float y = vtxY[i] - GetPosY();
		float r = GetColRadius();

		if((x * x) + (y * y) < (r * r))
			return true;
	}

	// ----- ��`��4�ӂƉ~�Ƃ̓����蔻��
	for(int i = 0; i < 4; ++i) {
		float x = vtxX[(i + 1) % 4] - vtxX[i];
		float y = vtxY[(i + 1) % 4] - vtxY[i];
		float t = -(x * (vtxX[i] - GetPosX()) + y * (vtxY[i] - GetPosY()) / (x * x + y * y));
		if(t < 0)
			t = 0;
		if(t > 1)
			t = 1;

		x = vtxX[i] + x * t;
		y = vtxY[i] + y * t;

		if(sqrt((GetPosX() - x) * (GetPosX() - x) + (GetPosY() - y) * (GetPosY() - y)) < GetColRadius())
			return true;
	}

	// ----- ��`��(��)�Ɖ~�Ƃ̓����蔻��
	float x, y;
	float qx, qy;
	float t0, t1;
	
	x	= vtxX[1] - vtxX[0];
	y	= vtxY[1] - vtxY[0];
	qx	= GetPosX() - vtxX[0];
	qy	= GetPosY() - vtxY[0];
	t0	= atan2(x * qx + y * qy, x * qy - y * qx);

	x	= vtxX[3] - vtxX[2];
	y	= vtxY[3] - vtxY[2];
	qx	= GetPosX() - vtxX[2];
	qy	= GetPosY() - vtxY[2];
	t1	= atan2(x * qx + y * qy, x * qy - y * qx);
	
	if(t0 >= 0 && t0 <= M_PI / 2 && t1 >= 0 && t1 <= M_PI / 2)
		return true;

	return false;
}

//����������������������������������������������������������������������������������������
//	Name        : �����蔻��
//	Description : �ՓˑΏۂ�2D�L�����N�^�Ƌ�`���m�̓����蔻����s��(��]���Ă��Ă���)
//	Arguments   : pCol / �ՓˑΏۃL�����N�^
//	Returns     : ���茋��(true:�������Ă���)
//����������������������������������������������������������������������������������������
bool CCharacter::JudgeSquareSquare(const CCharacter* pCol)
{
	// ----- �s�񉉎Z�ςݒ��_���Z�o
	// ���L�����N�^
	D3DXVECTOR3 vtx[4] = {m_vtx[1].vtx, m_vtx[0].vtx, m_vtx[2].vtx, m_vtx[3].vtx};
	float vtxX[4];
	float vtxY[4];
	for(int i = 0; i < 4; ++i) {
		D3DXVec3TransformCoord(&vtx[i], &vtx[i], &m_world);
		vtxX[i] = vtx[i].x;
		vtxY[i] = vtx[i].y;
	}
	// �ΏۃL�����N�^
	D3DXVECTOR3 colVtx[4] = {m_vtx[1].vtx, m_vtx[0].vtx, m_vtx[2].vtx, m_vtx[3].vtx};
	float colVtxX[4];
	float colVtxY[4];
	for(int i = 0; i < 4; ++i) {
		D3DXVec3TransformCoord(&colVtx[i], &colVtx[i], &pCol->GetMatrix());
		colVtxX[i] = colVtx[i].x;
		colVtxY[i] = colVtx[i].y;
	}

	float radius = 1.0f;	// ����Ώۂ̒��_�̔��a(�_�Ƃ��Ĉ���)
	for(int j = 0; j < 4; ++j) {
		// ----- ���L�����N�^����`�Ƃ���p�^�[��
		// ��`��4���_�Ɖ~�Ƃ̓����蔻��
		for(int i = 0; i < 4; ++i) {
			float x = vtxX[i] - colVtxX[j];
			float y = vtxY[i] - colVtxY[j];
			float r = radius;

			if((x * x) + (y * y) < (r * r))
				return true;
		}

		// ��`��4�ӂƉ~�Ƃ̓����蔻��
		for(int i = 0; i < 4; ++i) {
			float x = vtxX[(i + 1) % 4] - vtxX[i];
			float y = vtxY[(i + 1) % 4] - vtxY[i];
			float t = -(x * (vtxX[i] - colVtxX[j]) + y * (vtxY[i] - colVtxY[j]) / (x * x + y * y));
			if(t < 0)
				t = 0;
			if(t > 1)
				t = 1;

			x = vtxX[i] + x * t;
			y = vtxY[i] + y * t;

			if(sqrt((colVtxX[j] - x) * (colVtxX[j] - x) + (colVtxY[j] - y) * (colVtxY[j] - y)) < radius)
				return true;
		}

		// ��`��(��)�Ɖ~�Ƃ̓����蔻��
		float x, y;
		float qx, qy;
		float t0, t1;
	
		x	= vtxX[1] - vtxX[0];
		y	= vtxY[1] - vtxY[0];
		qx	= colVtxX[j] - vtxX[0];
		qy	= colVtxY[j] - vtxY[0];
		t0	= atan2(x * qx + y * qy, x * qy - y * qx);

		x	= vtxX[3] - vtxX[2];
		y	= vtxY[3] - vtxY[2];
		qx	= colVtxX[j] - vtxX[2];
		qy	= colVtxY[j] - vtxY[2];
		t1	= atan2(x * qx + y * qy, x * qy - y * qx);
	
		if(t0 >= 0 && t0 <= M_PI / 2 && t1 >= 0 && t1 <= M_PI / 2)
			return true;
		
		// ----- �ΏۃL�����N�^����`�Ƃ���p�^�[��
		// ��`��4���_�Ɖ~�Ƃ̓����蔻��
		for(int i = 0; i < 4; ++i) {
			float x = colVtxX[i] - vtxX[j];
			float y = colVtxY[i] - vtxY[j];
			float r = radius;

			if((x * x) + (y * y) < (r * r))
				return true;
		}

		// ��`��4�ӂƉ~�Ƃ̓����蔻��
		for(int i = 0; i < 4; ++i) {
			float x = colVtxX[(i + 1) % 4] - colVtxX[i];
			float y = colVtxY[(i + 1) % 4] - colVtxY[i];
			float t = -(x * (colVtxX[i] - vtxX[j]) + y * (colVtxY[i] - vtxY[j]) / (x * x + y * y));
			if(t < 0)
				t = 0;
			if(t > 1)
				t = 1;

			x = colVtxX[i] + x * t;
			y = colVtxY[i] + y * t;

			if(sqrt((vtxX[j] - x) * (vtxX[j] - x) + (vtxY[j] - y) * (vtxY[j] - y)) < radius)
				return true;
		}

		// ��`��(��)�Ɖ~�Ƃ̓����蔻��	
		x	= colVtxX[1] - colVtxX[0];
		y	= colVtxY[1] - colVtxY[0];
		qx	= vtxX[j] - colVtxX[0];
		qy	= vtxY[j] - colVtxY[0];
		t0	= atan2(x * qx + y * qy, x * qy - y * qx);

		x	= colVtxX[3] - colVtxX[2];
		y	= colVtxY[3] - colVtxY[2];
		qx	= vtxX[j] - colVtxX[2];
		qy	= vtxY[j] - colVtxY[2];
		t1	= atan2(x * qx + y * qy, x * qy - y * qx);
	
		if(t0 >= 0 && t0 <= M_PI / 2 && t1 >= 0 && t1 <= M_PI / 2)
			return true;
	}

	return false;
}

//����������������������������������������������������������������������������������������
//	Name        : �����蔻��
//	Description : �ՓˑΏۂ�2D�L�����N�^�ƁA��`�Ɛ����Ƃ̓����蔻����s��(�ՓˑΏۂ������̏ꍇ)
//	Arguments   : pCol / �ՓˑΏۃL�����N�^
//	Returns     : ���茋��(true:�������Ă���)
//����������������������������������������������������������������������������������������
bool CCharacter::JudgeSquareLine(const CCharacter* pCol)
{
	// ----- ���O����
	D3DXVECTOR2	line = pCol->GetColEndLine() - pCol->GetColStartLine();	// �����̕����x�N�g���y�ё傫��
	D3DXVECTOR3 colVtx[4] = {m_vtx[1].vtx, m_vtx[0].vtx, m_vtx[2].vtx, m_vtx[3].vtx};
	D3DXVECTOR2 colVtx2[4];
	for(int i = 0; i < 4; ++i) {
		D3DXVec3TransformCoord(&colVtx[i], &colVtx[i], &GetMatrix());
		colVtx2[i].x = colVtx[i].x;
		colVtx2[i].y = colVtx[i].y;
	}

	// ----- �����蔻��
	for(int i = 0; i < 4; ++i) {
		D3DXVECTOR2	frame;
		frame.x = colVtx2[(i + 1) % 4].x - colVtx2[i].x;
		frame.y = colVtx2[(i + 1) % 4].y - colVtx2[i].y;

		D3DXVECTOR2 v = colVtx2[i] - pCol->GetColStartLine();

		// ���t��Ԃ��`�F�b�N
		float v1 = System::D3DXVec2Cross(&line, &frame);
		if(v1 == 0.0f) {
			continue;
		}

		// �������Ă��邩�`�F�b�N
		float v2 = System::D3DXVec2Cross(&v, &line);
		float v3 = System::D3DXVec2Cross(&v, &frame);

		float t1 = v3 / v1;
		float t2 = v2 / v1;

		const float RANGE = 0.00001f;	// �덷�͈̔�
		if(	t1 + RANGE >= 0.0f && t1 - RANGE <= 1.0f &&
			t2 + RANGE >= 0.0f && t2 - RANGE <= 1.0f) {
			m_lastColLine		= frame;	// �Փː���
			m_lastColLinePos	= pCol->GetColStartLine() + line * t1;		// �Փˍ��W

			return true;
		}
	}

	return false;
}

//����������������������������������������������������������������������������������������
//	Name        : �����蔻��
//	Description : �ՓˑΏۂ�2D�L�����N�^�ƁA��`�Ɛ����Ƃ̓����蔻����s��(�ՓˑΏۂ���`�̏ꍇ)
//	Arguments   : pCol / �ՓˑΏۃL�����N�^
//	Returns     : ���茋��(true:�������Ă���)
//����������������������������������������������������������������������������������������
bool CCharacter::JudgeLineSquare(const CCharacter* pCol)
{
	// ----- ���O����
	D3DXVECTOR2	line = GetColEndLine() - GetColStartLine();	// �����̕����x�N�g���y�ё傫��
	D3DXVECTOR3 colVtx[4] = {pCol->GetVertex(1).vtx, pCol->GetVertex(0).vtx, pCol->GetVertex(2).vtx, pCol->GetVertex(3).vtx};
	D3DXVECTOR2 colVtx2[4];
	for(int i = 0; i < 4; ++i) {
		D3DXVec3TransformCoord(&colVtx[i], &colVtx[i], &pCol->GetMatrix());
		colVtx2[i].x = colVtx[i].x;
		colVtx2[i].y = colVtx[i].y;
	}

	// ----- �����蔻��
	for(int i = 0; i < 4; ++i) {
		D3DXVECTOR2	frame;
		frame.x = colVtx2[(i + 1) % 4].x - colVtx2[i].x;
		frame.y = colVtx2[(i + 1) % 4].y - colVtx2[i].y;

		D3DXVECTOR2 v = colVtx2[i] - GetColStartLine();

		// ���t��Ԃ��`�F�b�N
		float v1 = System::D3DXVec2Cross(&line, &frame);
		if(v1 == 0.0f) {
			continue;
		}

		// �������Ă��邩�`�F�b�N
		float v2 = System::D3DXVec2Cross(&v, &line);
		float v3 = System::D3DXVec2Cross(&v, &frame);

		float t1 = v3 / v1;
		float t2 = v2 / v1;

		const float RANGE = 0.00001f;	// �덷�͈̔�
		if(	t1 + RANGE >= 0.0f && t1 - RANGE <= 1.0f &&
			t2 + RANGE >= 0.0f && t2 - RANGE <= 1.0f) {
			m_lastColLine		= frame;	// �Փː���
			m_lastColLinePos	= GetColStartLine() + line * t1;		// �Փˍ��W

			return true;
		}
	}

	return false;
}

//����������������������������������������������������������������������������������������
//	Name        : �����蔻��
//	Description : �ՓˑΏۂ�2D�L�����N�^�ƁA�������m�̓����蔻����s��
//	Arguments   : pCol / �ՓˑΏۃL�����N�^
//	Returns     : ���茋��(true:�������Ă���)
//����������������������������������������������������������������������������������������
bool CCharacter::JudgeLineLine(const CCharacter* pCol)
{
	// ----- ���O����
	D3DXVECTOR2	line	= GetColEndLine() - GetColStartLine();				// �����̐����̕����x�N�g���y�ё傫��
	D3DXVECTOR2 colLine	= pCol->GetColEndLine() - pCol->GetColStartLine();	// �Ώۂ̐����̕����x�N�g���y�ё傫��

	// ----- �����蔻��
	D3DXVECTOR2 v = pCol->GetColStartLine() - GetColStartLine();

	// ���t��Ԃ��`�F�b�N
	float v1 = System::D3DXVec2Cross(&line, &colLine);
	if(v1 == 0.0f) {
		return false;
	}

	// �������Ă��邩�`�F�b�N
	float v2 = System::D3DXVec2Cross(&v, &line);
	float v3 = System::D3DXVec2Cross(&v, &colLine);

	float t1 = v3 / v1;
	float t2 = v2 / v1;

	const float RANGE = 0.00001f;	// �덷�͈̔�
	if(	t1 + RANGE < 0.0f || t1 - RANGE > 1.0f ||
		t2 + RANGE < 0.0f || t2 - RANGE > 1.0f) {
		return false;
	}
	
	m_lastColLine		= colLine;		// �Փː���
	m_lastColLinePos	= GetColStartLine() + line * t1;		// �Փˍ��W

	return true;
}


//========================================================================================
//	End of File
//========================================================================================