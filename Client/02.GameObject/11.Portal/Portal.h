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
private: // �缺
	void Stage1Portal();
	void Stage2Portal();
	void Stage3Portal();
	void Stage4Portal();
	void Stage5Portal();
	void SetStage(tagStage eStage);
public:
	//��Ż�� ���Ա�
	void SetEntrance(D3DXVECTOR3 pSrc, D3DXVECTOR3 pDst);

	//��ư ��ġ
	void SetPos(D3DXVECTOR3 vPos);

public:
	static CPortal* Create(
		LPDIRECT3DDEVICE9 pGraphicDev, tagType eType, tagStage eStage,
		D3DXVECTOR3 pSrc, D3DXVECTOR3 pDst = { 0.f, 0.f, 0.f } ); // �����̵�

	static CPortal* Create(LPDIRECT3DDEVICE9 pGraphicDev, tagType eType, tagStage eStage); // ��ư

private:
	ENGINE::CResourceMgr*		m_pResourceMgr;
	ENGINE::CManagement*		m_pManagement;
	ENGINE::CSphereCollider*	m_pSphereCollider;
	ENGINE::CTimeMgr*			m_pTimeMgr;

	CCollisionMgr*				m_pCollisionMgr;
	//��ư Ʈ����
	////////////////////////////////////////////////////
	//��ư�� ��ġ
	ENGINE::CTransform*			m_pTransform;

	//CubeLst�� ������ Ŭ����
	CMouse*						m_pMouse;

	//OptimizList
	list<vector<CBlock*>>*			m_pOptimizationList;
	list<list<vector<CBlock*>>>*	m_pInteractionList;
	////////////////////////////////////////////////////

	//����
	////////////////////////////////////////////////////
	//Target
	CPlayer*					m_pTarget;

	//Target�� Transform
	ENGINE::CTransform*			m_pTarget_Transform;

	//������ ����� Ÿ��
	tagType						m_eType;
	tagStage					m_eStage;
	////////////////////////////////////////////////////

	//�����̵� ��Ż
	////////////////////////////////////////////////////

	//�Ա� 
	D3DXVECTOR3					m_vSrc;
	bool						m_bIsActive_Src;

	//�ⱸ
	D3DXVECTOR3					m_vDst;
	bool						m_bIsActive_Dst;
	////////////////////////////////////////////////////
	bool						m_bIsStart;
	float						m_fMoveAngle;
};

#endif