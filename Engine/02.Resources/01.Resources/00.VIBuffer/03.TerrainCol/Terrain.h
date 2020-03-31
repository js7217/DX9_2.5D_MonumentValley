#pragma once

#ifndef __ENGINE_TERRAIN_H__
#define __ENGINE_TERRAIN_H__

#include "VIBuffer.h"

BEGIN(ENGINE)

class ENGINE_DLL CTerrain : public CVIBuffer
{
private:
	explicit CTerrain(LPDIRECT3DDEVICE9 pGraphicDev, const WORD & wCntX, const WORD & wCntY, const WORD & wItv);
public:
	virtual ~CTerrain();

public:
	virtual HRESULT CreateBuffer();
	virtual void Render();

private:
	void Release();

public:
	static CTerrain* Create(LPDIRECT3DDEVICE9 pGraphicDev, const WORD & wCntX, const WORD & wCntY, const WORD & wItv);

private:
	WORD m_wCntX; // ���� ���� ���� ����
	WORD m_wCntY; // ���� ���� ���� ����
	WORD m_wItv; // �������� ����
};


END
#endif