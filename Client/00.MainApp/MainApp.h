#pragma once

#ifndef __MAINAPP_H__
#define __MAINAPP_H__

namespace ENGINE
{
	class CGraphicDev;
	class CManagement;
	class CResourceMgr;
	class CTimeMgr;
	class CKeyMgr;
}

class CTextureMgr;
class CFrameMgr;
class CMainApp
{
private:
	explicit CMainApp();

public:
	~CMainApp();

public:
	void Update();
	void LateUpdate();
	void Render();

private:
	HRESULT Initialize();
	void Release();

public:
	static CMainApp* Create();

private:
	ENGINE::CGraphicDev*	m_pGraphicDev;
	ENGINE::CManagement*	m_pManagement;
	ENGINE::CResourceMgr*	m_pResourceMgr;
	ENGINE::CTimeMgr*		m_pTimeMgr;
	ENGINE::CKeyMgr*		m_pKeyMgr;
	CCollisionMgr*			m_pCollisionMgr;
	CTextureMgr*			m_pTextureMgr;
	CSoundMgr*				m_pSoundMgr;
	LPDIRECT3DDEVICE9 m_pDevice;
};
#endif