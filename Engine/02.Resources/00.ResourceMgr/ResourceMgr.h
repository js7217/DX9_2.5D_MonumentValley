#pragma once

#ifndef __RESOURCEMGR_H__
#define __RESOURCEMGR_H__

#include "VIBuffer.h"

BEGIN(ENGINE)

class ENGINE_DLL CResourceMgr
{
	DECLARE_SINGLETON(ENGINE::CResourceMgr)

private:
	explicit CResourceMgr();
public:
	~CResourceMgr();

public:
	HRESULT AddBuffer(LPDIRECT3DDEVICE9 pGraphiceDev,
		RESOURCE_TYPE eResourceType,
		CVIBuffer::BUFFER_TYPE eBufferType,
		const wstring& wstrResourceKey,
		const WORD& wCntX = 0, const WORD& wCntY = 0, const WORD& wItv = 0);

	HRESULT AddTexture(LPDIRECT3DDEVICE9 pGraphiceDev,
		RESOURCE_TYPE eResourceType,
		TEXTURE_TYPE eTextureType,
		const wstring& wstrResourceKey,
		const wstring& wstrFilePath,
		const WORD& wCnt);

	CResources* CloneResource(RESOURCE_TYPE eResourceType, const wstring& wstrResourceKey);

	void Render(const wstring& wstrResoruceKey, const short& nIndex = -1);
	void ResetDynamaicResource();
private:
	void Release();

private:
	typedef map<wstring, CResources*>		MAP_RESOURCE;
	MAP_RESOURCE							m_MapResource[RESOURCE_END];
};

END

#endif