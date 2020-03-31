#include "Engine_Include.h"
#include "Renderer.h"
#include "Scene.h"
ENGINE::CRenderer::CRenderer(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_pScene(nullptr)
{
	m_pGraphicDev->AddRef();
}

ENGINE::CRenderer::~CRenderer()
{
	Release();
}

void ENGINE::CRenderer::SetScene(CScene * pScene)
{
	NULL_CHECK_MSG(pScene, L"pScene is nullptr");
	m_pScene = pScene;
}

void ENGINE::CRenderer::Render()
{
	m_pGraphicDev->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	m_pGraphicDev->BeginScene();
	NULL_CHECK_MSG(m_pScene, L"pScene Is nullptr");

	m_pScene->Render();

	m_pGraphicDev->EndScene();
	m_pGraphicDev->Present(nullptr, nullptr, nullptr, nullptr);
}

HRESULT ENGINE::CRenderer::Initialize()
{
	return S_OK;
}

void ENGINE::CRenderer::Release()
{
	ENGINE::SafeRelease(m_pGraphicDev);
}

ENGINE::CRenderer* ENGINE::CRenderer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	NULL_CHECK_RETURN(pGraphicDev, nullptr);

	CRenderer* pInstance = new CRenderer(pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}
