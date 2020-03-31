#pragma once

#ifndef __TERRAIN_H__
#define __TERRAIN_H__


namespace ENGINE
{
	class CResourceMgr;
	class CTexture;
	class CVIBuffer;
	class CTransform;
	class CManagement;
	class CTerrainInfo;
}
#include "GameObject.h"

class CMyTerrain : public ENGINE::CGameObject
{
private:
	explicit CMyTerrain(LPDIRECT3DDEVICE9 pGraphicDev, const WORD & wCntX, const WORD & wCntY, const WORD & wItv);
public:
	~CMyTerrain();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
private:
	virtual HRESULT Initialize();
	virtual HRESULT LateInit();
	virtual void Release();

	HRESULT AddComponent();
public:
	static CMyTerrain* Create(LPDIRECT3DDEVICE9 pGraphicDev, const WORD & wCntX, const WORD & wCntY, const WORD & wItv);

private:
	ENGINE::CTransform*		m_pTransform;
	ENGINE::CResourceMgr*	m_pResourceMgr;
	ENGINE::CVIBuffer*		m_pBuffer;
	ENGINE::CTexture*		m_pTexture;
	ENGINE::CManagement*	m_pManagement;
	ENGINE::CTerrainInfo*	m_pTerrainInfo;
};


#endif