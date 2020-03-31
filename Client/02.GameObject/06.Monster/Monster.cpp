#include "stdafx.h"
#include "Monster.h"
#include "Texture.h"
#include "VIBuffer.h"
#include "TerrainTex.h"
#include "RcTex.h"
#include "TerrainInfo.h"
#include "Transform.h"
#include "SetTransform.h"
#include "CollTerrain.h"
#include "BillBoard.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	: ENGINE::CGameObject(pGraphicDev)
	, m_pResourceMgr(ENGINE::Get_ResourceMgr())
	, m_pManagement(ENGINE::Get_Management())
	, m_pBuffer(nullptr), m_pTexture(nullptr), m_pTransform(nullptr)
	, m_pCollTerrain(nullptr), m_pBillBoard(nullptr)
{

}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Update()
{
	ENGINE::CGameObject::LateInit();
	ENGINE::CGameObject::Update();
}

void CMonster::LateUpdate()
{
	ENGINE::CGameObject::LateUpdate();
}

void CMonster::Render()
{
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 1);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	ENGINE::CSetTransForm::Set_TransForm(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());
//	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());


	m_pTexture->Render(0);
	m_pBuffer->Render();

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

HRESULT CMonster::Initialize()
{
	HRESULT hr = AddComponent();
	FAILED_CHECK_MSG_RETURN(hr, L"AddComponent Failed", E_FAIL);

	m_pTransform->SetPos({ 0.f, -1.f, 0.f });
	m_pTransform->SetSize({ 1.f, 1.f, 1.f });


	return S_OK;
}

HRESULT CMonster::LateInit()
{
	ENGINE::CVIBuffer* pTerrainBuffer = dynamic_cast<ENGINE::CVIBuffer*>(
		m_pManagement->GetComponent(ENGINE::CLayer::OBJECT, L"Terrain", L"Buffer"));
	// 터레인 버퍼를 Management의 GetComponent 함수로 가져온다.
	NULL_CHECK_RETURN(pTerrainBuffer, E_FAIL);

	ENGINE::CTerrainInfo* pTerrainInfo = dynamic_cast<ENGINE::CTerrainInfo*>(
		m_pManagement->GetComponent(ENGINE::CLayer::OBJECT, L"Terrain", L"TerrainInfo"));

	WORD wCntX = pTerrainInfo->GetCntX();
	WORD wCntY = pTerrainInfo->GetCntZ();
	WORD wItv = pTerrainInfo->GetItv(); // 터레인 정보.

	m_pCollTerrain->SetTargetInfo(m_pTransform, pTerrainBuffer);
	m_pCollTerrain->SetTerrainInfo(wCntX, wCntY, wItv);
	// 가져온 터레인 버퍼의 주소값을 CollTerrain 컴포턴트에 Set시켜준다.
	return S_OK;
}

void CMonster::Release()
{
}

HRESULT CMonster::AddComponent()
{
	ENGINE::CComponent* pComponent = nullptr;
	// 사진
	pComponent = m_pResourceMgr->CloneResource(ENGINE::RESOURCE_STATIC, L"Texture_Cube");
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert({ L"Texture", pComponent });
	m_pTexture = dynamic_cast<ENGINE::CTexture*>(pComponent);

	// 사각형 버텍스 정보
	pComponent = m_pResourceMgr->CloneResource(ENGINE::RESOURCE_STATIC, L"Buffer_PlayerCube");
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert({ L"Buffer", pComponent });
	m_pBuffer = dynamic_cast<ENGINE::CVIBuffer*>(pComponent);

	// 위치정보
	m_pTransform = ENGINE::CTransform::Create({ 0.f, 0.f, 1.f });
	NULL_CHECK_RETURN(m_pTransform, E_FAIL);
	m_mapComponent.insert({ L"Transform", m_pTransform });


	//CollTerrain : 지형충돌
	m_pCollTerrain = CCollTerrain::Create(ENGINE::CCollision::TERRAIN);
	NULL_CHECK_RETURN(m_pCollTerrain, E_FAIL);

	m_mapComponent.insert({ L"CollTerrain", m_pCollTerrain });

	return S_OK;
}

void CMonster::SetPos(const float & fPosX, const float & fPosZ)
{
	m_pTransform->SetPos({ fPosX, -1.f, fPosZ });
}

CMonster * CMonster::Create(LPDIRECT3DDEVICE9 pGraphicDev, const float& fPosX, const float& fPosZ)
{
	CMonster* pInstance = new CMonster(pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	pInstance->SetPos(fPosX, fPosZ);

	return pInstance;
}
