#pragma once

#ifndef __STAGE4_H__
#define __STAGE4_H__

#include "Scene.h"

namespace ENGINE // 엔진에서 만든 클래스는 엔진 이름으로 묶어줌
{
	class CManagement;
	class CResourceMgr;
	class CLayer;
	class CKeyMgr;
}
class CPlayer;
class CStage4 : public ENGINE::CScene
{
private:
	explicit CStage4(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual ~CStage4();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	virtual HRESULT Initialize();
	HRESULT LateInit();
	virtual void Release();

public:
	static CStage4* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Environment_Layer();
	virtual HRESULT Add_Object_Layer();
	virtual HRESULT Add_UI_Layer();

public:
	void AddSpriteTexture();
	void SpriteRender();
public:
	//주형
	void CheckCollStair();
private:
	HRESULT LoadMap(ENGINE::CLayer* pObjLayer, CPlayer* pPlayer);
private:
	bool				m_bIsInit;

	CPlayer*			m_pPlayer;

	ENGINE::CManagement* m_pManagement;
	ENGINE::CResourceMgr* m_pResourceMgr;
	ENGINE::CKeyMgr*	m_pKeyMgr;
	CCollisionMgr*		m_pCollisionMgr;
	CSoundMgr*			m_pSoundMgr;
	bool				m_bIsCreateBox;
	float				m_fTime;

	int					m_iSpriteAlpha;
	float				m_fSpriteRenderTimer;
};
#endif // !__LOGO_H__