#include "stdafx.h"
#include "BitmapMgr.h"

CBitmapMgr* CBitmapMgr::m_pInstance = nullptr;

CBitmapMgr::CBitmapMgr()
{
}


CBitmapMgr::~CBitmapMgr()
{
	Release();
}

void CBitmapMgr::Insert_Bmp(const TCHAR * _pFilePath, const TCHAR * _pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(_pImgKey));

	// 맵 컨테이너는 탐색 실패시 반환값이 end 이다.
	if (iter == m_mapBit.end())
	{
		CMyBitmap* pBmp = new CMyBitmap;
		pBmp->Load_Bmp(_pFilePath);

		m_mapBit.insert({ _pImgKey, pBmp });
	}
}

HDC CBitmapMgr::Find_Bmp(const TCHAR * _pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(_pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

void CBitmapMgr::Release(void)
{
	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();
}
