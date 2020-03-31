#pragma once

#ifndef __MOUSE_H__
#define __MOUSE_H__

namespace ENGINE
{
	class CKeyMgr;
}

#include "GameObject.h"

class CCollMouse;
class CBlock;
class CPlayer;
class CMouse : public ENGINE::CGameObject
{
private:
	explicit CMouse(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	~CMouse();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	HRESULT AddComponent();
	virtual HRESULT Initialize();
	virtual HRESULT LateInit();
	virtual void Release();

public:
	static CMouse* Create(LPDIRECT3DDEVICE9 pGraphicDev);

public: // 재성
	void AddCube_List(CBlock* pBlock);
	void AddCube_OptimizationList(vector<CBlock*>* pVecBlock);
	void AddCube_InteractionList(list<vector<CBlock*>>* pvecBlockList);
	void GetMousePos();
	void KeyInput();

public: //동화
	list<CBlock*>*					GetCubeList();
	list<vector<CBlock*>>*			GetOpMzList();
	list<list<vector<CBlock*>>>*	GetInterActList();

public://주형
	list<CBlock*>& Get_MovingCubeList();
	void Set_Player(CPlayer* pPlayer);
	bool CollMovingCube();
	void Set_Value(const float& fValue);
private:
	CPlayer*					m_pPlayer;


	POINT						m_tPt; // 마우스 포인터.
	list<CBlock*>				m_CubeList; // 큐브리스트
	list<CBlock*>				m_MovingCubeList; // 큐브리스트


	list<vector<CBlock*>>		m_OptimizationList; // 합쳐진 큐브 리스트.
	list<list<vector<CBlock*>>> m_InteractionList; // InteractionList
	CCollisionMgr*				m_pCollisionMgr;

	list<CBlock*>			m_vecPickCubeList; // 픽킹된 큐브 리스트
	map<int, CBlock*>		m_mapRenderCube; // 렌더 소팅된 리스트.
	ENGINE::CKeyMgr*		m_pKeyMgr;

	CCollMouse*				m_pCollMouse;

	bool					m_bIsOrtho;
	float					m_fValue;
};


#endif