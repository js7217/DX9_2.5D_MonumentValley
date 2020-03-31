#pragma once

#ifndef __CUBE_H__
#define __CUBE_H__

#include "VIBuffer.h"

BEGIN(ENGINE)

class ENGINE_DLL CCube : public CVIBuffer
{
private:
	explicit CCube(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual ~CCube();

public:
	virtual HRESULT CreateBuffer();
	virtual void Render();

private:
	void Release();

public:
	static CCube* Create(LPDIRECT3DDEVICE9 pGraphicDev);
};


END

#endif