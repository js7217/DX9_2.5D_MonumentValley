#pragma once

#ifndef __STAGE3_H__
#define __STAGE3_H__

#include "Scene.h"

namespace ENGINE // 엔진에서 만든 클래스는 엔진 이름으로 묶어줌
{
	class CManagement;
	class CResourceMgr;
	class CLayer;
	class CKeyMgr;
}
class CPlayer;
class CStage3 : public ENGINE::CScene
{
private:
	explicit CStage3(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual ~CStage3();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	virtual HRESULT Initialize();
	virtual void Release();

public:
	static CStage3* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Environment_Layer();
	virtual HRESULT Add_Object_Layer();
	virtual HRESULT Add_UI_Layer();

public:
	void AddSpriteTexture();
	void SpriteRender();

private:
	HRESULT LoadMap(ENGINE::CLayer* pObjLayer, CPlayer* pPlayer);
private:

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