#include "stdafx.h"
#include "TextureMgr.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr()
{
}


CTextureMgr::~CTextureMgr()
{
	Release();
}

const TEX_INFO * CTextureMgr::GetTexInfo(
	const wstring & wstrObjKey, 
	const wstring & wstrStateKey, 
	const DWORD & dwIndex) const
{
	auto iter_find = m_MapTexture.find(wstrObjKey);

	if (m_MapTexture.end() == iter_find)
		return nullptr;

	return iter_find->second->GetTexInfo(wstrStateKey, dwIndex);
}

HRESULT CTextureMgr::InsertTexture(
	TEX_TYPE eTextureType, 
	const wstring & wstrFilePath, 
	const wstring & wstrObjKey, 
	const wstring & wstrStateKey, 
	const DWORD & dwCnt)
{
	CSpriteTexture* pTexture = nullptr;

	switch (eTextureType)
	{
	case TEX_SINGLE:
		pTexture = new CSingleTexture;
		break;
	case TEX_MULTI:
		pTexture = new CMultiTexture;
		break;
	}

	auto iter_find = m_MapTexture.find(wstrObjKey);

	if (m_MapTexture.end() == iter_find)
	{
		m_MapTexture[wstrObjKey] = pTexture;

		if (FAILED(pTexture->InsertTexture(wstrFilePath, wstrStateKey, dwCnt)))
		{
			MessageBox(g_hWnd, L"InsertTexture Failed", nullptr, MB_OK);
			return E_FAIL;
		}
	}
	else if (TEX_MULTI == eTextureType)
	{
		if (FAILED(m_MapTexture[wstrObjKey]->InsertTexture(wstrFilePath, wstrStateKey, dwCnt)))
		{
			MessageBox(g_hWnd, L"InsertTexture Failed", nullptr, MB_OK);
			return E_FAIL;
		}
	}

	return S_OK;
}

void CTextureMgr::Release()
{
	for_each(m_MapTexture.begin(), m_MapTexture.end(),
		[](auto& MyPair)
	{
		ENGINE::SafeDelete(MyPair.second);
	});

	m_MapTexture.clear();
}
