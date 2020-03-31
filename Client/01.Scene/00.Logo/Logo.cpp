#include "stdafx.h"
#include "Logo.h"
#include "Layer.h"
#include "LogoBack.h"
#include "SceneSelector.h"
#include "KeyMgr.h"
CLogo::CLogo(LPDIRECT3DDEVICE9 pGraphicDev)
	: ENGINE::CScene(pGraphicDev)
	, m_pManagement(ENGINE::Get_Management())
	, m_pResourceMgr(ENGINE::Get_ResourceMgr())
	, m_pKeyMgr(ENGINE::CKeyMgr::GetInstance())
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Update()
{
	ENGINE::CScene::Update();
}

void CLogo::LateUpdate()
{
	ENGINE::CScene::LateUpdate();

	
}

void CLogo::Render()
{
	CFrameMgr::GetInstance()->RenderFrame();

	ENGINE::CScene::Render();

	if (m_pKeyMgr->KeyDown(KEY_RETURN))
	{
		m_pManagement->SceneChange(CSceneSelector(CSceneSelector::STAGE));
		return;
	}
}

HRESULT CLogo::Initialize()
{
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	HRESULT hr = m_pResourceMgr->AddBuffer(m_pGraphicDev, ENGINE::RESOURCE_STATIC,
		ENGINE::CVIBuffer::BUFFER_RCTEX, L"Buffer_RcTex");
	FAILED_CHECK_MSG_RETURN(hr, L"Buffer_RcTex Add Failed", E_FAIL);

	hr = m_pResourceMgr->AddTexture(m_pGraphicDev, ENGINE::RESOURCE_STATIC,
		ENGINE::TEX_NORMAL, L"Texture_Logo", L"../Bin/Resources/Texture/LogoBack/LogoBack_%d.png", 38);
	FAILED_CHECK_MSG_RETURN(hr, L"LogoBack Add Failed", E_FAIL);


	hr = Add_Object_Layer();
	FAILED_CHECK_MSG_RETURN(hr, L"Object Layer Add Failed", E_FAIL);

	return S_OK;
}

void CLogo::Release()
{

}


CLogo * CLogo::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLogo* pInstance = new CLogo(pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

HRESULT CLogo::Add_Environment_Layer()
{
	return E_NOTIMPL;
}

HRESULT CLogo::Add_Object_Layer()
{
	// Layer 생성.
	ENGINE::CLayer* pObjLayer = ENGINE::CLayer::Create(m_pGraphicDev);

	//LogoBack 생성
	ENGINE::CGameObject* pGameObject = CLogoBack::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);

	//Layer에 LogoBack 추가
	HRESULT hr = pObjLayer->AddObject(L"LogoBack", pGameObject);
	FAILED_CHECK_RETURN(hr, E_FAIL);

	// OBJECT Layer Key에 만든 Layer 추가.
	m_mapLayer.insert({ ENGINE::CLayer::OBJECT, pObjLayer });

	return S_OK;
}

HRESULT CLogo::Add_UI_Layer()
{
	return E_NOTIMPL;
}
