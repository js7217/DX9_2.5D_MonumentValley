#include "stdafx.h"
#include "CollTerrain.h"
#include "Transform.h"

CCollTerrain::CCollTerrain()
{
}

CCollTerrain::CCollTerrain(ENGINE::CCollision::COLLISION_TYPE eType)
	: CCollision(eType)
	, m_pTarget(nullptr), m_pTerrainBuffer(nullptr), m_pTerrainVtx(nullptr)
	, m_wCntX(0), m_wCntZ(0), m_wItv(0)
{
}

CCollTerrain::~CCollTerrain()
{
}

void CCollTerrain::SetTargetInfo(ENGINE::CTransform* pTarget, ENGINE::CVIBuffer* pTerrainBuffer)
{
	NULL_CHECK(pTarget);
	NULL_CHECK(pTerrainBuffer);

	m_pTarget = pTarget;
	m_pTerrainBuffer = pTerrainBuffer;
	// 터레인과 충돌할 타겟을 받아오고 터레인의 버퍼를 가져온다.
	m_pTerrainVtx = (ENGINE::VTX_TEX*)(m_pTerrainBuffer->GetOriginVtxInfo());
	// 터레인의 버텍스 정보를 가져온다.
}

void CCollTerrain::SetTerrainInfo(const WORD & wCntX, const WORD & wCntZ, const WORD & wItv)
{
	m_wCntX = wCntX;
	m_wCntZ = wCntZ;
	m_wItv = wItv;
	// 해당 터레인의 가로, 세로 버텍스 개수와 인터벌을 가져와 세팅해준다.
}

void CCollTerrain::LateUpdate()
{
	D3DXVECTOR3 vTargetPos = m_pTarget->GetPos();

	int iIndex = int(vTargetPos.x / m_wItv) + m_wCntX * int(vTargetPos.z / m_wItv);

	if (0 > vTargetPos.x || 0 > vTargetPos.z || vTargetPos.x > m_wCntX || vTargetPos.z >= m_wCntZ)
	{
		vTargetPos.y = 1.f;
		m_pTarget->SetPos(vTargetPos);
		return;
	}

	float fRatioX = 0.f, fRatioZ = 0.f;

	fRatioX = vTargetPos.x - m_pTerrainVtx[iIndex + m_wCntX].vPos.x;
	fRatioZ = m_pTerrainVtx[iIndex + m_wCntX].vPos.z - vTargetPos.z;

	D3DXPLANE Plane;

	if (fRatioX > fRatioZ)
	{
		D3DXPlaneFromPoints(
			&Plane,
			&m_pTerrainVtx[iIndex + m_wCntX].vPos,
			&m_pTerrainVtx[iIndex + m_wCntX + 1].vPos,
			&m_pTerrainVtx[iIndex + 1].vPos);
	}
	else
	{
		D3DXPlaneFromPoints(
			&Plane,
			&m_pTerrainVtx[iIndex + m_wCntX].vPos,
			&m_pTerrainVtx[iIndex + 1].vPos,
			&m_pTerrainVtx[iIndex].vPos);
	}

	vTargetPos.y = (-Plane.a * vTargetPos.x - Plane.c * vTargetPos.z - Plane.d) / Plane.b;

	vTargetPos.y += 1.f;

	m_pTarget->SetPos(vTargetPos);
}

CCollTerrain * CCollTerrain::Create(ENGINE::CCollision::COLLISION_TYPE eType)
{
	return  new CCollTerrain(eType);
}
