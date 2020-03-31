#pragma once

#ifndef __SPHERECOLLIDER_H__
#define __SPHERECOLLIDER_H__

#include "Collision.h"

BEGIN(ENGINE)

class CTransform;
class CCollision;
class ENGINE_DLL CSphereCollider : public CCollision
{
private:
	explicit CSphereCollider();

public:
	virtual ~CSphereCollider();

public:
	void SetGraphicDev(LPDIRECT3DDEVICE9 pGraphicDev);
	void SetTransform(CTransform* pTransform);
	void SetCollisionState(bool bState);
	void SetWorld(const D3DXMATRIX* pMatWorld);
	void SetPos(const D3DXVECTOR3& vPos);
	void SetRadius(float fRadius);

	float GetRadius();
	D3DXVECTOR3 GetPos();
	

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

public:
	HRESULT CreateSphere();

public:
	static CSphereCollider* Create(
		LPDIRECT3DDEVICE9 pGraphicDev,
		CTransform*		  pTransform,
		float			  fRadius);

protected:
	LPDIRECT3DDEVICE9	m_pGraphicDev;

	//구체가 씌워질 대상의 Transform
	CTransform*			m_pTransform;

	//구체가 씌워질 대상의 월드 행렬
	const D3DXMATRIX*	m_pMatWorld;

	//원의 중심이 위치할 좌표
	D3DXVECTOR3			m_vCenter;

	//반지름
	float				m_fRadius;

	//충돌했을 때 밀어낼거니? 말거니?
	bool				m_bIsColl;

	//디버그용 메시
	LPD3DXMESH			m_pSphereMesh;
};

END

#endif