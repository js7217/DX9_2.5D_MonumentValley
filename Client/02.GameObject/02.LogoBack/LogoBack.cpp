#include "stdafx.h"
#include "LogoBack.h"
#include "Texture.h"
#include "VIBuffer.h"
#include "Component.h"
#include "SetTransform.h"
CLogoBack::CLogoBack(LPDIRECT3DDEVICE9 pGraphicDev)
	: ENGINE::CGameObject(pGraphicDev)
	, m_pResourceMgr(ENGINE::Get_ResourceMgr())
	, m_pTimeMgr(ENGINE::Get_TimeMgr())
	, m_pBuffer(nullptr), m_pTexture(nullptr)
	, m_fFrame(0.f), m_fMaxFrame(37.f)
{
}

CLogoBack::~CLogoBack()
{
	Release();
}

void CLogoBack::Update()
{
	CGameObject::Update();

	m_fFrame += m_fMaxFrame * m_pTimeMgr->GetDeltaTime();

	if (m_fFrame > m_fMaxFrame)
		m_fFrame = 0.f;
}

void CLogoBack::LateUpdate()
{
	CGameObject::LateUpdate();
}

void CLogoBack::Render()
{
	D3DXMATRIX matWorld;

//	ENGINE::CSetTransForm::Set_TransForm(D3DTS_WORLD, &matWorld);

	m_pTexture->Render((WORD)m_fFrame);
	m_pBuffer->Render();
}

HRESULT CLogoBack::Initialize()
{
	HRESULT hr = AddComponent();
	FAILED_CHECK_MSG_RETURN(hr, L"Component Add Failed", E_FAIL);

	return S_OK;
}

void CLogoBack::Release()
{
}

HRESULT CLogoBack::AddComponent()
{
	ENGINE::CComponent* pComponent = nullptr;

	pComponent =  m_pResourceMgr->CloneResource(ENGINE::RESOURCE_STATIC, L"Texture_Logo");
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert({ L"Texture", pComponent });
	m_pTexture = dynamic_cast<ENGINE::CTexture*>(pComponent);

	pComponent = m_pResourceMgr->CloneResource(ENGINE::RESOURCE_STATIC, L"Buffer_RcTex");
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert({ L"Buffer", pComponent });
	m_pBuffer = dynamic_cast<ENGINE::CVIBuffer*>(pComponent);

	return S_OK;
}

CLogoBack * CLogoBack::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLogoBack* pInstance = new CLogoBack(pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
