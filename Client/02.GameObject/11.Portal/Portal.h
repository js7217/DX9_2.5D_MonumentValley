#pragma once

#ifndef __PORTAL_H__
#define __PORTAL_H__

#include "GameObject.h"

namespace ENGINE
{
	class CTransform;
	class CVIBuffer;
}

class CPlayer;
class CMouse;
class CBlock;
class CPortal : public ENGINE::CGameObject
{
public:
	enum tagStage
	{
		STAGE1,
		STAGE2,
		STAGE3,
		STAGE4,
		STAGE5
	};
	enum tagType 
	{ 
		SCENECHANGE,
		TRANS, 
		INTERACT, 
		INTERACT2, 
		PORTAL_END 
	};

private:
	explicit CPortal(LPDIRECT3DDEVICE9 pGraphicDev, tagType eType);

public:
	virtual ~CPortal();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	virtual HRESULT Initialize();
	virtual HRESULT LateInit();
	virtual void Release();

private:
	HRESULT AddComponent();
private: // 재성
	void Stage1Portal();
	void Stage2Portal();
	void Stage3Portal();
	void Stage4Portal();
	void Stage5Portal();
	void SetStage(tagStage eStage);
public:
	//포탈의 출입구
	void SetEntrance(D3DXVECTOR3 pSrc, D3DXVECTOR3 pDst);

	//버튼 위치
	void SetPos(D3DXVECTOR3 vPos);

public:
	static CPortal* Create(
		LPDIRECT3DDEVICE9 pGraphicDev, tagType eType, tagStage eStage,
		D3DXVECTOR3 pSrc, D3DXVECTOR3 pDst = { 0.f, 0.f, 0.f } ); // 순간이동

	static CPortal* Create(LPDIRECT3DDEVICE9 pGraphicDev, tagType eType, tagStage eStage); // 버튼

private:
	ENGINE::CResourceMgr*		m_pResourceMgr;
	ENGINE::CManagement*		m_pManagement;
	ENGINE::CSphereCollider*	m_pSphereCollider;
	ENGINE::CTimeMgr*			m_pTimeMgr;

	CCollisionMgr*				m_pCollisionMgr;
	//버튼 트리거
	////////////////////////////////////////////////////
	//버튼의 위치
	ENGINE::CTransform*			m_pTransform;

	//CubeLst를 가지는 클래스
	CMouse*						m_pMouse;

	//OptimizList
	list<vector<CBlock*>>*			m_pOptimizationList;
	list<list<vector<CBlock*>>>*	m_pInteractionList;
	////////////////////////////////////////////////////

	//공용
	////////////////////////////////////////////////////
	//Target
	CPlayer*					m_pTarget;

	//Target의 Transform
	ENGINE::CTransform*			m_pTarget_Transform;

	//수행할 기능의 타입
	tagType						m_eType;
	tagStage					m_eStage;
	////////////////////////////////////////////////////

	//순간이동 포탈
	////////////////////////////////////////////////////

	//입구 
	D3DXVECTOR3					m_vSrc;
	bool						m_bIsActive_Src;

	//출구
	D3DXVECTOR3					m_vDst;
	bool						m_bIsActive_Dst;
	////////////////////////////////////////////////////
	bool						m_bIsStart;
	float						m_fMoveAngle;
};

#endif