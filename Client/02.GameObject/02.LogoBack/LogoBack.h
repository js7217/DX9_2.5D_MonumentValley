#pragma once

#ifndef __LOGOBACK_H__
#define __LOGOBACK_H__

namespace ENGINE
{
	class CResourceMgr;
	class CVIBuffer;
	class CTexture;
	class CTimeMgr;
}

#include "GameObject.h"

class CLogoBack : public ENGINE::CGameObject
{
private:
	explicit CLogoBack(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	~CLogoBack();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	virtual HRESULT Initialize();
	virtual void Release();
private:
	HRESULT AddComponent();
public:
	static CLogoBack* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	ENGINE::CResourceMgr*	m_pResourceMgr;
	ENGINE::CVIBuffer*		m_pBuffer;
	ENGINE::CTexture*		m_pTexture;
	ENGINE::CTimeMgr*		m_pTimeMgr;
	float					m_fFrame;
	float					m_fMaxFrame;
};

#endif