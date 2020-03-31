#pragma once

#ifndef __ENDINGSCENE_H__
#define __ENDINGSCENE_H__

namespace ENGINE // 엔진에서 만든 클래스는 엔진 이름으로 묶어줌
{
	class CManagement;
	class CKeyMgr;
}


#include "Scene.h"

class CEndingScene : public ENGINE::CScene
{
private:
	explicit CEndingScene(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual ~CEndingScene();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	virtual HRESULT Initialize();
	virtual void Release();

private:
	virtual HRESULT Add_Environment_Layer();
	virtual HRESULT Add_Object_Layer();
	virtual HRESULT Add_UI_Layer();

public:
	static CEndingScene* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	HWND m_hVideo;
	ENGINE::CManagement*	m_pManagement;
	ENGINE::CKeyMgr*		m_pKeyMgr;
};

#endif