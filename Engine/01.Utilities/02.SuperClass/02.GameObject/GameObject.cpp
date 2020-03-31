#include "Engine_Include.h"
#include "GameObject.h"
#include "Component.h"

using namespace ENGINE;

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bIsInit(false)
{
	m_pGraphicDev->AddRef();

}

CGameObject::~CGameObject()
{
	Release();
}

CComponent * CGameObject::GetComponent(const wstring & wstrComponentKey)
{
	auto iter_find = m_mapComponent.find(wstrComponentKey);

	if (m_mapComponent.end() == iter_find)
		return nullptr;

	return iter_find->second;
}

void CGameObject::Update()
{
	for (auto& iter : m_mapComponent)
	{
		(iter.second)->Update();
	}
}

void CGameObject::LateUpdate()
{
	for (auto& iter : m_mapComponent)
	{
		(iter.second)->LateUpdate();
	}
}

void CGameObject::Render()
{
	for (auto& iter : m_mapComponent)
	{
		(iter.second)->Render();
	}
}

HRESULT CGameObject::Initialize()
{
	return S_OK;
}

HRESULT CGameObject::LateInit()
{
	if (!m_bIsInit)
	{
		this->LateInit();
		m_bIsInit = true;
	}

	return S_OK;
}

void CGameObject::Release()
{
	SafeRelease(m_pGraphicDev);

	for_each(m_mapComponent.begin(), m_mapComponent.end(), 
		[](auto& MyPair)
	{
		SafeDelete(MyPair.second);
	});

	m_mapComponent.clear();
}
