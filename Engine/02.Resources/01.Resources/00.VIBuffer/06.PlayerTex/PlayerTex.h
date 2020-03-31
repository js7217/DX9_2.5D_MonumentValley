#pragma once

#ifndef __PLAYERTEX_H__
#define __PLAYERTEX_H__

#include "VIBuffer.h"

BEGIN(ENGINE)

class ENGINE_DLL CPlayerTex : public CVIBuffer
{
private:
	explicit CPlayerTex(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual ~CPlayerTex();

public:
	virtual HRESULT CreateBuffer();
	virtual void Render();

private:
	void Release();

public:
	static CPlayerTex* Create(LPDIRECT3DDEVICE9 pGraphicDev);
};


END

#endif