//========================================================================================
//		File        : System.cpp
//		Program     : �Q�[�����ʃf�[�^/�V�X�e��
//
//		Description : �Q�[���̋��ʃf�[�^�y�уV�X�e���̎���
//
//		History     : 2013/12/05	�쐬�J�n
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


//========================================================================================
// namespace:
//========================================================================================

//����������������������������������������������������������������������������������������
//	Name        : 2�����x�N�g���̊O��
//	Description : D3DXVECTOR2��p����2�����x�N�g���̊O�ς��Z�o����
//	Arguments   : v1 / 1�߂̃x�N�g��
//				  v2 / 2�߂̃x�N�g��
//	Returns     : None.
//����������������������������������������������������������������������������������������
float System::D3DXVec2Cross(const D3DXVECTOR2* v1, const D3DXVECTOR2* v2)
{
	return v1->x * v2->y - v1->y * v2->x;
}

//����������������������������������������������������������������������������������������
//	Name        : �t�@�C��������
//	Description : �w�肵���p�X�̃f�B���N�g�����ɂ���t�@�C������������
//				  �y���֐������Ń������m�ۂ��s�����ߒ��ӁI�z
//	Arguments   : pflist / �t�@�C����
//				  path   / �����f�B���N�g���̃p�X
//	Returns     : None.
//����������������������������������������������������������������������������������������
void System::SearchFileName(LPTSTR_ARRAY *pflist, LPCTSTR path)
{
	// ----- �ϐ��錾
	HANDLE			hFind;		// �����t�@�C���n���h��
	WIN32_FIND_DATA	fd;			// �f�[�^�o�b�t�@
	LPTSTR			tmpPath;	// �p�X�o�b�t�@

	// ----- �p�X�̃R�s�[���쐬
	tmpPath = new TCHAR[_MAX_PATH];
	lstrcpy(tmpPath, path);

	// ----- �ŏ��̃t�@�C��������
	hFind = FindFirstFile(tmpPath, &fd);
	if(hFind == INVALID_HANDLE_VALUE)
	{
#ifdef _DEBUG_MESSAGEBOX
		::MessageBox(NULL, _T("System::SearchFileName FindFirstFile Error!"), _T("error"), MB_OK);
#endif
		FindClose(hFind);
		return;
	}
	tmpPath[lstrlen(tmpPath) - 1] = '\0';	// ���C���h�J�[�h���폜

	// ----- ���̃t�@�C��������
	do
	{
		// �f�B���N�g���Ȃ�Č���
		if((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			lstrcmp(fd.cFileName, _T(".")) != 0 && lstrcmp(fd.cFileName, _T("..")) != 0)
		{
			LPTSTR subPath = new TCHAR[_MAX_PATH];						// �������m��
			wsprintf(subPath, _T("%s%s\\*"), tmpPath, fd.cFileName);	// �����񌋍�
			SearchFileName(pflist, subPath);							// �T�u�f�B���N�g����������
			SAFE_DELETE_ARRAY(subPath);									// ���������
		}

		// �t�@�C���Ȃ�p�X���L�^
		if((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY)
		{
			LPTSTR filePath = new TCHAR[_MAX_PATH];
			wsprintf(filePath, _T("%s%s"), tmpPath, fd.cFileName);
			pflist->push_back(filePath);
		}
	} while(FindNextFile(hFind, &fd));
	
	// ----- ���㏈��
	SAFE_DELETE_ARRAY(tmpPath);
	FindClose(hFind);
}


//========================================================================================
//	End of File
//========================================================================================