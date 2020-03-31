#include "Engine_Include.h"
#include "Layer.h"
#include "GameObject.h"

using namespace ENGINE;

CLayer::CLayer(LPDIRECT3DDEVICE9 pGraphicDev)
	:m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev->AddRef();
}

CLayer::~CLayer()
{
	Release();
}

CComponent * CLayer::GetComponent(const wstring & wstrObjectKey, const wstring & wstrComponentKey)
{
	auto iter_ObjList = m_mapObjList.find(wstrObjectKey);

	if (m_mapObjList.end() == iter_ObjList)
		return nullptr;

	CComponent* pComponent = nullptr;

	for (auto& iter_find : (iter_ObjList->second))
	{
		pComponent = iter_find->GetComponent(wstrComponentKey);

		if (nullptr != pComponent)
			return pComponent;
	}

	return nullptr;
}

list<CGameObject*>* CLayer::GetLst(const wstring & wstrObjectKey)
{
	auto iter_find = m_mapObjList.find(wstrObjectKey);

	if (m_mapObjList.end() == iter_find)
		return nullptr;

	return &iter_find->second;
}

HRESULT CLayer::AddObject(const wstring & wstrObjectKey, CGameObject * pObject)
{
	NULL_CHECK_RETURN(pObject, E_FAIL);

	MAP_OBJLST::iterator iter_find = m_mapObjList.find(wstrObjectKey);

	if (m_mapObjList.end() != iter_find)
		m_mapObjList[wstrObjectKey].emplace_back(pObject);
	else
	{
		OBJLST ObjList;
		ObjList.emplace_back(pObject);
		pair<wstring, OBJLST> p(wstrObjectKey, ObjList);

		m_mapObjList.insert(p);
	}

	return S_OK;
}

void CLayer::Update()
{
	for (auto& pObjList : m_mapObjList)
	{
		for (auto& pObj : pObjList.second)
		{
			pObj->Update();
		}
	}
}

void CLayer::LateUpdate()
{
	for (auto& pObjList : m_mapObjList)
	{
		for (auto& pObj : pObjList.second)
		{
			pObj->LateUpdate();
		}
	}
}

void CLayer::Render()
{
	for (auto& pObjList : m_mapObjList)
	{
		if (L"Block" == pObjList.first ||
			L"OptimizationBlock" == pObjList.first ||
			L"InteractionBlock" == pObjList.first)
			continue;
		for (auto& pObj : pObjList.second)
		{
			pObj->Render();
		}
	}
}

void CLayer::Release()
{
	SafeRelease(m_pGraphicDev);

	for (auto& pObjList : m_mapObjList)
	{
		for (auto& pObj : pObjList.second)
		{
			SafeDelete(pObj);
		}
		pObjList.second.clear();
	}

	m_mapObjList.clear();
}

CLayer * CLayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return new CLayer(pGraphicDev);
}
