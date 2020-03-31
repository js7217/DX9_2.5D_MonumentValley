#include "Engine_Include.h"
#include "Scene.h"
#include "Layer.h"

ENGINE::CScene::CScene(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bIsEnding(false)
{
	m_pGraphicDev->AddRef();
}

ENGINE::CScene::~CScene()
{
	Release();
}

ENGINE::CComponent * ENGINE::CScene::GetComponent(CLayer::LAYER_ID eLayerID, const wstring & wstrObjectKey, const wstring & wstrComponentKey)
{
	auto iter_find = m_mapLayer.find(eLayerID);

	if (m_mapLayer.end() == iter_find)
		return nullptr;

	return iter_find->second->GetComponent(wstrObjectKey, wstrComponentKey);
}

list<ENGINE::CGameObject*>* ENGINE::CScene::GetLst(CLayer::LAYER_ID eLayerID, const wstring & wstrObjectKey)
{
	auto iter_find = m_mapLayer.find(eLayerID);

	if(m_mapLayer.end() == iter_find)
		return nullptr;

	return iter_find->second->GetLst(wstrObjectKey);
}

void ENGINE::CScene::Update()
{
	for (auto& rLayer : m_mapLayer)
		(rLayer.second)->Update();
}

void ENGINE::CScene::LateUpdate()
{
	for (auto& rLayer : m_mapLayer)
		(rLayer.second)->LateUpdate();
}

void ENGINE::CScene::Render()
{
	for (auto& rLayer : m_mapLayer)
		(rLayer.second)->Render();
}

HRESULT ENGINE::CScene::Initialize()
{
	return S_OK;
}

void ENGINE::CScene::Release()
{
	ENGINE::SafeRelease(m_pGraphicDev);

	for_each(m_mapLayer.begin(), m_mapLayer.end(), 
		[](auto& MyPair)
	{
		SafeDelete(MyPair.second);
	});
}

void ENGINE::CScene::SetIsEnding(const bool & bIsEnding)
{
	m_bIsEnding = bIsEnding;
}

const bool& ENGINE::CScene::GetIsEnding()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_bIsEnding;
}
