#include "stdafx.h"
#include "BodyPart.h"
#include "Arm.h"
#include "Transform.h"
#include "SetTransform.h"
#include "Texture.h"
CArm::CArm()
	: m_pTexture(nullptr)
{
	m_pResourceMgr = ENGINE::Get_ResourceMgr();
	m_pTimeMgr = ENGINE::Get_TimeMgr();
	m_pTransform = ENGINE::CTransform::Create({ { 0.f, 0.f, 1.f } });
	m_pTramsformOpposite = ENGINE::CTransform::Create({ { 0.f, 0.f, 1.f } });
}

CArm::~CArm()
{
	if (nullptr != m_pBuffer)
		ENGINE::SafeDelete(m_pBuffer);

	if (nullptr != m_pTexture)
		ENGINE::SafeDelete(m_pTexture);

	if (nullptr != m_pTransform)
		ENGINE::SafeDelete(m_pTransform);

	if (nullptr != m_pTramsformOpposite)
		ENGINE::SafeDelete(m_pTramsformOpposite);

	m_pTransformTarget = nullptr;
}

void CArm::Update()
{
	float fRatio = 0.2f;

	D3DXMATRIX pMatWorld = m_pTransformTarget->GetWorldMatrix();

	m_pTransform->SetSize(fRatio * D3DXVECTOR3(0.1f, 0.6f, 0.1f));
	m_pTransform->SetAngle(60.f * sinf(7.f * (*m_fTimeCnt)), ENGINE::ANGLE_TYPE::ANGLE_X);
	m_pTransform->SetAngle(m_pTransformTarget->GetAngle(ENGINE::ANGLE_TYPE::ANGLE_Y), ENGINE::ANGLE_TYPE::ANGLE_Y);
	m_pTransform->SetPos({ pMatWorld._41 - 0.6f * fRatio, pMatWorld._42 + 0.85f * fRatio, pMatWorld._43 });
	m_pTransform->Update();


	m_pTramsformOpposite->SetSize(fRatio* D3DXVECTOR3( 0.1f, 0.6f, 0.1f ));
	m_pTramsformOpposite->SetAngle(60.f * -sinf(7.f * (*m_fTimeCnt)), ENGINE::ANGLE_TYPE::ANGLE_X);
	m_pTramsformOpposite->SetAngle(m_pTransformTarget->GetAngle(ENGINE::ANGLE_TYPE::ANGLE_Y), ENGINE::ANGLE_TYPE::ANGLE_Y);
	m_pTramsformOpposite->SetPos({ pMatWorld._41 + 0.6f * fRatio, pMatWorld._42 + 0.85f * fRatio, pMatWorld._43 });
	m_pTramsformOpposite->Update();
}

void CArm::LateUpdate()
{

}

void CArm::Render()
{
	ENGINE::CSetTransForm::Set_TransForm(D3DTS_WORLD, &(m_pTransform->GetWorldMatrix()));

	m_pTexture->Render(1);
	m_pBuffer->Render();

	ENGINE::CSetTransForm::Set_TransForm(D3DTS_WORLD, &(m_pTramsformOpposite->GetWorldMatrix()));
	m_pTexture->Render(1);
	m_pBuffer->Render();
}

HRESULT CArm::Initialize()
{
	m_fTimeCnt = 0;

	ENGINE::CComponent* pComponent = m_pResourceMgr->CloneResource(ENGINE::RESOURCE_STATIC, L"Buffer_CubeCol");
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_pBuffer = dynamic_cast<ENGINE::CVIBuffer*>(pComponent);

	pComponent = m_pResourceMgr->CloneResource(ENGINE::RESOURCE_STATIC, L"Texture_Cube");
	NULL_CHECK_MSG_RETURN(pComponent, L"Texture_Cube Clone Failed", E_FAIL);
	m_pTexture = dynamic_cast<ENGINE::CTexture*>(pComponent);

	return S_OK;
}

CArm * CArm::Create(
	ENGINE::CTransform*	pTransformTarget,
	const wstring&		wstrPartName,
	const float*		fTimeCnt)
{
	CArm* pInstance = new CArm();

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