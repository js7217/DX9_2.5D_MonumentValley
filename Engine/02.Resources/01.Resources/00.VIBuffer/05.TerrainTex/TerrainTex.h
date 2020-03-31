#pragma once

#ifndef __TERRAINTEX_H__
#define __TERRAINTEX_H__

#include "VIBuffer.h"

BEGIN(ENGINE)

class ENGINE_DLL CTerrainTex : public CVIBuffer
{
private:
	explicit CTerrainTex(LPDIRECT3DDEVICE9 pGraphicDev, const WORD & wCntX, const WORD & wCntY, const WORD & wItv);
public:
	virtual ~CTerrainTex();

public:
	virtual HRESULT CreateBuffer();
	virtual void Render();

public:
	WORD GetCntX();
	WORD GetCntY();
	WORD GetItv();
private:
	void Release();

private:
	DWORD* LoadHeightMap();

public:
	static CTerrainTex* Create(LPDIRECT3DDEVICE9 pGraphicDev, const WORD & wCntX, const WORD & wCntY, const WORD & wItv);

private:
	WORD m_wCntX; // 가로 방향 정점 개수
	WORD m_wCntY; // 세로 방향 정점 개수
	WORD m_wItv; // 정점간의 간격
};


END
#endif