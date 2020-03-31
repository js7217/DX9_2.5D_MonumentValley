#pragma once

#ifndef __LOGO_H__
#define __LOGO_H__

#include "Scene.h"

namespace ENGINE // 엔진에서 만든 클래스는 엔진 이름으로 묶어줌
{
	class CManagement;
	class CResourceMgr;
	class CKeyMgr;
}

class CLogo : public ENGINE::CScene
{
private:
	explicit CLogo(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual ~CLogo();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	virtual HRESULT Initialize();
	virtual void Release();

public:
	static CLogo* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Environment_Layer();
	virtual HRESULT Add_Object_Layer();
	virtual HRESULT Add_UI_Layer();

private:
	ENGINE::CManagement*	m_pManagement;
	ENGINE::CResourceMgr*	m_pResourceMgr;
	ENGINE::CKeyMgr*		m_pKeyMgr;
};
#endif // !__LOGO_H__