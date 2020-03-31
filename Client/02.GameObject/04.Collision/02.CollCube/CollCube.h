#pragma once

#ifndef __COLLCUBE_H__
#define __COLLCUBE_H__

#include "Collision.h"

namespace ENGINE
{
	class CTransform;
	class CVIBuffer;
}

class CMonster;
class CCollCube : public ENGINE::CCollision
{
private:
	explicit CCollCube();
	explicit CCollCube(ENGINE::CCollision::COLLISION_TYPE eType);

public:
	virtual ~CCollCube();

public:
	void SetTargetInfo(ENGINE::CTransform* pTarget, list<ENGINE::CGameObject*>* pObjLst);

public:
	virtual void LateUpdate();

public:
	static CCollCube* Create(ENGINE::CCollision::COLLISION_TYPE eType);

public:
	typedef list<ENGINE::CGameObject*>			CUBELST;
	//typedef list<ENGINE::CVIBuffer*>			BUFFERLST;

	typedef list<vector<ENGINE::CGameObject*>>	OPTIMIZE_LST;
	//typedef list<vector<ENGINE::CVIBuffer*>>	OPTIMIZE_BUFFER_LST;

private:
	//Target의 Transform
	ENGINE::CTransform*		m_pTarget;	

	// 가장 가까운 큐브를 저장하는 변수
	ENGINE::VTX_CUBE*		m_pCubeVtx;	

	//각종 충돌 함수 가져옴
	CCollisionMgr*			m_pCollisionMgr;

	//처리할 Cube 목록
	CUBELST*				m_pCubeLst;
	//BUFFERLST*				m_pBufferLst;

	

	
};

#endif