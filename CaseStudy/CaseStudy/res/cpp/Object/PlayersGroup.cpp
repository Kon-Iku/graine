//========================================================================================
//		File        : PlayersGroup.h
//		Program     : �v���C���[�ǂ�
//
//		Description : �v���C���[�ǂ��̓���,��΂���
//
//		History     : 2015/05/6	�쐬�J�n
//						   
//
//																Author : ���񂽂܃Y
//========================================================================================


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/Input.h"
#include "../../h/Object/PlayersGroup.h"

//========================================================================================
// public:
//========================================================================================
// �\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// using�錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
using namespace Input;
//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CPlayersGroup::CPlayersGroup()
{
	m_nCurrentControllNo = 0;		// ���삷����擪�ɃZ�b�g
}
//����������������������������������������������������������������������������������������
//	Name        : ����
//	Description : �I�u�W�F�N�g�𐶐�����
//	Arguments   : pszFName / �ǂݍ��݃t�@�C����
//	Returns     : �I�u�W�F�N�g�f�[�^
//����������������������������������������������������������������������������������������
CPlayersGroup* CPlayersGroup::Create(const LPCTSTR pszFName)
{
	// ----- �ϐ��錾
	CPlayersGroup* pObj;

	// ----- ����������
	pObj = new CPlayersGroup();

	pObj->SetTexture(pszFName);

	return pObj;
}
//����������������������������������������������������������������������������������������
//	Name        : ������
//	Description : �����ȏ�����
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CPlayersGroup::Init()
{
	
}
//����������������������������������������������������������������������������������������
//	Name        : ��n��
//	Description : �����Ȍ�n��
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CPlayersGroup::Uninit()
{
	// �v�f�S���폜
	for(m_listIt = m_list.begin(); m_listIt != m_list.end();)
	{
		// ����ȁAUTSUWA���Ȃ��ƒ�������Ȃ���
		CPlayer* p = *m_listIt;

		// ��n��
		p->Uninit();

		// ���X�g����v�f���폜
		if( (*m_listIt) == 0 ) {
			 m_listIt = m_list.erase( m_listIt );
			 continue;
		}

		// �����΂ɍŌ�ȁ�(�Ă����񂱂ꂢ��Ȃ��ǂ�)
		++m_listIt;
	}

	m_pField = NULL;

	CObject2D::Uninit();
}

//����������������������������������������������������������������������������������������
//	Name        : �X�V
//	Description : �����ȍX�V
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CPlayersGroup::Update()
{
	int currentNo = 0;			// ���̔ԍ�
	CPlayer* Player = NULL;			// ���삷����

	// �v�f�S���X�V
	for(m_listIt = m_list.begin(); m_listIt != m_list.end();)
	{
		// UTSUWA���Ȃ��ƒ�������Ȃ���
		CPlayer* p = *m_listIt;

		p->SetField(m_pField);

		// �v���C���[�Ɍ��݂̔ԍ����Z�b�g
		p->SetNo(currentNo);
		// ���݂̔ԍ�������ԍ��Ɠ����Ȃ�Player�𑀍�ݒ�ɂ���ȊO�͂��̑��ݒ��
		if(m_nCurrentControllNo == p->GetNo()){
			p->SetPlayerType(P_TYPE_PLAYER);
			Player = p;
		}else{
			p->SetPlayerType(P_TYPE_OTHER);
			// ���삷���ݒ�
			p->SetPlayer(Player);
		}
		// �X�V
		p->Update();

		if(p->GetNo() == 1)
			Player = p;
	
		// �ԍ����X�V����
		++currentNo;

		// �����΂ɍŌ�ȁ�
		++m_listIt;
	}

	// �f�o�b�O�p
	if (GetTrgKey(DIK_1)){		// 1
		AddPlayer();
	}
	if (GetTrgKey(DIK_2)){		// 2
		RedusePlayer();
	}
}
//����������������������������������������������������������������������������������������
//	Name        : �`��
//	Description : �����ȍX�V
//	Arguments   : �Ȃ���
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CPlayersGroup::Draw()
{
	// �v�f�S���`��
	for(m_listIt = m_list.begin(); m_listIt != m_list.end();)
	{
		// UTSUWA���Ȃ��ƒ�������Ȃ���
		CPlayer* p = *m_listIt;

		// �`��
		p->DrawAlpha();

		// �����΂ɍŌ�ȁ�
		++m_listIt;
	}
}
//����������������������������������������������������������������������������������������
//	Name        : Player���擾
//	Description : Player���擾
//	Arguments   : Player�̔ԍ�
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
CPlayer* CPlayersGroup::GetPlayer(int no)
{
	for(m_listIt = m_list.begin(); m_listIt != m_list.end();)
	{
		// UTSUWA���Ȃ��ƒ�������Ȃ���
		CPlayer* p = *m_listIt;

		// ���ʔԍ����ꏏ��������Ԃ�
		if(p->GetNo() == no){
			return p;
		}

		// �����΂ɍŌ�ȁ�
		++m_listIt;
	}

	// �Ȃ�������NULL��
	return NULL;
}
//����������������������������������������������������������������������������������������
//	Name        : Field���
//	Description : 
//	Arguments   : Field�̃|�C���^
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CPlayersGroup::SetField(CFieldObject* f)
{
	for(m_listIt = m_list.begin(); m_listIt != m_list.end();)
	{
		// UTSUWA���Ȃ��ƒ�������Ȃ���
		CPlayer* p = *m_listIt;

		m_pField = f;
		p->SetField(f);

		// �����΂ɍŌ�ȁ�
		++m_listIt;
	}
}
//����������������������������������������������������������������������������������������
//	Name        : Player�ǉ�
//	Description : Player�ǉ�
//	Arguments   : Player�̃|�C���^
//	Returns     : �Ȃ���
//����������������������������������������������������������������������������������������
void CPlayersGroup::AddPlayer(CPlayer* p)
{
	m_list.push_back(p);
}
//����������������������������������������������������������������������������������������
//	Name        : Player�ǉ�
//	Description : �Ō����Player�ǉ�
//	Arguments   : Player�̃|�C���^
//	Returns     : nai!
//����������������������������������������������������������������������������������������
void CPlayersGroup::AddPlayer()
{
	CPlayer* p;		// �ǉ�������
	// ����
	p = CPlayer::Create(m_lpTex);
	// ������
	p->Init();

	// :::: ���X�g�ɒǉ� ::::: //
	m_list.push_back(p);
}
//����������������������������������������������������������������������������������������
//	Name        : Player�폜
//	Description : �Ō����Player�폜
//	Arguments   : Player�̃|�C���^
//	Returns     : �Ȃ��I
//����������������������������������������������������������������������������������������
void CPlayersGroup::RedusePlayer()
{
	// 1�̂������Ȃ������猸�炳�Ȃ�
	if(m_list.size() == 1)
		return;

	// UTSUWA
	CPlayer* p = m_list.back();
	// ��n��
	p->Uninit();
	// �J��
	SAFE_RELEASE(p)

	// :::: ���X�g����폜 ::::: //
	m_list.pop_back();
}

//========================================================================================
//	End of File
//========================================================================================