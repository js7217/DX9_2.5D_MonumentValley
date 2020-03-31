#pragma once

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

BEGIN(ENGINE)

class CComponent;
class ENGINE_DLL CGameObject
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual ~CGameObject();

public:
	CComponent* GetComponent(const wstring& wstrComponentKey);
public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

protected:
	virtual HRESULT Initialize();
	virtual HRESULT LateInit();
	virtual void Release();

protected:
	bool				m_bIsInit;
	typedef map<wstring, CComponent*> MAP_COMPONENT;
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	MAP_COMPONENT		m_mapComponent;
};
END
#endif