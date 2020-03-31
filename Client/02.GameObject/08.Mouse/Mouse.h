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

public: // �缺
	void AddCube_List(CBlock* pBlock);
	void AddCube_OptimizationList(vector<CBlock*>* pVecBlock);
	void AddCube_InteractionList(list<vector<CBlock*>>* pvecBlockList);
	void GetMousePos();
	void KeyInput();

public: //��ȭ
	list<CBlock*>*					GetCubeList();
	list<vector<CBlock*>>*			GetOpMzList();
	list<list<vector<CBlock*>>>*	GetInterActList();

public://����
	list<CBlock*>& Get_MovingCubeList();
	void Set_Player(CPlayer* pPlayer);
	bool CollMovingCube();
	void Set_Value(const float& fValue);
private:
	CPlayer*					m_pPlayer;


	POINT						m_tPt; // ���콺 ������.
	list<CBlock*>				m_CubeList; // ť�긮��Ʈ
	list<CBlock*>				m_MovingCubeList; // ť�긮��Ʈ


	list<vector<CBlock*>>		m_OptimizationList; // ������ ť�� ����Ʈ.
	list<list<vector<CBlock*>>> m_InteractionList; // InteractionList
	CCollisionMgr*				m_pCollisionMgr;

	list<CBlock*>			m_vecPickCubeList; // ��ŷ�� ť�� ����Ʈ
	map<int, CBlock*>		m_mapRenderCube; // ���� ���õ� ����Ʈ.
	ENGINE::CKeyMgr*		m_pKeyMgr;

	CCollMouse*				m_pCollMouse;

	bool					m_bIsOrtho;
	float					m_fValue;
};


#endif