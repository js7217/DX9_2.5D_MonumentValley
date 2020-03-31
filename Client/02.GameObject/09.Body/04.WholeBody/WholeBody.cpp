#include "stdafx.h"
#include "WholeBody.h"
#include "Component.h"
#include "Transform.h"

//각종 부품/////////////////////////
#include "MainBody.h"
#include "Head.h"
#include "Arm.h"
#include "Leg.h"
////////////////////////////////////

CWholeBody::CWholeBody(
	LPDIRECT3DDEVICE9 pGraphicDev,
	ENGINE::CTransform* pTransformTarget,
	const float* fTimeCnt)
	: ENGINE::CGameObject(pGraphicDev)
	, m_pTransformTarget(pTransformTarget)
	, m_fTimeCnt(fTimeCnt)
{
}

CWholeBody::~CWholeBody()
{
	Release();
}

void CWholeBody::Update()
{
	CGameObject::Update();
}

void CWholeBody::LateUpdate()
{
	CGameObject::LateUpdate();
}

void CWholeBody::Render()
{
	CGameObject::Render();
}

HRESULT CWholeBody::Initialize()
{
	HRESULT hr = AddComponent();
	FAILED_CHECK_MSG_RETURN(hr, L"AddComponent Failed", E_FAIL);

	return S_OK;
}

HRESULT CWholeBody::LateInit()
{
	CGameObject::LateInit();
	return S_OK;
}

void CWholeBody::Release()
{

}

HRESULT CWholeBody::AddComponent()
{
	ENGINE::CComponent* pComponent = nullptr;

	//Transform
	m_pTransform = ENGINE::CTransform::Create({0.f, 1.f, 0.f});
	NULL_CHECK_RETURN(m_pTransform, E_FAIL);
	m_mapComponent.insert({ L"Transform", m_pTransform });

	//BODY
	pComponent = CMainBody::Create(m_pTransformTarget, L"MainBody", m_fTimeCnt);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert({ L"Buffer_MainBody", pComponent });

	//HEAD
	pComponent = CHead::Create(m_pTransformTarget, L"Head", m_fTimeCnt);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert({ L"Buffer_Head", pComponent });

	//LEG
	pComponent = CLeg::Create(m_pTransformTarget, L"Leg", m_fTimeCnt);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert({ L"Buffer_Leg", pComponent });

	//ARM
	pComponent = CArm::Create(m_pTransformTarget, L"Arm", m_fTimeCnt);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert({ L"Buffer_Arm", pComponent });

	return S_OK;
}

CWholeBody * CWholeBody::Create(
	LPDIRECT3DDEVICE9 pGraphicDev,
	ENGINE::CTransform* pTransformTarget,
	const float* fTimeCnt)
{
	CWholeBody* pInstance = 
		new CWholeBody(pGraphicDev, pTransformTarget, fTimeCnt);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
