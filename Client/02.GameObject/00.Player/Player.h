#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

namespace ENGINE
{
	class CResourceMgr;
	class CTexture;
	class CVIBuffer;
	class CTimeMgr;
	class CTransform;
	class CManagement;
	class CSphereCollider;
	class CKeyMgr;
}


#include "GameObject.h"

class CCollTerrain;
class CCollMouse;
class CCollCube;
class CBlock;
class CPlayer : public ENGINE::CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	~CPlayer();

public:
	ENGINE::CTransform* GetTransform();
public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	virtual HRESULT Initialize();
	virtual HRESULT LateInit();
	virtual void Release();

public:
	void SetState(bool bState);
	bool GetState();

private:
	HRESULT AddComponent();
	void KeyInput();
	void MovePlayer();

public:
	float*	GetTimeCnt();
public:
	list<CBlock*>& Get_CubeList();
public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pGraphicDev);

public: // 주형
	void Translation_ViewSpace();
	bool CollCube();

	void Set_bIsCollCube(bool Check);
	void Set_bChangeStair(bool Check);
	void Set_bIsPrePos(bool Check);
	void Set_CollYValue(float fValue);

	bool Get_bIsCollCube();
	bool Get_bChangeStair();

private:
	ENGINE::CTransform*		m_pTransform;
	ENGINE::CResourceMgr*	m_pResourceMgr;
	ENGINE::CVIBuffer*		m_pBuffer;
	ENGINE::CTexture*		m_pTexture;
	ENGINE::CTimeMgr*		m_pTimeMgr;
	ENGINE::CManagement*	m_pManagement;
	ENGINE::CSphereCollider* m_pSphereCollider;
	ENGINE::CKeyMgr*		m_pKeyMgr;


	CCollisionMgr*			m_pCollisionMgr;
	CCollTerrain*			m_pCollTerrain;
	CCollMouse*				m_pCollMouse;
	CCollCube*				m_pCollCube;
	bool					m_bIsMove;
	D3DXVECTOR3				m_vMousePos;

	float					m_fTimeCnt;

	bool					m_bIsDestination;


	//주형
	list<CBlock*>    		m_CubeList; // 큐브리스트
	D3DXVECTOR3				m_vOriginRay;
	D3DXVECTOR3				m_vRayDir;
	D3DXVECTOR3				m_vRayStairDir;

	D3DXVECTOR3				m_vPrePos;

	bool					m_bIsOnPrePos = true;
	bool					m_bOnOffCollCube = true;
	bool					m_bChangeStair = false;
	float					m_CollYValue;



};

#endif