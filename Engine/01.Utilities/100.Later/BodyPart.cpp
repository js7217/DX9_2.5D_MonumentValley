#include "Engine_Include.h"
#include "BodyPart.h"
#include "Transform.h"


using namespace ENGINE;

CBodyPart::CBodyPart()
	: m_pTransformTarget(nullptr)
	, m_pTransform(nullptr)
	, m_pBuffer(nullptr)
	, m_pTimeMgr(nullptr)
	, m_pResourceMgr(nullptr)
{
}

CBodyPart::~CBodyPart()
{
	////if (nullptr != m_pBuffer)
	////	ENGINE::SafeDelete(m_pBuffer);

	//if (nullptr != m_pTransform)
	//	ENGINE::SafeDelete(m_pTransform);

	//if (nullptr != m_pTransformTarget)
	//	ENGINE::SafeDelete(m_pTransformTarget);
}

const wstring & CBodyPart::GetPartsName()
{
	// 내 이름은
	return m_wstrPartName;
}

const D3DXMATRIX* CBodyPart::GetWorld()
{
	//나의 월드 행렬을 반환
	return &(m_pTransform->GetWorldMatrix());
}

const float* CBodyPart::GetTimer()
{
	return m_fTimeCnt;
}

void CBodyPart::SetTransform(const CTransform* pTransform)
{
	//종속되어 있는 파츠의  월드의 행렬을 업데이트
	m_pTransformTarget = pTransform;
}

void CBodyPart::SetTimer(const float* fTimeCnt)
{
	m_fTimeCnt = fTimeCnt;
}
