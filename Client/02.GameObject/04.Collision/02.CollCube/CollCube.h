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
	//Target�� Transform
	ENGINE::CTransform*		m_pTarget;	

	// ���� ����� ť�긦 �����ϴ� ����
	ENGINE::VTX_CUBE*		m_pCubeVtx;	

	//���� �浹 �Լ� ������
	CCollisionMgr*			m_pCollisionMgr;

	//ó���� Cube ���
	CUBELST*				m_pCubeLst;
	//BUFFERLST*				m_pBufferLst;

	

	
};

#endif