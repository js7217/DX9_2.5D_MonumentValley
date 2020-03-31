#include "stdafx.h"
#include "BodyPart.h"
#include "Head.h"
#include "Transform.h"
#include "SetTransform.h"

CHead::CHead()
{
	m_pResourceMgr = ENGINE::Get_ResourceMgr();
	m_pTimeMgr = ENGINE::Get_TimeMgr();
	m_pTransform = ENGINE::CTransform::Create({ { 0.f, 0.f, 1.f } });
}

CHead::~CHead()
{
	if (nullptr != m_pBuffer)
		ENGINE::SafeDelete(m_pBuffer);

	if (nullptr != m_pTransform)
		ENGINE::SafeDelete(m_pTransform);

	m_pTransformTarget = nullptr;
}

void CHead::Update()
{
	float fRatio = 0.2f;
	
	D3DXMATRIX pMatWorld = m_pTransformTarget->GetWorldMatrix();

	m_pTransform->SetSize(fRatio * D3DXVECTOR3( 0.6f, 0.5f, 0.4f ));

	m_pTransform->SetAngle(m_pTransformTarget->GetAngle(ENGINE::ANGLE_TYPE::ANGLE_Y), ENGINE::ANGLE_TYPE::ANGLE_Y);

	m_pTransform->SetPos({ pMatWorld._41, pMatWorld._42 + 2.1f * fRatio, pMatWorld._43 });

	m_pTransform->Update();
}

void CHead::LateUpdate()
{

}

void CHead::Render()
{
	ENGINE::CSetTransForm::Set_TransForm(D3DTS_WORLD, &(m_pTransform->GetWorldMatrix()));

	m_pBuffer->Render();
}

HRESULT CHead::Initialize()
{
	m_fTimeCnt = 0;

	ENGINE::CComponent* pComponent = m_pResourceMgr->CloneResource(ENGINE::RESOURCE_STATIC, L"Buffer_CubeCol");
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_pBuffer = dynamic_cast<ENGINE::CVIBuffer*>(pComponent);

	return S_OK;
}

CHead * CHead::Create(
	ENGINE::CTransform*	pTransformTarget,
	const wstring&		wstrPartName,
	const float*		fTimeCnt)
{
	CHead* pInstance = new CHead();

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	pInstance->m_wstrPartName = wstrPartName;
	pInstance->m_pTransformTarget = pTransformTarget;
	pInstance->m_fTimeCnt = fTimeCnt;

	return pInstance;
}
