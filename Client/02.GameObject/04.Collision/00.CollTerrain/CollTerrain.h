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
	void SetTargetInfo(ENGINE::CTransform* pTarget, ENGINE::CVIBuffer* pTerrainBuffer); // �÷��̾��� ��ġ ������ �ͷ����� ���ؽ� ����
	void SetTerrainInfo(const WORD& wCntX, const WORD& wCntZ, const WORD& wItv);
	// �ͷ����� ������.(����, ���� ���ؽ� ������ ���͹�)
public:
	virtual void LateUpdate();

public:
	static CCollTerrain* Create(ENGINE::CCollision::COLLISION_TYPE eType);

private:
	ENGINE::CTransform*			m_pTarget;
	ENGINE::VTX_TEX*			m_pTerrainVtx;
	ENGINE::CVIBuffer*			m_pTerrainBuffer;

	WORD m_wCntX; // ���� ���� ���� ����
	WORD m_wCntZ; // ���� ���� ���� ����
	WORD m_wItv; // �������� ����

};
#endif