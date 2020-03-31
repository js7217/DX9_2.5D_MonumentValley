#pragma once

#ifndef __STAGE_H__
#define __STAGE_H__

#include "Scene.h"

namespace ENGINE // 엔진에서 만든 클래스는 엔진 이름으로 묶어줌
{
	class CManagement;
	class CResourceMgr;
	class CLayer;
	class CKeyMgr;
}
class CPlayer;
class CStage : public ENGINE::CScene
{
private:
	explicit CStage(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual ~CStage();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	virtual HRESULT Initialize();
	virtual void Release();

public:
	static CStage* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Environment_Layer();
	virtual HRESULT Add_Object_Layer();
	virtual HRESULT Add_UI_Layer();
	void AddSpriteTexture();
private:
	HRESULT LoadMap(ENGINE::CLayer* pObjLayer, CPlayer* pPlayer);
private:
	ENGINE::CManagement* m_pManagement;
	ENGINE::CResourceMgr* m_pResourceMgr;
	ENGINE::CKeyMgr*	m_pKeyMgr;
	CCollisionMgr*		m_pCollisionMgr;
	CSoundMgr*			m_pSoundMgr;
	bool				m_bIsCreateBox;
	float				m_fTime;
	CPlayer*			m_pPlayer;

	bool				m_bIsLogoDone;
};
#endif // !__LOGO_H__