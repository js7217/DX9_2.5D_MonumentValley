#pragma once

#ifndef __COLLMOUSE_H__
#define __COLLMOUSE_H__

#include "Collision.h"

namespace ENGINE
{
	class CTerrainInfo;
}

class CCollMouse : public ENGINE::CCollision
{
private:
	explicit CCollMouse();

public:
	virtual ~CCollMouse();
	
public:
	bool PickTerrain(D3DXVECTOR3* pOut, const ENGINE::VTX_TEX* pTerrainVtx);
	bool PickObject(D3DXVECTOR3* pOut, const ENGINE::VTX_TEX* pObjectVtx, const D3DXMATRIX* pMatWorld);

	bool PickSphere(D3DXMATRIX* pMatWorld);
	void SetTerrainInfo(ENGINE::CTerrainInfo* pTerrainInfo);
	void Set_bIsOrtho(bool bIsOrtho);
private:
	HRESULT Initialize();
	void Release();

private:
	void Translation_ViewSpace();
	void Translation_LocalSpace(const D3DXMATRIX* pMatWorld);

public:
	static POINT GetMousePos();
	static CCollMouse* Create();

private:
	D3DXVECTOR3 m_vPivotPos; // 광선 출발점.
	D3DXVECTOR3 m_vRayDir; // 광선 방향.
	ENGINE::CTerrainInfo* m_pTerrainInfo; // 터레인 정보 컴포넌트 주소값.
	bool		m_bIsOrtho; // 직교인지 아닌지.
};
#endif