//========================================================================================
//		File        : MapData.cpp
//		Program     : �}�b�v�f�[�^�N���X
//
//		Description : �}�b�v�f�[�^�N���X�̎���
//
//		History     : 2015/05/18	�쐬�J�n
//
//																Author : Kei Hashimoto
//========================================================================================


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �x��������
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#pragma warning(disable:4996)

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �C���N���[�h
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include "../../h/System/PreInclude.h"
#
#include <tchar.h>
#include <fstream>
#include <string>
#include <sstream>
#include "../../h/System/MapData.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �����o���̐錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ----- �萔
// private:
LPCTSTR CMapData::MAPDATA_LIST[MAX_STAGEID] = {		// �}�b�v�f�[�^�̃t�@�C�������X�g
	_T("res/data/map/Stage1.csv"),
};
const int	CMapData::INIT_OBJECT_NUM	= 1000;		// �����I�u�W�F�N�g��

// ----- �ϐ�
// private:
LPFIELDOBJECT_ARRAY	CMapData::m_pFieldObj;	// �t�B�[���h�I�u�W�F�N�g���X�g
LPCHARACTER_ARRAY	CMapData::m_pLayoutObj;	// ���C�A�E�g�I�u�W�F�N�g���X�g
D3DXVECTOR2			CMapData::m_startPoint;	// �J�n�ʒu

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �O���[�o���ϐ��錾
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
static CMapData& g_mapData = CMapData::GetInstance();		// �}�b�v�f�[�^�N���X�̎��̐���


//========================================================================================
// public:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �C���X�^���X�擾
//	Description : �}�b�v�f�[�^�N���X�̃C���X�^���X���擾����
//	Arguments   : None.
//	Returns     : �}�b�v�f�[�^�N���X
//����������������������������������������������������������������������������������������
CMapData& CMapData::GetInstance()
{
	// ----- �C���X�^���X����
	static CMapData mapData;

	return mapData;
}

//����������������������������������������������������������������������������������������
//	Name        : �}�b�v�f�[�^���[�h
//	Description : �C�ӂ̃}�b�v�f�[�^�����[�h����
//	Arguments   : id / �X�e�[�WID
//	Returns     : ����(true:����)
//����������������������������������������������������������������������������������������
bool CMapData::LoadData(int id)
{
	// ----- ����������
	m_pFieldObj.clear();
	m_pLayoutObj.clear();

	// ----- �}�b�v�f�[�^�ǂݍ���
	std::ifstream ifs(MAPDATA_LIST[id]);
	if(ifs.fail()) {
#ifdef _DEBUG_MESSAGEBOX
		MessageBox(hWnd, _T("MapData::Load map data error!"), _T("error"), MB_OK | MB_ICONERROR);
#endif
		return false;
	}
	std::istreambuf_iterator<char> it(ifs);
	std::istreambuf_iterator<char> last;
	std::string str(it, last);

	// ----- �}�b�v�f�[�^�o�^
	// �o�^����
	std::stringstream ss(str);
	std::string tmp;

	// �R�����g�s���X�L�b�v
//	for(int i = 0; i < MAX_DATAPARAM; ++i) {
//		if(!getline(ss, tmp, ',')) {
//#ifdef _DEBUG_MESSAGEBOX
//			MessageBox(hWnd, _T("MapData::map data error!"), _T("error"), MB_OK | MB_ICONERROR);
//#endif
//			return false;
//		}
//	}

	// �J�n�ʒu�ǂݍ���
	getline(ss, tmp, ',');		// X���W�o�^
	m_startPoint.x = stof(tmp);
	getline(ss, tmp, ',');		// Y���W�o�^
	m_startPoint.y = stof(tmp);

	// �t�B�[���h�u���b�N�̃f�[�^�ǂݍ���
	CCharacter* pObj = NULL;
	int			cnt		= 0;
	float		width	= 0.0f;
	float		height	= 0.0f;
	D3DXVECTOR3	color(0.0f, 0.0f, 0.0f);
	while(getline(ss, tmp, ',')) {
		switch(cnt % MAX_DATAPARAM) {
			case DP_ID:
				// TODO:ID��ۑ��������ꍇ�͒ǉ�
				break;

			case DP_TEX:
			{
				LPTSTR ws = new TCHAR[tmp.size() + 1];
				mbstowcs(ws, tmp.c_str(), tmp.size());
				ws[tmp.size()] = '\0';
				pObj = CCharacter::Create(ws);
				pObj->Init();
				delete[] ws;
				break;
			}

			case DP_POSX:
				pObj->TranslateX(stof(tmp));
				break;

			case DP_POSY:
				pObj->TranslateY(stof(tmp));
				break;

			case DP_POSZ:
				pObj->TranslateZ(stof(tmp));
				break;

			case DP_WIDTH:
				width = stof(tmp);
				break;

			case DP_HEIGHT:
				height = stof(tmp);
				pObj->Resize(D3DXVECTOR2(width, height));
				break;

			case DP_ANGLE:
				pObj->RotateZ(stof(tmp));
				break;

			case DP_COLR:
				color.x = stof(tmp);
				break;

			case DP_COLG:
				color.y = stof(tmp);
				break;

			case DP_COLB:
				color.z = stof(tmp);
				pObj->SetColor(color);
				break;

			case DP_COLA:
				pObj->SetAlpha(stof(tmp));
				break;

			case DP_COLFLG:
				stoi(tmp) > 0 ? m_pFieldObj.push_back((CFieldObject*)pObj) : m_pLayoutObj.push_back(pObj);
				break;

			case DP_TYPE:
			{
				// 0:���ʂ̃t�B�[���h�u���b�N
				// 1:�N���A�����t�B�[���h�u���b�N
				// 2:��Q�t�B�[���h�u���b�N
				// 3:���C�A�E�g�u���b�N
				// 4:���C�A�E�g�I�u�W�F�N�g
				int type = stoi(tmp);
				if(type <= BT_OVER)
					m_pFieldObj.back()->SetType(type);
				break;
			}

			default:
				break;
		}

		++cnt;	// ���̃f�[�^��
	}

	return true;
}

//����������������������������������������������������������������������������������������
//	Name        : �}�b�v�f�[�^�j��
//	Description : ���ݕۑ����Ă���}�b�v�f�[�^��j������
//	Arguments   : id / �X�e�[�WID
//	Returns     : ����(true:����)
//����������������������������������������������������������������������������������������
void CMapData::DeleteData()
{
	for(LPFIELDOBJECT_ARRAY_IT it = m_pFieldObj.begin(); it != m_pFieldObj.end(); ++it) {
		SAFE_RELEASE((*it));
	}
	for(LPCHARACTER_ARRAY_IT it = m_pLayoutObj.begin(); it != m_pLayoutObj.end(); ++it) {
		SAFE_RELEASE((*it));
	}
}

//����������������������������������������������������������������������������������������
//	Name        : �t�B�[���h�I�u�W�F�N�g���X�g�擾
//	Description : �t�B�[���h�I�u�W�F�N�g���X�g���擾����
//	Arguments   : pObjList / �t�B�[���h�I�u�W�F�N�g���X�g�̊i�[��|�C���^
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CMapData::GetFieldObjList(LPFIELDOBJECT_ARRAY* pObjList)
{
	pObjList->resize(m_pFieldObj.size());
	std::copy(m_pFieldObj.begin(), m_pFieldObj.end(), pObjList->begin());
}

//����������������������������������������������������������������������������������������
//	Name        : ���C�A�E�g�I�u�W�F�N�g���X�g�擾
//	Description : ���C�A�E�g�I�u�W�F�N�g���X�g���擾����
//	Arguments   : pObjList / ���C�A�E�g�I�u�W�F�N�g���X�g�̊i�[��|�C���^
//	Returns     : None.
//����������������������������������������������������������������������������������������
void CMapData::GetLayoutObjList(LPCHARACTER_ARRAY* pObjList)
{
	pObjList->resize(m_pLayoutObj.size());
	std::copy(m_pLayoutObj.begin(), m_pLayoutObj.end(), pObjList->begin());
}

//����������������������������������������������������������������������������������������
//	Name        : �N���A�����u���b�N���擾
//	Description : �N���A�����t�B�[���h�u���b�N�����擾����
//	Arguments   : None.
//	Returns     : �N���A�����u���b�N��
//����������������������������������������������������������������������������������������
int CMapData::GetClearBlockNum()
{
	int num = 0;
	for(LPFIELDOBJECT_ARRAY_IT it = m_pFieldObj.begin(); it != m_pFieldObj.end(); ++it) {
		if((*it)->GetType() == BT_CLEAR)
			++num;
	}

	return num;
}


//========================================================================================
// private:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : �R���X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CMapData::CMapData()
{
	m_pFieldObj.reserve(INIT_OBJECT_NUM);
	m_pLayoutObj.reserve(INIT_OBJECT_NUM);
	m_startPoint = D3DXVECTOR2(0.0f, 0.0f);
}

//����������������������������������������������������������������������������������������
//	Name        : �f�X�g���N�^
//	Arguments   : None.
//����������������������������������������������������������������������������������������
CMapData::~CMapData()
{
}


//========================================================================================
//	End of File
//========================================================================================