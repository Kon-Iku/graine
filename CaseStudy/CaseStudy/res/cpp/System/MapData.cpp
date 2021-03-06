//========================================================================================
//		File        : MapData.cpp
//		Program     : マップデータクラス
//
//		Description : マップデータクラスの実装
//
//		History     : 2015/05/18	作成開始
//
//																Author : Kei Hashimoto
//========================================================================================


//――――――――――――――――――――――――――――――――――――――――――――
// 警告無効化
//――――――――――――――――――――――――――――――――――――――――――――
#pragma warning(disable:4996)

//――――――――――――――――――――――――――――――――――――――――――――
// インクルード
//――――――――――――――――――――――――――――――――――――――――――――
#include "../../h/System/PreInclude.h"
#
#include <tchar.h>
#include <fstream>
#include <string>
#include <sstream>
#include "../../h/System/MapData.h"

//――――――――――――――――――――――――――――――――――――――――――――
// メンバ実体宣言
//――――――――――――――――――――――――――――――――――――――――――――
// ----- 定数
// private:
LPCTSTR CMapData::MAPDATA_LIST[MAX_STAGEID] = {		// マップデータのファイル名リスト
	_T("res/data/map/Stage1.csv"),
	_T("res/data/map/Stage2.csv"),
	_T("res/data/map/Stage3.csv"),
	_T("res/data/map/Stage4.csv"),
	_T("res/data/map/Stage5.csv"),
};
const int	CMapData::INIT_OBJECT_NUM	= 1000;		// 初期オブジェクト数
const int	CMapData::LAYOUTOBJ_HFRAME	= 6;		// レイアウトオブジェクトの横分割数
const int	CMapData::LAYOUTOBJ_VFRAME	= 2;		// レイアウトオブジェクトの縦分割数

// ----- 変数
// private:
LPFIELDBLOCK_ARRAY	CMapData::m_pFieldBlock;	// フィールドブロックリスト
LPCHARACTER_ARRAY	CMapData::m_pLayoutBlock;	// レイアウトブロックリスト
LPCHARACTER_ARRAY	CMapData::m_pLayoutObject;	// レイアウトオブジェクトリスト
D3DXVECTOR2			CMapData::m_startPoint;		// 開始位置

float	CMapData::m_leftWallX;		// 左壁X座標
float	CMapData::m_rightWallX;		// 右壁X座標
float	CMapData::m_topWallY;		// 上壁Y座標
float	CMapData::m_bottomWallY;	// 下壁Y座標

//――――――――――――――――――――――――――――――――――――――――――――
// グローバル変数宣言
//――――――――――――――――――――――――――――――――――――――――――――
static CMapData& g_mapData = CMapData::GetInstance();		// マップデータクラスの実体生成


//========================================================================================
// public:
//========================================================================================

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	Name        : インスタンス取得
//	Description : マップデータクラスのインスタンスを取得する
//	Arguments   : None.
//	Returns     : マップデータクラス
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
CMapData& CMapData::GetInstance()
{
	// ----- インスタンス生成
	static CMapData mapData;

	return mapData;
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	Name        : マップデータロード
//	Description : 任意のマップデータをロードする
//	Arguments   : id / ステージID
//	Returns     : 成否(true:成功)
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
bool CMapData::LoadData(int id)
{
	// ----- 初期化処理
	m_pFieldBlock.clear();
	m_pLayoutBlock.clear();
	m_pLayoutObject.clear();

	// ----- マップデータ読み込み
	std::ifstream ifs(MAPDATA_LIST[id]);
	if (ifs.fail()) {
#ifdef _DEBUG_MESSAGEBOX
		LPTSTR str = new TCHAR[256];
		_swprintf(str, _T("MapData::Load map data error! stage ID %d."), id);
		MessageBox(NULL, str, _T("error"), MB_OK | MB_ICONERROR);
		delete[] str;
#endif
		return false;
	}
	std::istreambuf_iterator<char> it(ifs);
	std::istreambuf_iterator<char> last;
	std::string str(it, last);

	// ----- マップデータ登録
	// 登録準備
	std::stringstream ss(str);
	std::string tmp;

	// 開始位置読み込み
	getline(ss, tmp, ',');		// X座標登録
	m_startPoint.x = stof(tmp);
	getline(ss, tmp, ',');		// Y座標登録
	m_startPoint.y = stof(tmp);
	getline(ss, tmp);			// 改行をスキップ

	// 左右壁位置読み込み
	getline(ss, tmp, ',');		// 左壁のX座標登録
	m_leftWallX = stof(tmp);
	getline(ss, tmp, ',');		// 右壁のX座標登録
	m_rightWallX = stof(tmp);
	getline(ss, tmp);			// 改行をスキップ

	// 上下壁位置読み込み
	getline(ss, tmp, ',');		// 上壁のY座標登録
	m_topWallY = stof(tmp);
	getline(ss, tmp, ',');		// 下壁のY座標登録
	m_bottomWallY = stof(tmp);
	getline(ss, tmp);			// 改行をスキップ

	// フィールドブロックのデータ読み込み
	CCharacter* pObj = NULL;
	CFieldBlock* pFBlock = NULL;
	int			eid = 0;
	int			prevBid = -1;
	int			cnt = 0;
	float		width = 0.0f;
	float		height = 0.0f;
	D3DXVECTOR3	color(0.0f, 0.0f, 0.0f);
	int			type = -1;
	while (getline(ss, tmp, ',')) {
		switch (cnt % MAX_DATAPARAM) {
		case DP_BID:
			break;

		case DP_EID:
			eid = stoi(tmp);
			if (eid <= 0) {
				pFBlock = CFieldBlock::Create();
				pFBlock->Init();
			}
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
			pObj->SetAlpha(stoi(tmp));
			break;

		case DP_COLFLG:
			if (eid <= 0) {
				m_pFieldBlock.push_back(pFBlock);
			}
			if(stoi(tmp) > 0)
				m_pFieldBlock.back()->SetElement(pObj);
			break;

		case DP_TYPE:
		{
			// 0:普通のフィールドブロック
			// 1:クリア条件フィールドブロック
			// 2:障害フィールドブロック
			// 3:レイアウトブロック
			// 4:レイアウトオブジェクト
			type = stoi(tmp);
			switch(type)
			{
				case BT_NORMAL:
				case BT_CLEAR:
				case BT_OVER:
					m_pFieldBlock.back()->SetType(type);
					break;
		
				case BT_LAYOUT:
					m_pLayoutBlock.push_back(pObj);
					break;

				case BT_LAYOUTOBJ:
					m_pLayoutObject.push_back(pObj);
					break;
			}
				
			break;
		}

		case DP_TEX_NO:
			if(type == BT_LAYOUTOBJ)
				m_pLayoutObject.back()->UVDivision(stoi(tmp), LAYOUTOBJ_HFRAME, LAYOUTOBJ_VFRAME);
			break;

		default:
			break;
		}

		++cnt;	// 次のデータへ
		if (cnt >= MAX_DATAPARAM) {
			getline(ss, tmp);		// 改行をスキップ
			cnt = 0;
		}
	}

	return true;
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	Name        : マップデータ破棄
//	Description : 現在保存しているマップデータを破棄する
//	Arguments   : id / ステージID
//	Returns     : 成否(true:成功)
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CMapData::DeleteData()
{
	for (LPFIELDBLOCK_ARRAY_IT it = m_pFieldBlock.begin(); it != m_pFieldBlock.end(); ++it) {
		SAFE_RELEASE((*it));
	}
	for (LPCHARACTER_ARRAY_IT it = m_pLayoutBlock.begin(); it != m_pLayoutBlock.end(); ++it) {
		SAFE_RELEASE((*it));
	}
	for (LPCHARACTER_ARRAY_IT it = m_pLayoutObject.begin(); it != m_pLayoutObject.end(); ++it) {
		SAFE_RELEASE((*it));
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	Name        : フィールドブロックリスト取得
//	Description : フィールドブロックリストを取得する
//	Arguments   : pObjList / フィールドブロックリストの格納先ポインタ
//	Returns     : None.
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CMapData::GetFieldBlockList(LPFIELDBLOCK_ARRAY* pObjList)
{
	pObjList->resize(m_pFieldBlock.size());
	std::copy(m_pFieldBlock.begin(), m_pFieldBlock.end(), pObjList->begin());
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	Name        : レイアウトブロックリスト取得
//	Description : レイアウトブロックリストを取得する
//	Arguments   : pObjList / レイアウトブロックリストの格納先ポインタ
//	Returns     : None.
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CMapData::GetLayoutBlockList(LPCHARACTER_ARRAY* pObjList)
{
	pObjList->resize(m_pLayoutBlock.size());
	std::copy(m_pLayoutBlock.begin(), m_pLayoutBlock.end(), pObjList->begin());
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	Name        : レイアウトオブジェクトリスト取得
//	Description : レイアウトオブジェクトリストを取得する
//	Arguments   : pObjList / レイアウトオブジェクトリストの格納先ポインタ
//	Returns     : None.
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CMapData::GetLayoutObjectList(LPCHARACTER_ARRAY* pObjList)
{
	pObjList->resize(m_pLayoutObject.size());
	std::copy(m_pLayoutObject.begin(), m_pLayoutObject.end(), pObjList->begin());
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	Name        : クリア条件ブロック数取得
//	Description : クリア条件フィールドブロック数を取得する
//	Arguments   : None.
//	Returns     : クリア条件ブロック数
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
int CMapData::GetClearBlockNum()
{
	int num = 0;
	for (LPFIELDBLOCK_ARRAY_IT it = m_pFieldBlock.begin(); it != m_pFieldBlock.end(); ++it) {
		if ((*it)->GetType() == BT_CLEAR)
			++num;
	}

	return num;
}


//========================================================================================
// private:
//========================================================================================

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	Name        : コンストラクタ
//	Arguments   : None.
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
CMapData::CMapData()
{
	m_pFieldBlock.reserve(INIT_OBJECT_NUM);
	m_pLayoutBlock.reserve(INIT_OBJECT_NUM);
	m_pLayoutObject.reserve(INIT_OBJECT_NUM);
	m_startPoint = D3DXVECTOR2(0.0f, 0.0f);

	m_leftWallX		= 0.0f;
	m_rightWallX	= 0.0f;
	m_topWallY		= 0.0f;
	m_bottomWallY	= 0.0f;
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	Name        : デストラクタ
//	Arguments   : None.
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
CMapData::~CMapData()
{
}


//========================================================================================
//	End of File
//========================================================================================