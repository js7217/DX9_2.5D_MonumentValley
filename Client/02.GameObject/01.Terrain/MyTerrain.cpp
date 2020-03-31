#include "stdafx.h"
#include "MyTerrain.h"
#include "Texture.h"
#include "VIBuffer.h"
#include "Transform.h"
#include "SetTransform.h"
#include "TerrainInfo.h"
#include "CollTerrain.h"

CMyTerrain::CMyTerrain(LPDIRECT3DDEVICE9 pGraphicDev, const WORD & wCntX, const WORD & wCntY, const WORD & wItv)
	: ENGINE::CGameObject(pGraphicDev)
	, m_pResourceMgr(ENGINE::Get_ResourceMgr())
	, m_pManagement(ENGINE::Get_Management())
	, m_pBuffer(nullptr), m_pTexture(nullptr), m_pTransform(nullptr), m_pTerrainInfo(nullptr)
{

}

CMyTerrain::~CMyTerrain()
{
	Release();
}

void CMyTerrain::Update()
{
	ENGINE::CGameObject::LateInit();
	ENGINE::CGameObject::Update();
}

void CMyTerrain::LateUpdate()
{
	ENGINE::CGameObject::LateUpdate();

}

void CMyTerrain::Render()
{
//	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

//	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());
	ENGINE::CSetTransForm::Set_TransForm(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());
//	m_pBuffer->Set_Transform();
	m_pTexture->Render(0);
	m_pBuffer->Render();
//	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

HRESULT CMyTerrain::AddComponent()
{
	ENGINE::CComponent* pComponent = nullptr;
	
	pComponent = m_pResourceMgr->CloneResource(ENGINE::RESOURCE_STATIC, L"Texture_Terrain");
	NULL_CHECK_MSG_RETURN(pComponent, L"Texture_Terrain Clone Failed", E_FAIL);
	m_mapComponent.insert({ L"Texture", pComponent });
	m_pTexture = dynamic_cast<ENGINE::CTexture*>(pComponent);

	pComponent = m_pResourceMgr->CloneResource(ENGINE::RESOURCE_DYNAMIC, L"Buffer_TerrainTex");
	NULL_CHECK_MSG_RETURN(pComponent, L"Buffer_TerrainTex Clone Failed", E_FAIL);
	m_mapComponent.insert({ L"Buffer", pComponent });
	m_pBuffer = dynamic_cast<ENGINE::CVIBuffer*>(pComponent);

	// Transform
	m_pTransform = ENGINE::CTransform::Create({ 0.f, 0.f, 1.f });
	NULL_CHECK_MSG_RETURN(m_pTransform, L"Transform Component Failed", E_FAIL);
	m_mapComponent.insert({ L"Transform", m_pTransform });
	// Terrain Info
	m_pTerrainInfo = ENGINE::CTerrainInfo::Create();
	NULL_CHECK_MSG_RETURN(m_pTerrainInfo, L"TerrainInfo Component Failed", E_FAIL);
	m_mapComponent.insert({ L"TerrainInfo", m_pTerrainInfo });

	return S_OK;
}

HRESULT CMyTerrain::Initialize()
{
	HRESULT hr = AddComponent();
	FAILED_CHECK_MSG_RETURN(hr, L"Terrain AddComponent Failed", E_FAIL);

	m_pTransform->SetSize({ 1.f, 1.f, 1.f });
	m_pTransform->SetPos({ 0.f, 0.f, 0.f });
	return S_OK;
}

HRESULT CMyTerrain::LateInit()
{
	
	return S_OK;
}

void CMyTerrain::Release()
{
}

CMyTerrain * CMyTerrain::Create(LPDIRECT3DDEVICE9 pGraphicDev, const WORD & wCntX, const WORD & wCntY, const WORD & wItv)
{
	CMyTerrain* pInstance = new CMyTerrain(pGraphicDev, wCntX, wCntY, wItv);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	pInstance->m_pTerrainInfo->SetTerrainInfo(wCntX, wCntY, wItv);

	return pInstance;
}
