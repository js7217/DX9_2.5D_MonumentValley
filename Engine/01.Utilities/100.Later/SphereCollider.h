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

	//��ü�� ������ ����� Transform
	CTransform*			m_pTransform;

	//��ü�� ������ ����� ���� ���
	const D3DXMATRIX*	m_pMatWorld;

	//���� �߽��� ��ġ�� ��ǥ
	D3DXVECTOR3			m_vCenter;

	//������
	float				m_fRadius;

	//�浹���� �� �о�Ŵ�? ���Ŵ�?
	bool				m_bIsColl;

	//����׿� �޽�
	LPD3DXMESH			m_pSphereMesh;
};

END

#endif