#include "Engine_Include.h"
#include "ResourceMgr.h"
#include "TriCol.h"
#include "RcCol.h"
#include "Cube.h"
#include "PlayerTex.h"
#include "CubeTex.h"
#include "RcTex.h"
#include "Cube.h"
#include "TerrainTex.h"
#include "Texture.h"
#include "Terrain.h"
using namespace ENGINE;

IMPLEMENT_SINGLETON(CResourceMgr)

CResourceMgr::CResourceMgr()
{
}

CResourceMgr::~CResourceMgr()
{
	Release();
}

HRESULT CResourceMgr::AddBuffer(LPDIRECT3DDEVICE9 pGraphiceDev, 
	RESOURCE_TYPE eResourceType, CVIBuffer::BUFFER_TYPE eBufferType, 
	const wstring & wstrResourceKey, 
	const WORD & wCntX, const WORD & wCntY, const WORD & wItv)
{
	auto iter = m_MapResource[eResourceType].find(wstrResourceKey); 

	if (iter != m_MapResource[eResourceType].end()) // 찾는다. 이미 리소스 키가 있는지 없는지.
	{
		MSG_BOX(L"중복 리소스 키");
		return E_FAIL;
	}

	CResources* pResource = nullptr;

	switch (eBufferType)
	{
	case ENGINE::CVIBuffer::BUFFER_TRICOL:
		pResource = CTriCol::Create(pGraphiceDev);
		break;
	case ENGINE::CVIBuffer::BUFFER_RCCOL:
		pResource = CRcCol::Create(pGraphiceDev);
		break;
	case ENGINE::CVIBuffer::BUFFER_CUBE:
		pResource = CCube::Create(pGraphiceDev);
		break;
	case ENGINE::CVIBuffer::BUFFER_CUBETEX:
		pResource = CCubeTex::Create(pGraphiceDev);
		break;
	case ENGINE::CVIBuffer::BUFFER_PLAYER_CUBE:
		pResource = CPlayerTex::Create(pGraphiceDev);
		break;
	case ENGINE::CVIBuffer::BUFFER_RCTEX:
		pResource = CRcTex::Create(pGraphiceDev);
		break;
	case ENGINE::CVIBuffer::BUFFER_TERRAIN:
		pResource = CTerrain::Create(pGraphiceDev, wCntX, wCntY, wItv);
		break;
	case ENGINE::CVIBuffer::BUFFER_TERRAINTEX:
		pResource = CTerrainTex::Create(pGraphiceDev, wCntX, wCntY, wItv);
		break;
	default:
		break;
	}

	NULL_CHECK_RETURN(pResource, E_FAIL);

	m_MapResource[eResourceType].insert({ wstrResourceKey, pResource });

	return S_OK;
}

HRESULT CResourceMgr::AddTexture(LPDIRECT3DDEVICE9 pGraphiceDev, RESOURCE_TYPE eResourceType, TEXTURE_TYPE eTextureType, const wstring & wstrResourceKey, const wstring & wstrFilePath, const WORD & wCnt)
{
	auto iter = m_MapResource[eResourceType].find(wstrResourceKey);

	if (iter != m_MapResource[eResourceType].end()) // 찾는다. 이미 리소스 키가 있는지 없는지.
	{
		MSG_BOX(L"중복 리소스 키");
		return E_FAIL;
	}

	CResources* pResource = CTexture::Create(pGraphiceDev, eTextureType, wstrFilePath, wCnt);
	NULL_CHECK_RETURN(pResource, E_FAIL);

	m_MapResource[eResourceType].insert({ wstrResourceKey, pResource });
	return S_OK;
}

CResources * CResourceMgr::CloneResource(RESOURCE_TYPE eResourceType, const wstring & wstrResourceKey)
{
	auto iter_find = m_MapResource[eResourceType].find(wstrResourceKey);

	if (m_MapResource[eResourceType].end() == iter_find)
		return nullptr;

	return iter_find->second->CloneResource();
}

void CResourceMgr::Render(const wstring & wstrResoruceKey, const short& nIndex)
{
	auto iter = m_MapResource[RESOURCE_STATIC].find(wstrResoruceKey); // 지금은 스테틱만 사용할것.
	
	if (iter == m_MapResource[RESOURCE_STATIC].end())
		return;

	switch (nIndex)
	{
	case -1:
		iter->second->Render(); // 받아온 키 값의 세컨드를 렌더.
		break;
	default:
		dynamic_cast<CTexture*>(iter->second)->Render(nIndex);
		break;
	}
}

void CResourceMgr::ResetDynamaicResource()
{
	for_each(m_MapResource[RESOURCE_DYNAMIC].begin(), m_MapResource[RESOURCE_DYNAMIC].end(),
		[](auto& MyPair)
	{
		SafeDelete(MyPair.second);
	});

	m_MapResource[RESOURCE_DYNAMIC].clear();
}

void CResourceMgr::Release()
{
	for (int i = 0; i < RESOURCE_END; ++i)
	{
		for_each(m_MapResource[i].begin(), m_MapResource[i].end(),
			[](auto& MyPair)
		{
			SafeDelete(MyPair.second);
		});

		m_MapResource[i].clear();
	}
}
