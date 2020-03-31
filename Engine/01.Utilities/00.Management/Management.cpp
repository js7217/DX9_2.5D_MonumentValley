#include "Engine_Include.h"
#include "Management.h"
#include "Scene.h"
#include "Layer.h"

IMPLEMENT_SINGLETON(ENGINE::CManagement)

ENGINE::CManagement::CManagement()
	: m_pGraphicDev(nullptr)
	, m_pScene(nullptr)
	, m_pRenderer(nullptr)
{
}

ENGINE::CManagement::~CManagement()
{
	Release();
}

ENGINE::CComponent* ENGINE::CManagement::GetComponent(CLayer::LAYER_ID eLayerID, 
	const wstring & wstrObjectKey, const wstring & wstrComponentKey)
{
	NULL_CHECK_RETURN(m_pScene, nullptr);

	return m_pScene->GetComponent(eLayerID, wstrObjectKey, wstrComponentKey);
}

list<ENGINE::CGameObject*>* ENGINE::CManagement::GetLst(CLayer::LAYER_ID eLayerID, const wstring & wstrObjectKey)
{
	NULL_CHECK_RETURN(m_pScene, nullptr);

	return m_pScene->GetLst(eLayerID, wstrObjectKey);
}

HRESULT ENGINE::CManagement::InitManagement(LPDIRECT3DDEVICE9 pGraphicDev)
{
	NULL_CHECK_RETURN(pGraphicDev, E_FAIL);

	m_pGraphicDev = pGraphicDev;
	m_pGraphicDev->AddRef(); // 레퍼런스 카운트 하나 증가

	m_pRenderer = CRenderer::Create(pGraphicDev);
	NULL_CHECK_MSG_RETURN(m_pRenderer, L"Renderer Create Failed", E_FAIL);
	return S_OK;
}

void ENGINE::CManagement::Update()
{
	NULL_CHECK_MSG(m_pScene, L"m_pScene is nullptr");
	m_pScene->Update();
}

void ENGINE::CManagement::LateUpdate()
{
	NULL_CHECK_MSG(m_pScene, L"m_pScene is nullptr");
	m_pScene->LateUpdate();
}

void ENGINE::CManagement::Render()
{
	NULL_CHECK_MSG(m_pRenderer, L"m_pRenderer is nullptr");
	if (m_pScene->GetIsEnding()) // 엔딩씬일 경우 Render를 하지 않아야 동영상 출력이 잘된다.
		return;
	m_pRenderer->Render();
}

void ENGINE::CManagement::Release()
{
	ENGINE::SafeDelete(m_pRenderer);
	ENGINE::SafeDelete(m_pScene);
	ENGINE::SafeRelease(m_pGraphicDev);
}
