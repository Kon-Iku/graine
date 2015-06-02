//========================================================================================
//		File        : Character.h
//		Program     : �L�����N�^�x�[�X
//
//		Description : �L�����N�^�x�[�X�̒�`
//					  ���_�F�|���S���̒���
//
//		History     : 2015/05/11	�쐬�J�n
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
#include <vector>
#include "../System/System.h"
#include "../System/Graphics.h"
#include "../System/Timer.h"
#include "../Object/Object2D.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �萔��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ���
enum _eStatus {
	ST_NONE		= 0,	// ��
	ST_WAIT		= 1,	// �ҋ@
	ST_MOVE		= 2,	// �ړ�
	ST_FLYING	= 4,	// ���V��
	ST_JUMP		= 8,	// �W�����v
};

// �����蔻��
enum _eCollision2D {
	COL2D_BOUNDINGBOX = 0,		// �o�E���f�B���O�{�b�N�X
	COL2D_BOUNDINGCIRCLE,		// �o�E���f�B���O�T�[�N��
	COL2D_SQUARECIRCLE,			// ��`�Ɖ~�Ƃ̓����蔻��(�ՓˑΏۂ��~�̏ꍇ)(��`����]���Ă��Ă���)
	COL2D_CIRCLESQUARE,			// ��`�Ɖ~�Ƃ̓����蔻��(�ՓˑΏۂ���`�̏ꍇ)(��`����]���Ă��Ă���)
	COL2D_SQUARESQUARE,			// ��`���m�̓����蔻��(��]���Ă��Ă���)
	COL2D_SQUARELINE,			// ��`�Ɛ����Ƃ̓����蔻��(�ՓˑΏۂ������̏ꍇ)
	COL2D_LINESQUARE,			// ��`�Ɛ����Ƃ̓����蔻��(�ՓˑΏۂ���`�̏ꍇ)

	MAX_COLLISION2D
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �N���X��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class CCharacter : public CObject2D
{
// ===== using�錾
public:
	using CObject2D::Init;

// ===== �����o�萔
private:
	static const float	DEFAULT_GRAVITY;		// �d�͂̃f�t�H���g�l

// ===== �����o�ϐ�
protected:
	ULONG		m_status;		// ���
	float		m_gravity;		// �d��
	float		m_graAccel;		// �d�͉����x

	// ----- �A�j���[�V�����p�ϐ�
	double		m_timeSeed;		// �A�j���[�V�����J�n����

	// ----- �����蔻��p�ϐ�
	float		m_colRadius;		// ���a
	D3DXVECTOR2	m_colStartLine;		// �����̎n�_
	D3DXVECTOR2	m_colEndLine;		// �����̏I�_
	D3DXVECTOR2	m_lastColLinePos;	// �����̓����蔻��ōŌ�ɏՓ˂������W

// ===== �����o�֐�
public:
	CCharacter();			// �R���X�g���N�^
	virtual ~CCharacter();	// �f�X�g���N�^

	virtual void Init();		// ������
	virtual void Uninit();		// ��n��
	virtual void Update();		// �X�V
	virtual void Draw();		// �`��(�A���t�@����)
	virtual void DrawAlpha();	// �`��(�A���t�@�L��)
	virtual void DrawBillBoard(const D3DXVECTOR3& target);		// �r���{�[�h�`��(�A���t�@����)
	virtual void DrawBillBoardAlpha(const D3DXVECTOR3& target);	// �r���{�[�h�`��(�A���t�@�L��)

	static CCharacter* Create(const LPCTSTR pszFName);	// ����
	virtual void Release();								// �j��
	
	// ----- �Z�b�^�[
	virtual void SetGravity(float gravity) {m_gravity = gravity;}				// �d�͐ݒ�
	virtual void SetColRadius(float radius) {m_colRadius = radius;}				// �����蔻��p���a�ݒ�
	virtual void SetColStartLine(D3DXVECTOR2 line) {m_colStartLine = line;}		// �����蔻��p�����̎n�_�ݒ�
	virtual void SetColEndLine(D3DXVECTOR2 line) {m_colEndLine = line;}			// �����蔻��p�����̏I�_�ݒ�

	// ----- �Q�b�^�[
	virtual int GetStatus() const {return m_status;}							// ��Ԏ擾
	virtual float GetGravity() const {return m_gravity;}						// �d�͎擾
	virtual float GetColRadius() const {return m_colRadius;}					// �����蔻��p���a�擾
	virtual D3DXVECTOR2 GetColStartLine() const {return m_colStartLine;}		// �����蔻��p�����̎n�_�擾
	virtual D3DXVECTOR2 GetColEndLine() const {return m_colEndLine;}			// �����蔻��p�����̏I�_�擾
	virtual D3DXVECTOR2 GetLastColLinePos() const {return m_lastColLinePos;}	// �����̓����蔻��ōŌ�ɏՓ˂������W���擾

	// ----- ��ԑ���֘A
	virtual int CheckStatus(int status) {return m_status & status;}		// ��ԃ`�F�b�N
	virtual void AddStatus(int status) {m_status |= status;}			// ��Ԃ�ǉ�
	virtual void SubStatus(int status) {m_status ^= status;}			// ��Ԃ��팸
	virtual void ClearStatus() {m_status = ST_NONE;}					// ��Ԃ𖳏�Ԃɏ�����

	// ----- �t���[���A�j���[�V�����֘A
	virtual void StartAnimation();		// �t���[���A�j���[�V�����J�n����
	virtual void FrameAnimation(int start, int end, int width, int height, double time);	// �t���[���A�j���[�V����(�b�w��ŃA�j���[�V����)

	// ----- �����蔻��֘A
	virtual bool CollisionEnter(int id, const CCharacter* pCol);	// ���������u��
	virtual bool CollisionStay(int id, const CCharacter* pCol);		// �������Ă����
	virtual bool CollisionExit(int id, const CCharacter* pCol);		// ���ꂽ�u��
	
	virtual void Resize(const D3DXVECTOR2& size);	// �I�u�W�F�N�g�T�C�Y�ύX
	virtual void Resize(const float width, const float height);	// �I�u�W�F�N�g�T�C�Y�ύX

protected:
	virtual bool Initialize(const LPCTSTR pszFName);	// ������
	virtual void Finalize();							// ��n��

	// ----- �����蔻��
	virtual bool BoundingBox(const CCharacter* pCol);			// �o�E���f�B���O�{�b�N�X
	virtual bool BoundingCircle(const CCharacter* pCol);		// �o�E���f�B���O�T�[�N��
	virtual bool JudgeSquareCircle(const CCharacter* pCol);		// ��`�Ɖ~�Ƃ̓����蔻��(�ՓˑΏۂ��~�̏ꍇ)(��`����]���Ă��Ă���)
	virtual bool JudgeCircleSquare(const CCharacter* pCol);		// ��`�Ɖ~�Ƃ̓����蔻��(�ՓˑΏۂ���`�̏ꍇ)(��`����]���Ă��Ă���)
	virtual bool JudgeSquareSquare(const CCharacter* pCol);		// ��`���m�̓����蔻��(��]���Ă��Ă���)
	virtual bool JudgeSquareLine(const CCharacter* pCol);		// ��`�Ɛ����Ƃ̓����蔻��(�ՓˑΏۂ������̏ꍇ)
	virtual bool JudgeLineSquare(const CCharacter* pCol);		// ��`�Ɛ����Ƃ̓����蔻��(�ՓˑΏۂ���`�̏ꍇ)
};

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ���[�U�^��`
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
typedef std::vector<CCharacter*>	LPCHARACTER_ARRAY;		// �L�����N�^�N���X�̃��X�g
typedef LPCHARACTER_ARRAY::iterator	LPCHARACTER_ARRAY_IT;	// �L�����N�^�N���X���X�g�̃C�e���[�^


//========================================================================================
//	End of File
//========================================================================================