#include "stdafx.h"
#include "CollisionMgr.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Component.h"
#include "Collision.h"
#include "Block.h"

IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::CCollisionMgr()
	: m_bIsValid(true), m_bIsSceneChange(false), m_bIsStair3(false), m_bIsSphereColl(true)
{
}

CCollisionMgr::~CCollisionMgr()
{
	m_mapSphere.clear();
}

void CCollisionMgr::OBB(const wstring& wstrSrcLst, const wstring& wstrDstLst)
{

}

void CCollisionMgr::AABB(const wstring& wstrSrcLst, const wstring& wstrDstLst)
{
	//CComponent* pComponent = nullptr;
}

void CCollisionMgr::CollisionSphere(const wstring& wstrSrcLst, const wstring& wstrDstLst)
{
	if (m_mapSphere[wstrSrcLst].empty() ||
		m_mapSphere[wstrDstLst].empty())
		return;
	 
	for (auto& pSource : m_mapSphere[wstrSrcLst])
	{
		for (auto& pDest : m_mapSphere[wstrDstLst])
		{
			if (pSource == pDest)
				return;

			D3DXVECTOR3 vDist = pSource->GetPos() - pDest->GetPos();
			 
			if (IntersectSphere(
				pSource->GetRadius(), pSource->GetPos(),
				pDest->GetRadius(), pDest->GetPos()))
			{
				
				D3DXVECTOR3 vDir = pDest->GetPos() - pSource->GetPos();	//충돌시 방향
				D3DXVec3Normalize(&vDir, &vDir);						//방향 정규화

				float fOverLap = fabs((pSource->GetRadius() + pDest->GetRadius())
					- D3DXVec3Length(&(pDest->GetPos() - pSource->GetPos())));	//겹치는 영역 길이

				//pSource->SetPos(pSource->GetPos() + ((-1.01f) * vDir * fOverLap));	//충돌한 방향의 반대방향으로 밀어내기	
			}

		}
	}
}

void CCollisionMgr::Collision_OpMz_Nor()
{
	NULL_CHECK(m_CubeList);
	NULL_CHECK(m_OptimizationList);

	for (auto& pVecOpMz : *m_OptimizationList)
	{
		for (auto& pOpMzBlock : pVecOpMz)
		{
			for (auto& pNorBlock : *m_CubeList)
			{
				D3DXVECTOR3 vDist = pOpMzBlock->Get_CubePos() - pNorBlock->Get_CubePos();

				float fRadius_OpMz = 0.5f;
				float fRadius_Nor = 0.5f;

				if (IntersectSphere(
					fRadius_OpMz, pOpMzBlock->Get_CubePos(),
					fRadius_Nor, pNorBlock->Get_CubePos()))
				{
					m_bIsValid = false;
					D3DXVECTOR3 vDir =  pNorBlock->Get_CubePos() - pOpMzBlock->Get_CubePos();
					D3DXVec3Normalize(&vDir, &vDir);

					float fOverLap = fabs((fRadius_OpMz + fRadius_Nor))
						- D3DXVec3Length(&(pNorBlock->Get_CubePos() - pOpMzBlock->Get_CubePos()));	

					for (auto& pOpMzBlock : pVecOpMz)
					{
						pOpMzBlock->SetPos(pOpMzBlock->Get_CubePos() + ((-1.1f) * vDir * fOverLap));
					}				
				}		
			}	
		}
		
		
	}
}

void CCollisionMgr::AddCollider(const wstring & wstrColliderName, ENGINE::CSphereCollider * pCollider)
{
	auto& iter_find = m_mapSphere.find(wstrColliderName);

	//if (m_mapSphere.end() != iter_find)
	//	return;

	m_mapSphere[wstrColliderName].push_back(pCollider);
}

void CCollisionMgr::AddCollider(const wstring & wstrColliderName, ENGINE::CBoxCollider * pCollider)
{
	auto& iter_find = m_mapBox.find(wstrColliderName);

	if (m_mapBox.end() != iter_find)
		return;

	m_mapBox[wstrColliderName].push_back(pCollider);
}

bool CCollisionMgr::IntersectSphere(
	const float& fRadiousSrc,
	const D3DXVECTOR3& vCenterSrc,
	const float& fRadiousDst,
	const D3DXVECTOR3& vCenterDst,
	float* vDist)
{
	if (!m_bIsSphereColl)
		return false;
	D3DXVECTOR3 vDiff = vCenterSrc - vCenterDst;

	float fDistance = D3DXVec3Length(&vDiff);
	
	if(nullptr != vDist)
		vDist = &fDistance;

	if (fDistance < (fRadiousSrc + fRadiousDst))
		return true;

	return false;
}

bool CCollisionMgr::IntersectBox(
	const D3DXVECTOR3 & vMinSrc, 
	const D3DXVECTOR3 & vMaxSrc,
	const D3DXVECTOR3 & vMinDst,
	const D3DXVECTOR3 & vMaxDst)
{
	if (vMaxSrc.x < vMinDst.x ||
		vMinSrc.x > vMaxDst.x)
		return false;

	if (vMaxSrc.y < vMinDst.y ||
		vMinSrc.y > vMaxDst.y)
		return false;

	if (vMaxSrc.z < vMinDst.z ||
		vMinSrc.z > vMaxDst.z)
		return false;

	return true;
}

void CCollisionMgr::SetCubeList(list<CBlock*>* pList)
{
	m_CubeList = pList;
}

void CCollisionMgr::SetOpMzList(list<vector<CBlock*>>* pList)
{
	m_OptimizationList = pList;
}

void CCollisionMgr::SetInterActList(list<list<vector<CBlock*>>>* pList)
{
	m_InteractionList = pList;
}

bool CCollisionMgr::GetVailedState()
{
	return m_bIsValid;
}

void CCollisionMgr::SetVailedState(bool bState)
{
	m_bIsValid = bState;
}

void CCollisionMgr::SetIsSceneChange(const bool & bIsSceneChange)
{
	m_bIsSceneChange = bIsSceneChange;
}

const bool & CCollisionMgr::GetIsSceneChange()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_bIsSceneChange;
}

void CCollisionMgr::SetIsStair3(const bool & bIsStair3)
{
	m_bIsStair3 = bIsStair3;
}

const bool & CCollisionMgr::GetIsStair3()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_bIsStair3;
}

void CCollisionMgr::SetSphereColl(const bool & bIsSphereColl)
{
	m_bIsSphereColl = bIsSphereColl;
}



