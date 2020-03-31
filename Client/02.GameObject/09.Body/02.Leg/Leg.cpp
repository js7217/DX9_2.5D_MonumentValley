#include "stdafx.h"
#include "BodyPart.h"
#include "Leg.h"
#include "Transform.h"
#include "SetTransform.h"

CLeg::CLeg()
{
	m_pResourceMgr = ENGINE::Get_ResourceMgr();
	m_pTimeMgr = ENGINE::Get_TimeMgr();
	m_pTransform = ENGINE::CTransform::Create({ { 0.f, 0.f, 1.f } });
	m_pTramsformOpposite = ENGINE::CTransform::Create({ { 0.f, 0.f, 1.f } });
}

CLeg::~CLeg()
{
	if (nullptr != m_pBuffer)
		ENGINE::SafeDelete(m_pBuffer);

	if (nullptr != m_pTransform)
		ENGINE::SafeDelete(m_pTransform);

	if (nullptr != m_pTramsformOpposite)
		ENGINE::SafeDelete(m_pTramsformOpposite);

	m_pTransformTarget = nullptr;
}

void CLeg::Update()
{

	if(0.99f <= sinf(7.f*(*m_fTimeCnt)) || -0.99f >= sinf(7.f*(*m_fTimeCnt)))
		CSoundMgr::GetInstance()->MyPlaySound(L"foot.wav", CSoundMgr::PLAYER);

	float fRatio = 0.2f;

	D3DXMATRIX pMatWorld = m_pTransformTarget->GetWorldMatrix();

	m_pTransform->SetSize(fRatio * D3DXVECTOR3( 0.1f, 0.7f, 0.1f ));
	m_pTransform->SetAngle(30 * -sinf( 7.f*(*m_fTimeCnt)), ENGINE::ANGLE_TYPE::ANGLE_X);
	m_pTransform->SetAngle(m_pTransformTarget->GetAngle(ENGINE::ANGLE_TYPE::ANGLE_Y), 
		ENGINE::ANGLE_TYPE::ANGLE_Y);
	m_pTransform->SetPos({ pMatWorld._41 - 0.2f * fRatio, pMatWorld._42 , pMatWorld._43 });
	m_pTransform->Update();


	m_pTramsformOpposite->SetSize(fRatio * D3DXVECTOR3(0.1f, 0.7f, 0.1f));
	m_pTramsformOpposite->SetAngle(30 * sinf(7.f*(*m_fTimeCnt)), ENGINE::ANGLE_TYPE::ANGLE_X);
	m_pTramsformOpposite->SetAngle(m_pTransformTarget->GetAngle(ENGINE::ANGLE_TYPE::ANGLE_Y),
		ENGINE::ANGLE_TYPE::ANGLE_Y);
	m_pTramsformOpposite->SetPos({ pMatWorld._41 + 0.2f* fRatio, pMatWorld._42 , pMatWorld._43 });
	m_pTramsformOpposite->Update();
}

void CLeg::LateUpdate()
{

}

void CLeg::Render()
{
	ENGINE::CSetTransForm::Set_TransForm(D3DTS_WORLD, &(m_pTransform->GetWorldMatrix()));

	m_pBuffer->Render();

	ENGINE::CSetTransForm::Set_TransForm(D3DTS_WORLD, &(m_pTramsformOpposite->GetWorldMatrix()));

	m_pBuffer->Render();
}

HRESULT CLeg::Initialize()
{
	m_fTimeCnt = 0;

	ENGINE::CComponent* pComponent = m_pResourceMgr->CloneResource(ENGINE::RESOURCE_STATIC, L"Buffer_CubeCol");
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_pBuffer = dynamic_cast<ENGINE::CVIBuffer*>(pComponent);

	return S_OK;
}

CLeg * CLeg::Create(
	ENGINE::CTransform*	pTransformTarget,
	const wstring&		wstrPartName,
	const float*		fTimeCnt)
{
	CLeg* pInstance = new CLeg();

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
