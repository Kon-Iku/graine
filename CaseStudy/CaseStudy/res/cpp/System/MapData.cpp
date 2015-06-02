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
	for(int i = 0; i < MAX_DATAPARAM; ++i) {
		if(!getline(ss, tmp, ',')) {
#ifdef _DEBUG_MESSAGEBOX
			MessageBox(hWnd, _T("MapData::map data error!"), _T("error"), MB_OK | MB_ICONERROR);
#endif
			return false;
		}
	}

	// �f�[�^�ǂݍ���
	int		cnt		= 0;
	float	width	= 0.0f;
	float	height	= 0.0f;
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
				CFieldObject* pFieldObj = CFieldObject::Create(ws);
				pFieldObj->Init();
				m_pFieldObj.push_back(pFieldObj);
				delete[] ws;
				break;
			}

			case DP_POSX:
				m_pFieldObj.back()->TranslateX(stof(tmp));
				break;

			case DP_POSY:
				m_pFieldObj.back()->TranslateY(stof(tmp));
				break;

			case DP_POSZ:
				m_pFieldObj.back()->TranslateZ(stof(tmp));
				break;

			case DP_WIDTH:
				width = stof(tmp);
				break;

			case DP_HEIGHT:
				height = stof(tmp);
				m_pFieldObj.back()->Resize(D3DXVECTOR2(width, height));
				break;

			case DP_ANGLE:
				m_pFieldObj.back()->RotateZ(stof(tmp));
				break;

			case DP_COLFLG:
			{
				stoi(tmp) > 0 ? m_pFieldObj.back()->EnableCol() : m_pFieldObj.back()->DisableCol();
				break;
			}

			case DP_TYPE:
				m_pFieldObj.back()->SetrType(stoi(tmp));
				break;

			default:
				break;
		}

		++cnt;	// ���̃f�[�^��
	}

	return true;
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