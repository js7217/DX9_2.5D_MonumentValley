#pragma once

#ifndef __BUILDING_H__
#define __BUILDING_H__

namespace ENGINE
{
	class CResourceMgr;
	class CTexture;
	class CVIBuffer;
	class CTransform;
	class CManagement;
	class CBillBoard;
}

#include "GameObject.h"

class CCollTerrain;
class CBuilding : public ENGINE::CGameObject
{
private:
	explicit CBuilding(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	~CBuilding();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	virtual HRESULT Initialize();
	virtual HRESULT LateInit();
	virtual void Release();

private:
	HRESULT AddComponent();
	void SetPos(const float& fPosX, const float& fPosZ);
public:
	static CBuilding* Create(LPDIRECT3DDEVICE9 pGraphicDev, const float& fPosX, const float& fPosZ);

private:
	ENGINE::CTransform*		m_pTransform; // ��ġ
	ENGINE::CResourceMgr*	m_pResourceMgr; // ���ҽ��Ŵ���(Ŭ�� ������)
	ENGINE::CVIBuffer*		m_pBuffer;
	ENGINE::CTexture*		m_pTexture;
	ENGINE::CManagement*	m_pManagement; // �ͷ��� ���ؽ� ����.
	ENGINE::CBillBoard*		m_pBillBoard;
	CCollTerrain*			m_pCollTerrain;
};

#endif