#pragma once

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Resources.h"

BEGIN(ENGINE)

class ENGINE_DLL CTexture : public CResources
{
private:
	explicit CTexture(LPDIRECT3DDEVICE9 pGraphicDev);

public:
	virtual ~CTexture();

public:
	virtual void Render();
	virtual void Render(const WORD& dwIndex);
	virtual CResources* CloneResource();
	virtual void Set_Transform();
private:
	HRESULT LoadTexture(TEXTURE_TYPE eTexType,
		const wstring& wstrFilePath,
		const WORD& wCnt);
	void Release();

public:
	static CTexture* Create(LPDIRECT3DDEVICE9 pGraphicDev,
		TEXTURE_TYPE eTexType,
		const wstring& wstrFilePath,
		const WORD& wCnt);

private:
	typedef vector<IDirect3DBaseTexture9*> VEC_TEXTURE;
	VEC_TEXTURE m_vecTexture;
	DWORD m_dwContainerSize;
};

END
#endif