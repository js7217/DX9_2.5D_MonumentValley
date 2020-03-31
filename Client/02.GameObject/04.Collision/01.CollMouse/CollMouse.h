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
	D3DXVECTOR3 m_vPivotPos; // ���� �����.
	D3DXVECTOR3 m_vRayDir; // ���� ����.
	ENGINE::CTerrainInfo* m_pTerrainInfo; // �ͷ��� ���� ������Ʈ �ּҰ�.
	bool		m_bIsOrtho; // �������� �ƴ���.
};
#endif