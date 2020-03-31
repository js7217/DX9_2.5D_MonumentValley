#pragma once

#ifndef __COLLTERRAIN_H__
#define __COLLTERRAIN_H__

#include "Collision.h"

namespace ENGINE
{
	class CTransform;
	class CVIBuffer;
}

class CCollTerrain : public ENGINE::CCollision
{
private:
	explicit CCollTerrain();
	explicit CCollTerrain(ENGINE::CCollision::COLLISION_TYPE eType);

public:
	virtual ~CCollTerrain();

public:
	void SetTargetInfo(ENGINE::CTransform* pTarget, ENGINE::CVIBuffer* pTerrainBuffer); // 플레이어의 위치 정보와 터레인의 버텍스 정보
	void SetTerrainInfo(const WORD& wCntX, const WORD& wCntZ, const WORD& wItv);
	// 터레인의 정보들.(가로, 세로 버텍스 개수와 인터벌)
public:
	virtual void LateUpdate();

public:
	static CCollTerrain* Create(ENGINE::CCollision::COLLISION_TYPE eType);

private:
	ENGINE::CTransform*			m_pTarget;
	ENGINE::VTX_TEX*			m_pTerrainVtx;
	ENGINE::CVIBuffer*			m_pTerrainBuffer;

	WORD m_wCntX; // 가로 방향 정점 개수
	WORD m_wCntZ; // 세로 방향 정점 개수
	WORD m_wItv; // 정점간의 간격

};
#endif