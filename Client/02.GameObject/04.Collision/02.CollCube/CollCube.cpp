#include "stdafx.h"
#include "CollCube.h"
#include "Transform.h"
#include "GameObject.h"

CCollCube::CCollCube()
	: m_pCollisionMgr(CCollisionMgr::GetInstance())
{
}

CCollCube::CCollCube(ENGINE::CCollision::COLLISION_TYPE eType)
	: CCollision(eType)
	, m_pTarget(nullptr), m_pCubeVtx(nullptr)
{
}

CCollCube::~CCollCube()
{

}

void CCollCube::SetTargetInfo(ENGINE::CTransform * pTarget, list<ENGINE::CGameObject*>* pObjLst)
{
	NULL_CHECK(pTarget);
	NULL_CHECK(pObjLst);

	m_pTarget = pTarget;
	m_pCubeLst = pObjLst;

	for (auto& pLst : *m_pCubeLst)
	{
		ENGINE::CComponent* pComponent = pLst->GetComponent(L"Buffer");
		ENGINE::CVIBuffer* pBuffer = dynamic_cast<ENGINE::CVIBuffer*>(pComponent);
	}
}

void CCollCube::LateUpdate()
{
	ENGINE::CComponent* pComponent = nullptr;
	D3DXVECTOR3 vTargetPos = m_pTarget->GetPos();

	D3DXVECTOR3 vTargetDir = m_pTarget->GetDir();

	printf("%f, %f, %f\n", vTargetDir.x, vTargetDir.y, vTargetDir.z);

	ENGINE::CGameObject* pClosestCube = nullptr;
	float fMinimumDist = 100000000.f; //가장 가까운 큐브와의 거리를 저장하는 변수
		
	//가장 가까운 큐브를 검사
	for(auto& pLst : *m_pCubeLst)
	{
		pComponent = pLst->GetComponent(L"Transform");
		D3DXVECTOR3 vDstPos = dynamic_cast<ENGINE::CTransform*>(pComponent)->GetPos();
		if (m_pCollisionMgr->IntersectSphere(0.5f, vTargetPos, 1.5f, vDstPos))
		{
			float fDist = D3DXVec3Length(&(vTargetPos - vDstPos));

			if (fMinimumDist > fDist)
				pClosestCube = pLst;
			else
				pClosestCube = nullptr;
		}
	}
	
	if (nullptr != pClosestCube)
	{
		pComponent = pClosestCube->GetComponent(L"Transform");
		D3DXVECTOR3 vPos = dynamic_cast<ENGINE::CTransform*>(pComponent)->GetPos();

		float fDist = D3DXVec3Length(&(vPos - vTargetPos));

		//가장 가까운 큐브의 중점
		//D3DXVECTOR3 vCenter = { m_pCubeVtx[0].vPos.x + (0.5f), m_pCubeVtx[0].vPos.y + (0.5f), m_pCubeVtx[0].vPos.z + 0.5f };

		
		if (fDist <= 0.5f)
		{
			//가상 가까운 큐브의 버퍼 가져오기
			pComponent = pClosestCube->GetComponent(L"Buffer");
			ENGINE::CVIBuffer* pBuffer = dynamic_cast<ENGINE::CVIBuffer*>(pComponent);
			m_pCubeVtx = (ENGINE::VTX_CUBE*)(pBuffer->GetOriginVtxInfo());

			//상하단 삼각형 구별
			float fRatioX = 0.f, fRatioZ = 0.f;
			fRatioX = fabs(vTargetPos.x - m_pCubeVtx[4].vPos.x);
			fRatioZ = fabs(m_pCubeVtx[4].vPos.z - vTargetPos.z);

			m_pCubeVtx[0].vPos.x += 0.5f;
			m_pCubeVtx[0].vPos.z += 0.5f;

			D3DXPLANE Plane;

			if (fRatioX > fRatioZ)
			{
				D3DXPlaneFromPoints(
					&Plane,
					&m_pCubeVtx[4].vPos,
					&m_pCubeVtx[1].vPos,
					&m_pCubeVtx[0].vPos);
			}
			else
			{
				D3DXPlaneFromPoints(
					&Plane,
					&m_pCubeVtx[4].vPos,
					&m_pCubeVtx[5].vPos,
					&m_pCubeVtx[1].vPos);
			}

			vTargetPos.y = (-Plane.a * vTargetPos.x - Plane.c * vTargetPos.z - Plane.d) / Plane.b;
			vTargetPos.y += 0.1f;
		}	
	}
	else
	{	
		//vTargetPos.y = 0.f;
	}

	m_pTarget->SetPos(vTargetPos);
	
	
	
}

CCollCube * CCollCube::Create(ENGINE::CCollision::COLLISION_TYPE eType)
{
	return new CCollCube(eType);
}
